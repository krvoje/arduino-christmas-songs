#define SPEAKER 11
#define NUM_LEDS 8
#define NUM_SONGS 6
#define NEUMA 500 / 4

struct Note
{
  int frequency;
  int current_duration;
  int remaining;
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

const char adeste_fideles_soprano[] PROGMEM = "2a4a2ea4be2c#*bc#*d*4c#*2ba4a2g#f#g#abc#*4g#2f#1e8e4e*2d*c#*4d*c#*2bc#*ab2g#1f#12e2aag#ab4a2ec#*c#*bc#*d*4c#*2bc#*d*c#*ba4g#2ad*4c#*3b1a6a\0";
const char adeste_fideles_alto[] PROGMEM = "2e4e2ec#4ee2eeef#4e2ec#c#d#ed#eeee4e3d#1e8e4e1f#g#2af#g#4a2eef#f#4e2e2x8xxx6x2a1f#g#2aed#4e2ef#4e3e1c#6c#\0";
const char adeste_fideles_tenor[] PROGMEM = "2c#*4c#*2aa4g#b2abaa4a2g#a4a2bbec#g#f#4b3a1g#8g#4c#*2d*e*4d*e*2e*ac#*d*3b1a2g#x8xxx6x2e*d*e*bb4baa3g#1a6a\0";
const char adeste_fideles_bass[] PROGMEM = "2A4A2c#A4eg#2ag#ad4e2ef#4f#2eBBAG#A4B3B1e8e4c#*2ba4ba2g#af#d4e2wx8xxx6x2abag#f#2edc#d4e3e1A6A\0";

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
    "2dbag6d1dd2dbag4ex2ec*ba8f#2d*d*c*a4bx2dbag8d2dbag4e2xeec*bad*d*d*d*e*d*c*agx4d*2bb4b2bb4b2bd*3g1a4bx2c*c*3c*1c*2c*bb1bb2baab4a2d*xbb4b2bb4b2bd*3g1a4bx2c*c*3c*1c*2c*bb1bb2d*d*c*ag6x\0";
const char jingle_bells_alto[] PROGMEM =
    "2dddd6d1dd2dddd4cx2ceee8d2f#f#f#f#4gx2dddd8d2dddd4c2xcceeef#f#f#f#f#f#f#f#4dx2gg4g2gg4g2gg3d1f#4gx2ee3e1e2egg1gg2gf#f#e6f#2x2gg4g2gg4g2gg3d1f#4gx2ee3e1e2egg1gg2f#gf#ag6x\0";
const char jingle_bells_tenor[] PROGMEM =
    "2bbbb6b1bb2bbbb4gx2gggg8c*2c*c*ad*4d*x2bbbb8b2bbbb4g2xgggggaaaac*c*c*c*4bx2d*d*4d*2d*d*4d*2d*d*3b1c*4d*x2c*c*3c*1c*2c*d*d*1d*d*2c#*c#*c#*c#*6d*2x2d*d*4d*2d*d*4d*2d*d*3b1c*4d*x2c*c*3c*1c*2c*d*d*1d*d*2abac*d*6x\0";
const char jingle_bells_bass[] PROGMEM =
    "2gggg6g1gg2gggg4cx2cccc8d2dddd4gx2gggg8g2gggg4c2xcccccdddddddd4gx2gg4g2gg4g2gg3g1g4gx2cc3c1c2ggg1gg2aaaa6d2x2gg4g2gg4g2gg3g1g4gx2cc3c1c2ggg1gg2ddddg6x\0";

const char silent_night_soprano[] PROGMEM =
    "3f1g2f6d3f1g2f6d4c*2c*6a4b'2b'6f4g2g3b'1a2g3f1g2f6d4g2g3b'1a2g3f1g2f6d4c*2c*3e'*1c*2a6b'd*2b'fd3f1e'2c8B'x\0";
const char silent_night_alto[] PROGMEM =
    "3d1e'2d6B'3d1e'2d6B'4e'2e'6e'4d2d6d4e'2e'3g1f2e'3d1e'2d6B'4e'2e'3g1f2e'3d1e'2d6B'4f2f3f1f2f6ff2B'fB'3A1A2A8B'x\0";
const char silent_night_tenor[] PROGMEM =
    "4f2f6f4f2f6f4a2a6c*4b'2b'6b'4b'2b'4b'2b'3b'1b'2b'6b'4b'2b'3b'1b'2b'3b'1b'2b'6b'4a2a3a1a2e'*6e'*b'4f2f3f1f2f8dx\0";
const char silent_night_bass[] PROGMEM =
    "4B'2B'6B'4B'2B'6B'4f2f6f4B'2B'6B'4e'2e'4e'2e'3B'1B'2B'6B'4e'2e'3e'1e'2e'3B'1B'2B'6B'4f2f3f1f2f6b'b'4d2B3F1F2F8Bx\0";

const char veselje_ti_navjescujem_soprano[] PROGMEM =
    "2ad*c#*b3a1b2ag1f#ef#g2ac#8d2ad*c#*b3a1b2ag1f#ef#g2ac#8d2f#aeef#aeea1ab2agf#1f#g2f#ea1ab2agf#1f#g2f#e3f#1g2f#e4de3f#1g2f#e8d\0";
const char veselje_ti_navjescujem_alto[] PROGMEM =
    "2f#1f#g2agf#gf#e2dcde2c#c#8A2f#1f#g2agf#gf#e2dcde2c#c#8A2f#d#Bc#f#d#Bc#ddc#edddc#ddc#edddc#3d1d2c#c#4B2Bc#3d1d2c#c#8A\0";
const char veselje_ti_navjescujem_tenor[] PROGMEM =
    "2d*aabc#*c#*1d*c#*2bbb3a1g8f#2d*aabc#*c#*1d*c#*2bbb3a1g8f#2a1ba2ga2a1ba2ga2f#1f#g2aa2a1ab2aa2f#1f#g2aaabba3a1b2ag4f#2ga3a1b2ag8f#\0";
const char veselje_ti_navjescujem_bass[] PROGMEM =
    "2ddf#gae1dd#2e2beaA8d2ddf#gae1dd#2e2beaA8d1dc#2Be1Ac#dc#2BeAf#f#Ac#dd1df#2addAc#1dc2BG#A3d1d2AA#4B2eA3d1G2AA8d\0";

const Song songs[NUM_SONGS] PROGMEM = {
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
    {
        // First Noel
        first_noel_soprano,
        first_noel_alto,
        first_noel_tenor,
        first_noel_bass,
    },
    {
        // Jingle Bells
        jingle_bells_soprano,
        jingle_bells_alto,
        jingle_bells_tenor,
        jingle_bells_bass,
    },
    {
        // Silent Night
        silent_night_soprano,
        silent_night_alto,
        silent_night_tenor,
        silent_night_bass,
    },
    {
        // Veselje ti navješčujem
        veselje_ti_navjescujem_soprano,
        veselje_ti_navjescujem_alto,
        veselje_ti_navjescujem_tenor,
        veselje_ti_navjescujem_bass,
    },
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
  song_index = (song_index + 1) % NUM_SONGS;
  is_single_note = random(0, 2);
  free(song.soprano);
  free(song.alto);
  free(song.tenor);
  free(song.bass);
  auto soprano_ptr = pgm_read_ptr(&songs[song_index].soprano);
  auto alto_ptr = pgm_read_ptr(&songs[song_index].alto);
  auto tenor_ptr = pgm_read_ptr(&songs[song_index].tenor);
  auto bass_ptr = pgm_read_ptr(&songs[song_index].bass);
  if (soprano_ptr != NULL)
  {
    song.soprano = (char *)malloc(calculate_size(soprano_ptr));
    strcpy_P(song.soprano, (char *)soprano_ptr);
  }
  else
  {
    song.soprano = NULL;
  }
  if (alto_ptr != NULL)
  {
    song.alto = (char *)malloc(calculate_size(alto_ptr));
    strcpy_P(song.alto, (char *)alto_ptr);
  }
  else
  {
    song.alto = NULL;
  }
  if (tenor_ptr != NULL)
  {
    song.tenor = (char *)malloc(calculate_size(tenor_ptr));
    strcpy_P(song.tenor, (char *)tenor_ptr);
  }
  else
  {
    song.tenor = NULL;
  }
  if (bass_ptr != NULL)
  {
    song.bass = (char *)malloc(calculate_size(bass_ptr));
    strcpy_P(song.bass, (char *)bass_ptr);
  }
  else
  {
    song.bass = NULL;
  }
}

unsigned int calculate_size(byte *ptr)
{
  unsigned int size = 0;
  while (pgm_read_byte(ptr) != '\0')
  {
    size++;
    ptr++;
  }
  return size;
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
  if (part.remaining)
  {
    if (part.frequency)
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

  auto audible_notes = 0;
  if (soprano.frequency && soprano.remaining)
    audible_notes++;
  if (alto.frequency && alto.remaining)
    audible_notes++;
  if (tenor.frequency && tenor.remaining)
    audible_notes++;
  if (bass.frequency && bass.remaining)
    audible_notes++;

  auto DELAY = NEUMA / 4;
  if(!audible_notes) delay(NEUMA);
  else for (int remaining_in_strum = 0; remaining_in_strum < shortest_remaining; remaining_in_strum += DELAY * audible_notes)
  {
    if (bass.frequency && bass.remaining)
    {
      tone(SPEAKER, bass.frequency / 2);
      delay(DELAY);
    }

    if (tenor.frequency && tenor.remaining)
    {
      tone(SPEAKER, tenor.frequency / 2);
      delay(DELAY);
    }

    if (alto.frequency && alto.remaining)
    {
      tone(SPEAKER, alto.frequency);
      delay(DELAY);
    }

    if (soprano.frequency && soprano.remaining)
    {
      tone(SPEAKER, soprano.frequency);
      delay(DELAY);
    }
  }

  bass.remaining = max(0, bass.remaining - NEUMA);
  tenor.remaining = max(0, tenor.remaining - NEUMA);
  alto.remaining = max(0, alto.remaining - NEUMA);
  soprano.remaining = max(0, soprano.remaining - NEUMA);

  if (!soprano.remaining && !alto.remaining && !tenor.remaining && !bass.remaining)
  {
    noTone(SPEAKER);
  }
}

int shortest_positive(int a, int b, int c, int d)
{
  auto min = a;
  if (b && b < min)
    min = b;
  if (c && c < min)
    min = c;
  if (d && d < min)
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
  } while ((*note.current) != '\0' && !note.remaining);
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
  bool is_sharp = *(c + 1) == '#';
  bool is_flat = *(c + 1) == '\'';
  bool is_octave_up = *(c + 1) == '*' || is_sharp && *(c + 2) == '*' || is_flat && *(c + 2) == '*';
  bool is_octave_down = *(c + 1) == '_' || is_sharp && *(c + 2) == '_' || is_flat && *(c + 2) == '_';
  bool is_low_octave = isupper(*c);

  auto frequency = 0;
  auto index = 0;
  switch (tolower(*c))
  {
  case 'c':
    index = 0;
    break;
  case 'd':
    index = 2;
    break;
  case 'e':
    index = 4;
    break;
  case 'f':
    index = 5;
    break;
  case 'g':
    index = 7;
    break;
  case 'a':
    index = 9;
    break;
  case 'b':
    index = 11;
    break;
  case 'x':
    return 0;
  default:
    break;
  }

  if (is_sharp)
    index++;
  if (is_flat)
    index--;
  frequency = twelve_tet[index % 12];
  if (index < 0)
    frequency /= 2;
  if (index > 11)
    frequency *= 2;
  if (is_low_octave)
    frequency /= 2;
  if (is_octave_up)
    frequency *= 2;
  if (is_octave_down)
    frequency /= 2;

  return frequency;
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
}