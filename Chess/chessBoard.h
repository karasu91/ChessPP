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
	void printBoard(Piece***, bool);
	void setPieceTo(Piece*, coordinates, bool simulate);
	void updatePlayerCheckedStatus(Player*);
	void calculateAllPossibleMoves(Player*);  // Check every possible player's move
	bool checkForMate(Player*);
	void recalculatePieceThreats(void);
	bool tryMove(Piece* piece, string target, bool simulate);
	bool playMove(Player*, string, string);

	bool simulateMove(Player* player, string startCoord, string targetCoord);

	Piece* getPiece(int, int);
	Piece*** getBoard(void);
	vector<string> calculateAvailableMovesForPiece(Piece*);
	void addPlayer(Player*);
	vector<Player*> getPlayers();
	void updateGameState();
	bool gameOver = false;
private:		
	Board* _board;
	vector<Player*> _players;
	
};

