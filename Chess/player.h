#pragma once
#include "Piece.h"
#include <vector>

using namespace std;

class chessBoardManager;

class Player
{
public:
	Player(int);
	~Player();
	void addPiece(Piece*);
	int getColor(void);
	void initPieces(int);
	void printPieces(void);	
	string toString();
	vector<string> getMoves(void);
	vector<Piece*> getPieces(void);
	void copyPieces(vector<Piece*>);
	void setChecked(bool);
	bool isChecked();
	void setOpponent(Player*);
	Player* getOpponent();
	bool isWinner = false;
private:
	int color = 0;
	vector<Piece*> pieces;
	Player* opponent = NULL;
	bool _checked = false;
};


