/*
 *
 * This class will hold a KeypadWrapper object and handle all I2C communication with the slave.
 */

#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <Wire.h>

class MasterController {
    public:
        MasterController();
        int sync();
        int randomize();
        bool isWin();

    private:
        bool STATE_MATRIX[5][5] = {{false, false, false, false, false},
                                   {false, false, false, false, false},
                                   {false, false, false, false, false},
                                   {false, false, false, false, false},
                                   {false, false, false, false, false}};



};


#endif //MASTERCONTROLLER_H
