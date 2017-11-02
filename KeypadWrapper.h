/*
 *
 *
 */

#ifndef KEYPADWRAPPER_H
#define KEYPADWRAPPER_H

#include "Keypad.h"

class KeypadWrapper {
    public:
        KeypadWrapper();
        KeypadWrapper(int *row_pins, int *col_pins);
        int pollKeypad();

    private:
        int ROW_PINS[5] = {2, 3, 4, 5, 6};
        int COL_PINS[5] = {7, 8, 9, 10, 11};
        const char KEY_MAP [5][5] = {{1, 2, 3, 4, 5},
                                     {6, 7, 8, 9, 10},
                                     {11, 12, 13, 14, 15},
                                     {16, 17, 18, 19, 20},
                                     {21, 22, 23, 24, 25}};
        Keypad kpd;

};


#endif //KEYPADWRAPPER_H
