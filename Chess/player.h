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
	void makeMove(chessBoardManager*, Player*);
	vector<string> getMoves(void);
	vector<Piece*> getPieces(void);
	void setChecked(bool);
	bool getChecked();
	void checkGame(chessBoardManager*);
	void setOpponent(Player*);
	Player* getOpponent();
private:
	int color;
	vector<Piece*> pieces;
	Player* opponent = NULL;
	bool checked;
};


