#include "Piece.h"
#include "defines.h"

using namespace std;

Piece::Piece(int col, int typ)
{
	color = col;
	type = typ;
	threat.clear();
	moved = 0;
}

int Piece::getColor(void)
{
	return color;
}

vector<int> Piece::getThreatVect(void)
{
	return threat;
}

void Piece::resetThreatVector(void)
{
	this->threat.clear();
}

void Piece::addThreatVect(int state)
{
	bool whiteIsListed = false;
	bool blackIsListed = false;

	/*	Check if the piece has already the current color assigned in its threat list
		to avoid putting it again */
	for (int i = 0; i < threat.size(); i++) {
		if (this->threat[i] == WHITE)
			whiteIsListed = true;
		if (this->threat[i] == BLACK)
			blackIsListed = true;
	}
	for (int x = 0; x<threat.size(); x++)
		int i = this->threat[x];

	/*	Push threat color into vector if the color does not already exist in it */
	if (state == WHITE && !whiteIsListed) {
		this->threat.push_back(state);
	}
	if (state == BLACK && !blackIsListed) {
		this->threat.push_back(state);
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
	return moved;
}

void Piece::setMoved(int state) {
	moved = state;
}



