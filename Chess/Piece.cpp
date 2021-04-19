#include "Piece.h"
#include "defines.h"

using namespace std;

Piece::Piece(int col, int typ, coordinates coords) {
	_color = col;
	_type = typ;
	_hasMoved = 0;
#if _DEBUG
	cout << "allocating " << coords.toCharString() << " to piece " << this->toString() << endl;
#endif
	_coords._row = coords._row;
	_coords._column = coords._column;
}

Piece::~Piece() {
#if _DEBUG
	//cout << "deleting Piece: " << this->toString() << " at " << getCoordinates().toCharString() << endl;
	//resetThreatVector();
	//_availableMoves.clear();
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

void Piece::setCoordinates(const coordinates &coords) {
#if _DEBUG
	cout << "Setting new coordinates..." << endl;
#endif
	_coords._row = coords._row;
	_coords._column = coords._column;
}

void Piece::operator=(const Piece& right) {
	for(int i = 0; i < right._availableMoves.size(); i++)
		this->_availableMoves.push_back(right._availableMoves[i]);
	for(int i = 0; i < right._threats.size(); i++)
		this->_threats.push_back(right._threats[i]);
	_coords._row = right._coords._row;
	_coords._column = right._coords._column;
	_color = right._color;
	_type = right._type;
	_hasMoved = right._hasMoved;
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



