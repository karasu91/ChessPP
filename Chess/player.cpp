#include "player.h"
#include "Piece.h"
#include <string>
#include "chessBoard.h"
#include <locale> 
#include "defines.h"

using namespace std;

extern bool boeq(int, int, int); // in chessboardManager.cpp

Player::Player(int col)
{
	this->color = col;
}

void Player::initPieces(int color)
{

	if (color == WHITE) {
		/* Pawns */
		addPiece(new Piece(WHITE, PAWN, 6, 0));
		addPiece(new Piece(WHITE, PAWN, 6, 1));
		addPiece(new Piece(WHITE, PAWN, 6, 2));
		addPiece(new Piece(WHITE, PAWN, 6, 3));
		addPiece(new Piece(WHITE, PAWN, 6, 4));
		addPiece(new Piece(WHITE, PAWN, 6, 5));
		addPiece(new Piece(WHITE, PAWN, 6, 6));
		addPiece(new Piece(WHITE, PAWN, 6, 7));

		/* The rest */
		addPiece(new Piece(WHITE, ROOK, 7, 0));
		addPiece(new Piece(WHITE, HORSE, 7, 1));
		addPiece(new Piece(WHITE, BISHOP, 7, 2));
		addPiece(new Piece(WHITE, KING, 7, 3));
		addPiece(new Piece(WHITE, QUEEN, 7, 4));
		addPiece(new Piece(WHITE, BISHOP, 7, 5));
		addPiece(new Piece(WHITE, HORSE, 7, 6));
		addPiece(new Piece(WHITE, ROOK, 7, 7));
	}
	else { // Color == Black
		/* Pawns */
		addPiece(new Piece(BLACK, PAWN, 1, 0));
		addPiece(new Piece(BLACK, PAWN, 1, 1));
		addPiece(new Piece(BLACK, PAWN, 1, 2));
		addPiece(new Piece(BLACK, PAWN, 1, 3));
		addPiece(new Piece(BLACK, PAWN, 1, 4));
		addPiece(new Piece(BLACK, PAWN, 1, 5));
		addPiece(new Piece(BLACK, PAWN, 1, 6));
		addPiece(new Piece(BLACK, PAWN, 1, 7));

		/* The rest */
		addPiece(new Piece(BLACK, ROOK, 0, 0));
		addPiece(new Piece(BLACK, HORSE, 0, 1));
		addPiece(new Piece(BLACK, BISHOP, 0, 2));
		addPiece(new Piece(BLACK, QUEEN, 0, 3));
		addPiece(new Piece(BLACK, KING, 0, 4));
		addPiece(new Piece(BLACK, BISHOP, 0, 5));
		addPiece(new Piece(BLACK, HORSE, 0, 6));
		addPiece(new Piece(BLACK, ROOK, 0, 7));
	}	
}

vector<Piece*> Player::getPieces(void) {
	return pieces;
}

Player::~Player()
{
}

void Player::addPiece(Piece* piece)
{
	pieces.push_back(piece);	
}

void Player::printPieces(void)
{
	for (int i = 0; i < (int)pieces.size(); i++) {
		cout << getPieces()[i]->getColor() << " " << getPieces()[i]->getType() << endl;
	}
}

string Player::toString() {
	switch(color)
	{
		case BLACK:
			return "PLAYER_BLACK";
		case WHITE:
			return "PLAYER_WHITE";
		default:
			return "PLAYER_?";
	}
}


void Player::checkGame(chessBoardManager* board) {

	vector<Player*> players = board->getPlayers();

	board->recalculatePieceThreats(); // Assigns every threat into all pieces on the board	

	for(int i = 0; i < players.size(); i++) {
		board->updatePlayerCheckedStatus(players[i]);
	}

}

bool Player::getChecked() {
	return checked;
}

void Player::setChecked(bool newCheck) {

	if(checked == false && newCheck == true) {
		cout << color << " is checked!" << endl; cin.ignore();
	} 
	else if(checked == true && newCheck == false)
		cout << color << " not checked anymore!" << endl; cin.ignore();

	checked = newCheck;
}

void Player::setOpponent(Player* p) 
{
	if(p != this)
		opponent = p;
	else
		cout << "Cant set myself as an opponent!" << endl;
}

Player* Player::getOpponent() 
{
	return opponent;

}

//https://stackoverflow.com/a/30727561
int charToInt(char c) 
{
	return (int)c - 48;
}


int Player::getColor(void)
{
	return color;
}