#include "I2C.h"

void I2C_Slave::init(void(*callback)()){
  Wire.begin(SLAVE_ADDR);
  Wire.onReceive(callback);  /* Register callback */
}

int I2C_Slave::available() {
  return Wire.available();
}

EVENT I2C_Slave::read() {
  return (EVENT) Wire.read();
}

void I2C_Master::init(){
  Wire.begin();
}

void I2C_Master::write(EVENT e) {
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(e);
  Wire.endTransmission();
}

