#include "Board.h"

void Board::randomize(int choice) {
	/* Bernoulli - 50% chance for each */
    std::default_random_engine generator;
    if(choice == 1) {
        std::bernoulli_distribution distribution(0.5);
        for (byte i = 0; i < (byte) 25; ++i) {
            if (distribution(generator)) {
                set(i, true);
            }
        }
    }
    /* Generates rounds number of ON lights. */
    else if(choice == 2) {
        std::uniform_int_distribution<int> distribution(0,24);
        int rounds = distribution(generator);
        for (byte i = 0; i < (byte) rounds; ++i) {
            int n = distribution(generator);
            set((byte) n, true);
        }
    }
    else if(choice == 3) {

    }

	//long seed = std::chrono::system_clock::now().time_since_epoch().count();
}

void Board::reset() {
    for(byte row = 0; row < RC; ++row) {
        GAME_BOARD[row] = false;
    }
}

bool Board::isWin() {
	for(byte row = 0; row < RC; ++row) {
        if(GAME_BOARD[row]) {
            return false;
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

/* Matrix Vector Multiply */
void Board::mvm(const bool(&mat)[RC][RC], bool(&vec)[RC], bool (&result)[RC]) {
    for(byte i = 0; i < RC; ++i) {
        result[i] = dot(mat[i], vec);
    }
}

/* 25x1 Vector Dot Product */
bool Board::dot(const bool(&v1)[RC], bool(&v2)[RC]) {
    bool temp[RC] = {false, false, false, false, false,
                             false, false, false, false, false,
                             false, false, false, false, false,
                             false, false, false, false, false,
                             false, false, false, false, false};
    bool result = true;
    for(byte i = 0; i < RC; ++i) {
        temp[i] = multiply(v1[i], v2[i]);
    }
    for(byte i = 0; i < RC; ++i) {
        if(i == 0){
            result = temp[0];
        }else {
            result = add(result, temp[i]);
        }
    }
    return result;
}


/* True if board is solvable, false if not. */
bool Board::isSolvable() {
	bool s1 = false;
	bool s2 = false;

	s1 = dot(SOLVABLE1, GAME_BOARD);
	s2 = dot(SOLVABLE2, GAME_BOARD);

	if(!s1 && !s2) {
		return true;
	}
	else {
		return false;
	}
}

/* Sets 0-indexed grid number to true/false without toggling adjacent squares */
void Board::set(byte gridNum, bool state) {
    GAME_BOARD[gridNum] = state;
}

/* Toggles 0-indexed square and adjacent squares. */
void Board::toggle(byte gridNum) {
	/* Error checking for valid range? */
    /* Toggle the square itself. */
    GAME_BOARD[gridNum] = !GAME_BOARD[gridNum];

    /* North Adjacent only when row > 4 */
    if(gridNum > FOUR){
        GAME_BOARD[gridNum - FIVE] = !GAME_BOARD[gridNum - FIVE];
    }

    /* South adjacent only when row < 20 */
    if(gridNum < TWENTY){
        GAME_BOARD[gridNum + FIVE] = !GAME_BOARD[gridNum + FIVE];
    }

    /* East adjacent only when row MOD 5 != 4 */
    if(gridNum % FIVE != FOUR) {
        GAME_BOARD[gridNum + ONE] = !GAME_BOARD[gridNum + ONE];
    }

    /* West adjacent only when row MOD 5 != 0 */
    if(gridNum % FIVE != ZERO) {
        GAME_BOARD[gridNum - ONE] = !GAME_BOARD[gridNum - ONE];
    }
}

void Board::printConsole() {
    for(byte i = 0; i < RC; ++i){
        if(GAME_BOARD[i]){
            std::cout << "| ON";
        }
        else {
            std::cout << "|OFF";
        }
        if(i % FIVE == 4) {
            std::cout << "|" << std::endl;
        }
    }
}

void Board::printConsole(bool(&colvec)[RC]) {
    for(byte i = 0; i < RC; ++i){
        if(colvec[i]){
            std::cout << "| ON";
        }
        else {
            std::cout << "|OFF";
        }
        if(i % FIVE == 4) {
            std::cout << "|" << std::endl;
        }
    }
    std::cout << std::endl;
}
