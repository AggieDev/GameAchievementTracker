#include "stdafx.h"
#include "Database.h"
#include <iostream>
#include <algorithm>

using namespace std;

//must be defined here since static
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
	//retrieve references to both players to befriend
	Player* firstPlayer = getPlayerByID(firstID);
	Player* secondPlayer = getPlayerByID(secondID);

	firstPlayer->addFriend(secondID);
	secondPlayer->addFriend(firstID);

	//print friend lists
	cout << "Friend list for " + firstPlayer->getName() + ":\n-----------\n";
	firstPlayer->printFriends();
	cout << "\nFriend list for " + secondPlayer->getName() + ":\n-----------\n";
	secondPlayer->printFriends();
}

void Database::achieved(int playerID, int gameID, int achievementID)
{
	//add id of game and id of achievement achievement to player achievement list
	Player* thisPlayer = getPlayerByID(playerID);
	thisPlayer->addAchievement(gameID, achievementID);
	//print achievement list
	thisPlayer->printAchievements();
}

void Database::printFriendsWhoPlay(int playerID, int gameID)
{
	//retrieve references to player and game
	Player* thisPlayer = getPlayerByID(playerID);
	Game* thisGame = getGameByID(gameID);
	vector<int> friendList = thisPlayer->getFriendList();				//friend list
	vector<pair<string, int>> gameIGNList = thisGame->getIGNList();		//player playing list for game
	cout << "Friends of " + thisPlayer->getName() + " who play " + thisGame->getName() + "\n-----------------\n";

	//go through friend list
	for (int i = 0; i < friendList.size(); i++)
	{
		int currentFriendID = friendList.at(i);
		//go through the game's playerlist to see if the current friend plays it
		for (int j = 0; j < gameIGNList.size(); j++)
		{
			pair<string, int> thisIGN = gameIGNList.at(j);
			//if friend plays this game
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
	//achievements
	vector<pair<int, int>> p1Achievements = firstPlayer->getAchievementList();
	vector<pair<int, int>> p2Achievements = secondPlayer->getAchievementList();

	//tally first player
	for (int i = 0; i < p1Achievements.size(); i++)
	{
		//if achievement is for this game
		if (p1Achievements.at(i).first == gameID)
		{
			player1NumCount++;
			player1PtCount += getAchievementByID(gameID, p1Achievements.at(i).second)->getPoints();
		}
	}

	//tally second player
	for (int i = 0; i < p2Achievements.size(); i++)
	{
		//if achievement is for this game
		if (p2Achievements.at(i).first == gameID)
		{
			player2NumCount++;
			player2PtCount += getAchievementByID(gameID, p2Achievements.at(i).second)->getPoints();
		}
	}

	//output
	string player1Fraction = to_string(player1NumCount) + "/" + to_string(totalAchievementNum);
	string player2Fraction = to_string(player2NumCount) + "/" + to_string(totalAchievementNum);
	cout << "\nFor the game " + getGameByID(gameID)->getName() + ":\nPlayer name\tAchievements\tPoints (for this game)\n-------------------------------------------\n";
	cout << firstPlayer->getName() + "\t" + player1Fraction + "\t\t" + to_string(player1PtCount) + "\n";
	cout << secondPlayer->getName() + "\t" + player2Fraction + "\t\t" + to_string(player2PtCount) + "\n";
}

void Database::summarizePlayer(int playerID)
{
	Player* player = getPlayerByID(playerID);
	string name = player->getName();
	string gamerScore = to_string(player->getTotalGamerscore());
	vector<pair<string, int>> playsList = player->getPlaysList(); //string is ign, int is game id
	vector<int> friendList = player->getFriendList();

	//first part of printing: player name, gamerscore, each game playing summary
	cout << "\nPlayer: " + name + "\tTotal Gamerscore: " + gamerScore + " pts\n\n" +
		"Game name\tAchievements\tGamerscore\tIGN\n---------------------------------------------------\n";
	//for each game the player plays, print its summary for this player
	for (int i = 0; i < playsList.size(); i++)
		printPlayerGameSummary(i + 1, playerID, playsList.at(i).second, playsList.at(i).first);

	//second part of printing: friends and their gamerscores
	cout << "\nFriend name\tGamerscore\n---------------------------------------------------\n";
	//for each friend, print their summary (name and gamerscore)
	for (int i = 0; i < friendList.size(); i++)
		printPlayerFriendSummary(friendList.at(i));

}

//called from summarizePlayer()
//prints a line for the game when summarizing player
void Database::printPlayerGameSummary(int gameNum, int playerID, int gameID, string ign)
{
	Game* game = getGameByID(gameID);
	//first int is game id, second is achievement id
	vector<pair<int, int>> playerAchievements = getPlayerByID(playerID)->getAchievementList();
	string gameName = game->getName();
	string totalAchNumber = to_string(getGameByID(gameID)->getAchievementNumber());
	int achievementNumCount = 0;
	int achievementScore = 0;

	//tally achievements for this game
	for (int i = 0; i < playerAchievements.size(); i++)
	{
		//if achievement is for this game
		if (playerAchievements.at(i).first == gameID)
		{
			achievementNumCount++;
			achievementScore += getAchievementByID(gameID, playerAchievements.at(i).second)->getPoints();
		}
	}
	string scoreString = to_string(achievementScore);
	//use N/A instead of 0pts
	if (achievementScore == 0)
		scoreString = "N/A";
	else
		scoreString += " pts";

	//output
	string fraction = to_string(achievementNumCount) + "/" + totalAchNumber;
	cout << to_string(gameNum) + ". " + gameName + "\t" + fraction + "\t\t" + scoreString + "\t\t" + ign + "\n";
}

//called from summarizePlayer()
void Database::printPlayerFriendSummary(int friendID)
{
	//retrieve reference to friend
	Player* playerFriend = getPlayerByID(friendID);
	string name = playerFriend->getName();
	string gamerscore = to_string(playerFriend->getTotalGamerscore()) + " pts";
	//output
	cout << name + "\t" + gamerscore + "\n";
}

void Database::summarizeGame(int gameID)
{
	Game* thisGame = getGameByID(gameID);
	//string is ign, int is player id
	vector<pair<string, int>> ignList = thisGame->getIGNList();
	cout << "\nPlayers who have played " + thisGame->getName() + ":\nName\t\tIGN\n------------------------\n";
	//print players who've played game, as well as their igns
	for (int i = 0; i < ignList.size(); i++)
		cout << getPlayerByID(ignList.at(i).second)->getName() + "\t\t" + ignList.at(i).first + "\n";

	cout << "\nTimes each achievement achieved for this game:\nName\t\t# achieved across players\n-----------------------------------\n";
	//iterate through achievement list
	for (int i = 0; i < achievementList.size(); i++)
	{
		//if achievement is for this game
		if (achievementList.at(i).getGameID() == gameID)
		{
			int achievementCounter = 0;
			//iterate through each player who plays this game to see if they have achievement
			for (int j = 0; j < ignList.size(); j++)
			{
				//if this player has achievement
				if (getPlayerByID(ignList.at(j).second)->playerHasAchievement(gameID, achievementList.at(i).getID()))
					achievementCounter++;
			}
			cout << achievementList.at(i).getName() + "\t" + to_string(achievementCounter) + "\n";
		}
	}
}

void Database::summarizeAchievement(int gameID, int achID)
{
	int achievementCounter = 0;	//how many players have achievement
	int playersPlayingGame = 0;	//how many players play game
	vector<pair<string, int>> ignList = getGameByID(gameID)->getIGNList();
	//find number of players that play the game this achievement belongs to
	for (int i = 0; i < ignList.size(); i++)
		playersPlayingGame++;

	cout << "\nPlayer IGNs that have the achievement '" + getAchievementByID(gameID, achID)->getName() +
		"' from the game '" + getGameByID(gameID)->getName() + "':\n---------------------------------------------------------\n";
	//find players that have this achievement
	for (int i = 0; i < ignList.size(); i++)
	{
		//if player has achievement
		if (getPlayerByID(ignList.at(i).second)->playerHasAchievement(gameID, achID))
		{
			achievementCounter++;
			cout << getPlayerByID(ignList.at(i).second)->getName() + "\n";
		}
	}

	//output
	string fraction = to_string(achievementCounter) + "/" + to_string(playersPlayingGame) + " or ";
	string percentage = to_string(((float)achievementCounter / (float)playersPlayingGame) * 100.0f) + "%\n";
	cout << "\nPercentage of IGNs that have achievement: " + fraction + percentage;
}

void Database::achievementRanking()
{
	cout << "\nAchievement Ranking:\n-------------------\n";
	
	vector<pair<int, string>> playersInOrder;
	//iterate through players and make each into a pair<int, string> to sort
	for (int i = 0; i < playerList.size(); i++)
		playersInOrder.push_back(make_pair(playerList.at(i).getTotalGamerscore(), playerList.at(i).getName()));
	//use sort from library <algoritm>, using function comparison() to sort descending by gamerscore
	sort(playersInOrder.begin(), playersInOrder.end(), comparison);
	//once sorted, print players
	for (int i = 0; i < playerList.size(); i++)
		cout << to_string(i+1) + ". " + playersInOrder.at(i).second + "\t\t" + to_string(playersInOrder.at(i).first) + " pts\n";

}

//used for sorting in achievementRanking()
bool Database::comparison(pair<int, string> i, pair<int, string> j)
{
	return (i.first>j.first);
}

//accessors

//retrieve player at given id
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

//retrieve game at given id
Game* Database::getGameByID(int id)
{
	Game* thisGame = &Game();
	for (int i = 0; i < gameList.size(); i++)
	{
		//if game match
		if ((gameList.at(i).getID()) == id && (id != 0))
		{
			thisGame = &gameList.at(i);
			break;
		}
	}
	return thisGame;
}

//retrieve achievement at given gameID and achievementID
Achievement* Database::getAchievementByID(int gameID, int achID)
{
	Achievement* thisAchievement = &Achievement();
	for (int i = 0; i < achievementList.size(); i++)
	{
		//if achievement match
		if ((achievementList.at(i).getGameID() == gameID) && (achievementList.at(i).getID() == achID) && (achID != 0))
		{
			thisAchievement = &achievementList.at(i);
			break;
		}
	}
	return thisAchievement;
}

//printouts for each additional player/game/achievement

void Database::printPlayers()
{
	cout << "\nCurrent player list:\n-------------------\n";
	for (int i = 0; i < playerList.size(); i++)
	{
		cout << playerList.at(i).toString();
	}
	cout << "\n";
}

void Database::printGames()
{
	cout << "\nCurrent game list:\n------------------\n";
	for (int i = 0; i < gameList.size(); i++)
	{
		cout << gameList.at(i).toString();
	}
	cout << "\n";
}

void Database::printAchievements()
{
	cout << "\nCurrent achievement list:\n-----------------------\n";
	for (int i = 0; i < achievementList.size(); i++)
	{
		cout << achievementList.at(i).toString();
	}
	cout << "\n";
}
