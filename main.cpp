#include <Arduino.h>

// the input pins used for the buttons
int pins[]={A0,A1,A4,A5};
int numPins=4;

// baud rate for serial communications
int baud=9600;

// write a value to serial out and then pause
void write(int val) {
	Serial.println(val);
	delay(250);
}

// check all the input pins and return a bitfield of their states
int checkPins() {
	int pressed=0;
	for(int i=0;i<numPins;i++) pressed |= digitalRead(pins[i])<<i;
	return pressed;
}

// uhh... set up.
void setup() {
	for(int i=0;i<numPins;i++) pinMode(pins[i],INPUT);
	Serial.begin(baud);
}

// main loop
void loop() {
	int x=0;
	// if there's a pin active, wait 40ms and check again.
	// if it's still active, send the value via serial.
	// the double check is there so you can successfully
	// press two buttons and send that state to the handler.
	// without it, it's damn near impossible to get that timing.
	checkPins() && (delay(40),true) && (x=checkPins()) && (write(x),true);
}

// start it all up!
int main() {
	init();
	setup();
	while(true) loop();
	return 1;
}
