#pragma once
#include "player.h"
#include <windows.h> // WinApi header

using namespace std;

typedef Piece* Row;
typedef Row* Board;

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
	void printBoard(Piece***);
	void setPieceTo(Piece*, coordinates);
	void updatePlayerCheckedStatus(Player*);
	void calculateAllPossibleMoves(Player*);  // Check every possible player's move
	void checkForMate(Player*);
	void recalculatePieceThreats(void);
	void updatePlayerChecked(Player*, bool);
	bool tryMove(Piece* piece, string target);
	bool playMove(Player*, string, string);

	Piece* getPiece(int, int);
	Piece*** getBoard(void);
	vector<string> calculateAvailableMoves(Piece*);
	void addPlayer(Player*);
	vector<Player*> getPlayers();
private:	
	Board* _board;
	vector<Player*> _players;
};

