#include "KeypadWrapper.h"

KeypadWrapper::KeypadWrapper() {
  kpd = Keypad(makeKeymap(KEY_MAP), ROW_PINS, COL_PINS, 5, 5);
  kpd.setDebounceTime(100);
}

KeypadWrapper::KeypadWrapper(byte *rpins, byte *cpins) {
  for (byte i = 0; i < 5; ++i) {
    ROW_PINS[i] = rpins[i];
    COL_PINS[i] = cpins[i];
  }
  kpd = Keypad(makeKeymap(KEY_MAP), ROW_PINS, COL_PINS, 5, 5);
  kpd.setDebounceTime(100);
}

int KeypadWrapper::pollKeypad() {
  if (kpd.getKeys()) {
    int count = 0;
    for (int i = 0; i < LIST_MAX; i++) {
      if (kpd.key[i].kstate == HOLD) {
        ++count;
        if (count == 4) {
          return -1;
        }
      }
      else if (kpd.key[i].kstate == PRESSED) {
        if (kpd.key[i].kchar == 'a') {
          return 0;
        }
        else if (kpd.key[i].kchar == 'b') {
          return 1;
        }
        else if (kpd.key[i].kchar == 'c') {
          return 2;
        }
        else if (kpd.key[i].kchar == 'd') {
          return 3;
        }
        else if (kpd.key[i].kchar == 'e') {
          return 4;
        }
        else if (kpd.key[i].kchar == 'f') {
          return 5;
        }
        else if (kpd.key[i].kchar == 'g') {
          return 6;
        }
        else if (kpd.key[i].kchar == 'h') {
          return 7;
        }
        else if (kpd.key[i].kchar == 'i') {
          return 8;
        }
        else if (kpd.key[i].kchar == 'j') {
          return 9;
        }
        else if (kpd.key[i].kchar == 'k') {
          return 10;
        }
        else if (kpd.key[i].kchar == 'l') {
          return 11;
        }
        else if (kpd.key[i].kchar == 'm') {
          return 12;
        }
        else if (kpd.key[i].kchar == 'n') {
          return 13;
        }
        else if (kpd.key[i].kchar == 'o') {
          return 14;
        }
        else if (kpd.key[i].kchar == 'p') {
          return 15;
        }
        else if (kpd.key[i].kchar == 'q') {
          return 16;
        }
        else if (kpd.key[i].kchar == 'r') {
          return 17;
        }
        else if (kpd.key[i].kchar == 's') {
          return 18;
        }
        else if (kpd.key[i].kchar == 't') {
          return 19;
        }
        else if (kpd.key[i].kchar == 'u') {
          return 20;
        }
        else if (kpd.key[i].kchar == 'v') {
          return 21;
        }
        else if (kpd.key[i].kchar == 'w') {
          return 22;
        }
        else if (kpd.key[i].kchar == 'x') {
          return 23;
        }
        else if (kpd.key[i].kchar == 'y') {
          return 24;
        }
      }
    }
  }
  else {
    return 128;
  }
}

