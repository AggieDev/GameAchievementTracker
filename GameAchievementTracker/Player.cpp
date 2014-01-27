#include "stdafx.h"
#include "Player.h"
#include "Achievement.h"
#include "Database.h"
#include <iostream>

Player::Player()
{
}
Player::~Player()
{
}

Player::Player(int i, string n)
{
	id = i;
	name = n;
}

//add to list of games that player plays, as well as ign for that game
void Player::addPlays(int gameID, string ign)
{
	playsList.push_back(make_pair(ign, gameID));
}

//return if player has given achievement
bool Player::playerHasAchievement(int gameID, int achID)
{
	for (int i = 0; i < achievementList.size(); i++)
	{
		//if player has achievement
		if ((achievementList.at(i).first == gameID) && (achievementList.at(i).second == achID))
			return true;
	}
	return false; //achievement not found for player
}


//accessors

string Player::toString()
{
	return "Name: " + name + " ID: " + to_string(id) + "\n";
}

int Player::getTotalGamerscore()
{
	int gamerScore = 0;
	//tally achievement score for all achieved achievements
	for (int i = 0; i < achievementList.size(); i++)
	{
		Achievement* thisAchievement = Database::getAchievementByID(achievementList.at(i).first, achievementList.at(i).second);
		gamerScore += thisAchievement->getPoints();
	}
	//return total
	return gamerScore;
}

//test printing

void Player::printGamesPlay()
{
	for (int i = 0; i < playsList.size(); i++)
		cout << "Player ID: " + to_string(id) + " Player IGN: " + playsList.at(i).first + " Game ID: " + to_string(playsList.at(i).second) + "\n";
}

void Player::printFriends()
{
	for (int i = 0; i < friendList.size(); i++)
		cout << "Friend with ID of " + to_string(friendList.at(i)) + "\n";
}

void Player::printAchievements()
{
	cout << "\n" + name + " has the following achievements:\n-------------------------\n";
	for (int i = 0; i < achievementList.size(); i++)
		cout << "Achievement with id of " + to_string(achievementList.at(i).second) + " from game with id of " + to_string(achievementList.at(i).first) + "\n";
}