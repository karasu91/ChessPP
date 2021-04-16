#pragma once
#include "Piece.h"
#include <vector>

using namespace std;

class chessBoard;

class player
{
public:
	player(int);
	~player();
	void addPiece(Piece*);
	int getColor(void);
	void initPieces(int);
	void printPieces(void);
	void makeMove(chessBoard*, player*);
	void validMovesTotal(vector<string>);
	void addMoves(vector<string>);
	vector<string> getMoves(void);
	vector<Piece*> getPieces(void);
	void setThreatMoves(chessBoard*);
	vector<string> getThreatMoves(void);
	void setChecked(bool, chessBoard*, player*);
	void checkGame(player*, player*, chessBoard*);
private:
	int color;
	vector<string> validMoves;
	vector<string> threatMoves;
	vector<Piece*> pieces;
	bool checked;
};


