#ifndef I2C_COMM_H
#define I2C_COMM_H

#include <cinttypes>
#include "Wire.h"


/*
	LEDs & Switches refer to same square on grid.

	| 1| 2| 3| 4| 5|
	| 6| 7| 8| 9|10|
	|11|12|13|14|15|
	|16|17|18|19|20|
	|21|22|23|24|25|
*/


enum EVENT : uint8_t {
	/* THE EVENTS LISTED HERE MAP THE ENTIRE BYTE */

	/* TOGGLE EVENTS */
	/* UPPER 3 BITS ARE 001 */
	/* DECIMAL RANGE 33 - 57 */
	TOGGLE1 = 33,
	TOGGLE2 = 34,
	TOGGLE3 = 35,
	TOGGLE4 = 36,
	TOGGLE5 = 37,
	TOGGLE6 = 38,
	TOGGLE7 = 39,
	TOGGLE8 = 40,
	TOGGLE9 = 41,
	TOGGLE10 = 42,
	TOGGLE11 = 43,
	TOGGLE12 = 44,
	TOGGLE13 = 45,
	TOGGLE14 = 46,
	TOGGLE15 = 47,
	TOGGLE16 = 48,
	TOGGLE17 = 49,
	TOGGLE18 = 50,
	TOGGLE19 = 51,
	TOGGLE20 = 52,
	TOGGLE21 = 53,
	TOGGLE22 = 54,
	TOGGLE23 = 55,
	TOGGLE24 = 56,
	TOGGLE25 = 57,

	/* BOOT EVENT */
	BOOTSYNC = 64,

	/* GAME WON */
	WIN = 96,

	/* RESET/NEW GAME */
	RESET = 160,

	/* MASTER ERROR */
	ERROR = 224
};

class I2C_Slave {
	public:
		const uint8_t SLAVE_ADDR = 27;

		/* Slave constructor (calls setup routines) 
		   Uses internal callback */
		I2C_Slave();

		/* Slave constructor that uses external callback */
		I2C_Slave(void(*)(int));

		/* Slave functions */
		int available();
		EVENT read();

		/* Internal callback for I2C data received. 
		   Ignore int parameter (how many bytes) and call available()
		   Implement on your own */
		void callback(int);
};

class I2C_Master {
	public:
		const uint8_t SLAVE_ADDR = 27;

		/* Master constructor (calls setup routines) */
		I2C_Master();

		void write(EVENT);

};

#endif