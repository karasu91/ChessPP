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

	cout << "TEST: " << endl;
	int val1 = 5;
	int val2 = 5;

	cout << "converting_column " << val2 << " results in " << convertColumnIndexToChar(val2) << endl;
	cout << "converting_row" << val1 << " results in " << convertRowIndexToChar(val1) << endl;
	


	unsigned sleepforMs = 750;
	// initial moves
	if(boardManager->playMove(activePlayers->currentPlayer, coordinates("F7"), coordinates("F6")) == true)
		activePlayers->swapTurn();
	std::this_thread::sleep_for(std::chrono::milliseconds(sleepforMs));

	if(boardManager->playMove(activePlayers->currentPlayer, coordinates("E2"), coordinates("E3")) == true)
		activePlayers->swapTurn();
	std::this_thread::sleep_for(std::chrono::milliseconds(sleepforMs));

	if(boardManager->playMove(activePlayers->currentPlayer, coordinates("G7"), coordinates("G5")) == true)
		activePlayers->swapTurn();
	std::this_thread::sleep_for(std::chrono::milliseconds(sleepforMs));

	if(boardManager->playMove(activePlayers->currentPlayer, coordinates("F2"), coordinates("F4")) == true)
		activePlayers->swapTurn();
	std::this_thread::sleep_for(std::chrono::milliseconds(sleepforMs));

	if(boardManager->playMove(activePlayers->currentPlayer, coordinates("B8"), coordinates("C6")) == true)
		activePlayers->swapTurn();
	std::this_thread::sleep_for(std::chrono::milliseconds(sleepforMs));

	if(boardManager->playMove(activePlayers->currentPlayer, coordinates("D1"), coordinates("H5")) == true)
		activePlayers->swapTurn();

	//std::this_thread::sleep_for(std::chrono::milliseconds(sleepforMs));

	string start;
	string end;

	// Start game
	while(!boardManager->gameOver)
	{
		cout << activePlayers->currentPlayer->toString() << ": Select piece: ";
		cin >> start;
		cout << activePlayers->currentPlayer->toString() << ": Select target: ";
		cin >> end;

		if(boardManager->playMove(activePlayers->currentPlayer, coordinates(start), coordinates(end)) == true)
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
