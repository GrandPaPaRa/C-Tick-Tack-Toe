#include "Meniu.h"                       //***************DE REINTRODUS FUNCTILE STATICE IN MENIU IMPREUNA CU VARIABILELE STATICE

//Tree Meniu::tree;

Tree::Tree() {

	ifstream input1("Latura.txt");
	ifstream input2("Distanta.txt");
	int latura, distanta;
	input1 >> latura;
	input2 >> distanta;

	for (int i = 0; i < 3; i++) {      //initializarea memoriei heap
		nodes.push_back(new Node);
	}

	//NODE 0
	nodes[0]->name = "Meniu";
	nodes[0]->subNodes.push_back(SubNode("Play", nodes[1], 0));
	nodes[0]->subNodes.push_back(SubNode("Optiuni", nodes[2], 0));
	nodes[0]->subNodes.push_back(SubNode("Exit", nullptr, 1));

	//NODE 1
	nodes[1]->name = "Play";
	nodes[1]->subNodes.push_back(SubNode("Multiplayer", nullptr, 2));
	nodes[1]->subNodes.push_back(SubNode("Inapoi", nodes[0], 0));

	//NODE 2
	nodes[2]->name = "Optiuni";
	nodes[2]->subNodes.push_back(SubNode("Latura", nullptr, 3, latura));
	nodes[2]->subNodes.push_back(SubNode("Distanta", nullptr, 4, distanta));
	nodes[2]->subNodes.push_back(SubNode("Inapoi", nodes[0], 0));

}

SubNode::SubNode(string Name, Node* NextNode, int Code) {
	name = Name;
	nextNode = NextNode;
	code = Code;
}

SubNode::SubNode(string Name, Node* NextNode, int Code, int Option) {
	name = Name;
	nextNode = NextNode;
	code = Code;
	option = Option;
}

void Meniu::printNode(Node* node, int i) {
	system("CLS");
	cout << node->name << endl << endl;
	for (int j = 0; j < node->subNodes.size(); j++) {
		if (i == j)
			cout << ">>>";
		cout << node->subNodes[j].name;
		if (node->subNodes[j].option != 0)
			cout << " <" << node->subNodes[j].option << ">" << endl;
		else
			cout << endl;
	}
}

int Meniu::getInput(int &i,Node* &node) {
	char input;
	input = _getch();
	switch (input) {
	case 'w':
		i--;
		if (i == -1)
			i = node->subNodes.size() - 1;
		break;
	case 's':
		i++;
		if (i == node->subNodes.size())
			i = 0;
		break;
	case 'a':
		if (node->subNodes[i].code == 3)
			return 31;
		if (node->subNodes[i].code == 4)
			return 41;
		break;
	case 'd':
		if (node->subNodes[i].code == 3)
			return 32;
		if (node->subNodes[i].code == 4)
			return 42;
		break;
	case 'l':
		if (node->subNodes[i].nextNode != nullptr) {
			node = node->subNodes[i].nextNode;
			i = 0;
		}
			
		else
			if (node->subNodes[i].option == 0)
				return node->subNodes[i].code;
		break;
	}

	return 0;
	
}

void Meniu::processMeniu(int input,int &i, GameState & gameState, Node* node){
	switch (input) {
	case 1:
		gameState = GameState::EXIT;
		break;
	case 2:
		gameState = GameState::PLAYGAME;
		break;
	case 31:                 //Cazul de latura partea stanga(negativ)
		switchLaturaLeft(node);
		break;
	case 41:				//Cazul de Distanta partea stanga(negativ)
		switchDistantaLeft(node);
		break;
	case 32:				//Cazul de latura partea stanga(pozitiv)
		switchLaturaRight(node);
		break;
	case 42:				//Cazul de Distanta partea dreapta(pozitiv)
		switchDistantaRight(node);
		break;
	}
	switch (input) {
	case 41:
	case 42:
		i = 1;
		break;
	default:
		i = 0;
	}

}

void Meniu::switchLaturaLeft(Node* &node) {
	ofstream input("Latura.txt");
	node->subNodes[0].option--;  
	if (node->subNodes[0].option == 2)         //template(valabil pt toate) cazul de inlocuire in cazul extremitatilor
		node->subNodes[0].option = 10;
	if (node->subNodes[0].option < node->subNodes[1].option) {      //schimbarea specifica in cazul depasirii relatiei latura-distanta
		ofstream input2("Distanta.txt");
		node->subNodes[1].option = node->subNodes[0].option;
		input2 << node->subNodes[1].option;
	}
		
	input << node->subNodes[0].option;
}

void Meniu::switchLaturaRight(Node* &node) {
	ofstream input("Latura.txt");
	node->subNodes[0].option++;
	if (node->subNodes[0].option == 11)
		node->subNodes[0].option = 3;
	if (node->subNodes[0].option < node->subNodes[1].option) {
		ofstream input2("Distanta.txt");
		node->subNodes[1].option = node->subNodes[0].option;
		input2 << node->subNodes[1].option;
	}
		

	input << node->subNodes[0].option;
}

void Meniu::switchDistantaLeft(Node* &node) {
	ofstream input("Distanta.txt");
	node->subNodes[1].option--;
	if (node->subNodes[1].option == 2)
		node->subNodes[1].option = 10;
	if (node->subNodes[1].option > node->subNodes[0].option) {
		ofstream input2("Latura.txt");
		node->subNodes[0].option = node->subNodes[1].option;
		input2 << node->subNodes[0].option;
	}
		

	input << node->subNodes[1].option;
}

void Meniu::switchDistantaRight(Node* &node) {
	ofstream input("Distanta.txt");
	node->subNodes[1].option++;
	if (node->subNodes[1].option == 11)
		node->subNodes[1].option = 3;
	if (node->subNodes[1].option > node->subNodes[0].option) {
		ofstream input2("Latura.txt");
		node->subNodes[0].option = node->subNodes[1].option;
		input2 << node->subNodes[0].option;
	}
		
	input << node->subNodes[1].option;
}

void Meniu::playMeniu(GameState &gameState) {
	int i = 0;
	int input;
	tree = new Tree();
	Node* nextNode = tree->nodes[0];
	while (gameState == GameState::PLAYMENIU) {
		do {
			printNode(nextNode, i);
			input = getInput(i, nextNode);
		} while (input == 0);
		processMeniu(input,i,gameState,nextNode);
	}
	
}