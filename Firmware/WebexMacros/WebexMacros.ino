/*
 * ============================================================
 * Project: Macro Keyboard (Webex Macros - 1x2)
 * Developer: Sean Conroy
 * Board: Seeed XIAO SAMD21
 * License: MIT
 * Description:
 *   - Button 1 toggles mute/unmute in Webex (Cmd + Shift + M).
 *   - Button 2 toggles video on/off in Webex (Ctrl + Shift + V).
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

void toggleMute() {
  // Webex mute/unmute shortcut: Cmd + Shift + M
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('M');
  delay(100);
  Keyboard.releaseAll();
  delay(100);
}

void toggleVideo() {
  // Webex start/stop video shortcut: Ctrl + Shift + V
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('V');
  delay(100);
  Keyboard.releaseAll();
  delay(100);
}

Button buttons[] = {
  {0, HIGH, HIGH, 0, toggleMute},
  {1, HIGH, HIGH, 0, toggleVideo},
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
