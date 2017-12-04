#include "I2C.h"
#include "Board.h"
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x3f, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

const byte ROWS = 5;
const byte COLS = 5;
                                        
char hexaKeys[ROWS][COLS] = {
  {'a','b','c','d','e'},
  {'f','g','h','i','j'},
  {'k','l','m','n','o'},
  {'p','q','r','s','t'},
  {'u','v','w','x','y'}
};

byte rowPins[ROWS] = {6,5,4,3,2};
byte colPins[COLS] = {11,10,9,8,7};
bool sol[25];
bool ingame = false;
int score;
int hscore;
long long last_score_update = millis();;
long long start_time = millis();
int moves = 0;

Keypad kpad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

I2C_Master mcomm;
Board board;

int pollKeypad();
void gameReset();
void findsolution();
void initlcd();

void setup() {
  lcd.begin(16,2);
  initlcd();
  score = 0;
  randomSeed(analogRead(0));
  mcomm.init();
  gameReset();
}
void loop() {
  if (millis() - last_score_update > 1000 && ingame){
    last_score_update = millis();
    score = max(0,9999 - moves*10*((.5*(millis()-start_time))/1000));
    lcd.setCursor(7,0); lcd.print("    "); lcd.setCursor(7,0);
    lcd.print(score);
  }
  
  int keyEvent = pollKeypad();
  if (keyEvent == 128) {}
  else if (keyEvent == -1) {
    gameReset();
  }
  else if (keyEvent >= 0 && keyEvent <= 24) {
    moves++;
    mcomm.write(TOGGLE0+keyEvent);
    board.toggle(keyEvent);
    if (board.isWin()) {
      ingame = false;
      lcd.clear();
      lcd.print("You win!");
      if(score > hscore) {
        lcd.setCursor(0,1);
        lcd.print("New High Score!");
        EEPROM.write(0, 1);
        EEPROM.put(1, score);
      }
      mcomm.write(WIN);
    }
  }
}

int pollKeypad() {
  if (kpad.getKeys()) {
    int count = 0;
    for (int i = 0; i < LIST_MAX; i++) {
      if (kpad.key[i].kstate == HOLD) {
        ++count;
        if (count == 2) return -1;
      }
      else if (kpad.key[i].kstate == PRESSED) return kpad.key[i].kchar - 97;
    }
  }

  else return 128;
}

void gameReset() {
  mcomm.write(RESET);
  board.reset();
  board.randomize();
  for (byte i = board.ZERO; i < board.RC; ++i) {
    if (board.GAME_BOARD[i]) mcomm.write(SET0+i);
  }
  initlcd();
  moves = 0;
  start_time = millis();
  last_score_update = -1000;
  ingame = true;
}

void initlcd(){
  lcd.clear();
  lcd.print("Score: 0");
  lcd.setCursor(0, 1);
  lcd.print("Hscore: ");
  if(EEPROM.read(0) == 0) hscore = 0;
  else EEPROM.get(1, hscore);
  lcd.print(hscore);
}


