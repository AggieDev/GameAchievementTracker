#pragma once
#include <string>

class Achievement
{
	//private
	int gameID, id, points;
	std::string name;
public:
	Achievement();
	~Achievement();
	Achievement(int gameID, int id, std::string name, int points);
	std::string toString();

	//accessors
	int getID(){ return id; };
	int getPoints(){ return points; };
};

