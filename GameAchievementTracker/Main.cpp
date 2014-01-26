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

string removeQuotes(string str)
{
	return str.substr(1, str.length() - 3);
}

void addPlayer(vector<string> arguments)
{
	try //try/catch to throw exception if user parameters arent correct
	{
		// support quotes for name
		string playerName = "";
		if (arguments.at(2).substr(0, 1) == "\"")	//if begins with quote, add words in quotes to player name
		{
			for (int i = 2; i < arguments.size(); i++)
				playerName += arguments.at(i) + " ";
			playerName = removeQuotes(playerName);
		}
		else
			playerName = arguments.at(3);
		Database::newPlayer(atoi(arguments.at(1).c_str()), playerName);
		Database::printPlayers();
	}
	catch (out_of_range)
	{
		cout << "Wrong parameters used.\n";
	}
}

void addGame(vector<string> arguments)
{
	try	//try/catch to throw exception if user parameters arent correct
	{
		//support quotes for name
		string gameName = "";
		if (arguments.at(2).substr(0, 1) == "\"")	//if begins with quote, add words in quotes to game name
		{
			for (int i = 2; i < arguments.size(); i++)
				gameName += arguments.at(i) + " ";
			gameName = removeQuotes(gameName);
		}
		else
			gameName = arguments.at(3);
		Database::newGame(atoi(arguments.at(1).c_str()), gameName);
		Database::printGames();
	}
	catch (out_of_range)
	{
		cout << "Wrong parameters used.\n";
	}
}

void addAchievement(vector<string> arguments)
{
	try	//try/catch to throw exception if user parameters arent correct
	{
		//support quotes for name
		string name = "";
		if (arguments.at(3).substr(0, 1) == "\"")	//if begins with quote, add words in quotes to game name
		{
			for (int i = 3; i < arguments.size(); i++)
			{
				//if not end quote, keep adding
				if (arguments.at(i).substr(arguments.at(i).length() - 2, arguments.at(i).length() - 1) != "\"")
					name += arguments.at(i) + " ";
				else //else finish adding to name
				{
					name += arguments.at(i) + " ";
					break;
				}
			}
			name = removeQuotes(name);
		}
		else
			name = arguments.at(3);
		Database::newAchievement(atoi(arguments.at(1).c_str()), atoi(arguments.at(2).c_str()), name, atoi(arguments.at(arguments.size() -1).c_str()));
		Database::printAchievements();
	}
	catch (out_of_range e)
	{
		cout << "Wrong parameters used.\n" + e.what();
	}
}

void determineFunction(vector<string> arguments)
{
	string functionCall = arguments.at(0);
	if (functionCall == "AddPlayer")
		addPlayer(arguments);
	else if (functionCall == "AddGame")
		addGame(arguments);
	else if (functionCall == "AddAchievement")
		addAchievement(arguments);
	else if (functionCall == "Plays")
		cout << "Adding player playing game...\n";
	else if (functionCall == "AddFriends")
		cout << "Adding friends...\n";
	else if (functionCall == "Achieve")
		cout << "Adding achievement to player...\n";
	else if (functionCall == "FriendsWhoPlay")
		cout << "Showing which friends play the game...\n";
	else if (functionCall == "ComparePlayers")
		cout << "Comparing players...\n";
	else if (functionCall == "SummarizePlayer")
		cout << "Showing player summary...\n";
	else if (functionCall == "SummarizeGame")
		cout << "Showing game summary...\n";
	else if (functionCall == "SummarizeAchievement")
		cout << "Showing achievement summary...\n";
	else if (functionCall == "AchievementRanking")
		cout << "Showing achievement ranking...\n";
	else
		cout << "Command '" + functionCall + "' is not valid.\n";
}

int _tmain(int argc, _TCHAR* argv[])
{
	string input = "";
	while (!(input == "exit"))
	{
		cout << "\nEnter a command, or 'exit' to end program:\n";
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

