#include "stdafx.h"

void SERIAL_findDevice()
{
	HKEY hKey = 0;
	TCHAR buf[255] = {0};
	DWORD dwBufSize = sizeof(buf)/sizeof(TCHAR);
 
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"), NULL, KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS)
	{
			MessageBox(0, TEXT("Can't open key."), NULL, MB_OK);
	}
	else if(RegQueryValueEx(hKey, TEXT("\\Device\\FTDI"), NULL, NULL, (LPBYTE)buf, &dwBufSize) != ERROR_SUCCESS)
	{
		MessageBox(0, TEXT("Can't query key."),NULL, MB_OK);
	}
	else
		wcout << "key value is '" << buf << "'\n";
 
	RegCloseKey(hKey);
}

unsigned char SERIAL_readWrite(int port, unsigned char data)
{
	unsigned char INBUFFER;//[6];
    unsigned char OUTBUFFER;//[6];
	char buffer[20];
	char temp[255];
	INBUFFER = 0;//[0] = 0;
    DWORD bytes_read    = 0;    // Number of bytes read from port
    DWORD bytes_written = 0;    // Number of bytes written to the port
    HANDLE comport = NULL;  // Handle COM port
	int   bStatus;
    DCB          comSettings;          // Contains various port settings
    COMMTIMEOUTS CommTimeouts;
	// Set Parameters
	strcpy(buffer, "\\\\.\\COM");
	stringstream s1;
	s1 << port;
	s1 >> temp;
	strcat(buffer, temp);
	//for(int x = 0 ; x < 6 ; x++)
	//	OUTBUFFER[x] = data[x];
	OUTBUFFER = data;
    // Open COM port
	wchar_t buf[20];
	mbstowcs(buf, buffer, 20);
    if ((comport = 
         CreateFile(buf,                // open com6:
                    GENERIC_READ | GENERIC_WRITE, // for reading and writing
                    0,                            // exclusive access
                    NULL,                         // no security attributes
                    OPEN_EXISTING,              
                    FILE_ATTRIBUTE_NORMAL,
                    NULL)) == INVALID_HANDLE_VALUE)
    {
        // error processing code goes here
    }
    // Set timeouts in milliseconds
    CommTimeouts.ReadIntervalTimeout         = 0; 
    CommTimeouts.ReadTotalTimeoutMultiplier  = 0; 
    CommTimeouts.ReadTotalTimeoutConstant    = 100;
    CommTimeouts.WriteTotalTimeoutMultiplier = 0;
    CommTimeouts.WriteTotalTimeoutConstant   = 100;
    bStatus = SetCommTimeouts(comport,&CommTimeouts);
    if (bStatus != 0)
    {
        // error processing code goes here
    }
    // Set Port parameters.
    // Make a call to GetCommState() first in order to fill
    // the comSettings structure with all the necessary values.
    // Then change the ones you want and call SetCommState().
    GetCommState(comport, &comSettings);
    comSettings.BaudRate = 9600;
    comSettings.StopBits = ONESTOPBIT;
    comSettings.ByteSize = 8;
    comSettings.Parity   = NOPARITY;
    comSettings.fParity  = FALSE;
    bStatus = SetCommState(comport, &comSettings);
    if (bStatus == 0)
    {
        // error processing code goes here
    }
    bStatus = WriteFile(comport,              // Handle
         &OUTBUFFER,      // Outgoing data
         6,              // Number of bytes to write
         &bytes_written,  // Number of bytes written
         NULL);
         if (bStatus != 0)
         {
            //error writing to comm port
		 }
        bStatus = ReadFile(comport,   // Handle
                &INBUFFER,            // Incoming data
                1,                  // Number of bytes to read
                &bytes_read,          // Number of bytes read
                NULL);
        if (bStatus != 0)
        {
            // error processing code goes here
        }
        
    CloseHandle(comport);
	return INBUFFER;//acknowledgement code
}
//int writePort(int port, char *data)
//	{
//    DWORD        bytes_read    = 0;    // Number of bytes read from port
//    DWORD        bytes_written = 0;    // Number of bytes written to the port
//    HANDLE       comport      = NULL;  // Handle COM port
//	int   bStatus;
//    DCB          comSettings;          // Contains various port settings
//    COMMTIMEOUTS CommTimeouts;
//    // Open COM port
//
//	unsigned char OUTBUFFER[6];
//	// Assign Packet
//	for(int x = 0 ; x < 6 ; x++)
//		OUTBUFFER[x] = data[x];
//	
//	char BUFFER[255];
//	char TEMP[255];
//	stringstream s1;
//	strcpy(BUFFER, "\\\\.\\COM");
//	s1 << port;
//	s1 >> TEMP;
//	strcat(BUFFER, TEMP);
//
//    if ((comport = 
//         CreateFile(BUFFER,                // open com6:
//                    GENERIC_WRITE, // for reading and writing
//                    0,                            // exclusive access
//                    NULL,                         // no security attributes
//                    OPEN_EXISTING,              
//                    FILE_ATTRIBUTE_NORMAL,
//                    NULL)) == INVALID_HANDLE_VALUE)
//    {
//        // error processing code goes here
//    }
//    // Set timeouts in milliseconds
//    CommTimeouts.ReadIntervalTimeout         = 0; 
//    CommTimeouts.ReadTotalTimeoutMultiplier  = 0; 
//    CommTimeouts.ReadTotalTimeoutConstant    = 100;
//    CommTimeouts.WriteTotalTimeoutMultiplier = 0;
//    CommTimeouts.WriteTotalTimeoutConstant   = 100;
//    bStatus = SetCommTimeouts(comport,&CommTimeouts);
//    if (bStatus != 0)
//    {
//        // error processing code goes here
//    }
//    // Set Port parameters.
//    // Make a call to GetCommState() first in order to fill
//    // the comSettings structure with all the necessary values.
//    // Then change the ones you want and call SetCommState().
//    GetCommState(comport, &comSettings);
//    comSettings.BaudRate = 9600;
//    comSettings.StopBits = ONESTOPBIT;
//    comSettings.ByteSize = 8;
//    comSettings.Parity   = NOPARITY;
//    comSettings.fParity  = FALSE;
//    bStatus = SetCommState(comport, &comSettings);
//    if (bStatus == 0)
//    {
//        // error processing code goes here
//    }
//    bStatus = WriteFile(comport,              // Handle
//       OUTBUFFER,      // Outgoing data
//       6,              // Number of bytes to write
//       &bytes_written,  // Number of bytes written
//       NULL);
//    //CloseHandle(comport);
// return 0;
//}
//int readPort(int port, unsigned char *data)
//{
//    DWORD        bytes_read    = 0;    // Number of bytes read from port
//    DWORD        bytes_written = 0;    // Number of bytes written to the port
//    HANDLE       comport      = NULL;  // Handle COM port
//	int   bStatus;
//	unsigned char INBUFFER[6];
//	char BUFFER[255];
//	char TEMP[255];
//	stringstream s1;
//	strcpy(BUFFER, "\\\\.\\COM");
//	s1 << port;
//	s1 >> TEMP;
//	strcat(BUFFER, TEMP);
//
//    DCB          comSettings;          // Contains various port settings
//    COMMTIMEOUTS CommTimeouts;
//    // Open COM port
//    if ((comport = 
//         CreateFile(BUFFER,                // open com6:
//                    GENERIC_READ, // for reading and writing
//                    0,                            // exclusive access
//                    NULL,                         // no security attributes
//                    OPEN_EXISTING,              
//                    FILE_ATTRIBUTE_NORMAL,
//                    NULL)) == INVALID_HANDLE_VALUE)
//    {
//        // error processing code goes here
//    }
//    // Set timeouts in milliseconds
//    CommTimeouts.ReadIntervalTimeout         = 0; 
//    CommTimeouts.ReadTotalTimeoutMultiplier  = 0; 
//    CommTimeouts.ReadTotalTimeoutConstant    = 100;
//    CommTimeouts.WriteTotalTimeoutMultiplier = 0;
//    CommTimeouts.WriteTotalTimeoutConstant   = 100;
//    bStatus = SetCommTimeouts(comport,&CommTimeouts);
//    if (bStatus != 0)
//    {
//        // error processing code goes here
//    }
//    // Set Port parameters.
//    // Make a call to GetCommState() first in order to fill
//    // the comSettings structure with all the necessary values.
//    // Then change the ones you want and call SetCommState().
//    GetCommState(comport, &comSettings);
//    comSettings.BaudRate = 9600;
//    comSettings.StopBits = ONESTOPBIT;
//    comSettings.ByteSize = 8;
//    comSettings.Parity   = NOPARITY;
//    comSettings.fParity  = FALSE;
//    bStatus = SetCommState(comport, &comSettings);
//    if (bStatus == 0)
//    {
//        // error processing code goes here
//    }
//        bStatus = ReadFile(comport,   // Handle
//                INBUFFER,            // Incoming data
//                6,                  // Number of bytes to read
//                &bytes_read,          // Number of bytes read
//                NULL);
//        if (bStatus != 0)
//        {
//            // error processing code goes here
//        }
//    //CloseHandle(comport);
// return 0;
//}