#include "Piece.h"
#include "defines.h"

using namespace std;

Piece::Piece(int col, int typ, int row, int column)
{
	_color = col;
	_type = typ;
	_threats.clear();
	_hasMoved = 0;
	_coords = * new coordinates;
	_coords.x = row;
	_coords.y = column;
}

Piece::~Piece() {
	cout << "deleting Piece: " << this->toString() << " at " << getCoordinates().toString() << endl;
}


int Piece::getColor(void)
{
	return _color;
}

vector<Piece*> Piece::getThreatVector(void)
{
	return _threats;
}

coordinates Piece::getCoordinates() {
	return _coords;
}

void Piece::setCoordinates(coordinates coords) {
#if DEBUG
	cout << "Setting new coordinates..." << endl;
#endif
	_coords.x = coords.x;
	_coords.y = coords.y;
}

void Piece::resetThreatVector(void)
{
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
	string piece;
	if(num == 0) {
		piece = "EMPTY";
	}
	if(num == 1) {
		piece = "P";
	}
	if(num == 2) {
		piece = "R";
	}
	if(num == 3) {
		piece = "H";
	}
	if(num == 4) {
		piece = "B";
	}
	if(num == 5) {
		piece = "Q";
	}
	if(num == 6) {
		piece = "K";
	}
	return piece;
}


string Piece::toString(void) {
	return numToPiece(getType()) + to_string(getColor());
}

void Piece::addThreat(Piece* piece)
{
	//string msg = piece->getColor() + " type: " + piece->getType();
	////cout << msg << endl;
	//msg = "";

	if(piece->getColor() == this->getColor()) // friendly pieces do not matter
		return;

	// Check if threats array already contains the piece
	if(std::find(_threats.begin(), _threats.end(), piece) != _threats.end()) {
		// Element in vector.
	}
	else
	{
		_threats.push_back(piece);
		if(this->getType() == KING) {

			string msg = "Check! " + this->toString() + " is threatened by " + piece->toString();
			cout << msg << endl;
		}
	}
}



int Piece::getType(void)
{
	return _type;
}

bool Piece::isMoved(void) {
	return _hasMoved;
}

void Piece::setMoved(bool state) {
	_hasMoved = state;
}



