/*
 * ============================================================
 * Project: Macro Keyboard (Browser Macros - 1x4)
 * Developer: Sean Conroy
 * Board: Seeed XIAO SAMD21
 * License: MIT
 * Description:
 *   - Button 1 opens GitHub (https://github.com)
 *   - Button 2 opens Google (https://google.com)
 *   - Button 3 opens YouTube (https://youtube.com)
 *   - Button 4 opens Twitch (https://twitch.tv)
 * ============================================================
 */

#include <Keyboard.h>

constexpr int URL_KEY_DELAY = 5;
constexpr int URL_COMMAND_DELAY = 100;

typedef void (*ButtonAction)();

struct Button {
  uint8_t pin;
  int currentState;
  int lastState;
  unsigned long lastDebounceTime;
  ButtonAction action;
};

void openUrl(const char *url) {
  const char *prefix = "https://";

  // Open new tab
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('t');
  delay(URL_COMMAND_DELAY);
  Keyboard.releaseAll();
  delay(URL_COMMAND_DELAY);

  // Focus browser address bar
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('l');
  delay(URL_COMMAND_DELAY);
  Keyboard.releaseAll();
  delay(URL_COMMAND_DELAY);

  // Type the URL prefix
  for (const char *p = prefix; *p; ++p) {
    Keyboard.press(*p);
    delay(URL_KEY_DELAY);
    Keyboard.release(*p);
    delay(URL_KEY_DELAY);
  }

  // Type the actual URL
  for (const char *p = url; *p; ++p) {
    Keyboard.press(*p);
    delay(URL_KEY_DELAY);
    Keyboard.release(*p);
    delay(URL_KEY_DELAY);
  }

  // Press Enter to go to the URL
  Keyboard.press(KEY_RETURN);
  delay(URL_COMMAND_DELAY);
  Keyboard.releaseAll();
}

void openGithub() {
  openUrl("github.com");
}

void openGoogle() {
  openUrl("google.com");
}

void openYoutube() {
  openUrl("youtube.com");
}

void openTwitch() {
  openUrl("twitch.tv");
}

Button buttons[] = {
  { 0, HIGH, HIGH, 0, openGithub },
  { 1, HIGH, HIGH, 0, openGoogle },
  { 2, HIGH, HIGH, 0, openYoutube },
  { 3, HIGH, HIGH, 0, openTwitch },
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
