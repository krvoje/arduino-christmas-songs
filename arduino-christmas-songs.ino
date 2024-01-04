#include "songs.h"

#define SPEAKER 11
#define BUTTON 6
#define NUM_LEDS 8
#define NEUMA 500 / 4

void play_single();
void play_multiple();

struct Note
{
  int frequency;
  int current_duration;
  int remaining;
  const char *current;

  void reset()
  {
    frequency = 0;
    current_duration = 0;
    remaining = 0;
    current = NULL;
  }
};

struct CurrentParts
{
  Note soprano;
  Note alto;
  Note tenor;
  Note bass;

  void reset(Song& song)
  {
    soprano.reset();
    alto.reset();
    tenor.reset();
    bass.reset();

    soprano.current = song.soprano;
    alto.current = song.alto;
    tenor.current = song.tenor;
    bass.current = song.bass;
  }
};

const int ALL_LEDS[NUM_LEDS] = {5, 4, 3, 2, PIN_A0, PIN_A1, PIN_A2, PIN_A3};

const int twelve_tet_base[12] = {262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494};
int twelve_tet[12] = {262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494};

bool is_single_note;

Song current_song;
CurrentParts parts;
int song_index = -1;
int diode;
bool is_button_pressed = false;

void setup()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    pinMode(ALL_LEDS[i], OUTPUT);
  }
  pinMode(SPEAKER, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(A0, INPUT);
  randomSeed(analogRead(0));

  cycle_songs();
  diode = random(0, NUM_LEDS);
  parts.reset(current_song);
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

  is_button_pressed = digitalRead(BUTTON) == HIGH;
  if (is_finished() || is_button_pressed)
  {
    // The song finished, so we are picking a new one
    cycle_songs();
    parts.reset(current_song);
  }
}

void cycle_songs()
{
  transpose_steps(random(0, 12), random(0, 2));
  song_index = random(0, NUM_SONGS);
  is_single_note = random(0, 2);
  free(current_song.soprano);
  free(current_song.alto);
  free(current_song.tenor);
  free(current_song.bass);
  auto soprano_ptr = pgm_read_ptr(&ALL_SONGS[song_index].soprano);
  auto alto_ptr = pgm_read_ptr(&ALL_SONGS[song_index].alto);
  auto tenor_ptr = pgm_read_ptr(&ALL_SONGS[song_index].tenor);
  auto bass_ptr = pgm_read_ptr(&ALL_SONGS[song_index].bass);
  if (soprano_ptr != NULL)
  {
    current_song.soprano = (char *)malloc(calculate_size(soprano_ptr));
    strcpy_P(current_song.soprano, (char *)soprano_ptr);
  }
  else
  {
    current_song.soprano = NULL;
  }
  if (alto_ptr != NULL)
  {
    current_song.alto = (char *)malloc(calculate_size(alto_ptr));
    strcpy_P(current_song.alto, (char *)alto_ptr);
  }
  else
  {
    current_song.alto = NULL;
  }
  if (tenor_ptr != NULL)
  {
    current_song.tenor = (char *)malloc(calculate_size(tenor_ptr));
    strcpy_P(current_song.tenor, (char *)tenor_ptr);
  }
  else
  {
    current_song.tenor = NULL;
  }
  if (bass_ptr != NULL)
  {
    current_song.bass = (char *)malloc(calculate_size(bass_ptr));
    strcpy_P(current_song.bass, (char *)bass_ptr);
  }
  else
  {
    current_song.bass = NULL;
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
  return parts.soprano.current == NULL && parts.alto.current == NULL && parts.tenor.current == NULL && parts.bass.current == NULL;
}

bool has_only_soprano()
{
  return current_song.alto == NULL && current_song.tenor == NULL && current_song.bass == NULL;
}

void toggle_diode(int pin, uint8_t color)
{
  digitalWrite(pin, color);
}

void play_single()
{
  // soprano.current = NULL;
  parts.alto.current = NULL;
  parts.tenor.current = NULL;
  parts.bass.current = NULL;

  auto &part = parts.soprano;
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
  auto shortest_remaining = shortest_positive(parts.soprano.remaining, parts.alto.remaining, parts.tenor.remaining, parts.bass.remaining);
  auto longest_remaining = max(max(parts.soprano.remaining, parts.alto.remaining), max(parts.tenor.remaining, parts.bass.remaining));

  auto audible_notes = 0;
  if (parts.soprano.frequency && parts.soprano.remaining)
    audible_notes++;
  if (parts.alto.frequency && parts.alto.remaining)
    audible_notes++;
  if (parts.tenor.frequency && parts.tenor.remaining)
    audible_notes++;
  if (parts.bass.frequency && parts.bass.remaining)
    audible_notes++;

  int DELAY = audible_notes ? NEUMA / audible_notes : NEUMA;

  Note* all_parts[] = {&parts.soprano, &parts.alto, &parts.tenor, &parts.bass};

  if (!audible_notes)
    delay(NEUMA);
  else
    for (int remaining_in_strum = 0; remaining_in_strum < shortest_remaining; remaining_in_strum += DELAY * audible_notes)
    {
      for (auto part : all_parts)
      {
        if (part->frequency && part->remaining)
        {
          tone(SPEAKER, part->frequency);
          delay(DELAY);
        }
      }
    }

  parts.bass.remaining = max(0, parts.bass.remaining - NEUMA);
  parts.tenor.remaining = max(0, parts.tenor.remaining - NEUMA);
  parts.alto.remaining = max(0, parts.alto.remaining - NEUMA);
  parts.soprano.remaining = max(0, parts.soprano.remaining - NEUMA);

  if (!parts.soprano.remaining && !parts.alto.remaining && !parts.tenor.remaining && !parts.bass.remaining)
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
  parse_next(parts.soprano, 1);
  parse_next(parts.alto, 1);
  parse_next(parts.tenor, 2);
  parse_next(parts.bass, 2);
}

void parse_next(Note &note, int octave_coefficient)
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
      note.frequency = twelve_tet_frequency(note.current) / octave_coefficient;
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

void reset_playback(CurrentParts& parts, Song& song)
{
  parts.reset(song);  
}

void transpose_steps(int steps, bool up)
{
  for (int i = 0; i < 12; i++)
  {
    if (up)
    {
      auto multiplicator = (i + steps) > 11 ? 2 : 1;
      twelve_tet[i] = twelve_tet_base[(i + steps) % 12] * multiplicator;
    }
    else
    {
      auto divisor = (i - steps) < 0 ? 2 : 1;
      twelve_tet[i] = twelve_tet_base[(12 - steps + i) % 12] / divisor;
    }
  }
}