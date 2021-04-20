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
#include "scriptEngine.h"

#define DEMO_MODE 1;

using namespace std;

void initGame(void);





int main() {
	initGame();
	return 0;
}



void initGame(void) {

	string start;
	string end;

	chessBoardManager* boardManager = new chessBoardManager();
	ScriptEngine* game = new ScriptEngine();

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

	game->mgr = boardManager;

	// Starting player is white
	game->currentPlayer = whiteP;
	cin.ignore();

	game->game_script_enpassant_test();

	bool* gameOverPtr = &game->mgr->gameOver;


	// Start game
	while(!*gameOverPtr)
	{
		std::cout << game->currentPlayer->toString() << ": Select piece: "; cin >> start;
		std::cout << game->currentPlayer->toString() << ": Select target: "; cin >> end;
		if(game->playMove(start, end) == false)
			continue;
	}
	Player* winner = game->currentPlayer->isWinner ? game->currentPlayer : game->currentPlayer->getOpponent();

	std::cout << "Game over! Winner: " << winner->toString() << "!                             " << endl << endl;
	cin.ignore();
	cin.ignore();
	cin.ignore();

	cin.ignore();
}

ScriptEngine::ScriptEngine() {
}

ScriptEngine::~ScriptEngine() {
}
