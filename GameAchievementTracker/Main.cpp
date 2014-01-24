// GameAchievementTracker.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Database.h"

using namespace std;

//following 2 functions are used to split a string, used to parse input splitting by spaces
vector<string> &split(const string &s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}
vector<string> split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}

void determineFunction(vector<string> arguments)
{
	string functionCall = arguments.at(0);
	if (functionCall == "AddPlayer")
	{
		cout << "Adding player...\n";
		try
		{
			Database::newPlayer(atoi(arguments.at(1).c_str()), arguments.at(2));
			Database::printPlayers();
		}
		catch (out_of_range)
		{
			cout << "Wrong parameters used.\n";
		}
	}
	else if (functionCall == "AddGame")
	{
		cout << "Adding game...\n";
	}
	else if (functionCall == "AddAchievement")
	{
		cout << "Adding achievement...\n";
	}
	else if (functionCall == "Plays")
	{
		cout << "Adding player playing game...\n";
	}
	else if (functionCall == "AddFriends")
	{
		cout << "Adding friends...\n";
	}
	else if (functionCall == "Achieve")
	{
		cout << "Adding achievement to player...\n";
	}
	else if (functionCall == "FriendsWhoPlay")
	{
		cout << "Showing which friends play the game...\n";
	}
	else if (functionCall == "ComparePlayers")
	{
		cout << "Comparing players...\n";
	}
	else if (functionCall == "SummarizePlayer")
	{
		cout << "Showing player summary...\n";
	}
	else if (functionCall == "SummarizeGame")
	{
		cout << "Showing game summary...\n";
	}
	else if (functionCall == "SummarizeAchievement")
	{
		cout << "Showing achievement summary...\n";
	}
	else if (functionCall == "AchievementRanking")
	{
		cout << "Showing achievement ranking...\n";
	}
	else
		cout << "Command '" + functionCall + "' is not valid.\n";
}

int _tmain(int argc, _TCHAR* argv[])
{
	string input = "";
	while (!(input == "exit"))
	{
		cout << "Enter a command, or 'exit' to end program:\n";
		getline(cin, input);
		//so that on the exit prompt it doesn't parse as an achievement command
		if (!(input == "exit"))
		{
			vector<string> inputVec = split(input, ' ');
			//test split by string
			/*for (int i = 0; i < inputVec.size(); i++)
				cout << inputVec.at(i) + "\n";*/
			determineFunction(inputVec);
		}
	}
	return 0;
}

