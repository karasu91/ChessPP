#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

/* chessBoardManager.cpp */
extern int convertColumnCharToIndex(string);
extern int convertRowCharToIndex(string);
extern string convertColumnIndexToChar(int);
extern string convertRowIndexToChar(int);

extern int charToInt(char);

typedef struct coordinates {
private:
	string _row = "";
	string _column = "";
public:
	coordinates() {
	};

	coordinates(string str) {
		_column = str[0];
		_row = str[1];
	};

	coordinates(string col, string r) {
		_column = col;
		_row = r;
	}

	coordinates(int col, int r) {
		_column = convertColumnIndexToChar(col);
		_row = convertRowIndexToChar(r);
	}

	string toBoardIndices() {
		return "" + convertColumnCharToIndex(_column) + convertRowCharToIndex(_row);
	}

	string toCharString() {
		return "" + _column + _row;
	}

	int getBoardColumnIndex() {
		return convertColumnCharToIndex(_column);
	}

	int getBoardRowIndex() {
		return convertRowCharToIndex(_row);
	}
	bool operator ==(const coordinates& other) {
		return this->_column == other._column && this->_row == other._row;
	}
	void operator =(coordinates src) {
		this->_column = src._column;
		this->_row = src._row;
	}
} coordinates;
