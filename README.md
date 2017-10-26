# LightsOut-Arduino
## Shawn Johnson, Scott Fraser, Ava Mistry, Gavin Atkin, & Joe Dodson
### Software Design
#### Boot
> On boot, we will have the slave (LED controller) listen for an initial request from the master (switch controller) over I2C to ensure that both are communicating correctly. The slave should blink in a special pattern following receipt of the initial request to prove that a connection has been established (if the slave controls the LCD we could also blink the LCD screen). The master will not proceed until it has received a response.
#### I2C Message Format
> 

### TO-DO:
- [ ] Insert shit here.
- [X] Done.
