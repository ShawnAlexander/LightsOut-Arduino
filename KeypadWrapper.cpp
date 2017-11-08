#include "KeypadWrapper.h"

KeypadWrapper::KeypadWrapper() {
    kpd = Keypad(KEY_MAP, ROW_PINS, COL_PINS, 5, 5);
}

KeypadWrapper::KeypadWrapper(byte *rpins, byte *cpins) {
    for (uint8_t i = 0; i < 5; ++i) {
        ROW_PINS[i] = rpins[i];
        COL_PINS[i] = cpins[i];
    }
    kpd = Keypad(KEY_MAP, ROW_PINS, COL_PINS, 5, 5);
}

int KeypadWrapper::pollKeypad() {
    char key = kpd.getKey();
    if(key) {
        if(key == 1){

        }
        else if(key == 2){

        }
        else if(key == 3){

        }
        else if(key == 4){

        }
        else if(key == 5){

        }
        else if(key == 6){

        }
        else if(key == 7){

        }
        else if(key == 8){

        }
        else if(key == 9){

        }
        else if(key == 10){

        }
        else if(key == 11){

        }
        else if(key == 12){

        }
        else if(key == 13){

        }
        else if(key == 14){

        }
        else if(key == 15){

        }
        else if(key == 16){

        }
        else if(key == 17){

        }
        else if(key == 18){

        }
        else if(key == 19){

        }
        else if(key == 20){

        }
        else if(key == 21){
            
        }
        else if(key == 22){

        }
        else if(key == 23){

        }
        else if(key == 24){

        }
        else if(key == 25){

        }
        else {
            /* Error */
        }
    }
}
