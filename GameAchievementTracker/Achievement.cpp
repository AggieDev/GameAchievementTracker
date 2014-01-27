#include "stdafx.h"
#include "Achievement.h"

using namespace std;

Achievement::Achievement()
{
}
Achievement::~Achievement()
{
}

Achievement::Achievement(int gID, int achID, string n, int p)
{
	gameID = gID;
	id = achID;
	name = n;
	points = p;
}

//print out achievement data
string Achievement::toString()
{
	return "Name: " + name + " ID: " + to_string(id) + " GameID: " + to_string(gameID) + " Points: " + to_string(points) + "\n";
}
