#include <Arduino.h>
// Include the required Arduino libraries:
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <string.h>
#include <Dictionary.h>

// Hardware SPI:
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 3

// music constants
#define NOTE_COUNT 12

int RIFF_NOTE_COUNT = 4;

char *notes[NOTE_COUNT] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
char *major[] = {"1", "2", "3", "4", "5", "6", "7"};
char *minor[] = {"1", "2", "b3", "4", "5", "b6", "b7"};

Dictionary *intervals = new Dictionary();

char *majorNotes[7];

// Create a new instance of the MD_Parola class with hardware SPI connection:
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup()
{
  Serial.begin(9600);
  myDisplay.begin();
  myDisplay.setIntensity(0);
  myDisplay.setTextAlignment(PA_CENTER);
  myDisplay.displayClear();

  initializeIntervalMappings();
  calculateMajorNotes("C#");
}

void loop()
{
  if (myDisplay.displayAnimate())
  {
    myDisplay.displayReset();

    // -------------- at the end of each riff, display another

    String riff = generateRandomRiff(majorNotes);

    char buf[50];
    riff.toCharArray(buf, riff.length() + 1);

    // display generated riff
    myDisplay.displayText(buf, PA_CENTER, 100, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
}

int intervalToValue(char *interval)
{
  String intervalValue = intervals->search(interval);
  return intervalValue.toInt();
}

void calculateMajorNotes(char *key)
{
  int keyIndex = getNoteIndex(key);

  // calculate the all notes in the scale
  for (int i = 0; i < 7; i++)
  {
    // get the step of the interval
    int intervalValue = intervalToValue(major[i]);

    // TODO: replace this with wrapped index based on starting point
    int noteIndex = calculateWrappedNoteIndex(keyIndex + intervalValue);

    // grab note at cursor
    majorNotes[i] = notes[noteIndex];
  }
}

String generateRandomRiff(char *scaleNotes[])
{
  String riff = "";

  // generate next naive riff notes randomly
  for (int i = 0; i < RIFF_NOTE_COUNT; i++)
  {
    int randomIndex = random(0, 6);
    char *note = scaleNotes[randomIndex];

    riff.concat(note);

    // add comma (unless it's the last note)
    if (i != RIFF_NOTE_COUNT - 1)
    {
      riff.concat(", ");
    }
  }

  return riff;
}

void initializeIntervalMappings()
{
  intervals->insert("1", "0");
  intervals->insert("b2", "1");
  intervals->insert("2", "2");
  intervals->insert("b3", "3");
  intervals->insert("3", "4");
  intervals->insert("4", "5");
  intervals->insert("#4", "6");
  intervals->insert("b5", "6");
  intervals->insert("5", "7");
  intervals->insert("#5", "8");
  intervals->insert("b6", "8");
  intervals->insert("6", "9");
  intervals->insert("bb7", "9");
  intervals->insert("b7", "10");
  intervals->insert("7", "11");
}

int getNoteIndex(char *note)
{
  for (int i = 0; i < NOTE_COUNT; i++)
  {
    if (notes[i] == note)
    {
      // note found
      return i;
    }
  }

  // not found (:p)
  return -1;
}

int calculateWrappedNoteIndex(int virtualIndex)
{
  int wholeCycles = floor(virtualIndex / NOTE_COUNT);

  if (virtualIndex >= NOTE_COUNT)
  {
    return virtualIndex - wholeCycles * NOTE_COUNT;
  }
  else
  {
    return virtualIndex;
  }
}