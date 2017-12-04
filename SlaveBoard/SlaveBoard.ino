#include "I2C.h"

#define ON true
#define OFF false

const int rowpin[] = {2,3,4,5,6}; //pins used for rows
const int colpin[] = {7,8,9,10,11}; //pins used for columns

const uint8_t m_size = 5;

//corresponds to current state of LEDs in matrix, 1 = on
bool state[m_size*m_size];

//bool state[m_size*m_size] = { 0,1,1,0,1,
//                              1,1,0,1,1,
//                              0,0,1,0,0,
//                              1,0,0,1,1,
//                              1,1,1,1,1 };
                                  
uint8_t cur_row = 0; 

I2C_Slave slave;

void eventhandle();

void setup() {
  for(int i = 0; i < m_size; ++i){
    pinMode(rowpin[i], OUTPUT);
    pinMode(colpin[i], OUTPUT);
    digitalWrite(rowpin[i], LOW);
    digitalWrite(colpin[i], LOW);
  }
  for(int i = 0; i < m_size*m_size; ++i) state[i] = OFF;
  slave.init(eventhandle);  
}

void loop() {
  //turn off the other rows
  for(int i = 1; i < m_size; ++i) digitalWrite(rowpin[(cur_row+i)%m_size], LOW);

  //column = LOW lets current pass, HIGH blocks current
  for(int col = 0; col < m_size; ++col) digitalWrite(colpin[col], !(state[(cur_row)*m_size+col]));
  digitalWrite(rowpin[cur_row], HIGH); //set the current row to HIGH to light up the LEDs 
  cur_row = (cur_row+1)%m_size; //move to the next row
}

void eventhandle(){
  EVENT event = slave.read();
  if(event >= 33 && event <= 57){ //toggle
    uint8_t row = (event - TOGGLE0)/m_size;
    uint8_t col = (event - TOGGLE0)%m_size;
    uint8_t index = event - TOGGLE0;

    //toggle provided LED
    state[index] = !state[index];
    
    //toggle adjacent LEDs if applicable
    if(row > 0) state[index-m_size] = !state[index-m_size];
    if(row < m_size-1) state[index+m_size] = !state[index+m_size];
    if(col > 0) state[index-1] = !state[index-1];
    if(col < m_size-1) state[index+1] = !state[index+1];
  }
  else if(event >= 58 && event <= 82){ //set
    state[event-SET0] = ON;
  }
  else{
    switch(event){
      case WIN: 
        break;
      case RESET:
        for(byte i = 0; i < 25; ++i) state[i] = OFF;
        break;
      case M_ERROR: 
        for(byte i = 0; i < 25; ++i) state[i] = OFF;
        break;
      default: 
        break;
    }  
  }
}

