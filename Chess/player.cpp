#include "player.h"
#include "Piece.h"
#include <string>
#include "chessBoard.h"
#include <locale>
#include "defines.h"

using namespace std;

extern bool boeq(int, int, int); // in chessboardManager.cpp

void Player::removePiece(Piece* removeThis) {
	for (int i = 0; i < pieces.size(); i++) {
		if (pieces[i] == removeThis) {
			pieces.erase(pieces.begin() + i);
			break;
		}
	}
}

Player::Player(int col) {
	this->color = col;
}

void Player::initPieces(int color) {
	if (color == WHITE) {
		/* Pawns */
		addPiece(new Piece(WHITE, PAWN, coordinates("A7")));
		addPiece(new Piece(WHITE, PAWN, coordinates("B7")));
		addPiece(new Piece(WHITE, PAWN, coordinates("C7")));
		addPiece(new Piece(WHITE, PAWN, coordinates("D7")));
		addPiece(new Piece(WHITE, PAWN, coordinates("E7")));
		addPiece(new Piece(WHITE, PAWN, coordinates("F7")));
		addPiece(new Piece(WHITE, PAWN, coordinates("G7")));
		addPiece(new Piece(WHITE, PAWN, coordinates("H7")));

		/* The rest */
		addPiece(new Piece(WHITE, ROOK, coordinates("A8")));
		addPiece(new Piece(WHITE, HORSE, coordinates("B8")));
		addPiece(new Piece(WHITE, BISHOP, coordinates("C8")));
		addPiece(new Piece(WHITE, QUEEN, coordinates("D8")));
		addPiece(new Piece(WHITE, KING, coordinates("E8")));
		addPiece(new Piece(WHITE, BISHOP, coordinates("F8")));
		addPiece(new Piece(WHITE, HORSE, coordinates("G8")));
		addPiece(new Piece(WHITE, ROOK, coordinates("H8")));
	}
	else { // Color == Black
  /* Pawns */
		addPiece(new Piece(BLACK, PAWN, coordinates("A2")));
		addPiece(new Piece(BLACK, PAWN, coordinates("B2")));
		addPiece(new Piece(BLACK, PAWN, coordinates("C2")));
		addPiece(new Piece(BLACK, PAWN, coordinates("D2")));
		addPiece(new Piece(BLACK, PAWN, coordinates("E2")));
		addPiece(new Piece(BLACK, PAWN, coordinates("F2")));
		addPiece(new Piece(BLACK, PAWN, coordinates("G2")));
		addPiece(new Piece(BLACK, PAWN, coordinates("H2")));

		/* The rest */
		addPiece(new Piece(BLACK, ROOK, coordinates("A1")));
		addPiece(new Piece(BLACK, HORSE, coordinates("B1")));
		addPiece(new Piece(BLACK, BISHOP, coordinates("C1")));
		addPiece(new Piece(BLACK, QUEEN, coordinates("D1")));
		addPiece(new Piece(BLACK, KING, coordinates("E1")));
		addPiece(new Piece(BLACK, BISHOP, coordinates("F1")));
		addPiece(new Piece(BLACK, HORSE, coordinates("G1")));
		addPiece(new Piece(BLACK, ROOK, coordinates("H1")));
	}

	for (Piece* p : pieces)
		p->setOwner(this);
}

vector<Piece*> Player::getPieces(void) {
	return pieces;
}

void Player::copyPieces(vector<Piece*> oldPieces) {
	pieces.clear();
	for (int i = 0; i < oldPieces.size(); i++) {
		coordinates oldCoords = oldPieces[i]->getCoordinates();
		Piece* pieceCopy = new Piece(
			oldPieces[i]->getColor(),
			oldPieces[i]->getType(),
			oldCoords);
		pieceCopy->setCoordinates(oldCoords);
		pieceCopy->setMoved(oldPieces[i]->isMoved());
		pieces.push_back(pieceCopy);
	}
}

Player::~Player() {
	for (int i = 0; i < pieces.size(); i++)
		delete pieces[i];

	pieces.clear();
}

void Player::addPiece(Piece* piece) {
	pieces.push_back(piece);
}

void Player::printPieces(void) {
	for (int i = 0; i < (int) pieces.size(); i++) {
		std::cout << getPieces()[i]->getColor() << " " << getPieces()[i]->getType() << endl;
	}
}

string Player::toString() {
	switch (color) {
	case BLACK:
		return "PLAYER_BLACK";
	case WHITE:
		return "PLAYER_WHITE";
	default:
		return "PLAYER_?";
	}
}

bool Player::isChecked() {
	return _checked;
}

void Player::setChecked(bool check) {
	this->_checked = check;
}

void Player::setOpponent(Player* p) {
	if (p != this)
		opponent = p;
	else
		std::cout << "Cant set myself as an opponent!" << endl;
}

Player* Player::getOpponent() {
	return opponent;
}

int Player::getColor(void) {
	return color;
}