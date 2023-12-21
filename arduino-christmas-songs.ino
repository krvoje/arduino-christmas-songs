
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
.soprano="aa+eab+e+c#*bc#*d*c#*+baa+g#f#g#abc#*g#+f#.e-e+.xe*+d*c#*d*+c#*+bc#*abg#.f#-eaag#aba+ec#*c#*bc#*d*c#*+bc#*d*c#*bag#+ab-d*-c#*+b.a-a+xxx\0",
.alto="ee+eee+e+eeef#e+eec#d#ed#e+eee+d#.e-e+.xef#g#ae+e+f#f#f#f#e+exx++x+xaag#aba+g#ag#af#f#e+ef#eag#.a-a+xxx\0",
.tenor="c#*c#*+c#*c#*b+b+ag#aaa+g#g#a+bbbc#*ba-f#-g#ebag#+.xa+bc#*b+a+f#f#bbbag#xx++x++x++x+xe*d*e*d*c#*b+aaac#*e*d*c#*+xxx\0",
.bass="a_a_+aag#+g#+aeade+eef#+b_b_ec#g#_a_b_+b_+e+.xc#+b_a_g#_a_ddd#d#e+exx++x++x++x+xa_b_c#dd#edc#de+eea_+xxx\0",
    .QUARTER = 500,
};

Song jingle_bells = {
.soprano="dbagd+.d-d-dbage+x+ec*baf#++d*d*c*ab+x+dbagd++dbage+xeec*bad*d*d*d*e*d*c*agxd*+bbb+bbb+bd*g.a-b+x+c*c*c*.c*-c*bbb-b-baaba+d*xbbb+bbb+bd*g.a-b+x+c*c*c*.c*-c*bbb-b-d*d*c*agxxx\0",
.alto   ="ddddd+.d-d-ddddc+x+ceeed++f#f#f#f#g+x+ddddd++ddddc+xcceeef#f#f#f#f#f#f#f#dxxxggg+ggg+ggd.f#-g+x+eee.e-eeeg-g-gf#f#gf#+.xggg+ggg+ggd.f#-g+x+eee.e-eggg-g-f#gf#agxxx\0",
.tenor  ="bbbbb+.b-b-bbbbg+x+ggggc*++c*c*ad*d*+x+bbbbb++bbbbg+xgggggaaaac*c*c*c*bxxxd*d*d*+d*d*d*+d*d*b.c*-d*+x+c*c*c*.c*-c*d*d*d*-d*-c#*c#*c#*c#*d*+.xd*d*d*+d*d*d*+d*d*b.c#*-d*+x+c*c*c*.c*-c*d*d*d*-d*-abac*bxxx\0",
.bass   ="ggggg+.g-g-ggggc+x+ccccd++ddddg+x+ggggg++ggggc+xcccccddddddddgxxxggg+ggg+ggg.g-g+x+ccc.c-gggg-g-aaaad+.xggg+ggg+ggg.g#-g+x+ccc.c-gggg-g-ddddgxxx\0",
.QUARTER = 300,
};

Song silent_night = {
.soprano="f.g-fd+.f.g-fd+.c*+c*a+.b'+b'f+.g+gb'.a-gf.g-fd+.g+gb'.a-gf.g-fd+.c*+c*e'*.c*-ab'+.d*+. b'.f-df.e'-cb'_++.\0",
.alto="d.e'-db'_+.d.e'-db'_+.e'+e'e'+.d+dd+.e'+e'g.f-e'd.e'-db'_+.e'+e'g.f-e'd.e'-db'_+.f+ff.f-ff++.b'_+b'_a_.a_-a_b'_++\0",
.tenor="f+ff+.f+ff+.a+ac*+.b'+b'b'+.b'+b'b'.b'-b'b'.b'-b'b'+.b'+b'b'.b'-b'b'.b'-b'b'+.a+aa.a-e'*d*+.b'+.f+ff.f-fd++\0",
.bass="b'_+b'_b'_+.b'_+b'_b'_+.f+ff+.b'_+b'_b'_+.e'+e'e'.e'-e'b'_.b'_-b'_b'_+.e'+e'e'.e'-e'b'_.b'_-b'_b'_+.f+ff.f-fb'_++.d+b'_f_.f_-f_b'_++\0",
.QUARTER = 250,
};

auto is_only_melody = true;

const auto NUM_SONGS = 3;
Song songs[NUM_SONGS] = {
    adeste_fideles,
    jingle_bells,
    silent_night,
    };

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

  chosen_song = songs[random(0, NUM_SONGS)];
  is_only_melody = random(0, 2) > 0;
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
  //soprano.position=-1;
  alto.position = -1;
  tenor.position = -1;
  bass.position = -1;

  auto &part = soprano;
  if (part.duration > 0)
  {
    if (part.frequency > 0)
      tone(SPEAKER, part.frequency);
    delay(part.duration);
    noTone(SPEAKER);
    part.duration = 0;
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