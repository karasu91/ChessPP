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


string convertToUpper(string str) {
	string ret = "";
	for(auto& c : str) 
		ret += toupper(c);
	return ret;
}

class Game {
public:
	Game();
	~Game();
	Player* currentPlayer = NULL;
	chessBoardManager* mgr = NULL;
	int autoPlayDelayMs = 100;
	void swapTurn() {
		currentPlayer = currentPlayer->getOpponent();
	}
	void playMove(string start, string end) 	
	{
		start = convertToUpper(start);
		end = convertToUpper(end);
		if(mgr->playMove(currentPlayer, coordinates(start), coordinates(end)) == true)
		{
			swapTurn();
			std::this_thread::sleep_for(std::chrono::milliseconds(autoPlayDelayMs));
		}
	}
};


int main() {
	initGame();
	return 0;
}



void initGame(void) {

	chessBoardManager* boardManager = new chessBoardManager();
	Game* game = new Game();

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
	// initial moves
	game->playMove("F7", "F6");
	game->playMove("E2", "E3");
	game->playMove("G7", "G5");
	game->playMove("F2", "F4");
	game->playMove("E7", "E6");
	game->playMove("D1", "F3");
	game->playMove("G8", "H6");
	game->playMove("B1", "C3");
	game->playMove("F8", "B4");
	game->playMove("A2", "A3");
	game->playMove("D8", "E7");
	game->playMove("A3", "B4");

	game->playMove("B7", "B5");
	game->playMove("C3", "B5");
	game->playMove("C8", "A6");
	game->playMove("C2", "C4");
	game->playMove("B8", "C6");
	game->playMove("G1", "H3");
	game->playMove("E8", "C8");
	game->playMove("f1", "e2");
	game->playMove("D8", "G8");
	game->playMove("E1", "G1"); // castle to right
	game->playMove("C6", "D4");
	game->playMove("F3", "A8");

	bool* gameOverPtr = &game->mgr->gameOver;

	string start;
	string end;

	// Start game
	while(!*gameOverPtr)
	{
		std::cout << game->currentPlayer->toString() << ": Select piece: "; cin >> start;
		std::cout << game->currentPlayer->toString() << ": Select target: "; cin >> end;

		game->playMove(start, end);
	}
	Player* winner = game->currentPlayer->isWinner ? game->currentPlayer : game->currentPlayer->getOpponent();

	std::cout << "Game over! Winner: " << winner->toString() << "!                             " << endl << endl;
	cin.ignore();
	cin.ignore();
	cin.ignore();

	cin.ignore();
}

Game::Game() {
}

Game::~Game() {
}
