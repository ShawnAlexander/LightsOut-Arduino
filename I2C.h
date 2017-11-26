
#ifndef I2C_COMM_H
#define I2C_COMM_H

#include "Wire.h"
#include "Arduino.h"


/*
	LEDs & Switches refer to same square on grid.

	| 1| 2| 3| 4| 5|
	| 6| 7| 8| 9|10|
	|11|12|13|14|15|
	|16|17|18|19|20|
	|21|22|23|24|25|
*/


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


class I2C_Slave {
  public:
    const byte SLAVE_ADDR = 27;

    void init(void(*callback)());
    int available();
    EVENT read();
};

class I2C_Master {
  public:
    const byte SLAVE_ADDR = 27;
    void init();
    void write(EVENT);

};

#endif

