#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "coordinates.h"
using namespace std;

class Piece {
public:
	Piece(int, int, coordinates);
	~Piece();
	int getColor(void);
	int getType(void);
	void setType(int);
	bool isMoved(void);
	void setMoved(bool);
	void addThreat(Piece*);
	void resetThreatVector(void);
	void setAvailableMoves(vector<coordinates>);
	void clearAvailableMoves();
	vector<coordinates> getAvailableMoves();
	string toString(void);
	vector<Piece*> getThreatVector(void);
	coordinates getCoordinates();
	void setCoordinates(const coordinates &coords);
	void operator =(const Piece &right);
private:
	vector<Piece*> _threats;
	vector<coordinates> _availableMoves;
	coordinates _coords;
	int _color = 0;
	int _type = 0;
	bool _hasMoved = false;
};

