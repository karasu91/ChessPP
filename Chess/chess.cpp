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

using namespace std;

void initGame(void);

class ActivePlayers {
public:
	ActivePlayers();
	~ActivePlayers();
	Player* currentPlayer;
	void swapTurn() {
		currentPlayer = currentPlayer->getOpponent();
	}
};


int main()
{
	initGame();	
  	return 0;
}

void initGame(void)
{
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

	activePlayers->currentPlayer = whiteP;

	whiteP->initPieces(WHITE);
	blackP->initPieces(BLACK);
	//cout << board[
	boardManager->initBoard(whiteP);
	boardManager->initBoard(blackP);
	boardManager->printBoard(gameBoard, false);	

	unsigned sleepforMs = 250;
	// initial moves
	boardManager->playMove(activePlayers->currentPlayer, "G5", "E5");
	activePlayers->swapTurn();
	std::this_thread::sleep_for(std::chrono::milliseconds(sleepforMs));

	boardManager->playMove(activePlayers->currentPlayer, "B4", "D4");
	activePlayers->swapTurn();
	std::this_thread::sleep_for(std::chrono::milliseconds(sleepforMs));

	boardManager->playMove(activePlayers->currentPlayer, "H6", "D2");
	activePlayers->swapTurn();
	std::this_thread::sleep_for(std::chrono::milliseconds(sleepforMs));

	string startCoordinates;
	string finalCoordinates;

	// Start game


	while (!boardManager->gameOver) {		
		cout << activePlayers->currentPlayer->toString() << ": Select piece: ";
		cin >> startCoordinates;
		cout << activePlayers->currentPlayer->toString() << ": Select target: ";
		cin >> finalCoordinates;

		if (boardManager->playMove(activePlayers->currentPlayer, startCoordinates, finalCoordinates) == true)
			activePlayers->swapTurn();
	}
}

ActivePlayers::ActivePlayers() {
}

ActivePlayers::~ActivePlayers() {
}
