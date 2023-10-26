#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

#pragma once

enum class PlayerTurn { XPLAYER, OPLAYER, TIE};
enum class GameState { EXIT,PLAYMENIU,PLAYGAME };

struct Board {
	char cha;
	bool verif;
};

class Load
{
public:
	//fct
	Load();
	~Load();
	
	void playerTurn();
	bool checkWinner();
	bool checkTie(); //tot deodata reinitializeaza toate patratele _board[i][j].verif = false
	void winState(GameState &gameState);

private:
	//var
	Board** _board;
	int _size;
	int _distance;
	PlayerTurn _turn;
	//fct
	void print();
	void subPrint(int nr, char cha);
	void input();
	bool checkInput(int y,int x);
	
	int checkXAxis(int y, int x, char cha);
	int checkYAxis(int y, int x, char cha);
	int checkFirstDiag(int y, int x, char cha);
	int checkSecondDiag(int y, int x, char cha);

};

