#include "KeypadWrapper.h"

KeypadWrapper::KeypadWrapper() {

}

KeypadWrapper::KeypadWrapper(int *rpins, int *cpins) {
    for (int i = 0; i < 5; ++i) {
        ROW_PINS[i] = rpins[i];
        COL_PINS[i] = cpins[i];
    }
    kpd = Keypad();
}

int KeypadWrapper::pollKeypad() {
    char key = kpd.getKey();
    if(key) {
        switch(key){
            case 1:

        }
    }
}