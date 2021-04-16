#include "Piece.h"
#include "defines.h"

using namespace std;

Piece::Piece(int col, int typ)
{
	color = col;
	type = typ;
	threats.clear();
	hasMoved = 0;
}

int Piece::getColor(void)
{
	return color;
}

vector<Piece*> Piece::getThreatVector(void)
{
	return threats;
}

void Piece::resetThreatVector(void)
{
	this->threats.clear();
}

void Piece::setAvailableMoves(vector<string> moves) {
	availableMoves = moves;
}

void Piece::clearAvailableMoves() {
	availableMoves.clear();
}

vector<string> Piece::getAvailableMoves() {
	return availableMoves;
}


string numToPiece(int num) {
	string piece;
	if(num == 0) {
		piece = "-";
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
	if(std::find(threats.begin(), threats.end(), piece) != threats.end()) {
		// Element in vector.
	}
	else
	{
		threats.push_back(piece);
		if(this->getType() == KING) {
			cout << "Check!" << endl;
			string msg = this->toString() + " is threatened by " + piece->toString();
			cout << msg << endl;
		}
	}
}

Piece::~Piece()
{

}

int Piece::getType(void)
{
	return type;
}

int Piece::isMoved(void) {
	return hasMoved;
}

void Piece::setMoved(int state) {
	hasMoved = state;
}



