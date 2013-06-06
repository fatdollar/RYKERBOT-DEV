#include "common.h"

//Globals
unsigned char UART_Buffer[UART_BUFFERSIZE];
unsigned char UART_Buffer_Size;
unsigned char UART_Input_First;
unsigned char UART_Output_First;
unsigned char TX_Ready;
static char Byte;

void UART1_init(void)
{
	SCON1   = 0x50;		// SCON1: mode 1, 8-bit UART, enable RX

	TMOD   &= ~0xF0;
	TMOD   |=  0x20;    // TMOD: timer 1, mode 2, 8-bit reload

	PCON |= 0x10;       // SMOD1 (PCON.4) = 1 --> UART1 baudrate
                        // divide-by-two disabled
    CKCON |= 0x10;      // Timer1 uses the SYSTEMCLOCK
    TH1 = - ((SYSTEMCLOCK/BAUDRATE)/16);

	TL1 = TH1;          // init Timer1
	TR1 = 1;            // START Timer1
	EIE2 = 0x40;        // Enable UART1 interrupts

	EIP2 = 0x40;        // Make UART high priority

	// Set globals
	UART_Buffer_Size = 0;
	UART_Input_First = 0;
	UART_Output_First = 0;
	TX_Ready = 1;
}

void UART1_Interrupt (void) interrupt 20
{
	if ((SCON1 & 0x01) == 0x01)
	{
		// Check if a new word is being entered
		if( UART_Buffer_Size == 0)
		{
			UART_Input_First = 0;
		} 

		SCON1 = (SCON1 & 0xFE);          // Clear recieve flag

		if (UART_Buffer_Size < UART_BUFFERSIZE)
		{
			UART_Buffer[UART_Input_First] = SBUF1;  // Store character
			UART_Buffer_Size++;            // Update array's size
			UART_Input_First++;            // Update counter
		}
	}

	if ((SCON1 & 0x02) == 0x02)         // Check if transmit flag is set
	{
		SCON1 = (SCON1 & 0xFD);			// Clear transmit flag
		if (UART_Buffer_Size > 0)       // If buffer not empty
		{
			// Check if a new word is being output
			if ( UART_Buffer_Size == UART_Input_First )  
			{
				UART_Output_First = 0;
			}

			// Store a character in the variable byte
			SBUF1 = UART_Buffer[UART_Output_First];

			//if ((Byte >= 0x61) && (Byte <= 0x7A))  // If lower case letter
			//{
			//	Byte -= 32;
			//}

			//SBUF1 = Byte;

			UART_Output_First++;           // Update counter
			UART_Buffer_Size--;            // Decrease array size
		}
		else
		{
			TX_Ready = 1;                   // Indicate transmission complete
		}
	}
}

void UART1_transmit(void)
{
	if(TX_Ready == 1)
	{
		TX_Ready = 0;                  // Set the flag to zero
		SCON1 = (SCON1 | 0x02);        // Set transmit flag to 1
	}
}

void UART1_parseData(void)
{
	if(UART_Buffer_Size > 0)
	{
		//switch(UART_Buffer[0])
		//{
		//	case FORWARD:
		//	case REVERSE:
		//		PCA_setDutyCycle(85);
		//		break;
		//	case RIGHT:
		//	case LEFT:
		//		PCA_setDutyCycle(60);
		//		break;
		//	case STOP:
		//		PCA_setDutyCycle(0);
		//		break;
		//}
		PCA_setDutyCycle(UART_Buffer[0]);
		PCA_setDirection(UART_Buffer[0]);
		UART1_transmit();
	}
}
