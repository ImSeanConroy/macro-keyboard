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
    delay(10);
    Keyboard.release(*p);
    delay(10);
  }
}

void actionOne() {
  typeString("git pull");
}

void actionTwo() {
  typeString("git commit -m ''");
}

void actionThree() {
  typeString("git status");
}

void actionFour() {
  typeString("git push");
}

Button buttons[] = {
  {1, HIGH, HIGH, 0, actionOne},
  {2, HIGH, HIGH, 0, actionTwo},
  {3, HIGH, HIGH, 0, actionThree},
  {4, HIGH, HIGH, 0, actionFour},
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
