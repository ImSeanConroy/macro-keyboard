/*
 * ============================================================
 * Project: Macro Keyboard (Binary Keyboard - 1x2)
 * Developer: Sean Conroy
 * Board: Seeed XIAO SAMD21
 * License: MIT
 * Description:
 *   - Button 1 types binary 0
 *   - Button 2 types binary 1
 *   - After 8 bits are entered, converts to ASCII character and types it
 *   - Example: 01001000 01100101 01101100 01101100 01101111 00101100 00100000 01010111 01101111 01110010 01101100 01100100 00100001 00111111
 * ============================================================
 */

#include <Keyboard.h>

typedef void (*ButtonAction)();

struct Button {
  uint8_t pin;
  int currentState;
  int lastState;
  unsigned long lastDebounceTime;
  ButtonAction action;
};

String binaryBuffer = "";  // Store '0' and '1' presses

void typeChar(char c) {
  Keyboard.press(c);
  delay(5);
  Keyboard.release(c);
  delay(5);
}

void typeZero() {
  binaryBuffer += '0';
  checkBuffer();
}

void typeOne() {
  binaryBuffer += '1';
  checkBuffer();
}

void checkBuffer() {
  if (binaryBuffer.length() == 8) {
    // Convert binary string to char
    char c = (char) strtol(binaryBuffer.c_str(), nullptr, 2);

    // Type the ASCII char
    typeChar(c);

    // Clear buffer for next char
    binaryBuffer = "";
  }
}

Button buttons[] = {
  {0, HIGH, HIGH, 0, typeZero},
  {1, HIGH, HIGH, 0, typeOne},
};

const int NUM_BUTTONS = sizeof(buttons) / sizeof(buttons[0]);
const unsigned long DEBOUNCE_DELAY = 50;

void setup() {
  Keyboard.begin();
  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(buttons[i].pin, INPUT_PULLUP);
  }
}

void handleButton(Button &btn) {
  int reading = digitalRead(btn.pin);

  if (reading != btn.lastState) {
    btn.lastDebounceTime = millis();
  }

  if ((millis() - btn.lastDebounceTime) > DEBOUNCE_DELAY) {
    if (reading != btn.currentState) {
      btn.currentState = reading;

      if (btn.currentState == LOW && btn.action != nullptr) {
        btn.action();
      }
    }
  }

  btn.lastState = reading;
}

void loop() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    handleButton(buttons[i]);
  }
}
