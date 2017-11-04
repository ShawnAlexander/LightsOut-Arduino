# LightsOut-Arduino
## Shawn Johnson, Scott Fraser, Ava Mistry, Gavin Atkin, & Joe Dodson
### Software Design
#### Global Specifications
- Master controls switches and slave controls LEDs and LCD.
- Master writes to slave over I2C. Slave does not need to write to master.
- Switch rows are inputs & columns are outputs. (Or inverse?)
#### Boot
> On boot, we will have the slave (LED controller) listen for an initial request from the master (switch controller) over I2C to ensure that both are communicating correctly. The slave should blink in a special pattern following receipt of the initial request to prove that a connection has been established (if the slave controls the LCD we could also blink the LCD screen). The master will not proceed until it has received a response.
#### I2C Message Format
> Bitmask using a byte: Upper 3 bits as action: 000  Lower 5 bits as data: 00000
> Event Bits 8-6: 111 -> Master in Error State    101 -> Reset Game 	 001 -> Toggle LED in Data    010 - > Boot    011 -> Game Win
> Data Bits 5-1

#### Basic Control Flow
##### Master				I2C			Slave
1. Reset game. GOTO 2.		101XXXXX	Reset game. GOTO 2.
2. Get input. GOTO 3.		001XXXXX	Display output. GOTO 3.
3. Is Win?								Check for avaliable I2C.
* Yes. Notify. GOTO 1.		101			Inform user (blink). GOTO 1.
* No. GOTO 2.							GOTO 2.
> Error states deviate from this control flow.

#### Exception Handling
> AVR-GCC compiles with ```-fno-exceptions``` so we have to implement our own form of error handling.


### NOTES:
