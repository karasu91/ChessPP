#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

extern string rowToBoardChar(int);
extern string columnToBoardInt(int);

struct coordinates {
	int x = 0;
	int y = 0;
	string toString() {
		return rowToBoardChar(x) + columnToBoardInt(y);
	}
};

class Piece {
public:
	Piece(int, int, int, int);
	~Piece();
	int getColor(void);
	int getType(void);
	bool isMoved(void);
	void setMoved(bool);
	void addThreat(Piece*);
	void resetThreatVector(void);
	void setAvailableMoves(vector<string>);
	void clearAvailableMoves();
	vector<string> getAvailableMoves();
	string toString(void);
	vector<Piece*> getThreatVector(void);
	coordinates getCoordinates();
	void setCoordinates(coordinates coords);
private:
	vector<Piece*> _threats;
	vector<string> _availableMoves;
	coordinates _coords;
	int _color = 0;
	int _type = 0;
	bool _hasMoved = false;
};

