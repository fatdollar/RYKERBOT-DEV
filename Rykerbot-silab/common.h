#include <c8051f020.h>
#include "main.h"
#include "UART.h"
#include "PCA.h"

#define VERSION 0001

//opcodes
#define FORWARD 0x01
#define REVERSE 0x02
#define LEFT 0x03
#define RIGHT 0x04
#define STOP 0x05