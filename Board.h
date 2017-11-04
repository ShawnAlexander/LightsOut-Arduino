/*
	FALSE = OFF
	TRUE = ON

	| 1| 2| 3| 4| 5|
	| 6| 7| 8| 9|10|
	|11|12|13|14|15|
	|16|17|18|19|20|
	|21|22|23|24|25|

*/
#ifndef BOARD_LO_H
#define BOARD_LO_H


class Board {
	public:
		const uint8_t ROWS = 5;
		const uint8_t COLS = 5;

		Board();
		int randomize();
		void toggle(uint8_t, uint8_t);	/* Toggle by 0-indexed row and col */
		void toggle(uint8_t);	/* Toggle by 1-indexed grid number */
        bool isWin();



	private:
		bool GAME_BOARD[5][5] = {{false, false, false, false, false},
                           		{false, false, false, false, false},
                           		{false, false, false, false, false},
                           		{false, false, false, false, false},
                           		{false, false, false, false, false}};


};


#endif