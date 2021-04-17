// Shakki2.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include "player.h"
#include <string>
#include <vector>
#include "Piece.h"
#include "chessBoard.h"
#include "defines.h"

#include <chrono>
#include <thread>

#define DEMO_MODE 1;

using namespace std;

void initGame(void);

class ActivePlayers {
public:
	ActivePlayers();
	~ActivePlayers();
	Player* currentPlayer = NULL;
	void swapTurn() {
		currentPlayer = currentPlayer->getOpponent();
	}
};


int main() {
	initGame();
	return 0;
}

void initGame(void) {
	int gameOver = 0;

	/*
	  1 2 3 4 5 6 7 8
	  _____________

	|R H B K Q B H R|	A	B
	|P P P P P P P P|	B	B
	|0 0 0 0 0 0 0 0|	C
	|0 0 0 0 0 0 0 0|	D
	|0 0 0 0 0 0 0 0|	E
	|0 0 0 0 0 0 0 0|	F
	|P P P P P P P P|	G	W
	|R H B Q K B H R|	H	W
	¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
	*/


	chessBoardManager* boardManager = new chessBoardManager();
	ActivePlayers* activePlayers = new ActivePlayers();

	auto gameBoard = boardManager->getBoard();

	Player* whiteP = new Player(WHITE);
	Player* blackP = new Player(BLACK);

	whiteP->setOpponent(blackP);
	blackP->setOpponent(whiteP);

	boardManager->addPlayer(whiteP);
	boardManager->addPlayer(blackP);

	whiteP->initPieces(WHITE);
	blackP->initPieces(BLACK);
	boardManager->initBoard(whiteP);
	boardManager->initBoard(blackP);

	boardManager->printBoard(gameBoard, false);

	// Starting player is white
	activePlayers->currentPlayer = whiteP;

	unsigned sleepforMs = 750;
	// initial moves
	if(boardManager->playMove(activePlayers->currentPlayer, "G6", "F6") == true)
		activePlayers->swapTurn();
	std::this_thread::sleep_for(std::chrono::milliseconds(sleepforMs));

	if(boardManager->playMove(activePlayers->currentPlayer, "B5", "D5") == true)
		activePlayers->swapTurn();
	std::this_thread::sleep_for(std::chrono::milliseconds(sleepforMs));

	if(boardManager->playMove(activePlayers->currentPlayer, "G7", "E7") == true)
		activePlayers->swapTurn();
	std::this_thread::sleep_for(std::chrono::milliseconds(sleepforMs));

	if(boardManager->playMove(activePlayers->currentPlayer, "A4", "E8") == true)
		activePlayers->swapTurn();

	//std::this_thread::sleep_for(std::chrono::milliseconds(sleepforMs));

	string startCoordinates;
	string finalCoordinates;

	// Start game


	while(!boardManager->gameOver)
	{
		cout << activePlayers->currentPlayer->toString() << ": Select piece: ";
		cin >> startCoordinates;
		cout << activePlayers->currentPlayer->toString() << ": Select target: ";
		cin >> finalCoordinates;

		if(boardManager->playMove(activePlayers->currentPlayer, startCoordinates, finalCoordinates) == true)
			activePlayers->swapTurn();
	}

	Player* winner = activePlayers->currentPlayer->isWinner ? activePlayers->currentPlayer : activePlayers->currentPlayer->getOpponent();

	cout << "Game over! Winner: " << winner->toString() << "!                             " << endl << endl;
	cin.ignore();
}

ActivePlayers::ActivePlayers() {
}

ActivePlayers::~ActivePlayers() {
}
