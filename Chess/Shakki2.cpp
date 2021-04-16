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

using namespace std;

void initGame(void);

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

	chessBoardManager* board = new chessBoardManager;

	Player* whiteP = new Player(WHITE);
	Player* blackP = new Player(BLACK);

	whiteP->initPieces(WHITE);
	blackP->initPieces(BLACK);
	//cout << board[
	board->initBoard(whiteP);
	board->initBoard(blackP);

	board->printBoard();

	// Start game
	while (!gameOver) {			
		whiteP->makeMove(board, blackP);
		blackP->makeMove(board, whiteP);		
	}
}
