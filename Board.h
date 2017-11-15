/*
	FALSE = OFF	 0
	TRUE = ON	 1

	| 0| 1| 2| 3| 4|
	| 5| 6| 7| 8| 9|
	|10|11|12|13|14|
	|15|16|17|18|19|
	|20|21|22|23|24|

*/
#ifndef BOARD_LIGHTSOUT_H
#define BOARD_LIGHTSOUT_H

#include <iostream>
#include <cstdint>
#include <random>
#include <chrono>

typedef uint8_t byte;

class Board {
	public:
		static const byte FIVE = 5;
        static const byte FOUR = 4;
        static const byte ZERO = 0;
        static const byte TWENTY = 20;
        static const byte ONE = 1;
        static const byte RC = 25;
		void randomize(int);
		void set(byte, bool);	/* Sets 0-indexed grid number to true/false without toggling adjacent squares */
		void toggle(byte);	/* Toggle by 0-indexed grid number */
	    bool isWin();
	    bool isSolvable();
	    bool add(bool, bool);
	    bool multiply(bool, bool);
        void mvm(const bool(&)[RC][RC], bool(&)[RC], bool(&)[RC]);
        bool dot(const bool(&)[RC], bool(&)[RC]);
        void reset();

	    void printConsole();
        void printConsole(bool(&)[RC]);
	    //void printSerial();


		bool GAME_BOARD[RC]= {false, false, false, false, false,
                            false, false, false, false, false,
                            false, false, false, false, false,
                            false, false, false, false, false,
                            false, false, false, false, false};


        /* If board is orthogonal to these, then it is solvable. */
        /**/
		const bool SOLVABLE1[RC] = {false, true, true, true, false,
                                    true, false, true, false, true,
                                    true, true, false, true, true,
                                    true, false, true, false, true,
                                    false, true, true, true, false};

  		const bool SOLVABLE2[RC] = {true, false, true, false, true,
                                    true, false, true, false, true,
                                    false, false, false, false, false,
                                    true, false, true, false, true,
                                    true, false, true, false, true};
        /*  */
        const bool A[RC][RC] = {{true,true,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
                                  {true,true,true,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
                                  {false,true,true,true,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
                                  {false,false,true,true,true,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
                                  {false,false,false,true,true,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
                                  {true,false,false,false,false,true,true,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
                                  {false,true,false,false,false,true,true,true,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false},
                                  {false,false,true,false,false,false,true,true,true,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false},
                                  {false,false,false,true,false,false,false,true,true,true,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false},
                                  {false,false,false,false,true,false,false,false,true,true,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false},
                                  {false,false,false,false,false,true,false,false,false,false,true,true,false,false,false,true,false,false,false,false,false,false,false,false,false},
                                  {false,false,false,false,false,false,true,false,false,false,true,true,true,false,false,false,true,false,false,false,false,false,false,false,false},
                                  {false,false,false,false,false,false,false,true,false,false,false,true,true,true,false,false,false,true,false,false,false,false,false,false,false},
                                  {false,false,false,false,false,false,false,false,true,false,false,false,true,true,true,false,false,false,true,false,false,false,false,false,false},
                                  {false,false,false,false,false,false,false,false,false,true,false,false,false,true,true,false,false,false,false,true,false,false,false,false,false},
                                  {false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,true,true,false,false,false,true,false,false,false,false},
                                  {false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,true,true,true,false,false,false,true,false,false,false},
                                  {false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,true,true,true,false,false,false,true,false,false},
                                  {false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,true,true,true,false,false,false,true,false},
                                  {false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,true,true,false,false,false,false,true},
                                  {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,true,true,false,false,false},
                                  {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,true,true,true,false,false},
                                  {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,true,true,true,false},
                                  {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,true,true,true},
                                  {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,true,true}};
        /* Product of the elementary matrices that make up the row operations for Gaussian elimination. */
        const bool R[RC][RC] = {{false,false,false,false,false,true,false,false,false,false,true,true,false,false,false,true,false,true,false,false,false,true,true,true,false},
                                      {false,false,false,false,false,false,true,false,false,false,true,true,true,false,false,false,false,false,true,false,true,true,false,true,true},
                                      {false,false,false,true,false,false,false,false,true,true,false,false,true,true,false,false,true,false,true,false,true,true,true,false,true},
                                      {false,false,true,true,true,false,true,false,false,false,true,true,false,true,true,false,true,false,false,false,false,false,true,true,true},
                                      {false,false,false,true,true,false,false,true,false,true,false,true,true,true,false,true,false,false,false,false,true,false,true,true,false},
                                      {false,false,true,false,true,false,true,true,false,true,false,false,true,false,false,false,false,false,true,true,false,false,false,false,false},
                                      {false,false,true,false,false,false,true,true,true,false,true,true,false,false,true,false,true,false,false,true,false,false,true,true,false},
                                      {false,false,false,false,true,false,false,false,true,true,false,false,false,false,true,false,false,false,false,false,false,false,false,false,true},
                                      {false,false,true,false,false,false,true,true,true,false,true,false,false,true,true,true,false,false,true,false,false,true,true,false,false},
                                      {false,false,true,false,true,false,true,true,false,true,true,false,true,false,true,true,true,false,false,false,true,false,false,false,true},
                                      {false,false,false,false,true,false,false,false,true,true,false,false,true,false,true,true,true,true,true,false,false,true,false,false,false},
                                      {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,true,true,true,false,false},
                                      {false,false,false,true,true,false,false,true,false,false,false,true,true,false,true,true,false,false,false,true,true,false,true,true,false},
                                      {false,false,true,true,true,false,true,false,true,false,true,true,true,false,false,false,false,false,true,false,true,true,false,true,true},
                                      {false,false,false,true,false,false,false,true,true,true,false,true,false,false,false,true,true,false,true,false,false,true,false,true,true},
                                      {false,false,true,false,false,false,true,true,true,false,true,false,false,false,true,true,false,true,false,true,true,false,true,false,false},
                                      {false,false,true,true,false,false,true,false,false,true,true,true,false,false,true,false,true,true,true,false,false,false,true,false,false},
                                      {false,false,true,false,true,false,true,true,false,true,true,false,true,false,false,true,true,false,true,true,true,false,false,false,false},
                                      {false,false,false,true,false,false,false,true,true,true,false,true,false,false,false,true,true,false,true,true,false,true,false,true,false},
                                      {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true},
                                      {false,false,false,true,true,false,false,true,false,false,false,true,true,false,true,true,false,true,false,true,true,true,false,false,false},
                                      {false,false,true,true,true,false,true,false,true,false,true,true,true,false,false,false,false,false,false,false,true,true,true,false,false},
                                      {false,false,false,true,false,false,false,true,true,true,false,true,false,false,false,true,true,false,true,true,false,true,false,false,false},
                                      {true,false,true,false,true,true,false,true,false,true,false,false,false,false,false,true,false,true,false,true,true,false,true,false,true},
                                      {false,true,true,true,false,true,false,true,false,true,true,true,false,true,true,true,false,true,false,true,false,true,true,true,false}};
        /*  */
        const bool E[RC][RC] = {{true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true},
                                      {false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false},
                                      {false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true},
                                      {false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false},
                                      {false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true},
                                      {false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true},
                                      {false,false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
                                      {false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true},
                                      {false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
                                      {false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true},
                                      {false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,true,false},
                                      {false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,true,false},
                                      {false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false},
                                      {false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false,false,true,false},
                                      {false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false,true,false},
                                      {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,true,true},
                                      {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false},
                                      {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,true,true},
                                      {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false,false,false},
                                      {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,true,true},
                                      {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,true},
                                      {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,true,false},
                                      {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,true,true},
                                      {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
                                      {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false}};
};
#endif
