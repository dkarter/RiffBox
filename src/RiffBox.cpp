#include <Arduino.h>

// Include the required Arduino libraries:
#include <Dictionary.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include <Music.h>
#include <RotaryEncoder.h>
#include <SPI.h>
#include <string.h>

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
int modeIndex = 0;

const int RIFF_NOTE_COUNT = 4;

String modes[7] = {"ionian",     "dorian",  "phrygian", "lydian",
                   "mixolydian", "aeolian", "locrian"};

String notes[NOTE_COUNT] = {"C",  "C#", "D",  "D#", "E",  "F",
                            "F#", "G",  "G#", "A",  "A#", "B"};

String scaleNotes[7];

// Create a new instance of the MD_Parola class with hardware SPI connection:
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Setup a RotaryEncoder with 2 steps per latch for the 2 signal input pins:
RotaryEncoder encoder(inputCLK, inputDT, RotaryEncoder::LatchMode::FOUR3);

String generateRandomRiff() {
  String riff = "";

  // generate next naive riff notes randomly
  for (int i = 0; i < RIFF_NOTE_COUNT; i++) {
    int randomIndex = random(0, 6);
    String note = scaleNotes[randomIndex];

    riff.concat(note);

    // add comma (unless it's the last note)
    if (i != RIFF_NOTE_COUNT - 1) {
      riff.concat(", ");
    }
  }

  return riff;
}

void checkRotaryEncoderMovement() {
  // tell the encoder we had a tick - this allows it to debounce the multiple
  // signals per segment
  encoder.tick();

  // get the current physical position and calc the logical position
  int newPos = encoder.getPosition();

  // constrain output values to min and max index in the notes array
  if (newPos < KEY_MIN) {
    encoder.setPosition(KEY_MIN);
    newPos = KEY_MIN;
  } else if (newPos > KEY_MAX) {
    encoder.setPosition(KEY_MAX);
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

    notesForMode(keyIndex, modeIndex, scaleNotes);
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

void setup() {
  Serial.begin(9600);
  myDisplay.begin();
  myDisplay.setIntensity(0);
  myDisplay.setTextAlignment(PA_CENTER);
  myDisplay.displayClear();

  // set up intial position of rotary encoder
  encoder.setPosition(keyIndex);
}

void loop() {
  checkRotaryEncoderMovement();
  displayRandomRiffNotes();
}
