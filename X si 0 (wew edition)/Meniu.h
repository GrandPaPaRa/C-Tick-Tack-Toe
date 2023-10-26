#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include "Load.h"


using namespace std;

#pragma once


class Node;
class SubNode;
class Tree;

class Meniu
{
public:
	Meniu() {};
	 void playMeniu(GameState &gameState);
	
private:
	Tree* tree;
	 void printNode(Node* node, int i);
	 int getInput(int &i, Node* &node);
	 void processMeniu(int input, int &i, GameState &gameState, Node* node);

	 void switchLaturaLeft(Node* &node);
	 void switchLaturaRight(Node* &node);
	 void switchDistantaLeft(Node* &node);
	 void switchDistantaRight(Node* &node);

};

class Tree {
public:
	Tree();
	vector<Node*> nodes;
};

class Node {
public:
	string name;
	vector<SubNode> subNodes;
};

class SubNode {
public:
	SubNode(string Name,Node* NextNode,int Code);
	SubNode(string Name, Node* NextNode, int Code, int Option);
	string name; 
	Node* nextNode;
	int code;
	int option = 0;
};

