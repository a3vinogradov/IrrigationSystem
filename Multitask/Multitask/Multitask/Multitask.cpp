// Multitask.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <conio.h>
#include "ArduinoEmul.h"

using namespace std;
int main()
{
	Setup();
	while (1) {
		Loop();
		if (_kbhit() && _getch() == 27) break;
	}
}


