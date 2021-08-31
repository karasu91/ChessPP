#pragma once
#include "coordinates.h"
#include "piece.h"
#include "net.h"

class Player;

class Boardman{
public:
	Boardman();
	~Boardman();
	std::string numToPiece(PieceType);
	void initBoard(Player*);
	void printBoard(std::vector<std::vector<std::shared_ptr<Piece>>>);
	void setPieceTo(std::shared_ptr<Piece>, Coordinates, bool simulate);
	void updatePlayerCheckedStatus(Player*);
	//void calculateAllPossibleMoves(Player*);  // Check every possible player's move
	bool checkForMate(Player*);
	void recalculatePieceThreats(void);
	bool tryMove(std::shared_ptr<Piece> piece, Coordinates target, bool simulate);
	bool validateAndMove(Player*, Coordinates, Coordinates);
	Coordinates handleSelection(void);
	bool simulateMove(Player* player, Coordinates startCoord, Coordinates targetCoord);
	std::shared_ptr<Piece> getPiece(int, int);
	void upgradePawnCheck(std::shared_ptr<Piece> pawn);
	std::vector<std::vector<std::shared_ptr<Piece>>> getBoard(void);
	void addPlayer(Player*);
	std::vector<Player*> getPlayers();
	void updateGameState();
	void cleanPieceData();
	bool gameOver = false;
	unsigned turnNumber = 0;
	void enableTestMode(void) { _testState = true; printBoard(_board); }
	void disableTestMode(void) { _testState = false; printBoard(_board); }
private:
	
	// _resetCoordinates = {0, 0};
	//HANDLE _hConsoleHandle = NULL;
	bool _testState = false;
	int _drawIntervalMs = 500;
	int _boardSelectionRow = 4;
	int _boardSelectionCol = 4;
	std::vector<std::vector<std::shared_ptr<Piece>>> _board;
	std::vector<Player*> _players;
};
