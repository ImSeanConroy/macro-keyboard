/*
 * ============================================================
 * Project: Macro Keyboard (Webex Macros 1x2)
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

void muteUnmute() {
  // Webex mute/unmute shortcut: Ctrl + M (Cmd + M on Mac)
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('m');
  delay(100);
  Keyboard.release('m');
  Keyboard.release(KEY_LEFT_CTRL);
}

void startStopVideo() {
  // Webex start/stop video shortcut: Ctrl + Shift + V
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('v');
  delay(100);
  Keyboard.release('v');
  Keyboard.release(KEY_LEFT_SHIFT);
  Keyboard.release(KEY_LEFT_CTRL);
}

Button buttons[] = {
  {1, HIGH, HIGH, 0, muteUnmute},
  {2, HIGH, HIGH, 0, startStopVideo},
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
