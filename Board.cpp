#include "Board.h"

Board::Board() {

}

int Board::randomize() {

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