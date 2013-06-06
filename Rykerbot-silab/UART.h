#define SYSTEMCLOCK (22118400L)
#define BAUDRATE 9600
#define UART_BUFFERSIZE 64

//communication control
#define ACK 0xFF
#define NACK 0x0D

//Function Prototypes
void UART1_init(void);		// Initialize UART1
void UART1_transmit(void);	// Transmit from UART_Buffer
void UART1_parseData(void);		// Check received data and execute commands
