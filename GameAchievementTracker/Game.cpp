#include "stdafx.h"
#include "Game.h"

using namespace std;

Game::Game()
{
}


Game::~Game()
{
}

Game::Game(int i, string n)
{
	id = i;
	name = n;
}

string Game::toString()
{
	return "Name: " + name + " ID: " + to_string(id) + "\n";
}

void Game::addIGN(int id, string name)
{
	ignList.push_back(make_pair(name, id));
}