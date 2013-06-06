#include "common.h"

unsigned char dutycycle = 0xFF;//0% duty cycle to begin with

void PCA_init(void)
{
	P0MDOUT   = 0x3C;

    PCA0CPM0  = ON;
    PCA0CPM1  = ON;
    PCA0CPM2  = ON;
    PCA0CPM3  = ON;
			//small Duty Cycle for testing
		    //PCA0CPH0  = 0x00;//left wheel forward P0.0
		    //PCA0CPH1  = 0x00;//left wheel backward P0.1
		    //PCA0CPH2  = 0x00;//right wheel forward P0.2
		    //PCA0CPH3  = 0x00;//right wheel backward P0.3
	//start PWM
	CR = 1;
}

void PCA_setDutyCycle(unsigned char command)
{
	unsigned int temp;
	static unsigned char duty = 0;

	//adjust duty cycle in %
	switch(command)
	{
		case FORWARD:
		case REVERSE:
			//if(command == currentDir)
			//{
				duty += 10;
			//}
			break;
		case STOP:
			duty -= 10;
			break;
	}
	
	if(duty > 200)
		duty = 0;
	else if(duty > 90)
		duty = 90;			
	
	//convert dutycycle to PCA count
	if(duty == 0)
	{
		//PCA0CPM0 = OFF;
		//PCA0CPM1 = OFF;
		//PCA0CPM2 = OFF;
		//PCA0CPM3 = OFF;
		dutycycle = 0xFF;
	}
	else
	{
		//PCA0CPM0 = ON;
		//PCA0CPM1 = ON;
		//PCA0CPM2 = ON;
		//PCA0CPM3 = ON;
		//0 = 100% duty cycle 255
		temp = 256*(unsigned int)duty;
		dutycycle = (25600-temp)/100;
	}
	//update direction
	currentDir = command;
}		

void PCA_setDirection(unsigned char dir)
{
	//reset PCA modules to "ON"
    PCA0CPM0 = ON;
    PCA0CPM1 = ON;
    PCA0CPM2 = ON;
    PCA0CPM3 = ON;
	switch(dir)
	{
		case FORWARD:
		    PCA0CPH0  = dutycycle;//left wheel forward P0.0
		    PCA0CPM1 = OFF;
			PCA0CPH1  = 0xFF;//left wheel backward P0.1
		    PCA0CPH2  = dutycycle;//right wheel forward P0.2
		    PCA0CPM3 = OFF;
			PCA0CPH3  = 0xFF;//right wheel backward P0.3
			break;
		case REVERSE:
		    PCA0CPM0 = OFF;
			PCA0CPH0  = 0xFF;//left wheel forward P0.0
		    PCA0CPH1  = dutycycle;//left wheel backward P0.1
		    PCA0CPM2 = OFF;
			PCA0CPH2  = 0xFF;//right wheel forward P0.2
		    PCA0CPH3  = dutycycle;//right wheel backward P0.3
			break;
		case RIGHT:
		    PCA0CPH0  = dutycycle;//left wheel forward P0.0
		    PCA0CPM1 = OFF;
			PCA0CPH1  = 0xFF;//left wheel backward P0.1
			PCA0CPM2 = OFF;
			PCA0CPH2  = 0xFF;//right wheel forward P0.2
		    PCA0CPH3  = dutycycle;//right wheel backward P0.3
			break;
		case LEFT:
		    PCA0CPM0 = OFF;
			PCA0CPH0  = 0xFF;//left wheel forward P0.0
		    PCA0CPH1  = dutycycle;//left wheel backward P0.1
		    PCA0CPH2  = dutycycle;//right wheel forward P0.2
		    PCA0CPM0 = OFF;
			PCA0CPH3  = 0xFF;//right wheel backward P0.3
			break;
		case STOP:
		    PCA0CPM0 = OFF;
			PCA0CPH0  = 0xFF;//left wheel forward P0.0
		    PCA0CPM1 = OFF;
		    PCA0CPH1  = 0xFF;//left wheel backward P0.1
		    PCA0CPM2 = OFF;
		    PCA0CPH2  = 0xFF;//right wheel forward P0.2
		    PCA0CPM3 = OFF;
			PCA0CPH3  = 0xFF;//right wheel backward P0.3
			break;
	}
}	