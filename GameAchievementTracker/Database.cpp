#include "stdafx.h"
#include "Database.h"
#include <iostream>

using namespace std;

vector<Player> Database::playerList;
vector<Game> Database::gameList;
vector<Achievement> Database::achievementList;

Player Database::newPlayer(int id, string name)
{
	Player newPlayer = Player(id, name);
	playerList.push_back(newPlayer);
	return newPlayer;
}

Game Database::newGame(int id, string name)
{
	Game newGame = Game(id, name);
	gameList.push_back(newGame);
	return newGame;
}

Achievement Database::newAchievement(int gameID, int achID, string achName, int pts)
{
	Achievement newAchievement = Achievement(gameID, achID, achName, pts);
	achievementList.push_back(newAchievement);
	getGameByID(gameID)->addToAchievementNumber();	//add to total number of game achievements
	return newAchievement;
}

//two parts so that both the game and player have reference:
//add ign and game id to player
//add ign and player id to game
Game* Database::playerPlays(int playerID, int gameID, string ign)
{
	//add ign and game id to player
	Player* thisPlayer = getPlayerByID(playerID);
	try{
		thisPlayer->addPlays(gameID, ign);
	}
	catch (...) //if player doesn't exist
	{
		cout << "Player at id " + to_string(playerID) + " doesn't exist.\n";
	}	

	//add ign and player id to game
	Game* thisGame = getGameByID(gameID);
	try{
		thisGame->addPlays(playerID, ign);
	}
	catch (...) //if game doesn't exist
	{
		cout << "Game at id " + to_string(gameID) + " doesn't exist.\n";
	}

	return thisGame;
}

void Database::makeFriends(int firstID, int secondID)
{
	//add ign and game id to player
	Player* firstPlayer = getPlayerByID(firstID);
	Player* secondPlayer = getPlayerByID(secondID);

	firstPlayer->addFriend(secondID);
	secondPlayer->addFriend(firstID);

	cout << "Friend list for " + firstPlayer->getName() + ":\n-----------\n";
	firstPlayer->printFriends();
	cout << "\nFriend list for " + secondPlayer->getName() + ":\n-----------\n";
	secondPlayer->printFriends();
}

void Database::achieved(int playerID, int gameID, int achievementID)
{
	//add id of achievement to player list
	Player* thisPlayer = getPlayerByID(playerID);
	/*Game* thisGame = getGameByID(gameID);
	Achievement* thisAchievement*/

	thisPlayer->addAchievement(gameID, achievementID);
	thisPlayer->printAchievements();
}

void Database::printFriendsWhoPlay(int playerID, int gameID)
{
	Player* thisPlayer = getPlayerByID(playerID);
	Game* thisGame = getGameByID(gameID);
	vector<int> friendList = thisPlayer->getFriendList();
	vector<pair<string, int>> gameIGNList = thisGame->getIGNList();
	cout << "Friends of " + thisPlayer->getName() + " who play " + thisGame->getName() + "\n--------------\n";

	//go through friend list
	for (int i = 0; i < friendList.size(); i++)
	{
		int currentFriendID = friendList.at(i);
		//go through the game's playerlist to see if the current friend plays it
		for (int j = 0; j < gameIGNList.size(); j++)
		{
			pair<string, int> thisIGN = gameIGNList.at(j);
			if (currentFriendID == thisIGN.second)
				cout << "Player " + getPlayerByID(currentFriendID)->getName() + " plays this game with IGN: " + thisIGN.first + "\n";
		}
	}
}

//for the game given by gameID, print achievement # and achievement pts for
//that game for each player
void Database::comparePlayers(int playerID1, int playerID2, int gameID)
{
	//number of achievements
	int totalAchievementNum = getGameByID(gameID)->getAchievementNumber();
	int player1NumCount = 0;
	int player2NumCount = 0;
	//points from achievements
	int player1PtCount = 0;
	int player2PtCount = 0;
	//players
	Player* firstPlayer = getPlayerByID(playerID1);
	Player* secondPlayer = getPlayerByID(playerID2);
	vector<pair<int, int>> p1Achievements = firstPlayer->getAchievementList();
	vector<pair<int, int>> p2Achievements = secondPlayer->getAchievementList();

	//tally first player
	for (int i = 0; i < p1Achievements.size(); i++)
	{
		//if achievement is for this game
		if (p1Achievements.at(i).first == gameID)
		{
			player1NumCount++;
			player1PtCount += getAchievementByID(p1Achievements.at(i).second)->getPoints();
		}
	}

	//tally second player
	for (int i = 0; i < p2Achievements.size(); i++)
	{
		//if achievement is for this game
		if (p2Achievements.at(i).first == gameID)
		{
			player2NumCount++;
			player2PtCount += getAchievementByID(p2Achievements.at(i).second)->getPoints();
		}
	}

	//output
	string player1Fraction = to_string(player1NumCount) + "/" + to_string(totalAchievementNum);
	string player2Fraction = to_string(player2NumCount) + "/" + to_string(totalAchievementNum);
	cout << "For the game " + getGameByID(gameID)->getName() + ":\n-------------------------------------------\n";
	cout << firstPlayer->getName() + ":\tAchievements: " + player1Fraction + "\tPoints (for this game): " + to_string(player1PtCount) + "\n";
	cout << secondPlayer->getName() + ":\tAchievements: " + player2Fraction + "\tPoints (for this game): " + to_string(player2PtCount) + "\n";
}



//accessors

Player* Database::getPlayerByID(int id)
{
	Player* thisPlayer = &Player();
	for (int i = 0; i < playerList.size(); i++)
	{
		//if player match
		if ((playerList.at(i).getID()) == id && (id != 0))
		{
			thisPlayer = &playerList.at(i);
			break;
		}
	}
	return thisPlayer;
}

Game* Database::getGameByID(int id)
{
	Game* thisGame = &Game();
	for (int i = 0; i < gameList.size(); i++)
	{
		//if player match
		if ((gameList.at(i).getID()) == id && (id != 0))
		{
			thisGame = &gameList.at(i);
			break;
		}
	}
	return thisGame;
}

Achievement* Database::getAchievementByID(int id)
{
	Achievement* thisAchievement = &Achievement();
	for (int i = 0; i < achievementList.size(); i++)
	{
		//if player match
		if ((achievementList.at(i).getID()) == id && (id != 0))
		{
			thisAchievement = &achievementList.at(i);
			break;
		}
	}
	return thisAchievement;
}

void Database::printPlayers()
{
	cout << "Current player list:\n----------------\n";
	for (int i = 0; i < playerList.size(); i++)
	{
		cout << playerList.at(i).toString();
	}
	cout << "----------------\n";
}

void Database::printGames()
{
	cout << "Current game list:\n----------------\n";
	for (int i = 0; i < gameList.size(); i++)
	{
		cout << gameList.at(i).toString();
	}
	cout << "----------------\n";
}

void Database::printAchievements()
{
	cout << "Current achievement list:\n----------------\n";
	for (int i = 0; i < achievementList.size(); i++)
	{
		cout << achievementList.at(i).toString();
	}
	cout << "----------------\n";
}
