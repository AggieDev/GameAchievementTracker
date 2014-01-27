#pragma once
#include <string>
#include <vector>

using namespace std;

class Player
{
	//private
	int id;
	string name;
	vector<pair<string, int>> playsList;	//list of player's in-game names with the game id's
	vector<int> friendList;					//id's of friends
	vector<pair<int, int>> achievementList; //first int is game id, second is achievement id
public:
	Player();
	~Player();
	Player(int id, string name);
	//add to player
	void addPlays(int gameID, string ign);
	void addFriend(int id){ friendList.push_back(id); };
	void addAchievement(int gameID, int achievementID){ achievementList.push_back(make_pair(gameID, achievementID)); };
	//return if player has given achievement
	bool playerHasAchievement(int gameID, int achID);

	//public accessors
	string toString();
	int getID(){ return id; };
	string getName(){ return name; };
	vector<pair<string, int>> getPlaysList(){ return playsList; };
	vector<int> getFriendList(){ return friendList; };
	vector<pair<int, int>> getAchievementList(){ return achievementList; };
	int getTotalGamerscore();

	//test printing
	void printGamesPlay();
	void printFriends();
	void printAchievements();
};
