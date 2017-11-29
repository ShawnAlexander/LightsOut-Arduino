#include <Wire.h>
static const byte FIVE = 5;
static const byte FOUR = 4;
static const byte ZERO = 0;
static const byte TWENTY = 20;
static const byte ONE = 1;
static const byte RC = 25;

void randomize();
void shuffle(byte *);
unsigned long nrand25(byte);

void set(byte, bool); /* Sets 0-indexed grid number to true/false without toggling adjacent squares */
void toggle(byte);  /* Toggle by 0-indexed grid number */
bool isWin();
void reset();

bool add(bool, bool);
bool multiply(bool, bool);
void mvm(bool(&)[RC]);
bool dot(byte, bool(&)[RC]);

bool GAME_BOARD[RC] = {false, false, false, false, false,
                       false, false, false, false, false,
                       false, false, false, false, false,
                       false, false, false, false, false,
                       false, false, false, false, false
                      };
const bool A[] PROGMEM = {true, true, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
                          true, true, true, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
                          false, true, true, true, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
                          false, false, true, true, true, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
                          false, false, false, true, true, false, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
                          true, false, false, false, false, true, true, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
                          false, true, false, false, false, true, true, true, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false,
                          false, false, true, false, false, false, true, true, true, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false,
                          false, false, false, true, false, false, false, true, true, true, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false,
                          false, false, false, false, true, false, false, false, true, true, false, false, false, false, true, false, false, false, false, false, false, false, false, false, false,
                          false, false, false, false, false, true, false, false, false, false, true, true, false, false, false, true, false, false, false, false, false, false, false, false, false,
                          false, false, false, false, false, false, true, false, false, false, true, true, true, false, false, false, true, false, false, false, false, false, false, false, false,
                          false, false, false, false, false, false, false, true, false, false, false, true, true, true, false, false, false, true, false, false, false, false, false, false, false,
                          false, false, false, false, false, false, false, false, true, false, false, false, true, true, true, false, false, false, true, false, false, false, false, false, false,
                          false, false, false, false, false, false, false, false, false, true, false, false, false, true, true, false, false, false, false, true, false, false, false, false, false,
                          false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, true, true, false, false, false, true, false, false, false, false,
                          false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, true, true, true, false, false, false, true, false, false, false,
                          false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, true, true, true, false, false, false, true, false, false,
                          false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, true, true, true, false, false, false, true, false,
                          false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, true, true, false, false, false, false, true,
                          false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, true, true, false, false, false,
                          false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, true, true, true, false, false,
                          false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, true, true, true, false,
                          false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, true, true, true,
                          false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, false, false, false, true, true
                         };

int freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void randomize() {
  byte minMoves = random(FIVE, RC);
  unsigned long randomBits = nrand25(minMoves);
  unsigned long k;
  bool TEMP[RC] = {false, false, false, false, false,
                   false, false, false, false, false,
                   false, false, false, false, false,
                   false, false, false, false, false,
                   false, false, false, false, false
                  };
  for (byte i = ZERO; i < RC; ++i) {
    k = 1 << i;
    if (k & randomBits) {
      TEMP[i] = true;
    }
  }
  mvm(TEMP);
}

bool add(bool p1, bool p2) {
  if (p1 && !p2 || !p1 && p2) {
    return true;
  }
  else {
    return false;
  }
}
bool multiply(bool p1, bool p2) {
  if (p1 && p2) {
    return true;
  }
  else {
    return false;
  }
}

/* Matrix Vector Multiply */
void mvm(bool(&vec)[RC]) {
  for (byte i = ZERO; i < RC; ++i) {
    GAME_BOARD[i] = dot(i, vec);
  }
}

/* 25x1 Vector Dot Product */
bool dot(byte idx, bool(&v2)[RC]) {
  bool temp[RC] = {false, false, false, false, false,
                   false, false, false, false, false,
                   false, false, false, false, false,
                   false, false, false, false, false,
                   false, false, false, false, false
                  };
  bool result = true;
  for (byte i = ZERO; i < RC; ++i) {
    bool elem = pgm_read_byte(A + idx * RC + i);
    temp[i] = multiply(elem, v2[i]);
  }
  for (byte i = ZERO; i < RC; ++i) {
    if (i == ZERO) {
      result = temp[ZERO];
    } else {
      result = add(result, temp[i]);
    }
  }
  return result;
}

void shuffle(byte *x) {
  for (byte i = 0; i < RC; ++i) {
    byte j = random(ZERO, RC);
    byte tmp = x[i];
    x[i] = x[j];
    x[j] = tmp;
  }
}

/* Produces a "random" 25 bit integer with n bits set to 1. */
unsigned long nrand25(byte n) {
  unsigned long v = ZERO;
  byte pos[RC] = {0, 1, 2, 3, 4, 5, 6, 7,
                  8, 9, 10, 11, 12, 13, 14, 15,
                  16, 17, 18, 19, 20, 21, 22, 23, 24
                 };
  shuffle(pos);
  for (byte i = ZERO; i < n; ++i) {
    unsigned long k = 1;
    v |= (k << pos[i]);
  }
  return v;
}

/* All lights off. */
void reset() {
  for (byte row = 0; row < RC; ++row) {
    GAME_BOARD[row] = false;
  }
}

bool isWin() {
  for (byte row = 0; row < RC; ++row) {
    if (GAME_BOARD[row] == true) {
      return false;
    }
  }
  return true;
}

void set(byte gridNum, bool state) {
  GAME_BOARD[gridNum] = state;
}

/* Toggles 0-indexed square and adjacent squares. */
void toggle(byte gridNum) {
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


enum EVENT : byte {
  /* THE EVENTS LISTED HERE MAP THE ENTIRE BYTE */

  /* TOGGLE EVENTS */
  /* UPPER 3 BITS ARE 001 */
  /* DECIMAL RANGE 33 - 57 */
  TOGGLE0 = 33,
  TOGGLE1 = 34,
  TOGGLE2 = 35,
  TOGGLE3 = 36,
  TOGGLE4 = 37,
  TOGGLE5 = 38,
  TOGGLE6 = 39,
  TOGGLE7 = 40,
  TOGGLE8 = 41,
  TOGGLE9 = 42,
  TOGGLE10 = 43,
  TOGGLE11 = 44,
  TOGGLE12 = 45,
  TOGGLE13 = 46,
  TOGGLE14 = 47,
  TOGGLE15 = 48,
  TOGGLE16 = 49,
  TOGGLE17 = 50,
  TOGGLE18 = 51,
  TOGGLE19 = 52,
  TOGGLE20 = 53,
  TOGGLE21 = 54,
  TOGGLE22 = 55,
  TOGGLE23 = 56,
  TOGGLE24 = 57,

  /* We use these for game reset. Implies board is all false, so we are setting to true. */
  /* Do not toggle neighbors. */
  SET0 = 58,
  SET1 = 59,
  SET2 = 60,
  SET3 = 61,
  SET4 = 62,
  SET5 = 63,
  SET6 = 64,
  SET7 = 65,
  SET8 = 66,
  SET9 = 67,
  SET10 = 68,
  SET11 = 69,
  SET12 = 70,
  SET13 = 71,
  SET14 = 72,
  SET15 = 73,
  SET16 = 74,
  SET17 = 75,
  SET18 = 76,
  SET19 = 77,
  SET20 = 78,
  SET21 = 79,
  SET22 = 80,
  SET23 = 81,
  SET24 = 82,
  /* GAME WON */
  WIN = 96,

  /* RESET/NEW GAME */
  RESET = 160,

  /* TRANSMISSION FINISH */
  FIN = 170,

  /* MASTER ERROR */
  M_ERROR = 224
};

const byte ROWS = 5;
byte currentKey;
byte keyCount;
const byte COL_PINS[ROWS] = {3, 4, 5, 6, 7};
const byte ROW_PINS[ROWS] = {8, 9, 10, 11, 12};
unsigned long EPOCH;
const unsigned long DEBOUNCE = 100;

/* Key press is active low. */
/* Code modeled from Keypad library */
byte pollKeypad() {
  byte sig = 30;
  for (byte col = 0; col < ROWS; ++col) {
    pinMode(COL_PINS[col], OUTPUT);
    digitalWrite(COL_PINS[col], LOW);
    for (byte row = 0; row < ROWS; ++row) {
      int val = digitalRead(ROW_PINS[row]);
      if (val == LOW) {
        Serial.print(F("Col: "));
        Serial.println(col);
        Serial.print(F("Row: "));
        Serial.println(row);
        sig = row * ROWS + col;
      }
    }
    digitalWrite(COL_PINS[col], HIGH);
    pinMode(COL_PINS[col], INPUT); /* Terminates column signal. */
  }
  return sig;
}

void gameReset() {
  Serial.println(F("Game Reset!"));
  Wire.beginTransmission(8);
  Wire.write(RESET);
  Serial.println(F("Calling Reset"));
  reset();
  Serial.println(F("Calling Randomize!"));
  randomize();
  Serial.print(F("Free ram: "));
  Serial.println(freeRam());
  for (byte i = 0; i < RC; ++i) {
    if (GAME_BOARD[i] == true) {
      Serial.println(i);
      if (i == 0) {
        Wire.write(SET0);
      }
      else if (i == 1) {
        Wire.write(SET1);
      }
      else if (i == 2) {
        Wire.write(SET2);
      }
      else if (i == 3) {
        Wire.write(SET3);
      }
      else if (i == 4) {
        Wire.write(SET4);
      }
      else if (i == 5) {
        Wire.write(SET5);
      }
      else if (i == 6) {
        Wire.write(SET6);
      }
      else if (i == 7) {
        Wire.write(SET7);
      }
      else if (i == 8) {
        Wire.write(SET8);
      }
      else if (i == 9) {
        Wire.write(SET9);
      }
      else if (i == 10) {
        Wire.write(SET10);
      }
      else if (i == 11) {
        Wire.write(SET11);
      }
      else if (i == 12) {
        Wire.write(SET12);
      }
      else if (i == 13) {
        Wire.write(SET13);
      }
      else if (i == 14) {
        Wire.write(SET14);
      }
      else if (i == 15) {
        Wire.write(SET15);
      }
      else if (i == 16) {
        Wire.write(SET16);
      }
      else if (i == 17) {
        Wire.write(SET17);
      }
      else if (i == 18) {
        Wire.write(SET18);
      }
      else if (i == 19) {
        Wire.write(SET19);
      }
      else if (i == 20) {
        Wire.write(SET20);
      }
      else if (i == 21) {
        Wire.write(SET21);
      }
      else if (i == 22) {
        Wire.write(SET22);
      }
      else if (i == 23) {
        Wire.write(SET23);
      }
      else if (i == 24) {
        Wire.write(SET24);
      }
    }
  }
  byte error = Wire.endTransmission();
  if (error != 0) {
    Serial.println(F("I2C Error!"));
  }
  Serial.println(F("End randomize!"));
}

void setup() {
  //Wire.setClock(400000);
  Serial.begin(9600);
  Wire.begin();
  int v = analogRead(A0);
  randomSeed(v);
  Serial.print(F("Random Seed: "));
  Serial.println(v);
  gameReset();
  for (byte i = 0; i < ROWS; ++i) {
    pinMode(COL_PINS[i], OUTPUT);
    pinMode(ROW_PINS[i], INPUT_PULLUP);
  }
  EPOCH = 0;
}

void loop() {
  if (millis() - EPOCH >= DEBOUNCE) {
    EPOCH = millis();
    byte keyEvent = pollKeypad();
    if (keyEvent == 30) {
    }
    else if (keyEvent >= 0 && keyEvent <= 24) {
      Serial.print(F("Key press: "));
      Serial.println(keyEvent);
      if (keyEvent == currentKey) {
        ++keyCount;
      }
      else {
        currentKey = keyEvent;
        keyCount = 0;
      }

      Wire.beginTransmission(8);
      if (keyEvent == 0) {
        Wire.write(TOGGLE0);
      }
      else if (keyEvent == 1) {
        Wire.write(TOGGLE1);
      }
      else if (keyEvent == 2) {
        Wire.write(TOGGLE2);
      }
      else if (keyEvent == 3) {
        Wire.write(TOGGLE3);
      }
      else if (keyEvent == 4) {
        Wire.write(TOGGLE4);
      }
      else if (keyEvent == 5) {
        Wire.write(TOGGLE5);
      }
      else if (keyEvent == 6) {
        Wire.write(TOGGLE6);
      }
      else if (keyEvent == 7) {
        Wire.write(TOGGLE7);
      }
      else if (keyEvent == 8) {
        Wire.write(TOGGLE8);
      }
      else if (keyEvent == 9) {
        Wire.write(TOGGLE9);
      }
      else if (keyEvent == 10) {
        Wire.write(TOGGLE10);
      }
      else if (keyEvent == 11) {
        Wire.write(TOGGLE11);
      }
      else if (keyEvent == 12) {
        Wire.write(TOGGLE12);
      }
      else if (keyEvent == 13) {
        Wire.write(TOGGLE13);
      }
      else if (keyEvent == 14) {
        Wire.write(TOGGLE14);
      }
      else if (keyEvent == 15) {
        Wire.write(TOGGLE15);
      }
      else if (keyEvent == 16) {
        Wire.write(TOGGLE16);
      }
      else if (keyEvent == 17) {
        Wire.write(TOGGLE17);
      }
      else if (keyEvent == 18) {
        Wire.write(TOGGLE18);
      }
      else if (keyEvent == 19) {
        Wire.write(TOGGLE19);
      }
      else if (keyEvent == 20) {
        Wire.write(TOGGLE20);
      }
      else if (keyEvent == 21) {
        Wire.write(TOGGLE21);
      }
      else if (keyEvent == 22) {
        Wire.write(TOGGLE22);
      }
      else if (keyEvent == 23) {
        Wire.write(TOGGLE23);
      }
      else if (keyEvent == 24) {
        Wire.write(TOGGLE24);
      }
      if (isWin() == true) {
        Wire.write(WIN);
      }
      byte err = Wire.endTransmission();
      if (err != 0) {
        Serial.println(F("I2C Error!"));
      }
    }
  }

}








