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
	string numToPiece(int);	
	void initBoard(Player*);
	void printBoard(Board*, bool);
	void setPieceTo(Piece*, coordinates, bool simulate);
	void updatePlayerCheckedStatus(Player*);
	void calculateAllPossibleMoves(Player*);  // Check every possible player's move
	bool checkForMate(Player*);
	void recalculatePieceThreats(void);
	bool tryMove(Piece* piece, coordinates target, bool simulate);
	bool playMove(Player*, coordinates, coordinates);

	bool simulateMove(Player* player, coordinates startCoord, coordinates targetCoord);

	Piece* getPiece(int, int);
	Board* getBoard(void);
	vector<coordinates> calculateAvailableMovesForPiece(Piece*);
	void addPlayer(Player*);
	vector<Player*> getPlayers();
	void updateGameState();
	bool gameOver = false;
private:		
	Board* _board;
	vector<Player*> _players;	
};

