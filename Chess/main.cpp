// Shakki2.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "defines.h"
#include "chessBoardManager.h"
#include "scriptEngine.h"
#include "Piece.h"

#define DEMO_MODE 1;
#define WINDOWS false;


void initGame(void);

int main() {
	initGame();
	return 0;
}

void initGame(void) {
	std::string start;
	std::string end;

	chessBoardManager * pBoardManager = new chessBoardManager();;
	ScriptEngine game;

	Player* whiteP = new Player(Colors::WHITE);
	Player* blackP = new Player(Colors::BLACK);

	whiteP->initPieces();
	blackP->initPieces();

	whiteP->setOpponent(blackP);
	blackP->setOpponent(whiteP);

	pBoardManager->addPlayer(whiteP);
	pBoardManager->addPlayer(blackP);	

	pBoardManager->initBoard(whiteP);
	pBoardManager->initBoard(blackP);

	game.mgr = pBoardManager;
	game.board = pBoardManager->getBoard();

	// Starting player is white
	game.currentPlayer = whiteP;
	//std::cin.ignore();
	game.mgr->updateGameState();
	game.game_script_twopins_test();

	bool* gameOverPtr = &game.mgr->gameOver;

	// Start game
	while (!(*gameOverPtr)) {
		std::cout << game.currentPlayer->toCharString() << ": Select piece: "; std::cin >> start;
		std::cout << game.currentPlayer->toCharString() << ": Select target: "; std::cin >> end;
		game.playMove(start, end);
		
	}
	Player* winner = game.currentPlayer->isWinner ? game.currentPlayer : game.currentPlayer->getOpponent();

	std::cout << "Game over! Winner: " << winner->toCharString() << "!                             " << std::endl << std::endl;
	std::cin.ignore();
	std::cin.ignore();
}

ScriptEngine::ScriptEngine() {}

ScriptEngine::~ScriptEngine() {}