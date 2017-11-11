/*
	FALSE = OFF	 0
	TRUE = ON	 1

	| 1| 2| 3| 4| 5|
	| 6| 7| 8| 9|10|
	|11|12|13|14|15|
	|16|17|18|19|20|
	|21|22|23|24|25|

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
		static const byte ROWS = 5;
		static const byte COLS = 5;
		//Board();
		void randomize(int);
		void set(byte, bool);	/* Sets 1-indexed grid number to true/false without toggling adjacent squares */
		void set(byte, byte, bool); /* Sets 0-indexed row & col to true/false without toggling adjacent squares */
		void toggle(byte, byte);	/* Toggle by 0-indexed row and col */
		void toggle(byte);	/* Toggle by 1-indexed grid number */
	    bool isWin();
	    bool isSolvable();
	    bool add(bool, bool);
	    bool multiply(bool, bool);
		bool dot(bool(&)[ROWS][COLS], const bool(&)[ROWS][COLS]);
        void reset();

	    void printConsole();
	    void printSerial();


		bool GAME_BOARD[ROWS][COLS] = {{false, false, false, false, false},
	                           		{false, false, false, false, false},
	                           		{false, false, false, false, false},
	                           		{false, false, false, false, false},
	                           		{false, false, false, false, false}};


        /* If board is orthogonal to these, then it is solvable. */
		const bool SOLVABLE1[ROWS][COLS] = {{false, true, true, true, false},
	                       				  {true, false, true, false, true},
	                           		      {true, true, false, true, true},
	                           			  {true, false, true, false, true},
	                           			  {false, true, true, true, false}};

  		const bool SOLVABLE2[ROWS][COLS] = {{true, false, true, false, true},
	                       			     {true, false, true, false, true},
	                           			 {false, false, false, false, false},
	                           		 	 {true, false, true, false, true},
	                           			 {true, false, true, false, true}};

};
#endif
