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


class Board {
	public:
		const uint8_t ROWS = 5;
		const uint8_t COLS = 5;

		Board();
		void randomize();
		void set(uint8_t, bool);	/* Sets 1-indexed grid number to true/false without toggling adjacent squares */
		void set(uint8_t, uint8_t, bool); /* Sets 0-indexed row & col to true/false without toggling adjacent squares */
		void toggle(uint8_t, uint8_t);	/* Toggle by 0-indexed row and col */
		void toggle(uint8_t);	/* Toggle by 1-indexed grid number */
        bool isWin();
        bool isSolvable();
        bool add(bool, bool);
        bool multiply(bool, bool);
        bool dot(bool[ROWS][COLS], bool[ROWS][COLS]);


	private:
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