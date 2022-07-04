#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "boardman.h"
#include "engine.h"
#include "piece.h"

#define DEMO_MODE 1; /// ??

void initGame(std::string);

int main(int argc,char* argv[]) {

	initGame("59203");

	return 0;
}

void initGame(std::string lport) {

	auto myPlayer = Colors::WHITE;

	Coordinates start;
	Coordinates end;

	Boardman * pBoardManager = new Boardman();

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
