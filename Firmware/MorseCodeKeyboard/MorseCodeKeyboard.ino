/*
 * ============================================================
 * Project: Macro Keyboard (Morse Code Keyboard - 1x1)
 * Developer: Sean Conroy
 * Board: Seeed XIAO SAMD21
 * License: MIT
 * Description:
 *   - Single button for Morse input:
 *       - Short press types dot (.)
 *       - Long press types dash (-)
 *   - After a pause, accumulated Morse code is decoded and typed
 * ============================================================
 */

#include <Keyboard.h>

const uint8_t buttonPin = 0;
const unsigned long debounceDelay = 50;
const unsigned long longPressThreshold = 250;
const unsigned long decodeDelay = 1000;

String morseBuffer = "";

int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;

unsigned long buttonPressTime = 0;
unsigned long lastInputTime = 0;
bool buttonPressed = false;

void typeChar(char c) {
  Keyboard.press(c);
  delay(5);
  Keyboard.release(c);
  delay(5);
}

char decodeMorse(const String &code) {
  if (code == ".-") return 'A';
  if (code == "-...") return 'B';
  if (code == "-.-.") return 'C';
  if (code == "-..") return 'D';
  if (code == ".") return 'E';
  if (code == "..-.") return 'F';
  if (code == "--.") return 'G';
  if (code == "....") return 'H';
  if (code == "..") return 'I';
  if (code == ".---") return 'J';
  if (code == "-.-") return 'K';
  if (code == ".-..") return 'L';
  if (code == "--") return 'M';
  if (code == "-.") return 'N';
  if (code == "---") return 'O';
  if (code == ".--.") return 'P';
  if (code == "--.-") return 'Q';
  if (code == ".-.") return 'R';
  if (code == "...") return 'S';
  if (code == "-") return 'T';
  if (code == "..-") return 'U';
  if (code == "...-") return 'V';
  if (code == ".--") return 'W';
  if (code == "-..-") return 'X';
  if (code == "-.--") return 'Y';
  if (code == "--..") return 'Z';
  return '?';
}

void decodeAndType() {
  if (morseBuffer.length() > 0) {
    char decoded = decodeMorse(morseBuffer);
    typeChar(decoded);
    morseBuffer = "";
  }
}

void setup() {
  Keyboard.begin();
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        // Button pressed down
        buttonPressTime = millis();
        buttonPressed = true;
      } else {
        // Button released
        if (buttonPressed) {
          unsigned long pressDuration = millis() - buttonPressTime;

          if (pressDuration < longPressThreshold) {
            morseBuffer += '.';
          } else {
            morseBuffer += '-';
          }

          lastInputTime = millis();
          buttonPressed = false;
        }
      }
    }
  }

  lastButtonState = reading;
  
  if (morseBuffer.length() > 0 && (millis() - lastInputTime) > decodeDelay) {
    decodeAndType();
  }
}
