/*********************************************************************
  This is an example for our nRF51822 based Bluefruit LE modules
  Pick one up today in the adafruit shop!
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  MIT license, check LICENSE for more information
  All text above, and the splash screen below must be included in
  any redistribution
*********************************************************************/
#include<Keyboard.h>
#include"bleSetup.h"
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, 8, NEO_GRB + NEO_KHZ800);
#include "morseKey.h"

/* Global to both setups */
int buzzerPin = 5;
int debounceTime = 200;
int ditPin = A2;
int dahPin = A3;
int ditSound = 880;
int dahSound = 500;
int ditSoundDuration = 400;
int dahSoundDuration = 450;
int speedTyper = 300;
int speedSense = 3;
int accessPin = 12;

/* Global for BLE Keyboard Setup */
String bleDitKey = "37";
String bleDahKey = "2D";
String bleAltDitKey = "44";
String bleAltDahKey = "45";
String bleEnterKey = "28";

BLEKeyboardKey bleShortKey(ditPin, bleDitKey, bleAltDitKey, debounceTime, buzzerPin, ditSound, ditSoundDuration);
BLEKeyboardKey bleLongKey(dahPin, bleDahKey, bleAltDahKey, debounceTime, buzzerPin, dahSound, dahSoundDuration);
BLEAccessKey bleAccessButton(accessPin, debounceTime);


/* Global for USB Keyboard Setup
  char ditKey = 46;
  char dahKey = 45;
  char altDitKey = 204;
  char altDahKey = 205;

  KeyboardKey shortKey(ditPin, ditKey, altDitKey, debounceTime, buzzerPin, ditSound, ditSoundDuration);
  KeyboardKey longKey(dahPin, dahKey, altDahKey, debounceTime, buzzerPin, dahSound, dahSoundDuration);
  AccessKey accessButton(accessPin, debounceTime);
*/

//ModifierKey accessButton(accessPin, debounceTime);

void setup(void)
{
  Serial.begin(115200);
  bleSetup();
  strip.begin();
  strip.setBrightness(100);
  strip.show(); // Initialize all pixels to 'off'
  //Keyboard.begin();
}

void loop(void)
{
  //speedTyper = analogRead(A5)/speedSense;

  /*
    bool shiftValue = accessButton.Check();
    shortKey.Press(shiftValue, speedTyper);
    longKey.Press(shiftValue, speedTyper);
  */

  //bool shiftValue = bleAccessButton.Check();
  bool shiftValue = false;
  bleShortKey.NoRepeat(speedTyper, 5000);
  bleLongKey.NoRepeat(speedTyper, 5000);

  /*
    bleShortKey.Press(shiftValue, speedTyper);
    bleLongKey.Press(shiftValue, speedTyper);
  */

}
