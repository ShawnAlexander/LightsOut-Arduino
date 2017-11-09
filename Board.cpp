#include "Board.h"
/*
Board::Board() {

}*/

void Board::randomize() {
	/* Bernoulli - 50% chance for each */
	std::default_random_engine generator;
	std::bernoulli_distribution distribution(0.5);

	for(byte i = 1; i < (byte) 26; ++i) {
		if(distribution(generator)){
			set(i, true);
		}
	}

	//long seed = std::chrono::system_clock::now().time_since_epoch().count();
}

bool Board::isWin() {
	for(byte row = 0; row < ROWS; ++row) {
		for(byte col = 0; col < COLS; ++col) {
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

bool Board::dot(bool (&g1)[ROWS][COLS], const bool (&g2)[ROWS][COLS]) {
	bool temp[ROWS][COLS] = {{false, false, false, false, false},
	           			  {false, false, false, false, false},
	           			  {false, false, false, false, false},
	           			  {false, false, false, false, false},
	           			  {false, false, false, false, false}};
    bool result = true;
    for(byte i = 0; i < ROWS; ++i) {
    	for(byte j = 0; j < COLS; ++j) {
    		temp[i][j] = multiply(g1[i][j], g2[i][j]);
    	}
    }
    result = temp[0][0];
    for(byte i = 0; i < ROWS; ++i) {
    	for(byte j = 0; j < COLS; ++j) {
    		result = add(result, temp[i][j]);
    	}
    }
    return result;
}


/* True if board is solvable, false if not. */
bool Board::isSolvable() {
	bool s1 = false;
	bool s2 = false;

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
void Board::set(byte row, byte col, bool state) {
	GAME_BOARD[row][col] = state;
}


void Board::set(byte gridNum, bool state) {

	byte row = 0;
	byte col = 0;

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
void Board::toggle(byte row, byte col) {
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
void Board::toggle(byte gridNum) {
	/* Error checking for valid range? */

	byte row = 0;
	byte col = 0;

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

void Board::printConsole() {
	for(byte i = 0; i < ROWS; ++i){
		for(byte j = 0; j < COLS; ++j){
			std::cout << "|";
			if(GAME_BOARD[i][j]){
				std::cout << " ON";
			}else {
				std::cout << "OFF";
			}
		}
		std::cout << "|" << std::endl;
	}
}