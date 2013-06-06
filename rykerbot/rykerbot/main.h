//splash screen
#define SPLASHSCREEN1 "//**********************************************\\\\\n"
#define SPLASHSCREEN2 "//\t ___              __  ___      \t\t\\\\\n"
#define SPLASHSCREEN3 "//\t|   | |   | |  / |   |   | |         \t\\\\\n"
#define SPLASHSCREEN4 "//\t| __| |___| |_/  |__ | __| |_   _  |_\t\\\\\n"
#define SPLASHSCREEN5 "//\t| \\     |   | \\  |   | \\   | | | | | \t\\\\\n"
#define SPLASHSCREEN6 "//\t|  \\    |   |  \\ |__ |  \\  |_| |_| |_\t\\\\\n"
#define SPLASHSCREEN7 "//\tcreated by: Johnathan Nielsen\t\t\\\\\n"
#define SPLASHSCREEN8 "//\tversion 0.0.0.1\t\tcopyright 2012\t\\\\\n"
#define SPLASHSCREEN9 "//**********************************************\\\\\n"

//command list
#define COMMAND1 "?-print command list\tq-quit program\n"

int MAIN_getPort(char* asciiPort);
unsigned char MAIN_getInput();
void MAIN_parseInput(unsigned char ch);
void MAIN_Showsplash();