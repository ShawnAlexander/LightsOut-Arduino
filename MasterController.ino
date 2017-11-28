#include "I2C.h"
#include "Board.h"
#include "KeypadWrapper.h"

bool inGame;
I2C_Master mcomm;
Board board;
KeypadWrapper kpdw;

void gameReset() {
  mcomm.write(RESET);
  inGame = true;
  board.reset();
  board.randomize();
  for (byte i = board.ZERO; i < board.RC; ++i) {
    if (board.GAME_BOARD[i]) {
      if (i == 0) {
        mcomm.write(SET0);
      }
      else if (i == 1) {
        mcomm.write(SET1);
      }
      else if (i == 2) {
        mcomm.write(SET2);
      }
      else if (i == 3) {
        mcomm.write(SET3);
      }
      else if (i == 4) {
        mcomm.write(SET4);
      }
      else if (i == 5) {
        mcomm.write(SET5);
      }
      else if (i == 6) {
        mcomm.write(SET6);
      }
      else if (i == 7) {
        mcomm.write(SET7);
      }
      else if (i == 8) {
        mcomm.write(SET8);
      }
      else if (i == 9) {
        mcomm.write(SET9);
      }
      else if (i == 10) {
        mcomm.write(SET10);
      }
      else if (i == 11) {
        mcomm.write(SET11);
      }
      else if (i == 12) {
        mcomm.write(SET12);
      }
      else if (i == 13) {
        mcomm.write(SET13);
      }
      else if (i == 14) {
        mcomm.write(SET14);
      }
      else if (i == 15) {
        mcomm.write(SET15);
      }
      else if (i == 16) {
        mcomm.write(SET16);
      }
      else if (i == 17) {
        mcomm.write(SET17);
      }
      else if (i == 18) {
        mcomm.write(SET18);
      }
      else if (i == 19) {
        mcomm.write(SET19);
      }
      else if (i == 20) {
        mcomm.write(SET20);
      }
      else if (i == 21) {
        mcomm.write(SET21);
      }
      else if (i == 22) {
        mcomm.write(SET22);
      }
      else if (i == 23) {
        mcomm.write(SET23);
      }
      else if (i == 24) {
        mcomm.write(SET24);
      }
    }
  }
  mcomm.write(FIN);
}

void setup() {
  mcomm.init();
  inGame = false;
}

void loop() {
  int keyEvent = kpdw.pollKeypad();
  if (keyEvent == 128) {}
  else if (keyEvent == -1) {
    gameReset();
  }
  else if (keyEvent >= 0 && keyEvent <= 24) {
    if (keyEvent == 0) {
      mcomm.write(TOGGLE0);
    }
    else if (keyEvent == 1) {
      mcomm.write(TOGGLE1);
    }
    else if (keyEvent == 2) {
      mcomm.write(TOGGLE2);
    }
    else if (keyEvent == 3) {
      mcomm.write(TOGGLE3);
    }
    else if (keyEvent == 4) {
      mcomm.write(TOGGLE4);
    }
    else if (keyEvent == 5) {
      mcomm.write(TOGGLE5);
    }
    else if (keyEvent == 6) {
      mcomm.write(TOGGLE6);
    }
    else if (keyEvent == 7) {
      mcomm.write(TOGGLE7);
    }
    else if (keyEvent == 8) {
      mcomm.write(TOGGLE8);
    }
    else if (keyEvent == 9) {
      mcomm.write(TOGGLE9);
    }
    else if (keyEvent == 10) {
      mcomm.write(TOGGLE10);
    }
    else if (keyEvent == 11) {
      mcomm.write(TOGGLE11);
    }
    else if (keyEvent == 12) {
      mcomm.write(TOGGLE12);
    }
    else if (keyEvent == 13) {
      mcomm.write(TOGGLE13);
    }
    else if (keyEvent == 14) {
      mcomm.write(TOGGLE14);
    }
    else if (keyEvent == 15) {
      mcomm.write(TOGGLE15);
    }
    else if (keyEvent == 16) {
      mcomm.write(TOGGLE16);
    }
    else if (keyEvent == 17) {
      mcomm.write(TOGGLE17);
    }
    else if (keyEvent == 18) {
      mcomm.write(TOGGLE18);
    }
    else if (keyEvent == 19) {
      mcomm.write(TOGGLE19);
    }
    else if (keyEvent == 20) {
      mcomm.write(TOGGLE20);
    }
    else if (keyEvent == 21) {
      mcomm.write(TOGGLE21);
    }
    else if (keyEvent == 22) {
      mcomm.write(TOGGLE22);
    }
    else if (keyEvent == 23) {
      mcomm.write(TOGGLE23);
    }
    else if (keyEvent == 24) {
      mcomm.write(TOGGLE24);
    }
    mcomm.write(FIN);
    if (board.isWin()) {
      mcomm.write(WIN);
      inGame = false;
      mcomm.write(FIN);
    }
  }

}

