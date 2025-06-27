/*
 * ============================================================
 * Project: Macro Keyboard (Productivity Macros 1x4)
 * Developer: Sean Conroy
 * Board: Seeed XIAO SAMD21
 * License: MIT
 * Description:
 *   - 
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

void pressCtrlKey(char key) {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(key);
  delay(100);
  Keyboard.release(key);
  Keyboard.release(KEY_LEFT_CTRL);
}

void pressCtrlShiftKey(char key) {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(key);
  delay(100);
  Keyboard.release(key);
  Keyboard.release(KEY_LEFT_SHIFT);
  Keyboard.release(KEY_LEFT_CTRL);
}

void saveDocument() {
  // Save document shortcut: Ctrl + S (Cmd + S on Mac)
  pressCtrlKey('s');
}

void copyText() {
  // Copy shortcut: Ctrl + C (Cmd + C on Mac)
  pressCtrlKey('c');
}

void pasteText() {
  // Paste shortcut: Ctrl + V (Cmd + V on Mac)
  pressCtrlKey('v');
}

void undoAction() {
  // Undo shortcut: Ctrl + Z (Cmd + Z on Mac)
  pressCtrlKey('z');
}

Button buttons[] = {
  {1, HIGH, HIGH, 0, saveDocument},
  {2, HIGH, HIGH, 0, copyText},
  {3, HIGH, HIGH, 0, pasteText},
  {4, HIGH, HIGH, 0, undoAction},
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
