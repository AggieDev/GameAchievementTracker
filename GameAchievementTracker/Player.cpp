#include "stdafx.h"
#include "Player.h"


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

string Player::toString()
{
	return "Name: " + name + " ID: " + to_string(id) + "\n";
}