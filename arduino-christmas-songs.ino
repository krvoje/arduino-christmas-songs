#define SPEAKER 11
#define NUM_LEDS 8
#define NUM_SONGS 3
#define NEUMA 500 / 4

struct Note
{
  int frequency;
  int current_duration;
  int remaining;
  const char *repetition_start;
  const char *current;
};

struct Song
{
  char *soprano;
  char *alto;
  char *tenor;
  char *bass;
};

void play_single();
void play_multiple();

const int ALL_LEDS[NUM_LEDS] = {5, 4, 3, 2, A0, A1, A2, A3};

const int twelve_tet[12] = {262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494};

Note soprano;
Note alto;
Note tenor;
Note bass;

bool is_single_note;

const char adeste_fideles_soprano[] PROGMEM = "2g4g2dg4ad2babc*4b2ag4g2f#ef#gab4f#3e1d8d4d*2c*b4c*b2abga3f#1e2dggf#ga4g2dbbabc*4b2abc*bag4f#2g1bc*4b3a1g8g\0";
const char adeste_fideles_alto[] PROGMEM = "2d4d2de4f#A2gf#ge4d2f#e4e2dcdef#d4d3c#1d8A4g2ag4ed2ddBc3d1c#2Addded4d2Bggf#de4d2f#eegf#e4d2e1f#g4d3f#1d8d\0";
const char adeste_fideles_tenor[] PROGMEM = "2b4b2ab4d*f#2gagg4g2ab4b2ag4ag8f#4b2c*e*4gg2f#gegaaf#bbaba4g2gd*d*d*bc*4b2aggbac*4a2gg4b3a1c*8b\0";
const char adeste_fideles_bass[] PROGMEM = "2g4g2f#e4dd2ddec4B2de4e2f#gAddB4ce8d4d2ee4cA2dBBcdeAdgdef#4B2dggf#gg4g2decdde4d2ce4g3d1f#8g\0";

const char mehki_snezek_soprano[] PROGMEM =
    "1Gdgb Gdgb Gdgb GBgd* Acf#d* cdc*f# bGdg 4x 1gGBd GCga Gdbd* GBgb F#df#b cdaf# GBdg 4x|1Gdgb Bdf#b Begb Bdgd* Acf#d* cdc*f# Gdbg GBdg 1Gdbd GCga Gdbd* GBgb F#df#b cdaf# GBdg 4x| 2d*gab 1e*g#2d* 1c*e2b 2c*eab 1d*f#2c* 1bd2a 2bdga 1c*e2b 1ac2g 2aF#A1ef# 8d 1gBaA bGc*e bGdg aF#A1cd 2d*gab 1e*g#2d* 1c*e2b 2c*eab 1d*f#2c* 1bd2a 2bdga 1c*e2b 1ac2g 2aF#A 1f#e 8d 2gBaA bGc*e bGdg aF#A1cd 1GABd 6g \0";

const char first_noel_soprano[] PROGMEM =
    "1ag3f1gab'4c*1d*e*2f*e*d*4c*1d*e*2f*e*d*c*d*e*f*c*b'4a1ag3f1gab'4c*1d*e*2f*e*d*4c*1d*e*2f*e*d*c*d*e*f*c*b'4a2ag4f2f*4e*2e*3d*1e*2d*6c*2f*e*d*c*d*e*f*c*b'4a\0";
const char first_noel_alto[] PROGMEM =
    "1ag3c1c2ffee3d1e2a4e1eg2ag2b'afgc*ed4c1ag3c1c2fgab'3d*1c*2b'3g1a21b'g2c*c*b'fb'gafg4f1fe4c2f4g2a4b'2f6g2d*ab'e1fgcd2afe4f\0";
const char first_noel_tenor[] PROGMEM =
    "1ag3a1b'2b'4c*2b'4a2b'3a1f2b'a1gf2d*3c*1b'2c*bag4f2a4a2b'4c*2c*4d*2d*6e*1c*d*2e*d*c*b'1c*b'2fab'4a\0";
const char first_noel_bass[] PROGMEM =
    "1ag2gfd4c2c4d2f3e1d2cf1ed2defg3f1e2B4c2e4d2B4e2e4B2f6g2aef1ag2fc1ce2fe4c2c4f2d4c2A4B2d3e1d2cdcBABcFAG4c\0";

const char jingle_bells_soprano[] PROGMEM =
    "\0";

const Song songs[] PROGMEM = {
    {
        // Adeste Fideles
        adeste_fideles_soprano,
        adeste_fideles_alto,
        adeste_fideles_tenor,
        adeste_fideles_bass,
    },
    {
        // Mehki snežek
        mehki_snezek_soprano,
    },
    {// First Noel
     first_noel_soprano,
     first_noel_alto,
     first_noel_tenor,
     first_noel_bass},
};

Song song;
int song_index = -1;
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

  choose_song();
  diode = random(0, NUM_LEDS);
  reset_playback();
}

void loop()
{
  parse_next_note();

  toggle_diode(ALL_LEDS[diode], HIGH);
  if (is_single_note || has_only_soprano())
    play_single();
  else
    play_multiple();
  toggle_diode(ALL_LEDS[diode], LOW);

  auto olDdiode = diode;
  do
  {
    diode = random(0, NUM_LEDS);
  } while (diode == olDdiode);

  if (is_finished())
  {
    // The song finished, so we are picking a new one
    choose_song();
    reset_playback();
  }
}

void choose_song()
{
  auto old_song_index = song_index;
  do
  {
    song_index = random(0, NUM_SONGS);
    delete song.soprano;
    delete song.alto;
    delete song.tenor;
    delete song.bass;
    auto soprano_ptr = pgm_read_ptr(&songs[song_index].soprano);
    auto alto_ptr = pgm_read_ptr(&songs[song_index].alto);
    auto tenor_ptr = pgm_read_ptr(&songs[song_index].tenor);
    auto bass_ptr = pgm_read_ptr(&songs[song_index].bass);
    if (soprano_ptr != NULL)
    {
      song.soprano = malloc(300);
      strcpy_P(song.soprano, (char *)soprano_ptr);
    } else {
      song.soprano = NULL;
    }
    if (alto_ptr != NULL)
    {
      song.alto = malloc(300);
      strcpy_P(song.alto, (char *)alto_ptr);
    } else {
      song.alto = NULL;
    }
    if (tenor_ptr != NULL)
    {
      song.tenor = malloc(300);
      strcpy_P(song.tenor, (char *)tenor_ptr);
    } else {
      song.tenor = NULL;
    }
    if (bass_ptr != NULL)
    {
      song.bass = malloc(300);
      strcpy_P(song.bass, (char *)bass_ptr);
    } else {
      song.bass = NULL;
    }
  } while (song_index == old_song_index && NUM_SONGS > 1);
  is_single_note = random(0, 2);
}

bool is_finished()
{
  return soprano.current == NULL && alto.current == NULL && tenor.current == NULL && bass.current == NULL;
}

bool has_only_soprano()
{
  return song.alto == NULL && song.tenor == NULL && song.bass == NULL;
}

void toggle_diode(int pin, uint8_t color)
{
  digitalWrite(pin, color);
}

void play_single()
{
  // soprano.current = NULL;
  alto.current = NULL;
  tenor.current = NULL;
  bass.current = NULL;

  auto &part = soprano;
  if (part.remaining > 0)
  {
    if (part.frequency > 0)
      tone(SPEAKER, part.frequency);
    delay(part.remaining);
    noTone(SPEAKER);
    part.remaining = 0;
  }
}

// Simulate polyphony by quickly arpeggiating the notes
void play_multiple()
{
  auto shortest_remaining = shortest_positive(soprano.remaining, alto.remaining, tenor.remaining, bass.remaining);

  auto number_of_notes = 0;
  if (soprano.frequency > 0 && soprano.remaining > 0)
    number_of_notes++;
  if (alto.frequency > 0 && alto.remaining > 0)
    number_of_notes++;
  if (tenor.frequency > 0 && tenor.remaining > 0)
    number_of_notes++;
  if (bass.frequency > 0 && bass.remaining > 0)
    number_of_notes++;

  if (number_of_notes == 0)
    delay(shortest_remaining);
  else
  {
    auto DELAY = min(NEUMA / 2, shortest_remaining);
    for (int total_remaining_in_beat = 0; total_remaining_in_beat < shortest_remaining; total_remaining_in_beat += DELAY * number_of_notes)
    {
      if (bass.frequency > 0)
      {
        tone(SPEAKER, bass.frequency / 2);
        delay(DELAY);
      }
      bass.remaining = max(0, bass.remaining - DELAY);

      if (tenor.frequency > 0)
      {
        tone(SPEAKER, tenor.frequency / 2);
        delay(DELAY);
      }
      tenor.remaining = max(0, tenor.remaining - DELAY);
      if (alto.frequency > 0)
      {
        tone(SPEAKER, alto.frequency);
        delay(DELAY);
      }
      alto.remaining = max(0, alto.remaining - DELAY);
      if (soprano.frequency > 0)
      {
        tone(SPEAKER, soprano.frequency);
        delay(DELAY);
      }
      soprano.remaining = max(0, soprano.remaining - DELAY);
    }
  }

  if (soprano.remaining <= 0 && alto.remaining <= 0 && tenor.remaining <= 0 && bass.remaining <= 0)
  {
    noTone(SPEAKER);
  }
}

int shortest_positive(int a, int b, int c, int d)
{
  auto min = a;
  if (b > 0 && b < min)
    min = b;
  if (c > 0 && c < min)
    min = c;
  if (d > 0 && d < min)
    min = d;
  return min;
}

void parse_next_note()
{
  parse_next(soprano);
  parse_next(alto);
  parse_next(tenor);
  parse_next(bass);
}

void parse_next(Note &note)
{
  if (note.current == NULL || note.remaining)
  {
    // The part already finished, or the note is still ongoing
    return;
  }

  if ((*note.current) == '\0')
  {
    // We've reached the end of the part
    note.current = NULL;
    note.current_duration = 0;
    note.remaining = 0;
    note.frequency = 0;
    return;
  }

  do
  {
    if (is_number(note.current))
    {
      note.current_duration = (*note.current - '0') * NEUMA;
    }
    if (is_note(note.current))
    {
      note.frequency = twelve_tet_frequency(note.current);
      note.remaining = note.current_duration;
    }
    note.current++;
  } while ((*note.current) != '\0' && note.remaining <= 0);
}

bool is_note(const char *c)
{
  return 'a' <= *c && *c <= 'g' ||
         'A' <= *c && *c <= 'G' ||
         *c == 'x' ||
         *c == 'X';
}

int twelve_tet_frequency(const char *c)
{
  char next = *(c + 1);
  switch (*c)
  {
  case 'C':
    if (next == '#')
      return twelve_tet[1] / 2;
    if (next == '\'')
      return twelve_tet[11] / 2;
    if (next == '*')
      return twelve_tet[0];
    if (next == '_')
      return twelve_tet[0] / 4;
    return twelve_tet[0] / 2;
  case 'D':
    if (next == '#')
      return twelve_tet[3] / 2;
    if (next == '\'')
      return twelve_tet[1] / 2;
    if (next == '*')
      return twelve_tet[2];
    if (next == '_')
      return twelve_tet[2] / 4;
    return twelve_tet[2] / 2;
  case 'E':
    if (next == '#')
      return twelve_tet[5] / 2;
    if (next == '\'')
      return twelve_tet[3] / 2;
    if (next == '*')
      return twelve_tet[4];
    if (next == '_')
      return twelve_tet[4] / 4;
    return twelve_tet[4] / 2;
  case 'F':
    if (next == '#')
      return twelve_tet[6] / 2;
    if (next == '\'')
      return twelve_tet[4] / 2;
    if (next == '*')
      return twelve_tet[5];
    if (next == '_')
      return twelve_tet[5] / 4;
    return twelve_tet[5] / 2;
  case 'G':
    if (next == '#')
      return twelve_tet[8] / 2;
    if (next == '\'')
      return twelve_tet[6] / 2;
    if (next == '*')
      return twelve_tet[7];
    if (next == '_')
      return twelve_tet[7] / 4;
    return twelve_tet[7] / 2;
  case 'A':
    if (next == '#')
      return twelve_tet[10] / 2;
    if (next == '\'')
      return twelve_tet[8] / 2;
    if (next == '*')
      return twelve_tet[9];
    if (next == '_')
      return twelve_tet[9] / 4;
    return twelve_tet[9] / 2;
  case 'B':
    if (next == '#')
      return twelve_tet[0];
    if (next == '\'')
      return twelve_tet[10] / 2;
    if (next == '*')
      return twelve_tet[11];
    if (next == '_')
      return twelve_tet[11] / 4;
    return twelve_tet[11] / 2;
  case 'c':
    if (next == '#')
      return twelve_tet[1];
    if (next == '\'')
      return twelve_tet[11] / 2;
    if (next == '*')
      return twelve_tet[0] * 2;
    if (next == '_')
      return twelve_tet[0] / 2;
    return twelve_tet[0];
  case 'd':
    if (next == '#')
      return twelve_tet[3];
    if (next == '\'')
      return twelve_tet[1];
    if (next == '*')
      return twelve_tet[2] * 2;
    if (next == '_')
      return twelve_tet[2] / 2;
    return twelve_tet[2];
  case 'e':
    if (next == '#')
      return twelve_tet[5];
    if (next == '\'')
      return twelve_tet[3];
    if (next == '*')
      return twelve_tet[4] * 2;
    if (next == '_')
      return twelve_tet[4] / 2;
    return twelve_tet[4];
  case 'f':
    if (next == '#')
      return twelve_tet[6];
    if (next == '\'')
      return twelve_tet[4];
    if (next == '*')
      return twelve_tet[5] * 2;
    if (next == '_')
      return twelve_tet[5] / 2;
    return twelve_tet[5];
  case 'g':
    if (next == '#')
      return twelve_tet[8];
    if (next == '\'')
      return twelve_tet[6];
    if (next == '*')
      return twelve_tet[7] * 2;
    if (next == '_')
      return twelve_tet[7] / 2;
    return twelve_tet[7];
  case 'a':
    if (next == '#')
      return twelve_tet[10];
    if (next == '\'')
      return twelve_tet[8];
    if (next == '*')
      return twelve_tet[9] * 2;
    if (next == '_')
      return twelve_tet[9] / 2;
    return twelve_tet[9];
  case 'b':
    if (next == '#')
      return twelve_tet[0] * 2;
    if (next == '\'')
      return twelve_tet[10];
    if (next == '*')
      return twelve_tet[11] * 2;
    if (next == '_')
      return twelve_tet[11] / 2;
    return twelve_tet[11];
  default:
    return 0;
  }
}

bool is_number(const char *c)
{
  return *c >= '0' && *c <= '9';
}

void reset_playback()
{
  soprano.current_duration = 0;
  alto.current_duration = 0;
  tenor.current_duration = 0;
  bass.current_duration = 0;
  soprano.remaining = 0;
  alto.remaining = 0;
  tenor.remaining = 0;
  bass.remaining = 0;
  soprano.frequency = 0;
  alto.frequency = 0;
  tenor.frequency = 0;
  bass.frequency = 0;
  soprano.current = song.soprano;
  alto.current = song.alto;
  tenor.current = song.tenor;
  bass.current = song.bass;
  soprano.repetition_start = NULL;
  alto.repetition_start = NULL;
  tenor.repetition_start = NULL;
  bass.repetition_start = NULL;
}