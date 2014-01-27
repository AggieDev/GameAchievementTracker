// GameAchievementTracker.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Database.h"

using namespace std;

//following 2 functions are used to split a string, used to parse input splitting by spaces
vector<string> &split(const string &str, char chr, vector<string> &list) {
	stringstream ss(str);
	string item;
	while (getline(ss, item, chr)) {
		list.push_back(item);
	}
	return list;
}
vector<string> split(const string &str, char chr) {
	vector<string> vecList;
	split(str, chr, vecList);
	return vecList;
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
			playerName = arguments.at(2);
		Database::newPlayer(atoi(arguments.at(1).c_str()), playerName);
		Database::printPlayers();
	}
	catch (out_of_range)
	{
		cout << "Wrong parameters used. Try AddPlayer <Player ID> <Player Name>\n";
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
			gameName = arguments.at(2);
		Database::newGame(atoi(arguments.at(1).c_str()), gameName);
		Database::printGames();
	}
	catch (out_of_range)
	{
		cout << "Wrong parameters used. Try AddGame <Game ID> <Game Name>\n";
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
			for (int i = 3; i < arguments.size() - 1; i++)	//add all but last
				name += arguments.at(i) + " ";
			name = removeQuotes(name);
		}
		else
			name = arguments.at(3);
		Database::newAchievement(atoi(arguments.at(1).c_str()), atoi(arguments.at(2).c_str()), name, atoi(arguments.at(arguments.size() -1).c_str()));
		Database::printAchievements();
	}
	catch (out_of_range e)
	{
		cout << "Wrong parameters used. Try AddAchievement <Game ID> <Achievement ID> <Achievement Name> <Achievement Points>\n";
	}
}

void addPlays(vector<string> arguments)
{
	try
	{
		string ign = "";
		if (arguments.at(3).substr(0, 1) == "\"")	//if begins with quote, add words in quotes to game name
		{
			cout << "starts with quote\n";
			for (int i = 3; i < arguments.size(); i++)	//add the rest
				ign += arguments.at(i) + " ";
			ign = removeQuotes(ign);
		}
		else
			ign = arguments.at(3);
		Game* newPlays = Database::playerPlays(atoi(arguments.at(1).c_str()), atoi(arguments.at(2).c_str()), ign);
		//used for testing
		newPlays->printGamesPlay();
	}
	catch (out_of_range e)
	{
		cout << "Wrong parameters used. Try Plays <Player ID> <Game ID> <Player IGN>\n";
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
		addPlays(arguments);
	else if (functionCall == "AddFriends")
		Database::makeFriends(atoi(arguments.at(1).c_str()), atoi(arguments.at(2).c_str()));
	else if (functionCall == "Achieve")
		Database::achieved(atoi(arguments.at(1).c_str()), atoi(arguments.at(2).c_str()), atoi(arguments.at(3).c_str()));
	else if (functionCall == "FriendsWhoPlay")
		Database::printFriendsWhoPlay(atoi(arguments.at(1).c_str()), atoi(arguments.at(2).c_str()));
	else if (functionCall == "ComparePlayers")
		Database::comparePlayers(atoi(arguments.at(1).c_str()), atoi(arguments.at(2).c_str()), atoi(arguments.at(3).c_str()));
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
			determineFunction(inputVec);
		}
	}
	return 0;
}

