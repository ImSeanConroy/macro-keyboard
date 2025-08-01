/*
 * ============================================================
 * Project: Macro Keyboard (Git Macros - 1x4)
 * Developer: Sean Conroy
 * Board: Seeed XIAO SAMD21
 * License: MIT
 * Description:
 *   - Button 1 types "git pull" to update local repository.
 *   - Button 2 types "git status" to show working tree state.
 *   - Button 3 types "git commit -m """ to begin a commit message.
 *   - Button 4 types "git push" to upload changes to remote.
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

void typeString(const char *msg) {
  for (const char *p = msg; *p; p++) {
    Keyboard.press(*p);
    delay(5);
    Keyboard.release(*p);
    delay(5);
  }
}

void gitPull() {
  typeString("git pull");
}

void gitStatus() {
  typeString("git status");
}

void gitCommit() {
  typeString("git commit -m \"\"");
}

void gitPush() {
  typeString("git push");
}

Button buttons[] = {
  {0, HIGH, HIGH, 0, gitPull},
  {1, HIGH, HIGH, 0, gitStatus},
  {2, HIGH, HIGH, 0, gitCommit},
  {3, HIGH, HIGH, 0, gitPush},
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
