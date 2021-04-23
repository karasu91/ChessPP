#pragma once
#include <string>
#include <iostream>
#include <vector>

/* chessBoardManager.cpp */
extern int convertColumnCharToIndex(std::string);
extern int convertRowCharToIndex(std::string);
extern std::string convertColumnIndexToChar(int);
extern std::string convertRowIndexToChar(int);

typedef struct Coordinates {
private:
	std::string _row = "";
	std::string _column = "";
public:
	Coordinates() {};

	Coordinates(std::string str) {
		_column = str[0];
		_row = str[1];
	};

	Coordinates(std::string col, std::string r) {
		_column = col;
		_row = r;
	}

	Coordinates(int col, int r) {
		_column = convertColumnIndexToChar(col);
		_row = convertRowIndexToChar(r);
	}

	std::string toBoardIndices() {
		return "" + convertColumnCharToIndex(_column) + convertRowCharToIndex(_row);
	}

	std::string toCharString() {
		return "" + _column + _row;
	}

	int getBoardColumnIndex() {
		return convertColumnCharToIndex(_column);
	}

	int getBoardRowIndex() {
		return convertRowCharToIndex(_row);
	}
	bool operator ==(const Coordinates& other) {
		return this->_column == other._column && this->_row == other._row;
	}
	void operator =(Coordinates src) {
		this->_column = src._column;
		this->_row = src._row;
	}
} Coordinates;
