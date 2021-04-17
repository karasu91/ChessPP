#include "Piece.h"
#include "defines.h"

using namespace std;

Piece::Piece(int col, int typ, int row, int column) {
	_color = col;
	_type = typ;
	_hasMoved = 0;
	_coords = *new coordinates;
	_coords.x = row;
	_coords.y = column;
}

Piece::~Piece() {
#if _DEBUG
	cout << "deleting Piece: " << this->toString() << " at " << getCoordinates().toString() << endl;
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

void Piece::setCoordinates(coordinates coords) {
#if _DEBUG
	cout << "Setting new coordinates..." << endl;
#endif
	_coords.x = coords.x;
	_coords.y = coords.y;
}

void Piece::resetThreatVector(void) {
	this->_threats.clear();
}

void Piece::setAvailableMoves(vector<string> moves) {
	_availableMoves = moves;
}

void Piece::clearAvailableMoves() {
	_availableMoves.clear();
}

vector<string> Piece::getAvailableMoves() {
	return _availableMoves;
}


string numToPiece(int num) {
	switch(num)
	{
	case 0:
		return "EMPTY";
	case 1:
		return "P";
	case 2:
		return "R";
	case 3:
		return "H";
	case 4:
		return "B";
	case 5:
		return "Q";
	case 6:
		return "K";
	}
}


string Piece::toString(void) {
	return numToPiece(getType()) + to_string(getColor());
}

void Piece::addThreat(Piece* piece) {
	//string msg = piece->getColor() + " type: " + piece->getType();
	////cout << msg << endl;
	//msg = "";
	if(piece->getType() == EMPTYTILE)
		return;

	if(piece->getColor() == this->getColor()) // friendly pieces do not matter
		return;

	// Check if threats array already contains the piece
	if(std::find(_threats.begin(), _threats.end(), piece) != _threats.end())
	{
		// Element in vector.
	}
	else
	{
		this->_threats.push_back(piece);
		if(this->getType() == KING)
		{
#if _DEBUG
			string msg = "Check! " + this->toString() + " is threatened by " + piece->toString();
			cout << msg << endl;
			cout << "KING threat count: " << _threats.size() << endl;
#endif
		}
	}
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



