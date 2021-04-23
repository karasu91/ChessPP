#pragma once
#include "defines.h"
#include "coordinates.h"
#include <Windows.h>
#include "Piece.h"

class Player;

class chessBoardManager{
public:
	chessBoardManager();
	~chessBoardManager();
	std::string numToPiece(PieceType);
	void initBoard(Player*);
	void printBoard(std::vector<std::vector<std::shared_ptr<Piece>>>, bool);
	void setPieceTo(std::shared_ptr<Piece>, Coordinates, bool simulate, bool updateState);
	void updatePlayerCheckedStatus(Player*);
	void calculateAllPossibleMoves(Player*);  // Check every possible player's move
	bool checkForMate(Player*);
	void recalculatePieceThreats(void);
	bool tryMove(std::shared_ptr<Piece> piece, Coordinates target, bool simulate);
	bool validateAndMove(Player*, Coordinates, Coordinates);
	bool simulateMove(Player* player, Coordinates startCoord, Coordinates targetCoord);
	std::shared_ptr<Piece> getPiece(int, int);
	void upgradePawnCheck(std::shared_ptr<Piece> pawn);
	std::vector<std::vector<std::shared_ptr<Piece>>> getBoard(void);
	void addPlayer(Player*);
	std::vector<Player*> getPlayers();
	void updateGameState();
	bool gameOver = false;
	unsigned turnNumber = 0;
private:
	COORD _resetCoordinates = {0, 0};
	HANDLE _hConsoleHandle = NULL;
	std::vector<std::vector<std::shared_ptr<Piece>>> _board;
	std::vector<Player*> _players;
};
