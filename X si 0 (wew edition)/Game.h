#include "Load.h"
#include "Meniu.h"

#pragma once



class Game
{
public:
	Game();
	GameState gameState = GameState::PLAYMENIU;
	Meniu meniu;
	void playGame();
	
	
};

