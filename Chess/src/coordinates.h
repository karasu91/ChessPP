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
		_row = std::to_string(abs(r - 9) - 1);
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
		return abs(atoi(_row.c_str()) - 9) - 1;
	}

	bool operator ==(const Coordinates& other) {
		return this->_column == other._column && this->_row == other._row;
	}

	void operator =(Coordinates src) {
		this->_column = src._column;
		this->_row = src._row;
	}

	int convertColumnCharToIndex(std::string column) {
		if (column == "A")
			return 0;
		else if (column == "B")
			return 1;
		else if (column == "C")
			return 2;
		else if (column == "D")
			return 3;
		else if (column == "E")
			return 4;
		else if (column == "F")
			return 5;
		else if (column == "G")
			return 6;
		else if (column == "H")
			return 7;
		else
			return 99;
	}

	std::string convertColumnIndexToChar(int index) {
		switch (index) {
		case 0:
			return "A";
		case 1:
			return "B";
		case 2:
			return "C";
		case 3:
			return "D";
		case 4:
			return "E";
		case 5:
			return "F";
		case 6:
			return "G";
		case 7:
			return "H";
		default:
			throw std::runtime_error(std::string("Tried to convert index: ") + std::to_string(index));
		}
	}
	
} Coordinates;


