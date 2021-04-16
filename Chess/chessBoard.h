#pragma once
#include "player.h"
#include <windows.h> // WinApi header

using namespace std;

class chessBoardManager
{
public:
	chessBoardManager();
	~chessBoardManager();	
	int returnRow(string);
	int returnCol(string);
	string returnRowC(int);
	string returnColC(int);
	string numToPiece(int);	
	void initBoard(Player*);
	void printBoard(void);
	void setPiece(Piece*, int, int, int, int);
	void updatePlayerCheckedStatus(Player*);
	void calculateAllPossibleMoves(Player*);  // Check every possible player's move
	void checkForMate(Player*);
	void recalculatePieceThreats(void);
	void updatePlayerChecked(Player*, bool);
	Piece* getPiece(int, int);
	Piece* getBoard(void);
	vector<string> calculateAvailableMoves(Piece*, string);
	void addPlayer(Player*);
	vector<Player*> getPlayers();
private:	
	Piece* board[8][8];
	vector<Player*> players;
};

