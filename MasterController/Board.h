/*
  FALSE = OFF  0
  TRUE = ON  1

  | 0| 1| 2| 3| 4|
  | 5| 6| 7| 8| 9|
  |10|11|12|13|14|
  |15|16|17|18|19|
  |20|21|22|23|24|

*/
#ifndef BOARD_LIGHTSOUT_H
#define BOARD_LIGHTSOUT_H

#include "Arduino.h"


    
class Board {
  public:
    static const byte FIVE = 5;
    static const byte FOUR = 4;
    static const byte ZERO = 0;
    static const byte TWENTY = 20;
    static const byte ONE = 1;
    static const byte RC = 25;

    void randomize();
    int randto(int);
    void shuffle(int *, int);
    unsigned long nrand25(int);
    String solution;

    void set(byte, bool); /* Sets 0-indexed grid number to true/false without toggling adjacent squares */
    void toggle(byte);  /* Toggle by 0-indexed grid number */
    bool isWin();
    bool isSolvable();
    void reset();
    void solve();
    void setsolution();

    bool add(bool, bool);
    bool multiply(bool, bool);
    void mvm(const bool(&)[RC][RC], bool(&)[RC]);
    void mvm(const bool(&)[RC][RC], bool(&)[RC], bool(&)[RC]);
    bool dot(const bool(&)[RC], bool(&)[RC]);

    void printSerial();
    void bin(unsigned long);

    bool GAME_BOARD[RC] = {false, false, false, false, false,
                           false, false, false, false, false,
                           false, false, false, false, false,
                           false, false, false, false, false,
                           false, false, false, false, false
                          };
                          
    bool INITIAL_BOARD[RC] = {false, false, false, false, false,
                           false, false, false, false, false,
                           false, false, false, false, false,
                           false, false, false, false, false,
                           false, false, false, false, false
                          };
};
#endif






