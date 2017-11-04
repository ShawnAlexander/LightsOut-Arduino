#include "I2C.h"

/* Slave constructor */
I2C_Slave::I2C_Slave() {
	Wire.begin(SLAVE_ADDR);
	Wire.onReceive(callback);	/* Register callback */
}

/* Slave constructor external callback */
I2C_Slave::I2C_Slave(void(*cb)(int)) {
	Wire.begin(SLAVE_ADDR);
	Wire.onReceive(cb);	/* Register callback */
}

int I2C_Slave::available() {
	return Wire.available();
}

EVENT I2C_Slave::read() {
    // Check for validity?
	return (EVENT) Wire.read();
}

void I2C_Slave::callback(int numBytes) {
	/* Implement or use external */
}


I2C_Master::I2C_Master() {
	Wire.begin();
	
}

void I2C_Master::write(EVENT e) {
	Wire.beginTransmission(SLAVE_ADDR);
	Wire.write(e);
	Wire.endTransmission();
}