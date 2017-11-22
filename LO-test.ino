#include "Board.h"

Board gb;
const char INFO[] = "Commands\n\'n\' - New Game/Reset.\n\'i\' - Is Solvable?\n";
const char GRID[] = "| 0| 1| 2| 3| 4|\n"
                    "| 5| 6| 7| 8| 9|\n"
                    "|10|11|12|13|14|\n"
                    "|15|16|17|18|19|\n"
                    "|20|21|22|23|24|";
const char DIFFICULTY[] = "0. Random\n1. Easy\n2. Medium\n3. Hard\n4. Insane";

char buf[3];
bool mode = false;


void setup() {
  Serial.begin(9600);
  Serial.setTimeout(1000);
  randomSeed(analogRead(0));
}

void loop() {
  if (Serial.available() > 0) {
    int len = Serial.readBytes(buf, 2);
    if (len == 2) {
      mode = true;
    }
    else if (len == 1) {
      if (isDigit(buf[0])) {
        mode = true;
      }
      else {
        mode = false;
      }
    }
    else {
      Serial.println("Input error!");
    }

    if (mode) {
      int n = atoi(buf);
      gb.toggle((byte) n);
      gb.printSerial();
      if (gb.isWin()) {
        Serial.println("Game Won!");
      }
    }
    else {
      if (buf[0] == 'n') {
        Serial.println("Choose a difficulty level. ");
        Serial.println(DIFFICULTY);
        bool chosen = false;
        int diff = 0;
        while (!chosen) {
          if (Serial.available() > 0) {
            char c = Serial.read();
            Serial.println(c);
            diff = atoi(&c);
            chosen = true;
          }
        }
        Serial.print("Diff: ");
        Serial.println(diff);
        Serial.println("New Game!");
        gb.reset();
        gb.randomize(diff);
        gb.printSerial();
      }
      else if (buf[0] == 'i') {
        if (gb.isSolvable()) {
          Serial.println("Solvable!");
        }
        else {
          Serial.println("Not Solvable!");
        }
      }
      else if (buf[0] == 's') {
        gb.solve();
      }
    }
  }
}




