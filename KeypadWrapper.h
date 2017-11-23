/*
  Pushing and holding any four buttons at the same time will trigger a new game.
*/

#ifndef KEYPADWRAPPER_H
#define KEYPADWRAPPER_H

#include "Keypad.h"

class KeypadWrapper {
  public:
    KeypadWrapper();
    KeypadWrapper(byte *, byte *);
    int pollKeypad();

  private:
    byte ROW_PINS[5] = {2, 3, 4, 5, 6};
    byte COL_PINS[5] = {7, 8, 9, 10, 11};
    char KEY_MAP [5][5] = {{'a', 'b', 'c', 'd', 'e'},
      {'f', 'g', 'h', 'i', 'j'},
      {'k', 'l', 'm', 'n', 'o'},
      {'p', 'q', 'r', 's', 't'},
      {'u', 'v', 'w', 'x', 'y'}
    };
    Keypad &kpd;
};


#endif

