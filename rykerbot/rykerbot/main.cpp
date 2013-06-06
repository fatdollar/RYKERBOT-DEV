#include "stdafx.h"

//GLOBALS
int endProgram = 0;
int port = 0;

void main(int argc, char* argv[])
{
	unsigned char input;
	if(argc > 0)
	{
		port = MAIN_getPort(argv[1]);
	}
	else
	{
		cout << "No port number entered.\nPlease enter the desired port number.\n\nrykerbot.exe 13";
		return;
	}
	MAIN_Showsplash();
	//SERIAL_findDevice();
	while(!endProgram)
	{
		input = MAIN_getInput();
		//if(input)
		//	cout << input << endl;
		MAIN_parseInput(input);
		//else
			//SERIAL_readWrite(port,STOP);
	}
}

unsigned char MAIN_getInput()
{
	unsigned char ch;
	if(_kbhit())
	{
		ch = _getch();
		if (ch == 0xE0)
			return _getch();
		else
			return ch;
	}
	return STOP;
}

int MAIN_getPort(char* asciiPort)
{
	int length = 0, i = 0, intPort = 0;
	while (asciiPort[length++] != '\0');
	for(; i < length - 1; i++)
		intPort += (asciiPort[i] - 0x30);
	return intPort;
}

void MAIN_parseInput(unsigned char ch)
{
	switch(ch)
	{
		case 0x48://up arrow
			SERIAL_readWrite(port,(unsigned char)FORWARD);
			//cout << "Forward\n";
			break;
		case 0x50://down arrow
			SERIAL_readWrite(port,(unsigned char)REVERSE);
			//cout << "Reverse\n";
			break;
		case 0x4B://left arrow
			SERIAL_readWrite(port,(unsigned char)LEFT);
			//cout << "Left\n";
			break;
		case 0x4D://right arrow
			SERIAL_readWrite(port,(unsigned char)RIGHT);
			//cout << "Right\n";
			break;
		case 0x3F://'?'
			MAIN_Showsplash();
			break;
		case 0x71://'q'
			endProgram = 1;
			break;
		case STOP:
			SERIAL_readWrite(port,(unsigned char)STOP);
			break;
	}
}

void MAIN_Showsplash()
{
	//name and info
	cout << SPLASHSCREEN1 << SPLASHSCREEN2 << SPLASHSCREEN3;
	cout << SPLASHSCREEN4 << SPLASHSCREEN5 << SPLASHSCREEN6;
	cout << SPLASHSCREEN7 << SPLASHSCREEN8 << SPLASHSCREEN9;
	//command list-to come
	cout << COMMAND1;
}
