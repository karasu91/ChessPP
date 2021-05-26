#include <string>
#include <locale>
#include "player.h"
#include "Piece.h"



extern bool boeq(int, int, int); // in chessboardManager.cpp

void Player::removePiece(std::shared_ptr<Piece> removeThis) {
	for (int i = 0; i < pieces.size(); i++)
	{
		if (pieces[i] == removeThis)
		{
			pieces.erase(pieces.begin() + i);
			break;
		}
	}
}

Player::Player(Colors col) {
	this->color = col;
}

void Player::initPieces() {
	if (this->color == Colors::WHITE)
	{
		addPiece(std::make_shared<Pawn>(Pawn(this->color, Coordinates("A7"))));
		addPiece(std::make_shared<Pawn>(Pawn(this->color, Coordinates("B7"))));
		addPiece(std::make_shared<Pawn>(Pawn(this->color, Coordinates("C7"))));
		addPiece(std::make_shared<Pawn>(Pawn(this->color, Coordinates("D7"))));
		addPiece(std::make_shared<Pawn>(Pawn(this->color, Coordinates("E7"))));
		addPiece(std::make_shared<Pawn>(Pawn(this->color, Coordinates("F7"))));
		addPiece(std::make_shared<Pawn>(Pawn(this->color, Coordinates("G7"))));
		addPiece(std::make_shared<Pawn>(Pawn(this->color, Coordinates("H7"))));

		addPiece(std::make_shared<Rook>(Rook(this->color, Coordinates("A8"))));
		addPiece(std::make_shared<Knight>(Knight(this->color, Coordinates("B8"))));
		addPiece(std::make_shared<Bishop>(Bishop(this->color, Coordinates("C8"))));
		addPiece(std::make_shared<Queen>(Queen(this->color, Coordinates("D8"))));
		addPiece(std::make_shared<King>(King(this->color, Coordinates("E8"))));
		addPiece(std::make_shared<Bishop>(Bishop(this->color, Coordinates("F8"))));
		addPiece(std::make_shared<Knight>(Knight(this->color, Coordinates("G8"))));
		addPiece(std::make_shared<Rook>(Rook(this->color, Coordinates("H8"))));
	}
	else
	{
		addPiece(std::make_shared<Pawn>(Pawn(this->color, Coordinates("A2"))));
		addPiece(std::make_shared<Pawn>(Pawn(this->color, Coordinates("B2"))));
		addPiece(std::make_shared<Pawn>(Pawn(this->color, Coordinates("C2"))));
		addPiece(std::make_shared<Pawn>(Pawn(this->color, Coordinates("D2"))));
		addPiece(std::make_shared<Pawn>(Pawn(this->color, Coordinates("E2"))));
		addPiece(std::make_shared<Pawn>(Pawn(this->color, Coordinates("F2"))));
		addPiece(std::make_shared<Pawn>(Pawn(this->color, Coordinates("G2"))));
		addPiece(std::make_shared<Pawn>(Pawn(this->color, Coordinates("H2"))));

		addPiece(std::make_shared<Rook>(Rook(this->color, Coordinates("A1"))));
		addPiece(std::make_shared<Knight>(Knight(this->color, Coordinates("B1"))));
		addPiece(std::make_shared<Bishop>(Bishop(this->color, Coordinates("C1"))));
		addPiece(std::make_shared<Queen>(Queen(this->color, Coordinates("D1"))));
		addPiece(std::make_shared<King>(King(this->color, Coordinates("E1"))));
		addPiece(std::make_shared<Bishop>(Bishop(this->color, Coordinates("F1"))));
		addPiece(std::make_shared<Knight>(Knight(this->color, Coordinates("G1"))));
		addPiece(std::make_shared<Rook>(Rook(this->color, Coordinates("H1"))));
	}
}

std::vector<std::shared_ptr<Piece>> Player::getPieces(void) {
	return pieces;
}

void Player::updatePieceAt(std::shared_ptr<Piece> p, int i) {
	pieces[i] = p;
}

void Player::copyPieces(std::vector<std::shared_ptr<Piece>> oldPieces) {
	pieces.clear();
	for (int i = 0; i < oldPieces.size(); i++)
	{
		Coordinates oldCoords = oldPieces[i]->getCoordinates();

		auto pieceCopy = oldPieces[i]->Clone();

		pieceCopy->setCoordinates(oldCoords);
		pieceCopy->setMoved(oldPieces[i]->isMoved());
		pieces.push_back(pieceCopy);
	}
}

Player::~Player() {
	pieces.clear();
}

void Player::addPiece(std::shared_ptr<Piece> piece) {
	piece->setOwner(this);
	pieces.push_back(piece);
}

void Player::printPieces(void) {
	for (int i = 0; i < (int) pieces.size(); i++)
	{
		std::cout << static_cast<int>(getPieces()[i]->getColor()) << " " << static_cast<int>(getPieces()[i]->getType()) << std::endl;
	}
}

std::string Player::toCharString() {
	switch (color)
	{
	case Colors::BLACK:
		return "PLAYER_BLACK";
	case Colors::WHITE:
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
		std::cout << "Cant set myself as an opponent!" << std::endl;
}

Player* Player::getOpponent() {
	return opponent;
}

Colors Player::getColor(void) {
	return color;
}