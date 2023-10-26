#include "Load.h"





Load::Load()
{
	//initierea variabilelor retinute din optiuni
	ifstream input("Latura.txt");
	ifstream input2("Distanta.txt");

	input >> _size;
	input2 >> _distance;
	//incarcarea tablei folosind vector dinamici
	_board = new Board*[_size];
	for (int i = 0; i < _size; i++) {
		_board[i] = new Board[_size];
	}
	for (int i = 0; i < _size; i++)
		for (int j = 0; j < _size; j++) {
			_board[i][j].cha = ' ';
			_board[i][j].verif = false;
		}
	//initierea unor variabile
	_turn = PlayerTurn::XPLAYER;

}

Load::~Load()
{
	//stergerea memoriei
	for (int i = 0; i < _size; i++)
		delete[] _board[i];
	delete[] _board;
}

void Load::print() {
	//linia de cifre de sus
	{
		int i = 1;
		cout << "  ";
		for (int l = 0; l < 4 * _size; l++) {
			if ((l - 2) % 4 == 0) {
				cout << i;                                      
				i++;
			}else
			cout << " ";
		}
		cout << endl;
	}

	for (int l = 0; l < 4 * _size; l++)
		cout << " ";
	cout << endl;
	                                 
	for (int i = 0; i < _size; i++) {
		cout << "  ";
		for (int l = 0; l <= 4 *_size; l++)
			cout << "#";                                   //linia de # (capacul)
		cout << endl;
		for (int nr = 0; nr < 3; nr++) {

			if (nr == 1) {
				if (i >= 9)
					cout << i + 1 << "#";
				else
					cout << i + 1 << " #";
			}	
			else
				cout << "  #";

			for (int j = 0; j < _size; j++) {
				subPrint(nr, _board[i][j].cha);
				cout << "#";
			}

			cout << endl;

		}
	}
	cout << "  ";
	for (int l = 0; l <= 4 * _size; l++)                                  //sfarsitul
		cout << "#";
}

void Load::subPrint(int nr,char cha) {
	switch (nr) {
	case 0:
	case 2:                                           //inceputul si sfarsitul sunt indentice in cazul lui X,O si " "
		switch (cha) {
		case ' ':
			cout << "   ";
			break;
		case 'X':
			cout << "X X";
			break;
		case 'O':
			cout << "OOO";
			break;
		}
		break;
	case 1:
		switch (cha) {
		case ' ':
			cout << "   ";
			break;
		case 'X':
			cout << " X ";
			break;
		case 'O':
			cout << "O O";
			break;
		}
		break;
	}
}

void Load::playerTurn() {
	system("CLS");
	print();
	input();
	if (_turn == PlayerTurn::XPLAYER)
		_turn = PlayerTurn::OPLAYER;
	else if(_turn == PlayerTurn::OPLAYER)
		_turn = PlayerTurn::XPLAYER;
}

void Load::input() {
	int x, y;
	bool isdone = false;
	while (!isdone) {
		cout << endl << "Este randul jucatorului";
		if (_turn == PlayerTurn::XPLAYER)
			cout << " X!" << endl;
		else if (_turn == PlayerTurn::OPLAYER)
			cout << " O!" << endl;
		cout << "Introduce coordonatele! Mai intai axa X(cea de sus,orizontala) iar apoi axa Y(cea de pe stanga,verticala)." << endl;
		cin >> x >> y;
		isdone = checkInput(y - 1, x - 1);        
	}

	if (_turn == PlayerTurn::XPLAYER)
		_board[y - 1][x - 1].cha = 'X';
	else if(_turn == PlayerTurn::OPLAYER)
		_board[y - 1][x - 1].cha = 'O';
	
}

bool Load::checkInput(int y, int x) {
	if ((_board[y][x].cha != ' ') || (x < 0 || x > _size || y < 0 || y > _size)) { //verif daca spatiul este gol si daca coord nu sunt peste limita
		cout << "*** Input invalid ***" << endl;

		Sleep(1000);        //pauza dramatica...
		system("CLS");
		print();

		return false;
	}
	return true;
}

bool Load::checkWinner() {

	for (int i = 0; i < _size; i++) 
		for (int j = 0; j < _size; j++) 
			if ((_board[i][j].cha != ' ') && (_board[i][j].verif == false)) 
				if (checkXAxis(i, j, _board[i][j].cha) == _distance || checkYAxis(i, j, _board[i][j].cha) == _distance || checkFirstDiag(i, j, _board[i][j].cha) == _distance || checkSecondDiag(i, j, _board[i][j].cha) == _distance)
					return true;            //verifica daca a castigat pe orizontala, verticala si ambele diagonale

	return false;
}

int Load::checkXAxis(int y, int x,char cha) {
	int i = 0;
	while ((x < _size) && (_board[y][x].cha == cha)) {
		i++;
		_board[y][x].verif = true;
		x++;
	}
	return i;
}

int Load::checkYAxis(int y, int x, char cha) {
	int i = 0;
	while ((y < _size) && (_board[y][x].cha == cha)) {
		i++;
		_board[y][x].verif = true;
		y++;
	}
	return i;
}

int Load::checkFirstDiag(int y, int x, char cha) {
	int i = 0;
	while (((x < _size) && (y < _size)) && (_board[y][x].cha == cha)) {
		i++;
		_board[y][x].verif = true;
		x++;
		y++;
	}
	return i;
}

int Load::checkSecondDiag(int y, int x, char cha) {
	int i = 0;
	while (((x >= 0) && (y < _size)) && (_board[y][x].cha == cha)) {
		i++;
		_board[y][x].verif = true;
		x--;
		y++;
	}
	return i;
}

bool Load::checkTie() {
	int l = 0;             // cate patrate sunt pline
	for(int i=0;i<_size;i++)
		for(int j=0;j<_size;j++)
			if (_board[i][j].cha != ' ') {
				l++;
				_board[i][j].verif = false;
			}
	if (l == _size * _size) {
		_turn = PlayerTurn::TIE;
		return true;
	}
	return false;
}

void Load::winState(GameState &gameState) {
	system("CLS");
	print();

	if (_turn != PlayerTurn::TIE) {
		cout << endl << "***Jucatorul";
		if (_turn == PlayerTurn::XPLAYER)
			cout << " O";
		else
			cout << " X";
		cout << " a catigat!***" << endl;
	}
	else
		cout << endl << "***Egalitate intre cei doi jucatori!***" << endl;
	Sleep(3000);
	gameState = GameState::PLAYMENIU;
}
