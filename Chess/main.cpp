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
#include "chessBoard.h"
#include "scriptEngine.h"
#include "Piece.h"

#define DEMO_MODE 1;



void initGame(void);

int main() {
	initGame();
	return 0;
}

void initGame(void) {
	std::string start;
	std::string end;

	chessBoardManager boardManager;
	ScriptEngine game;

	Player* whiteP = new Player(Colors::WHITE);
	Player* blackP = new Player(Colors::BLACK);
	whiteP->initPieces();
	blackP->initPieces();

	whiteP->setOpponent(blackP);
	blackP->setOpponent(whiteP);

	boardManager.addPlayer(whiteP);
	boardManager.addPlayer(blackP);	

	boardManager.initBoard(whiteP);
	boardManager.initBoard(blackP);

	game.mgr = &boardManager;
	game.board = boardManager.getBoard();
	// Starting player is white
	game.currentPlayer = whiteP;
	std::cin.ignore();

	game.game_script_enpassant_test();

	bool* gameOverPtr = &game.mgr->gameOver;

	// Start game
	while (!(*gameOverPtr)) {
		std::cout << game.currentPlayer->toCharString() << ": Select piece: "; std::cin >> start;
		std::cout << game.currentPlayer->toCharString() << ": Select target: "; std::cin >> end;
		if (game.playMove(start, end) == false)
			continue;
		
	}
	Player* winner = game.currentPlayer->isWinner ? game.currentPlayer : game.currentPlayer->getOpponent();

	std::cout << "Game over! Winner: " << winner->toCharString() << "!                             " << std::endl << std::endl;
	std::cin.ignore();
	std::cin.ignore();

}

ScriptEngine::ScriptEngine() {}

ScriptEngine::~ScriptEngine() {}