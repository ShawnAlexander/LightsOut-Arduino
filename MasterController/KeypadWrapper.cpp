//#include "KeypadWrapper.h"
//
//KeypadWrapper::KeypadWrapper() {
//  _kpd = Keypad(makeKeymap(KEY_MAP), ROW_PINS, COL_PINS, 5, 5);
//  _kpd.setDebounceTime(100);
//}
//
//KeypadWrapper::KeypadWrapper(byte *rpins, byte *cpins) {
//  for (byte i = 0; i < 5; ++i) {
//    ROW_PINS[i] = rpins[i];
//    COL_PINS[i] = cpins[i];
//  }
//  _kpd = Keypad(makeKeymap(KEY_MAP), ROW_PINS, COL_PINS, 5, 5);
//  _kpd.setDebounceTime(100);
//}
//
//int KeypadWrapper::pollKeypad() {
//  if (_kpd.getKeys()) {
//    int count = 0;
//    for (int i = 0; i < LIST_MAX; i++) {
//      if (_kpd.key[i].kstate == HOLD) {
//        ++count;
//        if (count == 4) return -1;
//      }
//      else if (_kpd.key[i].kstate == PRESSED) return _kpd.key[i].kchar;
//    }
//  }
//  else return 128;
//}

