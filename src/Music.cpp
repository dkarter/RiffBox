/* ******************************************
 *  Auto Generated File                     *
 *                                          *
 *  Do not edit manually!                   *
 * ******************************************/


#include <Arduino.h>
#include <Music.h>
#include <string.h>

String cAeolian[7] = {"C", "D", "Eb", "F", "G", "Ab", "Bb"};
String cDorian[7] = {"C", "D", "Eb", "F", "G", "A", "Bb"};
String cIonian[7] = {"C", "D", "E", "F", "G", "A", "B"};
String cLocrian[7] = {"C", "Db", "Eb", "F", "Gb", "Ab", "Bb"};
String cLydian[7] = {"C", "D", "E", "F#", "G", "A", "B"};
String cMixolydian[7] = {"C", "D", "E", "F", "G", "A", "Bb"};
String cPhrygian[7] = {"C", "Db", "Eb", "F", "G", "Ab", "Bb"};
String cSharpAeolian[7] = {"C#", "D#", "E", "F#", "G#", "A", "B"};
String cSharpDorian[7] = {"C#", "D#", "E", "F#", "G#", "A#", "B"};
String cSharpIonian[7] = {"C#", "D#", "F", "Gb", "Ab", "Bb", "C"};
String cSharpLocrian[7] = {"C#", "D", "E", "F#", "G", "A", "B"};
String cSharpLydian[7] = {"C#", "D#", "F", "G", "Ab", "Bb", "C"};
String cSharpMixolydian[7] = {"C#", "D#", "F", "Gb", "Ab", "Bb", "B"};
String cSharpPhrygian[7] = {"C#", "D", "E", "F#", "G#", "A", "B"};
String dFlatAeolian[7] = {"Db", "Eb", "E", "Gb", "Ab", "A", "B"};
String dFlatDorian[7] = {"Db", "Eb", "E", "Gb", "Ab", "Bb", "B"};
String dFlatIonian[7] = {"Db", "Eb", "F", "F#", "G#", "A#", "C"};
String dFlatLocrian[7] = {"Db", "D", "E", "Gb", "G", "A", "B"};
String dFlatLydian[7] = {"Db", "Eb", "F", "G", "G#", "A#", "C"};
String dFlatMixolydian[7] = {"Db", "Eb", "F", "F#", "G#", "A#", "B"};
String dFlatPhrygian[7] = {"Db", "D", "E", "Gb", "Ab", "A", "B"};
String dAeolian[7] = {"D", "E", "F", "G", "A", "Bb", "C"};
String dDorian[7] = {"D", "E", "F", "G", "A", "B", "C"};
String dIonian[7] = {"D", "E", "F#", "G", "A", "B", "C#"};
String dLocrian[7] = {"D", "Eb", "F", "G", "Ab", "Bb", "C"};
String dLydian[7] = {"D", "E", "F#", "G#", "A", "B", "C#"};
String dMixolydian[7] = {"D", "E", "F#", "G", "A", "B", "C"};
String dPhrygian[7] = {"D", "Eb", "F", "G", "A", "Bb", "C"};
String dSharpAeolian[7] = {"D#", "F", "Gb", "Ab", "Bb", "B", "C#"};
String dSharpDorian[7] = {"D#", "F", "Gb", "Ab", "Bb", "C", "Db"};
String dSharpIonian[7] = {"D#", "F", "G", "Ab", "Bb", "C", "D"};
String dSharpLocrian[7] = {"D#", "E", "F#", "G#", "A", "B", "C#"};
String dSharpLydian[7] = {"D#", "F", "G", "A", "Bb", "C", "D"};
String dSharpMixolydian[7] = {"D#", "F", "G", "Ab", "Bb", "C", "Db"};
String dSharpPhrygian[7] = {"D#", "E", "F#", "G#", "A#", "B", "C#"};
String eFlatAeolian[7] = {"Eb", "F", "F#", "G#", "A#", "B", "Db"};
String eFlatDorian[7] = {"Eb", "F", "F#", "G#", "A#", "C", "C#"};
String eFlatIonian[7] = {"Eb", "F", "G", "G#", "A#", "C", "D"};
String eFlatLocrian[7] = {"Eb", "E", "Gb", "Ab", "A", "B", "Db"};
String eFlatLydian[7] = {"Eb", "F", "G", "A", "A#", "C", "D"};
String eFlatMixolydian[7] = {"Eb", "F", "G", "G#", "A#", "C", "C#"};
String eFlatPhrygian[7] = {"Eb", "E", "Gb", "Ab", "Bb", "B", "Db"};
String eAeolian[7] = {"E", "F#", "G", "A", "B", "C", "D"};
String eDorian[7] = {"E", "F#", "G", "A", "B", "C#", "D"};
String eIonian[7] = {"E", "F#", "G#", "A", "B", "C#", "D#"};
String eLocrian[7] = {"E", "F", "G", "A", "Bb", "C", "D"};
String eLydian[7] = {"E", "F#", "G#", "A#", "B", "C#", "D#"};
String eMixolydian[7] = {"E", "F#", "G#", "A", "B", "C#", "D"};
String ePhrygian[7] = {"E", "F", "G", "A", "B", "C", "D"};
String fAeolian[7] = {"F", "G", "Ab", "Bb", "C", "Db", "Eb"};
String fDorian[7] = {"F", "G", "Ab", "Bb", "C", "D", "Eb"};
String fIonian[7] = {"F", "G", "A", "Bb", "C", "D", "E"};
String fLocrian[7] = {"F", "Gb", "Ab", "Bb", "B", "C#", "D#"};
String fLydian[7] = {"F", "G", "A", "B", "C", "D", "E"};
String fMixolydian[7] = {"F", "G", "A", "Bb", "C", "D", "Eb"};
String fPhrygian[7] = {"F", "Gb", "Ab", "Bb", "C", "Db", "Eb"};
String fSharpAeolian[7] = {"F#", "G#", "A", "B", "C#", "D", "E"};
String fSharpDorian[7] = {"F#", "G#", "A", "B", "C#", "D#", "E"};
String fSharpIonian[7] = {"F#", "G#", "A#", "B", "C#", "D#", "F"};
String fSharpLocrian[7] = {"F#", "G", "A", "B", "C", "D", "E"};
String fSharpLydian[7] = {"F#", "G#", "A#", "C", "Db", "Eb", "F"};
String fSharpMixolydian[7] = {"F#", "G#", "A#", "B", "C#", "D#", "E"};
String fSharpPhrygian[7] = {"F#", "G", "A", "B", "C#", "D", "E"};
String gFlatAeolian[7] = {"Gb", "Ab", "A", "B", "Db", "D", "E"};
String gFlatDorian[7] = {"Gb", "Ab", "A", "B", "Db", "Eb", "E"};
String gFlatIonian[7] = {"Gb", "Ab", "Bb", "B", "Db", "Eb", "F"};
String gFlatLocrian[7] = {"Gb", "G", "A", "B", "C", "D", "E"};
String gFlatLydian[7] = {"Gb", "Ab", "Bb", "C", "C#", "D#", "F"};
String gFlatMixolydian[7] = {"Gb", "Ab", "Bb", "B", "Db", "Eb", "E"};
String gFlatPhrygian[7] = {"Gb", "G", "A", "B", "Db", "D", "E"};
String gAeolian[7] = {"G", "A", "Bb", "C", "D", "Eb", "F"};
String gDorian[7] = {"G", "A", "Bb", "C", "D", "E", "F"};
String gIonian[7] = {"G", "A", "B", "C", "D", "E", "F#"};
String gLocrian[7] = {"G", "Ab", "Bb", "C", "Db", "Eb", "F"};
String gLydian[7] = {"G", "A", "B", "C#", "D", "E", "F#"};
String gMixolydian[7] = {"G", "A", "B", "C", "D", "E", "F"};
String gPhrygian[7] = {"G", "Ab", "Bb", "C", "D", "Eb", "F"};
String gSharpAeolian[7] = {"G#", "A#", "B", "C#", "D#", "E", "F#"};
String gSharpDorian[7] = {"G#", "A#", "B", "C#", "D#", "F", "Gb"};
String gSharpIonian[7] = {"G#", "A#", "C", "Db", "Eb", "F", "G"};
String gSharpLocrian[7] = {"G#", "A", "B", "C#", "D", "E", "F#"};
String gSharpLydian[7] = {"G#", "A#", "C", "D", "Eb", "F", "G"};
String gSharpMixolydian[7] = {"G#", "A#", "C", "Db", "Eb", "F", "Gb"};
String gSharpPhrygian[7] = {"G#", "A", "B", "C#", "D#", "E", "F#"};
String aFlatAeolian[7] = {"Ab", "Bb", "B", "Db", "Eb", "E", "Gb"};
String aFlatDorian[7] = {"Ab", "Bb", "B", "Db", "Eb", "F", "F#"};
String aFlatIonian[7] = {"Ab", "Bb", "C", "C#", "D#", "F", "G"};
String aFlatLocrian[7] = {"Ab", "A", "B", "Db", "D", "E", "Gb"};
String aFlatLydian[7] = {"Ab", "Bb", "C", "D", "D#", "F", "G"};
String aFlatMixolydian[7] = {"Ab", "Bb", "C", "C#", "D#", "F", "F#"};
String aFlatPhrygian[7] = {"Ab", "A", "B", "Db", "Eb", "E", "Gb"};
String aAeolian[7] = {"A", "B", "C", "D", "E", "F", "G"};
String aDorian[7] = {"A", "B", "C", "D", "E", "F#", "G"};
String aIonian[7] = {"A", "B", "C#", "D", "E", "F#", "G#"};
String aLocrian[7] = {"A", "Bb", "C", "D", "Eb", "F", "G"};
String aLydian[7] = {"A", "B", "C#", "D#", "E", "F#", "G#"};
String aMixolydian[7] = {"A", "B", "C#", "D", "E", "F#", "G"};
String aPhrygian[7] = {"A", "Bb", "C", "D", "E", "F", "G"};
String aSharpAeolian[7] = {"A#", "C", "Db", "Eb", "F", "Gb", "Ab"};
String aSharpDorian[7] = {"A#", "C", "Db", "Eb", "F", "G", "Ab"};
String aSharpIonian[7] = {"A#", "C", "D", "Eb", "F", "G", "A"};
String aSharpLocrian[7] = {"A#", "B", "C#", "D#", "E", "F#", "G#"};
String aSharpLydian[7] = {"A#", "C", "D", "E", "F", "G", "A"};
String aSharpMixolydian[7] = {"A#", "C", "D", "Eb", "F", "G", "Ab"};
String aSharpPhrygian[7] = {"A#", "B", "C#", "D#", "F", "Gb", "Ab"};
String bFlatAeolian[7] = {"Bb", "C", "C#", "D#", "F", "F#", "G#"};
String bFlatDorian[7] = {"Bb", "C", "C#", "D#", "F", "G", "G#"};
String bFlatIonian[7] = {"Bb", "C", "D", "D#", "F", "G", "A"};
String bFlatLocrian[7] = {"Bb", "B", "Db", "Eb", "E", "Gb", "Ab"};
String bFlatLydian[7] = {"Bb", "C", "D", "E", "F", "G", "A"};
String bFlatMixolydian[7] = {"Bb", "C", "D", "D#", "F", "G", "G#"};
String bFlatPhrygian[7] = {"Bb", "B", "Db", "Eb", "F", "F#", "G#"};
String bAeolian[7] = {"B", "C#", "D", "E", "F#", "G", "A"};
String bDorian[7] = {"B", "C#", "D", "E", "F#", "G#", "A"};
String bIonian[7] = {"B", "C#", "D#", "E", "F#", "G#", "A#"};
String bLocrian[7] = {"B", "C", "D", "E", "F", "G", "A"};
String bLydian[7] = {"B", "C#", "D#", "F", "Gb", "Ab", "Bb"};
String bMixolydian[7] = {"B", "C#", "D#", "E", "F#", "G#", "A"};
String bPhrygian[7] = {"B", "C", "D", "E", "F#", "G", "A"};


void copyNotes(String *from, String *to) {
  for (int i; i < 7; i++) {
    to[i] = from[i];
  }
}

void notesForMode(int key, int mode, String *scaleNotes) {
  String selector = String(String(key) + "," + String(mode));

    if (key == 0 && mode == 0) {
      copyNotes(cAeolian, scaleNotes);
      return;
    }
    if (key == 0 && mode == 1) {
      copyNotes(cDorian, scaleNotes);
      return;
    }
    if (key == 0 && mode == 2) {
      copyNotes(cIonian, scaleNotes);
      return;
    }
    if (key == 0 && mode == 3) {
      copyNotes(cLocrian, scaleNotes);
      return;
    }
    if (key == 0 && mode == 4) {
      copyNotes(cLydian, scaleNotes);
      return;
    }
    if (key == 0 && mode == 5) {
      copyNotes(cMixolydian, scaleNotes);
      return;
    }
    if (key == 0 && mode == 6) {
      copyNotes(cPhrygian, scaleNotes);
      return;
    }
    if (key == 1 && mode == 0) {
      copyNotes(cSharpAeolian, scaleNotes);
      return;
    }
    if (key == 1 && mode == 1) {
      copyNotes(cSharpDorian, scaleNotes);
      return;
    }
    if (key == 1 && mode == 2) {
      copyNotes(cSharpIonian, scaleNotes);
      return;
    }
    if (key == 1 && mode == 3) {
      copyNotes(cSharpLocrian, scaleNotes);
      return;
    }
    if (key == 1 && mode == 4) {
      copyNotes(cSharpLydian, scaleNotes);
      return;
    }
    if (key == 1 && mode == 5) {
      copyNotes(cSharpMixolydian, scaleNotes);
      return;
    }
    if (key == 1 && mode == 6) {
      copyNotes(cSharpPhrygian, scaleNotes);
      return;
    }
    if (key == 2 && mode == 0) {
      copyNotes(dFlatAeolian, scaleNotes);
      return;
    }
    if (key == 2 && mode == 1) {
      copyNotes(dFlatDorian, scaleNotes);
      return;
    }
    if (key == 2 && mode == 2) {
      copyNotes(dFlatIonian, scaleNotes);
      return;
    }
    if (key == 2 && mode == 3) {
      copyNotes(dFlatLocrian, scaleNotes);
      return;
    }
    if (key == 2 && mode == 4) {
      copyNotes(dFlatLydian, scaleNotes);
      return;
    }
    if (key == 2 && mode == 5) {
      copyNotes(dFlatMixolydian, scaleNotes);
      return;
    }
    if (key == 2 && mode == 6) {
      copyNotes(dFlatPhrygian, scaleNotes);
      return;
    }
    if (key == 3 && mode == 0) {
      copyNotes(dAeolian, scaleNotes);
      return;
    }
    if (key == 3 && mode == 1) {
      copyNotes(dDorian, scaleNotes);
      return;
    }
    if (key == 3 && mode == 2) {
      copyNotes(dIonian, scaleNotes);
      return;
    }
    if (key == 3 && mode == 3) {
      copyNotes(dLocrian, scaleNotes);
      return;
    }
    if (key == 3 && mode == 4) {
      copyNotes(dLydian, scaleNotes);
      return;
    }
    if (key == 3 && mode == 5) {
      copyNotes(dMixolydian, scaleNotes);
      return;
    }
    if (key == 3 && mode == 6) {
      copyNotes(dPhrygian, scaleNotes);
      return;
    }
    if (key == 4 && mode == 0) {
      copyNotes(dSharpAeolian, scaleNotes);
      return;
    }
    if (key == 4 && mode == 1) {
      copyNotes(dSharpDorian, scaleNotes);
      return;
    }
    if (key == 4 && mode == 2) {
      copyNotes(dSharpIonian, scaleNotes);
      return;
    }
    if (key == 4 && mode == 3) {
      copyNotes(dSharpLocrian, scaleNotes);
      return;
    }
    if (key == 4 && mode == 4) {
      copyNotes(dSharpLydian, scaleNotes);
      return;
    }
    if (key == 4 && mode == 5) {
      copyNotes(dSharpMixolydian, scaleNotes);
      return;
    }
    if (key == 4 && mode == 6) {
      copyNotes(dSharpPhrygian, scaleNotes);
      return;
    }
    if (key == 5 && mode == 0) {
      copyNotes(eFlatAeolian, scaleNotes);
      return;
    }
    if (key == 5 && mode == 1) {
      copyNotes(eFlatDorian, scaleNotes);
      return;
    }
    if (key == 5 && mode == 2) {
      copyNotes(eFlatIonian, scaleNotes);
      return;
    }
    if (key == 5 && mode == 3) {
      copyNotes(eFlatLocrian, scaleNotes);
      return;
    }
    if (key == 5 && mode == 4) {
      copyNotes(eFlatLydian, scaleNotes);
      return;
    }
    if (key == 5 && mode == 5) {
      copyNotes(eFlatMixolydian, scaleNotes);
      return;
    }
    if (key == 5 && mode == 6) {
      copyNotes(eFlatPhrygian, scaleNotes);
      return;
    }
    if (key == 6 && mode == 0) {
      copyNotes(eAeolian, scaleNotes);
      return;
    }
    if (key == 6 && mode == 1) {
      copyNotes(eDorian, scaleNotes);
      return;
    }
    if (key == 6 && mode == 2) {
      copyNotes(eIonian, scaleNotes);
      return;
    }
    if (key == 6 && mode == 3) {
      copyNotes(eLocrian, scaleNotes);
      return;
    }
    if (key == 6 && mode == 4) {
      copyNotes(eLydian, scaleNotes);
      return;
    }
    if (key == 6 && mode == 5) {
      copyNotes(eMixolydian, scaleNotes);
      return;
    }
    if (key == 6 && mode == 6) {
      copyNotes(ePhrygian, scaleNotes);
      return;
    }
    if (key == 7 && mode == 0) {
      copyNotes(fAeolian, scaleNotes);
      return;
    }
    if (key == 7 && mode == 1) {
      copyNotes(fDorian, scaleNotes);
      return;
    }
    if (key == 7 && mode == 2) {
      copyNotes(fIonian, scaleNotes);
      return;
    }
    if (key == 7 && mode == 3) {
      copyNotes(fLocrian, scaleNotes);
      return;
    }
    if (key == 7 && mode == 4) {
      copyNotes(fLydian, scaleNotes);
      return;
    }
    if (key == 7 && mode == 5) {
      copyNotes(fMixolydian, scaleNotes);
      return;
    }
    if (key == 7 && mode == 6) {
      copyNotes(fPhrygian, scaleNotes);
      return;
    }
    if (key == 8 && mode == 0) {
      copyNotes(fSharpAeolian, scaleNotes);
      return;
    }
    if (key == 8 && mode == 1) {
      copyNotes(fSharpDorian, scaleNotes);
      return;
    }
    if (key == 8 && mode == 2) {
      copyNotes(fSharpIonian, scaleNotes);
      return;
    }
    if (key == 8 && mode == 3) {
      copyNotes(fSharpLocrian, scaleNotes);
      return;
    }
    if (key == 8 && mode == 4) {
      copyNotes(fSharpLydian, scaleNotes);
      return;
    }
    if (key == 8 && mode == 5) {
      copyNotes(fSharpMixolydian, scaleNotes);
      return;
    }
    if (key == 8 && mode == 6) {
      copyNotes(fSharpPhrygian, scaleNotes);
      return;
    }
    if (key == 9 && mode == 0) {
      copyNotes(gFlatAeolian, scaleNotes);
      return;
    }
    if (key == 9 && mode == 1) {
      copyNotes(gFlatDorian, scaleNotes);
      return;
    }
    if (key == 9 && mode == 2) {
      copyNotes(gFlatIonian, scaleNotes);
      return;
    }
    if (key == 9 && mode == 3) {
      copyNotes(gFlatLocrian, scaleNotes);
      return;
    }
    if (key == 9 && mode == 4) {
      copyNotes(gFlatLydian, scaleNotes);
      return;
    }
    if (key == 9 && mode == 5) {
      copyNotes(gFlatMixolydian, scaleNotes);
      return;
    }
    if (key == 9 && mode == 6) {
      copyNotes(gFlatPhrygian, scaleNotes);
      return;
    }
    if (key == 10 && mode == 0) {
      copyNotes(gAeolian, scaleNotes);
      return;
    }
    if (key == 10 && mode == 1) {
      copyNotes(gDorian, scaleNotes);
      return;
    }
    if (key == 10 && mode == 2) {
      copyNotes(gIonian, scaleNotes);
      return;
    }
    if (key == 10 && mode == 3) {
      copyNotes(gLocrian, scaleNotes);
      return;
    }
    if (key == 10 && mode == 4) {
      copyNotes(gLydian, scaleNotes);
      return;
    }
    if (key == 10 && mode == 5) {
      copyNotes(gMixolydian, scaleNotes);
      return;
    }
    if (key == 10 && mode == 6) {
      copyNotes(gPhrygian, scaleNotes);
      return;
    }
    if (key == 11 && mode == 0) {
      copyNotes(gSharpAeolian, scaleNotes);
      return;
    }
    if (key == 11 && mode == 1) {
      copyNotes(gSharpDorian, scaleNotes);
      return;
    }
    if (key == 11 && mode == 2) {
      copyNotes(gSharpIonian, scaleNotes);
      return;
    }
    if (key == 11 && mode == 3) {
      copyNotes(gSharpLocrian, scaleNotes);
      return;
    }
    if (key == 11 && mode == 4) {
      copyNotes(gSharpLydian, scaleNotes);
      return;
    }
    if (key == 11 && mode == 5) {
      copyNotes(gSharpMixolydian, scaleNotes);
      return;
    }
    if (key == 11 && mode == 6) {
      copyNotes(gSharpPhrygian, scaleNotes);
      return;
    }
    if (key == 12 && mode == 0) {
      copyNotes(aFlatAeolian, scaleNotes);
      return;
    }
    if (key == 12 && mode == 1) {
      copyNotes(aFlatDorian, scaleNotes);
      return;
    }
    if (key == 12 && mode == 2) {
      copyNotes(aFlatIonian, scaleNotes);
      return;
    }
    if (key == 12 && mode == 3) {
      copyNotes(aFlatLocrian, scaleNotes);
      return;
    }
    if (key == 12 && mode == 4) {
      copyNotes(aFlatLydian, scaleNotes);
      return;
    }
    if (key == 12 && mode == 5) {
      copyNotes(aFlatMixolydian, scaleNotes);
      return;
    }
    if (key == 12 && mode == 6) {
      copyNotes(aFlatPhrygian, scaleNotes);
      return;
    }
    if (key == 13 && mode == 0) {
      copyNotes(aAeolian, scaleNotes);
      return;
    }
    if (key == 13 && mode == 1) {
      copyNotes(aDorian, scaleNotes);
      return;
    }
    if (key == 13 && mode == 2) {
      copyNotes(aIonian, scaleNotes);
      return;
    }
    if (key == 13 && mode == 3) {
      copyNotes(aLocrian, scaleNotes);
      return;
    }
    if (key == 13 && mode == 4) {
      copyNotes(aLydian, scaleNotes);
      return;
    }
    if (key == 13 && mode == 5) {
      copyNotes(aMixolydian, scaleNotes);
      return;
    }
    if (key == 13 && mode == 6) {
      copyNotes(aPhrygian, scaleNotes);
      return;
    }
    if (key == 14 && mode == 0) {
      copyNotes(aSharpAeolian, scaleNotes);
      return;
    }
    if (key == 14 && mode == 1) {
      copyNotes(aSharpDorian, scaleNotes);
      return;
    }
    if (key == 14 && mode == 2) {
      copyNotes(aSharpIonian, scaleNotes);
      return;
    }
    if (key == 14 && mode == 3) {
      copyNotes(aSharpLocrian, scaleNotes);
      return;
    }
    if (key == 14 && mode == 4) {
      copyNotes(aSharpLydian, scaleNotes);
      return;
    }
    if (key == 14 && mode == 5) {
      copyNotes(aSharpMixolydian, scaleNotes);
      return;
    }
    if (key == 14 && mode == 6) {
      copyNotes(aSharpPhrygian, scaleNotes);
      return;
    }
    if (key == 15 && mode == 0) {
      copyNotes(bFlatAeolian, scaleNotes);
      return;
    }
    if (key == 15 && mode == 1) {
      copyNotes(bFlatDorian, scaleNotes);
      return;
    }
    if (key == 15 && mode == 2) {
      copyNotes(bFlatIonian, scaleNotes);
      return;
    }
    if (key == 15 && mode == 3) {
      copyNotes(bFlatLocrian, scaleNotes);
      return;
    }
    if (key == 15 && mode == 4) {
      copyNotes(bFlatLydian, scaleNotes);
      return;
    }
    if (key == 15 && mode == 5) {
      copyNotes(bFlatMixolydian, scaleNotes);
      return;
    }
    if (key == 15 && mode == 6) {
      copyNotes(bFlatPhrygian, scaleNotes);
      return;
    }
    if (key == 16 && mode == 0) {
      copyNotes(bAeolian, scaleNotes);
      return;
    }
    if (key == 16 && mode == 1) {
      copyNotes(bDorian, scaleNotes);
      return;
    }
    if (key == 16 && mode == 2) {
      copyNotes(bIonian, scaleNotes);
      return;
    }
    if (key == 16 && mode == 3) {
      copyNotes(bLocrian, scaleNotes);
      return;
    }
    if (key == 16 && mode == 4) {
      copyNotes(bLydian, scaleNotes);
      return;
    }
    if (key == 16 && mode == 5) {
      copyNotes(bMixolydian, scaleNotes);
      return;
    }
    if (key == 16 && mode == 6) {
      copyNotes(bPhrygian, scaleNotes);
      return;
    }

}
