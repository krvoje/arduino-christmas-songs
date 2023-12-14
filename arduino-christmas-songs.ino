
struct Note
{
  int frequency;
  int duration;
  int position;
};

struct Song
{
  char *soprano;
  char *alto;
  char *tenor;
  char *bass;
  int QUARTER;
};

void play_single(Song&, int);
//void play_multiple(Song);

const uint8_t SPEAKER = 11;

const int NUM_LEDS = 8;
const int ALL_LEDS[NUM_LEDS] = {5, 4, 3, 2, A0, A1, A2, A3};

const int twelve_tet[12] = {262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494};

Note soprano;
Note alto;
Note tenor;
Note bass;

Song adeste_fideles = {
    .soprano = "a  | a+ e a       | b+  e+  | c#* b c#* d* | c#*+ b a | a+  g# f#   | g# a b c#*   | g#+ f#. e- | e+. x | e*+ d* c#* | d*+ c#*+ | b c#* a  b  | g#. f#- e  |a| a g# a b | a+ e c#* | c#* b c#* d* | c#*+ b c#* | d* c#* b a    | g#+ a b- d*- | c#*+ b.  a-    | a+  xxx\0",
    .alto = "e  | e+ e e       | e+  e+  | e e e f#     | e+ e e   | c#  d# e d# | e+ e e       | e+ d#.  e- | e+. x | e   f# g# a| e+   e+  | f# f# f# f# | e+      e  |x| x++      | x+ x a   | a g# a b     | a+   g# a  | g# a   f# f#  | e+  e f#     | e    a   g#.a- | a+  xxx\0",
    .tenor = "c#*| c#*+ c#* c#* | b+  b+  | a g# a a     | a+ g# g# | a+  b b     | b c#* b a-f#-| g# e  b a  | g#+.x | a+  b  c#* | b+   a+  | f# f# b  b  | b a g#     |x| x++      | x++      | x++          | x+   x  e* | d* e*  d* c#* | b+  a a      | a    c#* e* d* | c#*+xxx\0",
    .bass = "a_ | a_+ a a      | g#+ g#+ | a e  a d     | e+ e  e  | f#+ b_ b_   | e c#  g#_ a_ | b_+   b_+  | e+. x | c#+ b_ a_  | g#_  a_  | d  d  d# d# | e+      e  |x| x++      | x++      | x++          | x+   x  a_ | b_ c#  d  d#  | e   d  c# d  | e+       e  e  | a_+ xxx\0",
    .QUARTER = 500,
};

Song jingle_bells = {
    .soprano = "d b a g | d+. d-d- | d b a g | e+. e-e- | e c* b a | f#+. d*-d*- | d*- x- d*- x- c* a | b+. d-d- | d b a g | d+. d-d- | d b a g | e+. e-e- | e c* b a | d*.d*- d* d*-d*- | e* d* c* a | g x d* x | b b b+ | b b b+ | b d* g. a- | b++ | c* c* c*.c*- | c* b b b-b- | b a a b | a x d* x | b b b+ | b b b+ | b d* g. a- | b++ | c* c* c*.c*- | c* b b b-b- | d* d* c* a | g+ x x | \0",
    .alto    = "d d e d | d+. d-d- | d d d d | c++      | c e  d e | c++    \0",
    .tenor = "\0",
    .bass = "\0",
    .QUARTER = 300,
};

auto is_only_melody = true;

const auto NUM_SONGS = 2;
Song songs[NUM_SONGS] = {
    adeste_fideles,
    jingle_bells};

Song &chosen_song = adeste_fideles;
int diode;

void setup()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    pinMode(ALL_LEDS[i], OUTPUT);
  }
  pinMode(SPEAKER, OUTPUT);
  pinMode(A0, INPUT);
  randomSeed(analogRead(0));

  is_only_melody = false;random(0, 2) > 0;
  chosen_song = jingle_bells;//songs[random(0, NUM_SONGS)];
  diode = random(0, NUM_LEDS);
}

void loop()
{
  parse_next_note(chosen_song);

  toggle_diode(ALL_LEDS[diode], HIGH);
  if (is_only_melody)
    play_single(chosen_song);
  else
    play_multiple(chosen_song);
  toggle_diode(ALL_LEDS[diode], LOW);

  auto old_diode = diode;
  do
  {
    diode = random(0, NUM_LEDS);
  } while (diode == old_diode);

  if (is_finished(chosen_song))
  {
    // The song finished, so we are picking a new one
    chosen_song = songs[random(0, NUM_SONGS)];
    is_only_melody = random(0, 2) > 0;
    reset_playback();
  }
}

bool is_finished(Song &song)
{
  return soprano.position < 0 && alto.position < 0 && tenor.position < 0 && bass.position < 0;
}

void toggle_diode(int pin, uint8_t color)
{
  digitalWrite(pin, color);
}

void play_single(Song &song)
{
  alto.position = -1;
  tenor.position = -1;
  bass.position = -1;
  if (soprano.duration > 0)
  {
    if (soprano.frequency > 0)
      tone(SPEAKER, soprano.frequency);
    delay(soprano.duration);
    noTone(SPEAKER);
    soprano.duration = 0;
  }
}

// Simulate polyphony by quickly arpeggiating the notes
void play_multiple(Song &song)
{
  auto shortest_note_duration = shortest_positive(soprano.duration, alto.duration, tenor.duration, bass.duration);

  auto number_of_notes = 0;
  if (soprano.frequency > 0)
    number_of_notes++;
  if (alto.frequency > 0)
    number_of_notes++;
  if (tenor.frequency > 0)
    number_of_notes++;
  if (bass.frequency > 0)
    number_of_notes++;

  if (number_of_notes == 0)
    delay(shortest_note_duration);
  else
  {
    auto DELAY = min(song.QUARTER / 3 / number_of_notes, shortest_note_duration);
    for (int total_duration_of_bar = 0; total_duration_of_bar < shortest_note_duration; total_duration_of_bar += DELAY * number_of_notes)
    {
      if (bass.frequency > 0)
      {
        tone(SPEAKER, bass.frequency / 2);
        delay(DELAY);
      }
      if (tenor.frequency > 0)
      {
        tone(SPEAKER, tenor.frequency / 2);
        delay(DELAY);
      }
      if (alto.frequency > 0)
      {
        tone(SPEAKER, alto.frequency);
        delay(DELAY);
      }
      if (soprano.frequency > 0)
      {
        tone(SPEAKER, soprano.frequency);
        delay(DELAY);
      }
    }
  }
  
  soprano.duration = max(0, soprano.duration - shortest_note_duration);
  alto.duration = max(0, alto.duration - shortest_note_duration);
  tenor.duration = max(0, tenor.duration - shortest_note_duration);
  bass.duration = max(0, bass.duration - shortest_note_duration);

  if (soprano.duration <= 0 && alto.duration <= 0 && tenor.duration <= 0 && bass.duration <= 0)
  {
    noTone(SPEAKER);
  }
}

int shortest_positive(int a, int b, int c, int d) {
  auto min = a;
  if (b > 0 && b < min) min = b;
  if (c > 0 && c < min) min = c;
  if (d > 0 && d < min) min = d;
  return min;

}

void parse_next_note(Song &song)
{
  parse_next_note(song.soprano, soprano, song.QUARTER);
  parse_next_note(song.alto, alto, song.QUARTER);
  parse_next_note(song.tenor, tenor, song.QUARTER);
  parse_next_note(song.bass, bass, song.QUARTER);
}

void parse_next_note(char *part, Note &current_note, int QUARTER)
{
  if (current_note.position < 0)
  {
    return; // This means the part already finished
  }
  if (current_note.duration > 0)
  {
    // This means the note is still ongoing
    return;
  }

  auto current_char = part[current_note.position];

  if (current_char == '\0')
  {
    // We've reached the end of the part
    current_note.position = -1;
    current_note.duration = 0;
    current_note.frequency = 0;
    return;
  }

  do
  {

    if (is_note(current_char))
    {
      current_note.frequency = frequency_from_char(part, current_note.position);
      current_note.duration = QUARTER;
    }
    else
    {
      modify_note(current_note, current_char);
    }

    current_note.position++;
    current_char = part[current_note.position];
  } while (!is_note(current_char) && current_char != '\0');
}

int frequency_from_char(char *c, int i)
{
  if (c[i] == 'x')
    return 0;
  if (is_note(c[i]))
  {
    auto note_index = note_twelve_tet_index(c[i]);
    if (c[i + 1] == '#')
    {
      note_index++;
    }
    else if (c[i + 1] == '\'')
    {
      note_index--;
    }
    // TODO: Does not support b sharp or c flat
    return twelve_tet[note_index];
  }
  else
  {
    return 0;
  }
}

void modify_note(Note &note, char modifier)
{
  switch (modifier)
  {
  case '+':
    note.duration *= 2;
    break;
  case '*':
    note.frequency *= 2;
    break;
  case '_':
    note.frequency /= 2;
    break;
  case '-':
    note.duration /= 2;
    break;
  case '.':
    note.duration = 3 * note.duration / 2;
    break;
  default:
    break;
  }
}

bool is_note(char c)
{
  switch (c)
  {
  case 'a':
  case 'b':
  case 'c':
  case 'd':
  case 'e':
  case 'f':
  case 'g':
  case 'x':
    return true;
  default:
    return false;
  }
}

int note_twelve_tet_index(char c)
{
  switch (c)
  {
  case 'c':
    return 0;
  case 'd':
    return 2;
  case 'e':
    return 4;
  case 'f':
    return 5;
  case 'g':
    return 7;
  case 'a':
    return 9;
  case 'b':
    return 11;
  default:
    return 0;
  }
}

void reset_playback()
  {
    soprano.duration = 0;
    soprano.frequency = 0;
    alto.duration = 0;
    alto.frequency = 0;
    tenor.duration = 0;
    tenor.frequency = 0;
    bass.duration = 0;
    bass.frequency = 0;
    soprano.position = 0;
    alto.position = 0;
    tenor.position = 0;
    bass.position = 0;
  }