#include "common.h"

unsigned char currentDir = STOP;

int main(void)
{
	initialize();
	
	EA = 1;

	//while(!UART1_getLink());//establish communication with computer
	//main loop
	while(1)
	{
		//UART1_transmit();
		UART1_parseData();		
	}
}

void initialize(void)
{
	int i;                              // Software timer

	//disable watchdog timer
	WDTCN = 0xde;                       // Disable watchdog timer
   	WDTCN = 0xad;
	
	//set external oscilator to 22.1184MHz 
	OSCICN |= 0x80;                     // Enable the missing clock detector

	// Initialize external crystal oscillator to use 22.1184 MHz crystal
	OSCXCN = 0x67;                      // Enable external crystal osc.
	for (i=0; i < 256; i++);            // Wait at least 1ms
	while (!(OSCXCN & 0x80));           // Wait for crystal osc to settle
	OSCICN |= 0x08;                     // Select external clock source
	OSCICN &= ~0x04; 
	
	//port initialization
	XBR0 = 0x20;						// Enable PCA
	XBR1 = 0x00;
	XBR2 = 0x44;                        // Enable crossbar and weak pull-up and UART1

	P0MDOUT |= 0x01;                    // Set TX pin to push-pull	

	//UART1-xbee module
	UART1_init();

	//Motor Driver(PCA)
	PCA_init();
	
	//others...
}
