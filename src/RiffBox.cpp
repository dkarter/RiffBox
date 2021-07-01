#include <Arduino.h>

// Include the required Arduino libraries:
#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include <RotaryEncoder.h>
#include <SPI.h>
#include <string.h>

// MAX72XX Hardware SPI:
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 3

// Key selector (Rotary Encoder) pinout
#define KEY_CLK 4
#define KEY_DT 5
#define KEY_SW 8

#define KEY_MIN 0
#define KEY_MAX 11

// Mode selector (Rotary Encoder) pinout
#define MODE_CLK 7
#define MODE_DT 6
#define MODE_SW 3

#define MODE_MIN 0
#define MODE_MAX 6

// music constants
#define NOTE_COUNT 12

int keyIndex = 0;
int modeIndex = 0;

const int RIFF_NOTE_COUNT = 4;

String notes[NOTE_COUNT] = {"C",  "C#", "D",  "D#", "E",  "F",
                            "F#", "G",  "G#", "A",  "A#", "B"};

String modes[] = {"Ionian",     "Dorian",  "Phrygian", "Lydian",
                  "Mixolydian", "Aeolian", "Locrian"};

String modesFormulas[][7] = {{"1", "2", "3", "4", "5", "6", "7"},
                             {"1", "2", "b3", "4", "5", "6", "b7"},
                             {"1", "b2", "b3", "4", "5", "b6", "b7"},
                             {"1", "2", "3", "#4", "5", "6", "7"},
                             {"1", "2", "3", "4", "5", "6", "b7"},
                             {"1", "2", "b3", "4", "5", "b6", "b7"},
                             {"1", "b2", "b3", "4", "b5", "b6", "b7"}};

String intervals[][2] = {{"1", "0"},   {"b2", "1"},  {"2", "2"},  {"b3", "3"},
                         {"3", "4"},   {"4", "5"},   {"#4", "6"}, {"b5", "6"},
                         {"5", "7"},   {"#5", "8"},  {"b6", "8"}, {"6", "9"},
                         {"bb7", "9"}, {"b7", "10"}, {"7", "11"}};

int scaleNotesIndices[7];

// Create a new instance of the MD_Parola class with hardware SPI connection:
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Setup a RotaryEncoder with 2 steps per latch for the 2 signal input pins:
RotaryEncoder keySelector(KEY_CLK, KEY_DT, RotaryEncoder::LatchMode::FOUR3);

// Setup a RotaryEncoder with 2 steps per latch for the 2 signal input pins:
RotaryEncoder modeSelector(MODE_CLK, MODE_DT, RotaryEncoder::LatchMode::FOUR3);

int intervalToValue(String interval) {
  for (String *intervalMapping : intervals) {
    if (intervalMapping[0].compareTo(interval) == 0) {
      return intervalMapping[1].toInt();
    }
  }
}

int calculateWrappedNoteIndex(int virtualIndex) {
  int wholeCycles = floor(virtualIndex / NOTE_COUNT);

  if (virtualIndex >= NOTE_COUNT) {
    return virtualIndex - wholeCycles * NOTE_COUNT;
  } else {
    return virtualIndex;
  }
}

// TODO(dorian):
// add logic to turn notes to b if previous note was a natural and the
// current one is the sharp version
void calculateScaleNotes() {
  // calculate the all notes in the scale
  for (int i = 0; i < 7; i++) {
    String interval = modesFormulas[modeIndex][i];

    // get the step of the interval
    int intervalValue = intervalToValue(interval);

    // Calculate wrapped note index based on interval value and key index
    int noteIndex = calculateWrappedNoteIndex(keyIndex + intervalValue);

    // grab note at cursor
    scaleNotesIndices[i] = noteIndex;
  }
}

String generateRandomRiff() {
  String riff = "";

  // generate next naive riff notes randomly
  for (int i = 0; i < RIFF_NOTE_COUNT; i++) {
    int randomIndex = random(0, 6);
    String note = notes[scaleNotesIndices[randomIndex]];

    riff.concat(note);

    // add comma (unless it's the last note)
    if (i != RIFF_NOTE_COUNT - 1) {
      riff.concat(", ");
    }
  }

  return riff;
}

void checkModeSelector() {
  // tell the encoder we had a tick - this allows it to debounce the multiple
  // signals per segment
  modeSelector.tick();

  // get the current physical position and calc the logical position
  int newPos = modeSelector.getPosition();

  // constrain output values to min and max index in the modes array
  if (newPos < MODE_MIN) {
    modeSelector.setPosition(MODE_MIN);
    newPos = MODE_MIN;
  } else if (newPos > MODE_MAX) {
    modeSelector.setPosition(MODE_MAX);
    newPos = MODE_MAX;
  }

  // check if mode changed
  if (modeIndex != newPos) {
    // update mode
    modeIndex = newPos;
    String newMode = modes[modeIndex];

    // display new mode
    myDisplay.displayClear();
    char buf[20];
    newMode.toCharArray(buf, newMode.length() + 1);
    myDisplay.displayText(buf, PA_CENTER, 100, 1000, PA_SCROLL_LEFT,
                          PA_SCROLL_LEFT);

    // recalculate scale notes based on new mode
    calculateScaleNotes();
  }
}

void checkKeySelector() {
  // tell the encoder we had a tick - this allows it to debounce the multiple
  // signals per segment
  keySelector.tick();

  // get the current physical position and calc the logical position
  int newPos = keySelector.getPosition();

  // constrain output values to min and max index in the notes array
  if (newPos < KEY_MIN) {
    keySelector.setPosition(KEY_MIN);
    newPos = KEY_MIN;
  } else if (newPos > KEY_MAX) {
    keySelector.setPosition(KEY_MAX);
    newPos = KEY_MAX;
  }

  // check if key changed
  if (keyIndex != newPos) {
    // update key
    keyIndex = newPos;
    String newKey = notes[keyIndex];

    // display new key
    myDisplay.displayClear();
    String displayText = "Key ";
    char buf[7];
    displayText.concat(newKey);
    displayText.toCharArray(buf, displayText.length() + 1);
    myDisplay.displayText(buf, PA_CENTER, 100, 1000, PA_DISSOLVE, PA_DISSOLVE);

    // recalculate scale notes based on new key
    calculateScaleNotes();
  }
}

void displayRandomRiffNotes() {
  if (myDisplay.displayAnimate()) {
    // reset display after each animation
    myDisplay.displayReset();

    // at the end of each riff, display another
    String riff = generateRandomRiff();

    // pad the buffer so it can fit the full riff notes + commas
    char buf[50];

    // convert the riff into a char array and copy it into the buffer (so that
    // we can pass it to the MAX72XX)
    riff.toCharArray(buf, riff.length() + 1);

    // display generated riff
    myDisplay.displayText(buf, PA_CENTER, 100, 0, PA_SCROLL_LEFT,
                          PA_SCROLL_LEFT);
  }
}

void setupDisplay() {
  myDisplay.begin();
  myDisplay.setIntensity(0);
  myDisplay.setTextAlignment(PA_CENTER);
  myDisplay.displayClear();
}

void setupKeySelector() {
  // set up intial position of rotary encoder
  keySelector.setPosition(keyIndex);
}

void setupModeSelector() {
  // set up intial position of rotary encoder
  modeSelector.setPosition(modeIndex);
}

void setup() {
  Serial.begin(9600);
  setupDisplay();
  setupKeySelector();
  setupModeSelector();

  calculateScaleNotes();
}

void loop() {
  checkKeySelector();
  checkModeSelector();
  displayRandomRiffNotes();
}
