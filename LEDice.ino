#include <Melody.h>
#include "WS2812-SOLDERED.h"

struct LedInfo
{
  uint8_t pin;
  uint32_t color;
};

const uint8_t NEO_DIODE = 8;
const uint8_t SPEAKER = 6;
WS2812 pixels(1, NEO_DIODE);

uint8_t brightness = 0xff;

auto color_red = pixels.Color(brightness, 0, 0);
auto color_green = pixels.Color(0, brightness, 0);
auto color_blue = pixels.Color(0, 0, brightness);
auto color_yellow = pixels.Color(brightness, brightness, 0);
auto color_purple = pixels.Color(brightness, 0, brightness);
auto color_cyan = pixels.Color(0, brightness, brightness);
auto color_white = pixels.Color(brightness, brightness, brightness);

const int NUM_LEDS = 8;

LedInfo ALL_LEDS[] = {
    {5, color_red},
    {4, color_green},
    {3, color_blue},
    {2, color_yellow},
    {A0, color_red},
    {A1, color_green},
    {A2, color_blue},
    {A3, color_yellow}
};
//auto notes = "a | a+ e a b+ e+ | c#* b c#* d* | c#*+ b b | a+ g# f# | g# a b c#* | g#+ f#. e- | e+. r | e*+ d* c#* | d*+ c#*+ | b c#* a b | g# f# e a | a g# a b | a+ e c#* | c#* b c#* d* | c#*+ b c# | d* c#* b a | g#+ a d#* | c#* b. a- | a+ r";
auto notes = "a | a+ e a b+ e+ | c#* b c#* d* | c#*+ b b | a+ g# f# | g# a b c#* | g#+ f#. e- | e+. r | e*+ d* c#* | d*+ c#*+ | b c#* a b | g# f# e a |";// a g# a b | a+ e c#* | c#* b c#* d* | c#*+ b c# | d* c#* b a | g#+ a d#* | c#* b. a- | a+ r";
Melody melody(notes);

/*
struct Song {
  Melody soprano;
  Melody alto;
  Melody tenor;
  Melody bass;
};

Song adeste_fideles = {
  Melody("a | a+ e a b+ e+ c#* b c#* d* | c#* b b | a+ g# f# | g# a b c#* | g#+ f#. e- | e+. r | e*+ d* c#* | d*+ c*+ | b c#* a b | g# f# e  a | a g# a b | a+ e c#* | c#* b c#* d* | c#*+ b c# | d* c#* b a | g#+ a d#* | c#* b. a- | a+ r"),
  melody,
  melody,
  melody,
};*/

void setup()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    pinMode(ALL_LEDS[i].pin, OUTPUT);
  }
  pinMode(SPEAKER, OUTPUT);
  pixels.begin();
  randomSeed(analogRead(0));
  melody.setTempo(120);
}

void loop()
{
  if (!melody.hasNext()) melody.restart();

  melody.next();
  auto frequency = melody.getFrequency();
  auto duration = melody.getDuration();

  auto number_of_leds_to_use = random(1, NUM_LEDS + 1);
  LedInfo *leds_to_use = pick_random_from(ALL_LEDS, number_of_leds_to_use);
  tone(SPEAKER, frequency, duration);
  for (int i = 0; i < number_of_leds_to_use; i++)
  {
    toggle_diode(leds_to_use[i].pin, HIGH);    
  }
  delay(duration);
  for (int i = 0; i < number_of_leds_to_use; i++)
  {
    toggle_diode(leds_to_use[i].pin, LOW);
  }
  noTone(SPEAKER);
}

void toggle_diode(int pin, uint8_t color)
{
  digitalWrite(pin, color);
}

void toggle_neo_diode(uint32_t color)
{
  pixels.setPixelColor(0, color);
  pixels.show();
}

void neo_diode_off()
{
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

int delayValue()
{
  return random(10, 100);
}

LedInfo* pick_random_from(LedInfo *ledice, int n)
{
  auto indices = shuffled_array_of_indices(n);
  auto leds = (LedInfo *)malloc(n * sizeof(LedInfo));
  for (int i = 0; i < n; i++)
  {
    leds[i] = ledice[indices[i]];
  }
  return leds;
}

int* shuffled_array_of_indices(int n)
{
  auto indices = (int *)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) indices[i] = i;
  for (int i = 0; i < n-1; i++)
  {
    auto j = random(i, n);
    auto tmp = indices[i];
    indices[i] = indices[j];
    indices[j] = tmp;
  }
  return indices;
}