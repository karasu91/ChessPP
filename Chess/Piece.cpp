#include "Piece.h"
#include "defines.h"
#include "player.h"

using namespace std;

Piece::Piece(int col, int typ, coordinates coords) {
	_color = col;
	_type = typ;
	_hasMoved = 0;
	_coords = coords;
}

Piece::~Piece() {
	if (_owner != NULL)
		_owner->removePiece(this);
#if _DEBUG
	//std::cout << "deleting Piece: " << this->toString() << " at " << getCoordinates().toCharString() << endl;
#endif
}

int Piece::getColor(void) {
	return _color;
}

vector<Piece*> Piece::getThreatVector(void) {
	return _threats;
}

coordinates Piece::getCoordinates() {
	return _coords;
}

void Piece::setCoordinates(const coordinates& coords) {
#if _DEBUG
	std::cout << "Setting new coordinates..." << endl;
#endif
	_coords = coords;
}

void Piece::operator=(const Piece& right) {
	for (int i = 0; i < right._availableMoves.size(); i++)
		this->_availableMoves.push_back(right._availableMoves[i]);
	for (int i = 0; i < right._threats.size(); i++)
		this->_threats.push_back(right._threats[i]);
	_coords = right._coords;
	_color = right._color;
	_type = right._type;
	_hasMoved = right._hasMoved;
}

Player* Piece::getOwner() {
	return _owner;
}

void Piece::resetThreatVector(void) {
	_threats.clear();
}

void Piece::setAvailableMoves(vector<coordinates> moves) {
	_availableMoves = moves;
}

void Piece::clearAvailableMoves() {
	_availableMoves.clear();
}

vector<coordinates> Piece::getAvailableMoves() {
	return _availableMoves;
}

string Piece::toString(void) {
	int num = getType();
	string str = "";
	switch (num) {
	case 0:
		str = "EMPTY";
	case 1:
		str = "P";
	case 2:
		str = "R";
	case 3:
		str = "H";
	case 4:
		str = "B";
	case 5:
		str = "Q";
	case 6:
		str = "K";
	}
	return str + to_string(getColor());
}

void Piece::addThreat(Piece* piece) {
	//string msg = piece->getColor() + " type: " + piece->getType();
	////std::cout << msg << endl;
	//msg = "";
	if (piece->getType() == EMPTYTILE)
		return;

	if (piece->getColor() == this->getColor()) // friendly pieces do not matter
		return;

	// Check if threats array already contains the piece
	if (std::find(_threats.begin(), _threats.end(), piece) != _threats.end()) {
		// Element in vector.
	}
	else {
		_threats.push_back(piece);
#if _DEBUG
		if (this->getType() == KING) {
			string msg = "Check! " + this->toString() + " is threatened by " + piece->toString();
			std::cout << msg << endl;
			std::cout << "KING threat count: " << _threats.size() << endl;
		}
#endif
	}
}

void Piece::setOwner(Player* p) {
	_owner = p;
}

int Piece::getType(void) {
	return _type;
}

void Piece::setType(int type) {
	_type = type;
}

bool Piece::isMoved(void) {
	return _hasMoved;
}

void Piece::setMoved(bool state) {
	_hasMoved = state;
}