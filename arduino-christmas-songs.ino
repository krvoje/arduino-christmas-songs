
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

const uint8_t SPEAKER = 12;

const int NUM_LEDS = 8;
const int ALL_LEDS[NUM_LEDS] = {5, 4, 3, 2, A0, A1, A2, A3};

const int twelve_tet[24] = {262/2, 277/2, 294/2, 311/2, 330/2, 349/2, 370/2, 392/2, 415/2, 440/2, 466/2, 494/2, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494};

Note soprano;
Note alto;
Note tenor;
Note bass;

Song adeste_fideles = {
.soprano="a|a+ea|b+e+|c#*bc#*d*|c#*+ba|a+g#f#|g#abc#*|g#+f#.e-|e+.x|e*+d*c#*|d*+c#*+|bc#*ab|g#.f#-e|a|ag#ab|a+ec#*|c#*bc#*d*|c#*+bc#*|d*c#*ba|g#+ab-d*-|c#*+b.a-|a+xxx\0",
.alto="e|e+ee|e+e+|eeef#|e+ee|c#d#ed#|e+ee|e+d#.e-|e+.x|ef#g#a|e+e+|f#f#f#f#|e+e|x|x++|x+xa|ag#ab|a+g#a|g#af#f#|e+ef#|eag#.a-|a+xxx\0",
.tenor="c#*|c#*+c#*c#*|b+b+|ag#aa|a+g#g#|a+bb|bc#*ba-f#-|g#eba|g#+.x|a+bc#*|b+a+|f#f#bb|bag#|x|x++|x++|x++|x+xe*|d*e*d*c#*|b+aa|ac#*e*d*|c#*+xxx\0",
.bass="a_|a_+aa|g#+g#+|aead|e+ee|f#+b_b_|ec#g#_a_|b_+b_+|e+.x|c#+b_a_|g#_a_|ddd#d#|e+e|x|x++|x++|x++|x+xa_|b_c#dd#|edc#d|e+ee|a_+xxx\0",
    .QUARTER = 500,
};

Song jingle_bells = {
.soprano="dbag|d+.d-d-|dbag|e+.e-e-|ec*ba|f#+.d*-d*-|d*-x-d*-x-c*a|b+.d-d-|dbag|d+.d-d-|dbag|e+.e-e-|ec*ba|d*.d*-d*d*-d*-|e*d*c*a|gxd*x|bbb+|bbb+|bd*g.a-|b++|c*c*c*.c*-|c*bbb-b-|baab|axd*x|bbb+|bbb+|bd*g.a-|b++|c*c*c*.c*-|c*bbb-b-|d*d*c*a|g+xx|\0",
.alto="dddd|d+.d-d-|dddd|c+.x|ceee|d++|f#f#f#f#|g++|dddd|d++|dddd|c+xc|ceee|f#f#f#f#|f#f#f#f#|dxxx|ggg+|ggg+|ggd.f#-|g++|eee.e-|eggg-g-|gf#f#g|f#xxx|ggg+|ggg+|ggd.f#-|g++|eee.e-|eggg-g-|f#af#a|b+xx|\0",
.tenor="bbbb|b+.b-b-|bbbb|g+.x|gggg|c*++|c*c*ad*|d*++|bbbb|b++|bbbb|g+xg|gggg|aaaa|c*c*c*c*|bxxx|d*d*d*+|d*d*d*+|d*d*b.-c*-|d*++|c*c*c*.c*-|c*d*d*d*-d*-|c#*c*#c#*c#*|d*xxx|d*d*d*+|d*d*d*+|d*d*b.-c*-|d*++|c*c*c*.c*-|c*d*d*d*-d*-|abac*#|g+xx|\0",
.bass="gggg|g+.g-g-|gggg|c+.x|cccc|d++|dddd|g++|gggg|g++|gggg|c+xc|cccc|dddd|dddd|gxxx|ggg+|ggg+|ggg.g-|g++|ccc.c|gggg-g-|aaaa|d+xxx|ggg+|ggg+|ggg.g-|g++|ccc.c-|gggg-g-|dddd|g+xx|\0",
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

  is_only_melody = random(0, 2) > 0;
  chosen_song = songs[random(0, NUM_SONGS)];
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
  switch (tolower(c))
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
  case 'C':
    return 0;
  case 'D':
    return 2;
  case 'E':
    return 4;
  case 'F':
    return 5;
  case 'G':
    return 7;
  case 'A':
    return 9;
  case 'B':
    return 11;
  case 'c':
    return 12;
  case 'd':
    return 14;
  case 'e':
    return 16;
  case 'f':
    return 17;
  case 'g':
    return 19;
  case 'a':
    return 21;
  case 'b':
    return 23;
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