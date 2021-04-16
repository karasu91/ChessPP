#pragma once
#include "player.h"

using namespace std;

class chessBoard
{
public:
	chessBoard();
	~chessBoard();	
	int returnRow(string);
	int returnCol(string);
	string returnRowC(int);
	string returnColC(int);
	string numToPiece(int);	
	void initBoard(player*);
	void printBoard(void);
	void setPiece(Piece*, int, int, int, int);
	void checkCheck(player*, player*);
	void addAllPossibleMoves(player*);  // Check every possible player's move
	void checkForMate(player*, player*);
	void createThreatVector(void);
	Piece* getPiece(int, int);
	Piece* getBoard(void);
	vector<string> validMoves(Piece*, string);
private:	
	Piece* board[8][8];
};

