#include "common.h"


void Console::startError(bool detail)
{
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), detail ? 4 : 12);
}
void Console::stopError()
{
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}