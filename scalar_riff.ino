#include <Arduino.h>

// Include the required Arduino libraries:
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <string.h>
#include <Dictionary.h>
#include <RotaryEncoder.h>

// MAX72XX Hardware SPI:
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 3

// Rotary encoder pinout
#define inputCLK 4
#define inputDT 5
#define inputSW 8

// music constants
#define NOTE_COUNT 12

const int KEY_MIN = 0;
const int KEY_MAX = 11;

int keyIndex = 0;

const int RIFF_NOTE_COUNT = 4;

char *notes[NOTE_COUNT] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
char *major[] = {"1", "2", "3", "4", "5", "6", "7"};
char *minor[] = {"1", "2", "b3", "4", "5", "b6", "b7"};

Dictionary *intervals = new Dictionary();

char *majorNotes[7];

// Create a new instance of the MD_Parola class with hardware SPI connection:
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Setup a RotaryEncoder with 2 steps per latch for the 2 signal input pins:
RotaryEncoder encoder(inputCLK, inputDT, RotaryEncoder::LatchMode::FOUR3);

void setup()
{
  Serial.begin(9600);
  myDisplay.begin();
  myDisplay.setIntensity(0);
  myDisplay.setTextAlignment(PA_CENTER);
  myDisplay.displayClear();

  // set up intial position of rotary encoder
  encoder.setPosition(keyIndex);

  initializeIntervalMappings();
  calculateMajorNotes(notes[keyIndex]);
}

void loop()
{
  checkRotaryEncoderMovement();
  displayRandomRiffNotes();
}

int intervalToValue(char *interval)
{
  String intervalValue = intervals->search(interval);
  return intervalValue.toInt();
}

// TODO:
// add logic to turn notes to b if previous note was a natural and the
// current one is the sharp version
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

// these constants are loaded into a dictionary during setup and are used to calculate the scale relative to each key
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

void checkRotaryEncoderMovement()
{
  // tell the encoder we had a tick - this allows it to debounce the multiple signals per segment
  encoder.tick();

  // get the current physical position and calc the logical position
  int newPos = encoder.getPosition();

  // constrain output values to min and max index in the notes array
  if (newPos < KEY_MIN)
  {
    encoder.setPosition(KEY_MIN);
    newPos = KEY_MIN;
  }
  else if (newPos > KEY_MAX)
  {
    encoder.setPosition(KEY_MAX);
    newPos = KEY_MAX;
  }

  // check if key changed
  if (keyIndex != newPos)
  {
    // update key
    keyIndex = newPos;
    char *newKey = notes[keyIndex];

    // display new key
    myDisplay.displayClear();
    String displayText = "Key ";
    char buf[7];
    displayText.concat(newKey);
    displayText.toCharArray(buf, displayText.length() + 1);
    myDisplay.displayText(buf, PA_CENTER, 100, 1000, PA_DISSOLVE, PA_DISSOLVE);

    // recalculate scale notes based on new key
    calculateMajorNotes(newKey);
  }
}

void displayRandomRiffNotes()
{
  if (myDisplay.displayAnimate())
  {
    // reset display after each animation
    myDisplay.displayReset();

    // at the end of each riff, display another
    String riff = generateRandomRiff(majorNotes);

    // pad the buffer so it can fit the full riff notes + commas
    char buf[50];

    // convert the riff into a char array and copy it into the buffer (so that
    // we can pass it to the MAX72XX)
    riff.toCharArray(buf, riff.length() + 1);

    // display generated riff
    myDisplay.displayText(buf, PA_CENTER, 100, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
}