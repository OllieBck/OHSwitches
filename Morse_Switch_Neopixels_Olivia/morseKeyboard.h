class KeyboardKey {
    int keyPin;      // the number of the button pin
    char modifierValue;
    char keyValue;
    char letterValue;
    char altLetterValue;
    int pressSpeed;
    int debounceDelay;
    int freq;
    int sndLength;
    int sndPin;
    bool buttonTriggerState;
    int lightTimer = 0;
    bool keyFirstPress = true;

    unsigned long lastDebounceTime = 0;

  public:
    KeyboardKey (int pin, char primaryKeyValue, char secondaryKeyValue, int debouncerTime, int speakerPin, int freqValue, int sndDuration, bool buttonValueState)
    {
      keyPin = pin;
      letterValue = primaryKeyValue;
      altLetterValue = secondaryKeyValue;
      keyValue = letterValue;
      debounceDelay = debouncerTime;
      freq = freqValue;
      sndLength = sndDuration;
      sndPin = speakerPin;
      buttonTriggerState = buttonValueState;
      int resistorType;

      if (buttonTriggerState == LOW) {
        resistorType = INPUT_PULLUP;
      }
      else {
        resistorType = INPUT_PULLDOWN;
      }

      pinMode(keyPin, resistorType);
    }

    void Press(int ditdahTimer, int lightClock)
    {
      int keyState = digitalRead(keyPin);
      int playLength = sndLength - pressSpeed;
      pressSpeed = ditdahTimer;

      if (keyState == buttonTriggerState) {
        if (millis() - lastDebounceTime > debounceDelay) {
          if (keyFirstPress == true) {
            tone(sndPin, freq, playLength / 3);
            Keyboard.press(keyValue);
            Keyboard.release(keyValue);
            keyFirstPress = false;
            lastDebounceTime = millis();
            lightTimer = millis();
            lightsOn(20, lightClock);
            //rainbowCycle(20, lightClock);
          }
        }
        lastDebounceTime = millis();
        if (millis() - lightTimer > lightClock) {
          lightShowOff();
        }
      }
      else {
        keyFirstPress = true;
        lightShowOff();
      }
    }

    void lightShowOn() {
      for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, 255, 105, 180);
        strip.show();
      }
    }

    void lightShowOff() {
      for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, 0, 0, 0);
        strip.show();
      }
    }

    void lightsOn(int wait, int lightMonitor) {
      uint16_t j;
      int finalBreak = false;
      for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
        if (digitalRead(keyPin) != buttonTriggerState) {
          break;
        }
        strip.setPixelColor(j, 255, 0, 255);
        strip.show();
        int waitTimer = millis();
        bool testState = false;
        while (millis() - waitTimer < wait && digitalRead(keyPin) == buttonTriggerState) {
          if (millis() - lightTimer > lightMonitor) {
            lightShowOff();
            testState = true;
            break;
          }
        }
        if (testState == true) {
          break;
        }
      }
    }

    void rainbowCycle(uint8_t wait, int lightMonitor) {
      uint16_t i, j;
      int finalBreak = false;
      for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
        if (digitalRead(keyPin) != buttonTriggerState) {
          break;
        }
        for (i = 0; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
        }
        strip.show();
        int waitTimer = millis();
        bool testState = false;
        while (millis() - waitTimer < wait && digitalRead(keyPin) == buttonTriggerState) {
          if (millis() - lightTimer > lightMonitor) {
            lightShowOff();
            testState = true;
            break;
          }
        }
        if (testState == true) {
          break;
        }
      }
    }

    uint32_t Wheel(byte WheelPos) {
      if (digitalRead(keyPin) != buttonTriggerState) {
        lightShowOff();
        return strip.Color(0, 0, 0);
      }
      else {
        WheelPos = 255 - WheelPos;
        if (WheelPos < 85) {
          return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
        }
        if (WheelPos < 170) {
          WheelPos -= 85;
          return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
        }
        WheelPos -= 170;
        return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
      }
    }
};

/*---------------------------------------------------------------------------------*/

class AccessKey {
    int keyPin;      // the number of the button pin
    char keyValue;
    int debounceDelay;
    bool buttonTriggerState;

    unsigned long lastDebounceTime = 0;

    bool lastButtonState = HIGH;
    bool buttonState;

    bool modifierState = false;

  public:
    AccessKey (int pin, int debouncerTime, bool buttonStateValue)
    {
      keyPin = pin;
      debounceDelay = debouncerTime;
      buttonTriggerState = buttonStateValue;

      int resistorValue;

      if (buttonTriggerState == LOW) {
        resistorValue = INPUT_PULLUP;
      }
      else {
        resistorValue = INPUT_PULLDOWN;
      }
      pinMode(keyPin, INPUT_PULLDOWN);
    }

    void Press()
    {
      int keyState = digitalRead(keyPin);

      if (keyState == buttonTriggerState) {
        if (millis() - lastDebounceTime > debounceDelay) {
          Keyboard.press(131);
          Keyboard.press(176);
          Keyboard.releaseAll();
          Keyboard.press(131);
          Keyboard.press(176);
          Keyboard.releaseAll();
          Keyboard.press(131);
          Keyboard.press(176);
          Keyboard.releaseAll();
          lastDebounceTime = millis();
        }
        lastDebounceTime = millis();
      }
    }

    boolean Check()
    {
      int keyState = digitalRead(keyPin);

      if (keyState != lastButtonState) {
        lastDebounceTime = millis();
      }

      if ((millis() - lastDebounceTime) > debounceDelay) {
        if (keyState != buttonState) {
          buttonState = keyState;

          if (buttonState == HIGH) {
            modifierState = !modifierState;
            Keyboard.press(131);
            Keyboard.press(176);
            Keyboard.releaseAll();
            Keyboard.press(131);
            Keyboard.press(176);
            Keyboard.releaseAll();
            Keyboard.press(131);
            Keyboard.press(176);
            Keyboard.releaseAll();
          }
        }
      }
      lastButtonState = keyState;
      return modifierState;
    }
};

//-------
