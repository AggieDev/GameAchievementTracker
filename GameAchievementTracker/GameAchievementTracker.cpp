// GameAchievementTracker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	string input = "";
	while (!(input == "exit"))
	{
		cout << "Enter a command, or 'exit' to end program:\n";
		getline(cin, input);
		cout << "last";
	}
	return 0;
}

