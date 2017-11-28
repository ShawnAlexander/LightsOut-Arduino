#include "Board.h"

void Board::bin(unsigned long n) {
  unsigned long k;
  for (int i = 31; i >= 0; --i) {
    k = (unsigned long) 1 << i;
    if (k & n) {
      Serial.print("1");
    }
    else {
      Serial.print("0");
    }
  }
  Serial.println();
}

void Board::solve() {
  Serial.println("Solution: ");
  bool TEMP[RC] = {false, false, false, false, false,
                   false, false, false, false, false,
                   false, false, false, false, false,
                   false, false, false, false, false,
                   false, false, false, false, false
                  };
  mvm(R, GAME_BOARD, TEMP);
  for (byte i = ZERO; i < RC; ++i) {
    if (TEMP[i]) {
      toggle(i);
      Serial.println(i);
      printSerial();
    }
  }
}

/* Call reset before */
void Board::randomize() {
  unsigned long minMoves = random(5, 25);
  unsigned long randomBits = nrand25(minMoves);
  unsigned long k;
  bool TEMP[RC] = {false, false, false, false, false,
                   false, false, false, false, false,
                   false, false, false, false, false,
                   false, false, false, false, false,
                   false, false, false, false, false
                  };
  for (unsigned long i = 0; i < 25; ++i) {
    k = 1 << i;
    if (k & randomBits) {
      TEMP[(byte) i] = true;
    }
  }
  mvm(A, TEMP);
}

/*
  void Board::randomize(int difficulty) {
  unsigned long minMoves = 0;
  if (difficulty == 1) {
    minMoves = random(5, 11);
  }
  else if (difficulty == 2) {
    minMoves = random(10, 16);
  }
  else if (difficulty == 3) {
    minMoves = random(15, 21);
  }
  else if (difficulty == 4) {
    minMoves = random(20, 25);
  }
  else {
    minMoves = random(5, 25);
  }
  Serial.print("Min Moves: ");
  Serial.println(minMoves, DEC);
  unsigned long randomBits = nrand25(minMoves);
  Serial.print("Random Bits Integer: ");
  Serial.println(randomBits, DEC);
  Serial.print("Binary: ");
  bin(randomBits);
  Serial.print("Binary: ");
  Serial.println(randomBits, BIN);

  unsigned long k;

  bool TEMP[RC] = {false, false, false, false, false,
                   false, false, false, false, false,
                   false, false, false, false, false,
                   false, false, false, false, false,
                   false, false, false, false, false
                  };
  for (unsigned long i = 0; i < 25; ++i) {
    k = 1 << i;
    if (k & randomBits) {
      TEMP[(byte) i] = true;
    }
  }
  mvm(A, TEMP);
  }*/

/* Excludes n, so call with n + 1. */
int Board::randto(int n) {
  int r = random(0, n);
  return r;
}

void Board::shuffle(int *x, int n) {
  for (int i = 0; i < n; ++i) {
    int j = randto(25);
    int tmp = x[i];
    x[i] = x[j];
    x[j] = tmp;
  }
}

/* Produces a "random" 25 bit integer with n bits set to 1. */
unsigned long Board::nrand25(int n) {
  unsigned long v = 0;
  int pos[25] = {0, 1, 2, 3, 4, 5, 6, 7,
                 8, 9, 10, 11, 12, 13, 14, 15,
                 16, 17, 18, 19, 20, 21, 22, 23, 24
                };
  shuffle(pos, 25);
  for (int i = 0; i < n; ++i) {
    unsigned long k = 1;
    v |= (k << pos[i]);
  }
  return v;
}

/* All lights off. */
void Board::reset() {
  for (byte row = 0; row < RC; ++row) {
    GAME_BOARD[row] = false;
  }
}

bool Board::isWin() {
  for (byte row = 0; row < RC; ++row) {
    if (GAME_BOARD[row]) {
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

  if (p1 && !p2 || !p1 && p2) {
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
  if (p1 && p2) {
    return true;
  }
  else {
    return false;
  }
}

/* Matrix Vector Multiply */
void Board::mvm(const bool(&mat)[RC][RC], bool(&vec)[RC]) {
  for (byte i = 0; i < RC; ++i) {
    GAME_BOARD[i] = dot(mat[i], vec);
  }
}

/* Matrix Vector Multiply */
void Board::mvm(const bool(&mat)[RC][RC], bool(&vec)[RC], bool(&result)[RC]) {
  for (byte i = 0; i < RC; ++i) {
    result[i] = dot(mat[i], vec);
  }
}

/* 25x1 Vector Dot Product */
bool Board::dot(const bool(&v1)[RC], bool(&v2)[RC]) {
  bool temp[RC] = {false, false, false, false, false,
                   false, false, false, false, false,
                   false, false, false, false, false,
                   false, false, false, false, false,
                   false, false, false, false, false
                  };
  bool result = true;
  for (byte i = 0; i < RC; ++i) {
    temp[i] = multiply(v1[i], v2[i]);
  }
  for (byte i = 0; i < RC; ++i) {
    if (i == 0) {
      result = temp[0];
    } else {
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

  if (!s1 && !s2) {
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
  if (gridNum > FOUR) {
    GAME_BOARD[gridNum - FIVE] = !GAME_BOARD[gridNum - FIVE];
  }

  /* South adjacent only when row < 20 */
  if (gridNum < TWENTY) {
    GAME_BOARD[gridNum + FIVE] = !GAME_BOARD[gridNum + FIVE];
  }

  /* East adjacent only when row MOD 5 != 4 */
  if (gridNum % FIVE != FOUR) {
    GAME_BOARD[gridNum + ONE] = !GAME_BOARD[gridNum + ONE];
  }

  /* West adjacent only when row MOD 5 != 0 */
  if (gridNum % FIVE != ZERO) {
    GAME_BOARD[gridNum - ONE] = !GAME_BOARD[gridNum - ONE];
  }
}

void Board::printSerial() {
  for (byte i = 0; i < RC; ++i) {
    if (GAME_BOARD[i]) {
      Serial.print("| ON");
    }
    else {
      Serial.print("|OFF");
    }
    if (i % FIVE == 4) {
      Serial.println("|");
    }
  }
  Serial.println();
}






