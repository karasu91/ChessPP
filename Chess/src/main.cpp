// Shakki2.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "chessBoardManager.h"
#include "engine.h"
#include "Piece.h"

#define DEMO_MODE 1;

void initGame(std::string, std::string);

int main(int argc,char* argv[]) {
	if (argc < 2)
		std::cout << "less than 2 arguments given." << std::endl;
	std::string localPort = argv[1];
	std::string targetPort = argv[2];
	initGame(localPort, targetPort);
	return 0;
}

void initGame(std::string lport, std::string tport) {

	auto myPlayer = Colors::WHITE;

	Coordinates start;
	Coordinates end;

	chessBoardManager * pBoardManager = new chessBoardManager();;
	
	Engine game;

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

	game.localPort = atoi(lport.c_str());
	game.targetPort = atoi(tport.c_str());

	game.mgr->updateGameState();

	std::string color;
	std::cout << "Select player color (w/b): " << std::endl;
	std::cin >> color;

	color == "w" ? game.initializeMultiplayer(whiteP) 
				: game.initializeMultiplayer(blackP);


	/////////////// region for tests
	// game.mgr->enableTestMode();
	// game.game_script_twopins_test();
	// game.mgr->disableTestMode();
	////////////// end region for tests

	game.run();

	//Player* winner = game._currentPlayer->isWinner ? game._currentPlayer : game._currentPlayer->getOpponent();

	//std::cout << "Game over! Winner: " << winner->toCharString() << "!                             " << std::endl << std::endl;
	std::cin.ignore();
	std::cin.ignore();
}

Engine::Engine() {}

Engine::~Engine() {}