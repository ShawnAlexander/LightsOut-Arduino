#include "Board.h"

Board::Board() {

}

void Board::randomize() {

}

bool Board::isWin() {
	for(uint8_t row = 0; row < ROWS; ++row) {
		for(uint8_t col = 0; col < COLS; ++col) {
			if(GAME_BOARD[row][col]) {
				return false;
			}
		}
	}
	return true;
}

/* Corresponds to XOR.
   +|0|1|
   0|0|1|
   1|1|0|
*/
bool Board::add(bool p1, bool p2) {

	if(p1 && !p2 || !p1 && p2) {
		return true;
	}
	else {
		return false;
	}
}

/* Corresponds to AND.
   x|0|1|
   0|0|0|
   1|0|1|
*/
bool Board::multiply(bool p1, bool p2) {
	if(p1 && p2) {
		return true;
	}
	else{
		return false;
	}
}

bool Board::dot(bool g1[ROWS][COLS], bool g2[ROWS][COLS]) {
	bool temp[ROWS][COLS] = {{false, false, false, false, false},
	           			  {false, false, false, false, false},
	           			  {false, false, false, false, false},
	           			  {false, false, false, false, false},
	           			  {false, false, false, false, false}};
    bool result = true;
    for(uint8_t i = 0; i < ROWS; ++i) {
    	for(uint8_t j = 0; j < COLS; ++j) {
    		temp[i][j] = multiply(g1[i][j], g2[i][j]);
    	}
    }
    result = temp[0][0];
    for(uint8_t i = 0; i < ROWS; ++i) {
    	for(uint8_t j = 0; j < COLS; ++j) {
    		result = add(result, temp[i][j]);
    	}
    }
    return result;
}

/* True if board is solvable, false if not. */
bool Board::isSolvable() {
	bool s1, s2 = false;

	s1 = dot(GAME_BOARD, SOLVABLE1);
	s2 = dot(GAME_BOARD, SOLVABLE2);

	if(!s1 && !s2) {
		return true;
	}
	else {
		return false;
	}
}


/* Row & Col are 0-indexed */
void Board::set(uint8_t row, uint8_t col, bool state) {
	GAME_BOARD[row][col] = state;
}


void Board::set(uint8_t gridNum, bool state) {

	uint8_t row = 0;
	uint8_t col = 0;

	if(gridNum <= 5) {
		row = 0;
	}
	else if(gridNum <= 10) {
		row = 1;
	}
	else if(gridNum <= 15) {
		row = 2;
	}
	else if(gridNum <= 20) {
		row = 3;
	}
	else {
		row = 4;
	}

	if(gridNum % 5 == 1) {
		col = 0;
	}
	else if(gridNum % 5 == 2) {
		col = 1;
	}
	else if(gridNum % 5 == 3) {
		col = 2;
	}
	else if(gridNum % 5 == 4) {
		col = 3;
	}
	else {
		col = 4;
	}

	set(row, col, state);
}

/* Toggles square and adjacent squares */
/* Parameters are 0-indexed */
void Board::toggle(uint8_t row, uint8_t col) {
	/* Error checking for valid range? */

	GAME_BOARD[row][col] = !GAME_BOARD[row][col];

	/* North adjacent */
	if(row > 0) {
		GAME_BOARD[row - 1][col] = !GAME_BOARD[row - 1][col];
	}

	/* East adjacent  */
	if(col < 4) {
		GAME_BOARD[row][col + 1] = !GAME_BOARD[row][col + 1];
	}

	/* South adjacent */
	if(row < 4) {
		GAME_BOARD[row + 1][col] = !GAME_BOARD[row + 1][col];
	}
	
	/* West adjacent */
	if(col > 0) {
		GAME_BOARD[row][col - 1] = !GAME_BOARD[row][col - 1];
	}
}

/* Toggles square and adjacent squares */
void Board::toggle(uint8_t gridNum) {
	/* Error checking for valid range? */

	uint8_t row = 0;
	uint8_t col = 0;

	if(gridNum <= 5) {
		row = 0;
	}
	else if(gridNum <= 10) {
		row = 1;
	}
	else if(gridNum <= 15) {
		row = 2;
	}
	else if(gridNum <= 20) {
		row = 3;
	}
	else {
		row = 4;
	}

	if(gridNum % 5 == 1) {
		col = 0;
	}
	else if(gridNum % 5 == 2) {
		col = 1;
	}
	else if(gridNum % 5 == 3) {
		col = 2;
	}
	else if(gridNum % 5 == 4) {
		col = 3;
	}
	else {
		col = 4;
	}

	toggle(row, col);
}
