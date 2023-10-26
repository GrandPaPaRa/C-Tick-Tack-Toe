#include "Game.h"



Game::Game()
{
	while (gameState!=GameState::EXIT) {
		if (gameState == GameState::PLAYMENIU)
			meniu.playMeniu(gameState);
		else if (gameState == GameState::PLAYGAME)
			playGame();
	}
}

void Game::playGame() {
	Load load;
	bool isdone = false;
	while (!isdone) {
		load.playerTurn();
		isdone = (load.checkWinner() || load.checkTie());
	}
	load.winState(gameState);
}

