#include "KeypadWrapper.h"

KeypadWrapper::KeypadWrapper() {
    kpd = Keypad(KEY_MAP, ROW_PINS, COL_PINS, 5, 5);
}

KeypadWrapper::KeypadWrapper(uint8_t *rpins, uint8_t *cpins) {
    for (uint8_t i = 0; i < 5; ++i) {
        ROW_PINS[i] = rpins[i];
        COL_PINS[i] = cpins[i];
    }
    kpd = Keypad(KEY_MAP, ROW_PINS, COL_PINS, 5, 5);
}

int KeypadWrapper::pollKeypad() {
    char key = kpd.getKey();
    if(key) {
        switch(key){
            case 1:

        }
    }
}