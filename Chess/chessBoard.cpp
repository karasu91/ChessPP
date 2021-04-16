#include "chessBoard.h"
#include <vector>
#include "Piece.h"
#include "player.h"
#include "defines.h"

Piece* emptyTile = new Piece(FREE, FREE);

using namespace std;

chessBoard::chessBoard()
{
	// Set the whole board completely empty
	for (int i = 0; i <= 7; i++)
		for (int j = 0; j <= 7; j++) {
			board[i][j] = emptyTile;
		}
}

chessBoard::~chessBoard()
{
}

void chessBoard::initBoard(player* p)
{
	// Initialize the board with players' pieces
	for (int i = 0; i < p->getPieces().size(); i++) {

		// White pawns
		if (p->getPieces()[i]->getColor() == WHITE && p->getPieces()[i]->getType() == PAWN) {
			for (int j = 0; j <= 7; j++) {
				if (board[6][j]->getType() == FREE) {
					board[6][j] = p->getPieces()[i];
					break;
				}
			}
		}
		// White rooks
		if (p->getPieces()[i]->getColor() == WHITE && p->getPieces()[i]->getType() == ROOK) {
			if (board[7][0]->getType() == FREE)
				board[7][0] = p->getPieces()[i];
			else if (board[7][7]->getType() == FREE)
				board[7][7] = p->getPieces()[i];
			else
				cout << "ERROR IN W ROOK INIT" << endl;
		}
		// White horses
		else if (p->getPieces()[i]->getColor() == WHITE && p->getPieces()[i]->getType() == HORSE) {
			if (board[7][1]->getType() == FREE)
				board[7][1] = p->getPieces()[i];
			else if (board[7][6]->getType() == FREE)
				board[7][6] = p->getPieces()[i];
			else
				cout << "ERROR IN W HORSE INIT" << endl;
		}
		// White bishops
		else if (p->getPieces()[i]->getColor() == WHITE && p->getPieces()[i]->getType() == BISHOP) {
			if (board[7][2]->getType() == FREE)
				board[7][2] = p->getPieces()[i];
			else if (board[7][5]->getType() == FREE)
				board[7][5] = p->getPieces()[i];
			else
				cout << "ERROR IN W BISHOP INIT" << endl;
		}
		// White queen
		else if (p->getPieces()[i]->getColor() == WHITE && p->getPieces()[i]->getType() == QUEEN) {
			// THIS SHOULD AWLAYS BE FREE!!	
			if (board[7][3]->getType() == FREE)
				board[7][3] = p->getPieces()[i];
			else
				cout << "ERROR IN W QUEEN INIT" << endl;
		}
		// White king 
		else if (p->getPieces()[i]->getColor() == WHITE && p->getPieces()[i]->getType() == KING) {
			// THIS SHOULD AWLAYS BE FREE!!	
			if (board[7][4]->getType() == FREE)
				board[7][4] = p->getPieces()[i];
			else
				cout << "ERROR IN W KING INIT" << endl;
		}
		// Black pawns
		if (p->getPieces()[i]->getColor() == BLACK && p->getPieces()[i]->getType() == PAWN) {
			for (int j = 0; j <= 7; j++) {
				// If an empty square is available in the last two rows, get square number in string and s				end new pawn piece in these coordinates //
				if (board[1][j]->getType() == FREE) {
					board[1][j] = p->getPieces()[i];
					break;
				}
			}
		}
		// Black rooks
		else if (p->getPieces()[i]->getColor() == BLACK && p->getPieces()[i]->getType() == ROOK) {
			if (board[0][0]->getType() == FREE)
				board[0][0] = p->getPieces()[i];
			else if (board[0][7]->getType() == FREE)
				board[0][7] = p->getPieces()[i];
			else
				cout << "ERROR IN B ROOK INIT" << endl;
		}
		// Black horses
		else if (p->getPieces()[i]->getColor() == BLACK && p->getPieces()[i]->getType() == HORSE) {
			if (board[0][1]->getType() == FREE)
				board[0][1] = p->getPieces()[i];
			else if (board[0][6]->getType() == FREE)
				board[0][6] = p->getPieces()[i];
			else
				cout << "ERROR IN B HORSE INIT" << endl;
		}
		// Black bishops
		else if (p->getPieces()[i]->getColor() == BLACK && p->getPieces()[i]->getType() == BISHOP) {
			if (board[0][2]->getType() == FREE)
				board[0][2] = p->getPieces()[i];
			else if (board[0][5]->getType() == FREE)
				board[0][5] = p->getPieces()[i];
			else
				cout << "ERROR IN B BISHOP INIT" << endl;
		}
		// Black queen
		else if (p->getPieces()[i]->getColor() == BLACK && p->getPieces()[i]->getType() == QUEEN) {
			// THIS SHOULD AWLAYS BE FREE!!	
			if (board[0][3]->getType() == FREE)
				board[0][3] = p->getPieces()[i];
			else
				cout << "ERROR IN B QUEEN INIT" << endl;
		}
		// Black king
		else if (p->getPieces()[i]->getColor() == BLACK && p->getPieces()[i]->getType() == KING) {
			// THIS SHOULD AWLAYS BE FREE!!	
			if (board[0][4]->getType() == FREE)
				board[0][4] = p->getPieces()[i];
			else
				cout << "ERROR IN B KING INIT" << endl;
		}
	}
}

int chessBoard::returnCol(string col)

{
	int column;
	if (col[1] == '1')
		column = 0;
	else if (col[1] == '2')
		column = 1;
	else if (col[1] == '3')
		column = 2;
	else if (col[1] == '4')
		column = 3;
	else if (col[1] == '5')
		column = 4;
	else if (col[1] == '6')
		column = 5;
	else if (col[1] == '7')
		column = 6;
	else if (col[1] == '8')
		column = 7;
	return column;
}

int chessBoard::returnRow(string row)

{
	int rrow;
	if (row[0] == 'A')
		rrow = 0;
	else if (row[0] == 'B')
		rrow = 1;
	else if (row[0] == 'C')
		rrow = 2;
	else if (row[0] == 'D')
		rrow = 3;
	else if (row[0] == 'E')
		rrow = 4;
	else if (row[0] == 'F')
		rrow = 5;
	else if (row[0] == 'G')
		rrow = 6;
	else if (row[0] == 'H')
		rrow = 7;
	return rrow;
}

Piece* chessBoard::getPiece(int row, int column)
{
	return board[row][column];
}

void chessBoard::setPiece(Piece* piece, int startRow, int startColumn, int endRow, int endColumn)
{
	//board[endRow][endColumn] = NULL;
	board[endRow][endColumn] = piece;
	board[startRow][startColumn] = emptyTile;
}

void chessBoard::createThreatVector(void)
{
	/* This function always runs the board empty of threat
		and then recalculates every piece's threat */
	int type;
	int color;
	int pColor;
	//for (int i = 0; i <= 7; i++)
		//for (int j = 0; j <= 7; j++)
			//board[i][j]->addThreatVect(FREE);

	for (int i = 0; i <= 7; i++) {
		int unitrow = i;
		for (int j = 0; j <= 7; j++) {
			int unitcol = j;
			board[i][j]->resetThreatVector();
			color = board[i][j]->getColor();
			type = board[i][j]->getType();
			if (type == PAWN) {
				if (board[i][j]->getColor() == WHITE) {
					// If the pawn is on the left side column
					if (unitcol == 0) {
						if (unitrow - 1 >= 0)
							// If enemy is on a killable tile
							if (board[unitrow - 1][unitcol + 1]->getColor() != color) {
								board[unitrow - 1][unitcol + 1]->addThreatVect(board[unitrow][unitcol]->getColor());
							}
					}
					// If the pawn is on the right side column
					else if (unitcol == 7) {
						if (unitrow - 1 >= 0)
							if (board[unitrow - 1][unitcol - 1]->getColor() != color) {
								board[unitrow - 1][unitcol - 1]->addThreatVect(board[unitrow][unitcol]->getColor());
							}
					}
					// Pawn is not on the side columns
					else {
						if (unitrow - 1 >= 0) {
							// Add threat to tiles that are under threat (row +-1 depending on color; column +-1)
							if (board[unitrow - 1][unitcol - 1]->getColor() != color) {
								board[unitrow - 1][unitcol - 1]->addThreatVect(board[unitrow][unitcol]->getColor());
							}
							if (board[unitrow - 1][unitcol + 1]->getColor() != color) {
								board[unitrow - 1][unitcol + 1]->addThreatVect(board[unitrow][unitcol]->getColor());
							}
						}
					}
				}
				else if (board[i][j]->getColor() == BLACK) {
					//type = board[i][j]->getType();
					// If the pawn is on the	 left side column
					if (unitcol == 0) {
						if (unitrow + 1 <= 7)
							// If enemy is on a killable tile	
							if (board[unitrow + 1][unitcol + 1]->getColor() != color) {
								board[unitrow + 1][unitcol + 1]->addThreatVect(board[unitrow][unitcol]->getColor());
							}
					}
					// If the pawn is on the right side column
					else if (unitcol == 7) {
						if (unitrow + 1 <= 7)
							if (board[unitrow + 1][unitcol - 1]->getColor() != color) {
								board[unitrow + 1][unitcol - 1]->addThreatVect(board[unitrow][unitcol]->getColor());
							}
					}
					// Pawn is not on the side columns
					else {
						if (unitrow + 1 <= 7) {
							// If enemy is on a killable	 tile
							if (board[unitrow + 1][unitcol - 1]->getColor() != color) {
								board[unitrow + 1][unitcol - 1]->addThreatVect(board[unitrow][unitcol]->getColor());
							}
							if (board[unitrow + 1][unitcol + 1]->getColor() != color) {
								board[unitrow + 1][unitcol - 1]->addThreatVect(board[unitrow][unitcol]->getColor());
							}
						}
					}
				}
			}
			// Rook
			else if (type == ROOK) {
				for (int k = 1; k <= 7; k++) {
					// Left							
					if (unitcol - k >= 0) {
						if (board[unitrow][unitcol - k]->getType() == FREE) {
							board[unitrow][unitcol - k]->addThreatVect(board[unitrow][unitcol]->getColor());
						}
						else {
							board[unitrow][unitcol - k]->addThreatVect(board[unitrow][unitcol]->getColor());
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Right							
					if (unitcol + k <= 7) {
						if (board[unitrow][unitcol + k]->getType() == FREE) {
							board[unitrow][unitcol + k]->addThreatVect(board[unitrow][unitcol]->getColor());
						}
						else {
							board[unitrow][unitcol + k]->addThreatVect(board[unitrow][unitcol]->getColor());
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Up							
					if (unitrow - k >= 0) {
						if (board[unitrow - k][unitcol]->getType() == FREE) {
							board[unitrow - k][unitcol]->addThreatVect(board[unitrow][unitcol]->getColor());
						}
						else {

							board[unitrow - k][unitcol]->addThreatVect(board[unitrow][unitcol]->getColor());
							break;
						}

					}
				}

				for (int k = 1; k <= 7; k++) {
					// Down	

					if (unitrow + k <= 7) {
						if (board[unitrow + k][unitcol]->getType() == FREE) {
							board[unitrow + k][unitcol]->addThreatVect(board[unitrow][unitcol]->getColor());
						}
						else {

							board[unitrow + k][unitcol]->addThreatVect(board[unitrow][unitcol]->getColor());
							break;
						}
					}
				}
			}
			// Bishop, both colors
			else if (type == BISHOP) {
				for (int k = 1; k <= 7; k++) {
					// Left up diagonal						
					if (unitcol - k >= 0 && unitrow - k >= 0) {
						if (board[unitrow - k][unitcol - k]->getType() == FREE) {
							board[unitrow - k][unitcol - k]->addThreatVect(board[unitrow][unitcol]->getColor());
						}
						else {

							board[unitrow - k][unitcol - k]->addThreatVect(board[unitrow][unitcol]->getColor());
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Right up diagonal			
					if (unitcol + k <= 7 && unitrow - k >= 0) {
						if (board[unitrow - k][unitcol + k]->getType() == FREE) {
							board[unitrow - k][unitcol + k]->addThreatVect(board[unitrow][unitcol]->getColor());
						}
						else {
							board[unitrow - k][unitcol + k]->addThreatVect(board[unitrow][unitcol]->getColor());
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					//	Right down di	agonal
					if (unitcol + k <= 7 && unitrow + k <= 7) {
						if (board[unitrow + k][unitcol + k]->getType() == FREE) {
							board[unitrow + k][unitcol + k]->addThreatVect(board[unitrow][unitcol]->getColor());
						}
						else {
							board[unitrow + k][unitcol + k]->addThreatVect(board[unitrow][unitcol]->getColor());
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					//	Left down dia	gonal
					if (unitcol - k >= 0 && unitrow + k <= 7) {
						if (board[unitrow + k][unitcol - k]->getType() == FREE) {
							board[unitrow + k][unitcol - k]->addThreatVect(board[unitrow][unitcol]->getColor());
						}
						else {
							board[unitrow + k][unitcol - k]->addThreatVect(board[unitrow][unitcol]->getColor());
							break;
						}
					}
				}
			}
			// Horse, both colors
			else if (type == HORSE) {
				// Left	
				if (unitcol - 2 >= 0 && unitrow + 1 <= 7)
					board[unitrow + 1][unitcol - 2]->addThreatVect(board[unitrow][unitcol]->getColor());
				if (unitcol - 2 >= 0 && unitrow - 1 >= 0)
					board[unitrow - 1][unitcol - 2]->addThreatVect(board[unitrow][unitcol]->getColor());
				// Up		
				if (unitcol - 1 >= 0 && unitrow - 2 >= 0)
					board[unitrow - 2][unitcol - 1]->addThreatVect(board[unitrow][unitcol]->getColor());
				if (unitcol + 1 <= 7 && unitrow - 2 >= 0)
					board[unitrow - 2][unitcol + 1]->addThreatVect(board[unitrow][unitcol]->getColor());
				// Right	
				if (unitcol + 2 <= 7 && unitrow - 1 >= 0)
					board[unitrow - 1][unitcol + 2]->addThreatVect(board[unitrow][unitcol]->getColor());
				if (unitcol + 2 <= 7 && unitrow + 1 <= 7)
					board[unitrow + 1][unitcol + 2]->addThreatVect(board[unitrow][unitcol]->getColor());
				// Down		
				if (unitcol - 1 >= 0 && unitrow + 2 <= 7)
					board[unitrow + 2][unitcol - 1]->addThreatVect(board[unitrow][unitcol]->getColor());
				if (unitcol + 1 <= 7 && unitrow + 2 <= 7)
					board[unitrow + 2][unitcol + 1]->addThreatVect(board[unitrow][unitcol]->getColor());
			}
			// Queen, both colors
			else if (type == QUEEN) {
				for (int k = 1; k <= 7; k++) {
					// Left
					if (unitcol - k >= 0) {
						if (board[unitrow][unitcol - k]->getType() == FREE) {
							board[unitrow][unitcol - k]->addThreatVect(board[unitrow][unitcol]->getColor());
						}
						else {
							board[unitrow][unitcol - k]->addThreatVect(board[unitrow][unitcol]->getColor());
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Right							
					if (unitcol + k <= 7) {
						if (board[unitrow][unitcol + k]->getType() == FREE) {
							board[unitrow][unitcol + k]->addThreatVect(board[unitrow][unitcol]->getColor());
						}
						else {
							board[unitrow][unitcol + k]->addThreatVect(board[unitrow][unitcol]->getColor());
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Up							
					if (unitrow - k >= 0) {
						if (board[unitrow - k][unitcol]->getType() == FREE) {
							board[unitrow - k][unitcol]->addThreatVect(board[unitrow][unitcol]->getColor());
						}
						else {
							board[unitrow - k][unitcol]->addThreatVect(board[unitrow][unitcol]->getColor());
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Down	
					if (unitrow + k <= 7) {
						if (board[unitrow + k][unitcol]->getType() == FREE) {
							board[unitrow + k][unitcol]->addThreatVect(board[unitrow][unitcol]->getColor());
						}
						else {
							board[unitrow + k][unitcol]->addThreatVect(board[unitrow][unitcol]->getColor());
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Left up diagonal						
					if (unitcol - k >= 0 && unitrow - k >= 0) {
						if (board[unitrow - k][unitcol - k]->getType() == FREE) {
							board[unitrow - k][unitcol - k]->addThreatVect(board[unitrow][unitcol]->getColor());
						}
						else {
							board[unitrow - k][unitcol - k]->addThreatVect(board[unitrow][unitcol]->getColor());
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Right up diagonal			
					if (unitcol + k <= 7 && unitrow - k >= 0) {
						if (board[unitrow - k][unitcol + k]->getType() == FREE) {
							board[unitrow - k][unitcol + k]->addThreatVect(board[unitrow][unitcol]->getColor());
						}
						else {
							board[unitrow - k][unitcol + k]->addThreatVect(board[unitrow][unitcol]->getColor());
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Right d	own d	iagonal
					if (unitcol + k <= 7 && unitrow + k <= 7) {
						if (board[unitrow + k][unitcol + k]->getType() == FREE) {
							board[unitrow + k][unitcol + k]->addThreatVect(board[unitrow][unitcol]->getColor());
						}
						else {
							board[unitrow + k][unitcol + k]->addThreatVect(board[unitrow][unitcol]->getColor());
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Left do	wn di	agonal
					if (unitcol - k >= 0 && unitrow + k <= 7) {
						if (board[unitrow + k][unitcol - k]->getType() == FREE) {
							board[unitrow + k][unitcol - k]->addThreatVect(board[unitrow][unitcol]->getColor());
						}
						else {
							board[unitrow + k][unitcol - k]->addThreatVect(board[unitrow][unitcol]->getColor());
							break;
						}
					}
				}
			}
			// King,	both colors

			// TODO

			//else if (type == KING) {
				//if (unitcol - 1 >= 0)
					//if (board[unitrow][unitcol - 1])
						//int i = 0;
			//}
		}
	}
}



vector<string> chessBoard::validMoves(Piece* unit, string pos)
{
	/*	This function returns a vector containing every possible
		move for a chosen piece */

	int unitrow = returnRow(pos);
	int unitcol = returnCol(pos);
	vector<string> validMoves;
	int type = unit->getType();
	int color = unit->getColor();

	// Pawn, white
	if (type == PAWN) {
		if (color == WHITE) {
			// If the pawn is on the left side column
			if (unitcol == 0) {
				// Basic one or two moves in front, default situation
				if (unitrow - 1 >= 0) {
					if (board[unitrow - 1][unitcol]->getType() == FREE) {
						validMoves.push_back(to_string(unitrow - 1) += to_string(unitcol));
					}
					// If pawn is on a starting position
					if (unit->isMoved() == NO) {
						if (board[unitrow - 1][unitcol]->getType() == FREE && board[unitrow - 2][unitcol]->getType() == FREE) {
							validMoves.push_back(to_string(unitrow - 2) += to_string(unitcol));
						}
					}
					// If enemy is on a killable tile
					if (board[unitrow - 1][unitcol + 1]->getColor() == BLACK) {
						validMoves.push_back(to_string(unitrow - 1) += to_string(unitcol + 1));
					}
				}
				else
					cout << "Cannot move!" << endl;
			}
			// If the pawn is on the right side column
			else if (unitcol == 7) {
				if (unitrow - 1 >= 0) {
					// Basic one or two moves in front, default situation
					if (board[unitrow - 1][unitcol]->getType() == FREE) {
						validMoves.push_back(to_string(unitrow - 1) += to_string(unitcol));
					}
					// If pawn has not moved before
					if (unit->isMoved() == NO) {
						if (board[unitrow - 1][unitcol]->getType() == FREE && board[unitrow - 2][unitcol]->getType() == FREE) {
							validMoves.push_back(to_string(unitrow - 2) += to_string(unitcol));
						}
					}
					// If enemy is on a killable FREE
					if (board[unitrow - 1][unitcol - 1]->getColor() == BLACK) {
						validMoves.push_back(to_string(unitrow - 1) += to_string(unitcol - 1));
					}
				}
				else
					cout << "Cannot move!" << endl;
			}
			// Pawn is not on the side columns
			else {
				if (unitrow - 1 >= 0) {
					if (board[unitrow - 1][unitcol]->getType() == FREE) {
						validMoves.push_back(to_string(unitrow - 1) += to_string(unitcol));
					}
					if (unit->isMoved() == NO) {
						if (board[unitrow - 1][unitcol]->getType() == FREE && board[unitrow - 2][unitcol]->getType() == FREE) {
							validMoves.push_back(to_string(unitrow - 2) += to_string(unitcol));
						}
					}
					// If enemy is on a killable tile
					if (board[unitrow - 1][unitcol - 1]->getColor() == BLACK) {
						validMoves.push_back(to_string(unitrow - 1) += to_string(unitcol - 1));
					}
					if (board[unitrow - 1][unitcol + 1]->getColor() == BLACK) {
						validMoves.push_back(to_string(unitrow - 1) += to_string(unitcol + 1));
					}
				}
				else
					cout << "Cannot move!" << endl;
			}
		}
		// Black case, pawn
		else if (color == BLACK) {
			// If the pawn is on the left side column
			if (unitcol == 0) {
				// Basic one or two moves in front, default situation
				if (board[unitrow + 1][unitcol]->getType() == FREE) {
					validMoves.push_back(to_string(unitrow + 1) += to_string(unitcol));
				}
				// If pawn is on a starting position
				if (unit->isMoved() == NO) {
					if (board[unitrow + 1][unitcol]->getType() == FREE && board[unitrow + 2][unitcol]->getType() == FREE) {
						validMoves.push_back(to_string(unitrow + 2) += to_string(unitcol));
					}
				}
				// If enemy is on a killable FREE
				if (board[unitrow + 1][unitcol + 1]->getColor() == WHITE) {
					validMoves.push_back(to_string(unitrow + 1) += to_string(unitcol + 1));
				}
			}
			// If the pawn is on the right side column
			else if (unitcol == 7) {
				// Basic one or two moves in front, default situation
				if (board[unitrow + 1][unitcol]->getType() == FREE) {
					validMoves.push_back(to_string(unitrow + 1) += to_string(unitcol));
				}
				// If pawn has not moved before
				if (unit->isMoved() == NO) {
					if (board[unitrow + 1][unitcol]->getType() == FREE && board[unitrow + 2][unitcol]->getType() == FREE) {
						validMoves.push_back(to_string(unitrow + 2) += to_string(unitcol));
					}
				}
				// If enemy is on a killable FREE
				if (board[unitrow + 1][unitcol - 1]->getColor() == WHITE) {
					validMoves.push_back(to_string(unitrow + 1) += to_string(unitcol - 1));
				}
			}
			// Pawn is not on the side columns
			else {
				if (board[unitrow + 1][unitcol]->getType() == FREE) {
					validMoves.push_back(to_string(unitrow + 1) += to_string(unitcol));
				}
				if (unit->isMoved() == NO) {
					if (board[unitrow + 1][unitcol]->getType() == FREE && board[unitrow + 2][unitcol]->getType() == FREE) {
						validMoves.push_back(to_string(unitrow + 2) += to_string(unitcol));
					}
				}
				// If enemy is on a killable FREEs
				if (board[unitrow + 1][unitcol - 1]->getColor() == WHITE) {
					validMoves.push_back(to_string(unitrow + 1) += to_string(unitcol - 1));
				}
				if (board[unitrow + 1][unitcol + 1]->getColor() == WHITE) {
					validMoves.push_back(to_string(unitrow + 1) += to_string(unitcol + 1));
				}
			}
		}
		// OHESTALYÖNTI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
	// Rook, both colors
	else if (type == ROOK) {
		for (int i = 1; i <= 7; i++) {
			// Left
			if (unitcol - i >= 0) {
				if (board[unitrow][unitcol - i]->getType() == FREE) {
					validMoves.push_back(to_string(unitrow) += to_string(unitcol - i));
				}
				else {
					if (board[unitrow][unitcol - i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(unitrow) += to_string(unitcol - i));
						break;
					}
				}
			}
		}
		for (int i = 1; i <= 7; i++) {
			// Right
			if (unitcol + i <= 7) {
				if (board[unitrow][unitcol + i]->getType() == FREE) {
					validMoves.push_back(to_string(unitrow) += to_string(unitcol + i));
				}
				else {
					if (board[unitrow][unitcol + i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(unitrow) += to_string(unitcol + i));
						break;
					}
				}
			}
		}
		for (int i = 1; i <= 7; i++) {
			// Up
			if (unitrow - i >= 0) {
				if (board[unitrow - i][unitcol]->getType() == FREE) {
					validMoves.push_back(to_string(unitrow - i) += to_string(unitcol));
				}
				else {
					if (board[unitrow - i][unitcol]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(unitrow - i) += to_string(unitcol));
						break;
					}
				}
			}
		}
		for (int i = 1; i <= 7; i++) {
			// Down
			if (unitrow + i <= 7) {
				if (board[unitrow + i][unitcol]->getType() == FREE) {
					validMoves.push_back(to_string(unitrow + i) += to_string(unitcol));
				}
				else {
					if (board[unitrow + i][unitcol]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(unitrow + i) += to_string(unitcol));
						break;
					}
				}
			}
		}
	}
	// Bishop, both colors
	else if (type == BISHOP) {
		for (int i = 1; i <= 7; i++)
			// Left up diagonal					
			if (unitcol - i >= 0 && unitrow - i >= 0) {
				if (board[unitrow - i][unitcol - i]->getType() == FREE) {
					validMoves.push_back(to_string(unitrow - i) += to_string(unitcol - i));
				}
				else {
					if (board[unitrow - i][unitcol - i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(unitrow - i) += to_string(unitcol - i));
						break;
					}
				}
			}
		for (int i = 1; i <= 7; i++) {
			// Right up diagonal		
			if (unitcol + i <= 7 && unitrow - i >= 0) {
				if (board[unitrow - i][unitcol + i]->getType() == FREE) {
					validMoves.push_back(to_string(unitrow - i) += to_string(unitcol + i));
				}
				else {
					if (board[unitrow - i][unitcol + i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(unitrow - i) += to_string(unitcol + i));
						break;
					}
				}
			}
		}
		for (int i = 1; i <= 7; i++) {
			// Right down diagonal
			if (unitcol + i <= 7 && unitrow + i <= 7) {
				if (board[unitrow + i][unitcol + i]->getType() == FREE) {
					validMoves.push_back(to_string(unitrow + i) += to_string(unitcol + i));
				}
				else {
					if (board[unitrow + i][unitcol + i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(unitrow + i) += to_string(unitcol + i));
						break;
					}
				}
			}
		}
		for (int i = 1; i <= 7; i++) {
			// Left down diagonal
			if (unitcol - i >= 0 && unitrow + i <= 7) {
				if (board[unitrow + i][unitcol - i]->getType() == FREE) {
					validMoves.push_back(to_string(unitrow + i) += to_string(unitcol - i));
				}
				else {
					if (board[unitrow + i][unitcol - i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(unitrow + i) += to_string(unitcol - i));
						break;
					}
				}
			}
		}
	}
	// Horse, both colors
	else if (type == HORSE) {
		// Left
		if (unitcol - 2 >= 0 && unitrow + 1 <= 7) {
			if (board[unitrow + 1][unitcol - 2]->getColor() != color) {
				validMoves.push_back(to_string(unitrow + 1) += to_string(unitcol - 2));
			}
		}
		if (unitcol - 2 >= 0 && unitrow - 1 >= 0) {
			if (board[unitrow - 1][unitcol - 2]->getColor() != color) {
				validMoves.push_back(to_string(unitrow - 1) += to_string(unitcol - 2));
			}
		}
		// Up
		if (unitcol - 1 >= 0 && unitrow - 2 >= 0) {
			if (board[unitrow - 2][unitcol - 1]->getColor() != color) {
				validMoves.push_back(to_string(unitrow - 2) += to_string(unitcol - 1));
			}
		}
		if (unitcol + 1 <= 7 && unitrow - 2 >= 0) {
			if (board[unitrow - 2][unitcol + 1]->getColor() != color) {
				validMoves.push_back(to_string(unitrow - 2) += to_string(unitcol + 1));
			}
		}
		// Right
		if (unitcol + 2 <= 7 && unitrow - 1 >= 0) {
			if (board[unitrow - 1][unitcol + 2]->getColor() != color) {
				validMoves.push_back(to_string(unitrow - 1) += to_string(unitcol + 2));
			}
		}
		if (unitcol + 2 <= 7 && unitrow + 1 <= 7) {
			if (board[unitrow + 1][unitcol + 2]->getColor() != color) {
				validMoves.push_back(to_string(unitrow + 1) += to_string(unitcol + 2));
			}
		}
		// Down
		if (unitcol - 1 >= 0 && unitrow + 2 <= 7) {
			if (board[unitrow + 2][unitcol - 1]->getColor() != color) {
				validMoves.push_back(to_string(unitrow + 2) += to_string(unitcol - 1));
			}
		}
		if (unitcol + 1 <= 7 && unitrow + 2 <= 7) {
			if (board[unitrow + 2][unitcol + 1]->getColor() != color) {
				validMoves.push_back(to_string(unitrow + 2) += to_string(unitcol + 1));
			}
		}
	}
	// Queen, both colors
	else if (type == QUEEN) {
		// Works the same way as bishop + rook combined -> copy paste rook and bishop functionalities
		for (int i = 1; i <= 7; i++) {
			// Left
			if (unitcol - i >= 0) {
				if (board[unitrow][unitcol - i]->getType() == FREE) {
					validMoves.push_back(to_string(unitrow) += to_string(unitcol - i));
				}
				else {
					if (board[unitrow][unitcol - i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(unitrow) += to_string(unitcol - i));
						break;
					}
				}
			}
		}
		for (int i = 1; i <= 7; i++) {
			// Right
			if (unitcol + i <= 7) {
				if (board[unitrow][unitcol + i]->getType() == FREE) {
					validMoves.push_back(to_string(unitrow) += to_string(unitcol + i));
				}
				else {
					if (board[unitrow][unitcol + i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(unitrow) += to_string(unitcol + i));
						break;
					}
				}
			}
		}
		for (int i = 1; i <= 7; i++) {
			// Up
			if (unitrow - i >= 0) {
				if (board[unitrow - i][unitcol]->getType() == FREE) {
					validMoves.push_back(to_string(unitrow - i) += to_string(unitcol));
				}
				else {
					if (board[unitrow - i][unitcol]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(unitrow - i) += to_string(unitcol));
						break;
					}
				}
			}
		}
		for (int i = 1; i <= 7; i++) {
			// Down
			if (unitrow + i <= 7) {
				if (board[unitrow + i][unitcol]->getType() == FREE) {
					validMoves.push_back(to_string(unitrow + i) += to_string(unitcol));
				}
				else {
					if (board[unitrow + i][unitcol]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(unitrow + i) += to_string(unitcol));
						break;
					}
				}
			}
		}
		for (int i = 1; i <= 7; i++)
			// Left up diagonal					
			if (unitcol - i >= 0 && unitrow - i >= 0) {
				if (board[unitrow - i][unitcol - i]->getType() == FREE) {
					validMoves.push_back(to_string(unitrow - i) += to_string(unitcol - i));
				}
				else {
					if (board[unitrow - i][unitcol - i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(unitrow - i) += to_string(unitcol - i));
						break;
					}
				}
			}
		for (int i = 1; i <= 7; i++) {
			// Right up diagonal		
			if (unitcol + i <= 7 && unitrow - i >= 0) {
				if (board[unitrow - i][unitcol + i]->getType() == FREE) {
					validMoves.push_back(to_string(unitrow - i) += to_string(unitcol + i));
				}
				else {
					if (board[unitrow - i][unitcol + i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(unitrow - i) += to_string(unitcol + i));
						break;
					}
				}
			}
		}
		for (int i = 1; i <= 7; i++) {
			// Right down diagonal
			if (unitcol + i <= 7 && unitrow + i <= 7) {
				if (board[unitrow + i][unitcol + i]->getType() == FREE) {
					validMoves.push_back(to_string(unitrow + i) += to_string(unitcol + i));
				}
				else {
					if (board[unitrow + i][unitcol + i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(unitrow + i) += to_string(unitcol + i));
						break;
					}
				}
			}
		}
		for (int i = 1; i <= 7; i++) {
			// Left down diagonal
			if (unitcol - i >= 0 && unitrow + i <= 7) {
				if (board[unitrow + i][unitcol - i]->getType() == FREE) {
					validMoves.push_back(to_string(unitrow + i) += to_string(unitcol - i));
				}
				else {
					if (board[unitrow + i][unitcol - i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(unitrow + i) += to_string(unitcol - i));
						break;
					}
				}
			}
		}
	}
	// King, both colors
	// Moving a king requires to check if the position is free as well as checking if it is under threat
	else if (type == KING) {
		bool threat = false; // Flag for checking threat
		// Left up diagonal
		if (unitcol - 1 >= 0 && unitrow + 1 <= 7) {
			// If the position is free or contains an enemy
			if (board[unitrow + 1][unitcol - 1]->getType() == FREE || board[unitrow + 1][unitcol - 1]->getColor() != color) {
				// Check if it is under threat
				for (int i = 0; i < board[unitrow + 1][unitcol - 1]->getThreatVect().size(); i++) {
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = board[unitrow + 1][unitcol - 1]->getThreatVect()[i];
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if (threatColor != color && threatColor != 0) {
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if (!threat) {
					validMoves.push_back(to_string(unitrow + 1) += to_string(unitcol - 1));
				}
			}
		}
		// Left down diagonal
		else if (unitcol - 1 >= 0 && unitrow - 1 >= 0) {
			if (board[unitrow - 1][unitcol - 1]->getType() == FREE || board[unitrow - 1][unitcol - 1]->getColor() != color) {
				// Check if it is under threat
				for (int i = 0; i < board[unitrow - 1][unitcol - 1]->getThreatVect().size(); i++) {
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = board[unitrow - 1][unitcol - 1]->getThreatVect()[i];
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if (threatColor != color && threatColor != 0) {
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if (!threat) {
					validMoves.push_back(to_string(unitrow - 1) += to_string(unitcol - 1));
				}
			}
		}
		// Right up diagonal
		if (unitcol - 1 >= 0 && unitrow + 1 <= 7) {
			if (board[unitrow + 1][unitcol - 1]->getType() == FREE || board[unitrow + 1][unitcol - 1]->getColor() != color) {
				// Check if it is under threat
				for (int i = 0; i < board[unitrow + 1][unitcol - 1]->getThreatVect().size(); i++) {
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = board[unitrow + 1][unitcol - 1]->getThreatVect()[i];
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if (threatColor != color && threatColor != 0) {
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if (!threat) {
					validMoves.push_back(to_string(unitrow + 1) += to_string(unitcol - 1));
				}
			}
		}
		// Right down diagonal
		if (unitcol + 1 <= 7 && unitrow - 1 >= 0) {
			if (board[unitrow - 1][unitcol + 1]->getType() == FREE || board[unitrow - 1][unitcol + 1]->getColor() != color) {
				// Check if it is under threat
				for (int i = 0; i < board[unitrow - 1][unitcol + 1]->getThreatVect().size(); i++) {
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = board[unitrow - 1][unitcol + 1]->getThreatVect()[i];
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if (threatColor != color && threatColor != 0) {
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if (!threat) {
					validMoves.push_back(to_string(unitrow - 1) += to_string(unitcol + 1));
				}
			}
		}
		// Left
		if (unitcol - 1 >= 0) {
			if (board[unitrow][unitcol - 1]->getType() == FREE || board[unitrow][unitcol - 1]->getColor() != color) {
				// Check if it is under threat
				for (int i = 0; i < board[unitrow][unitcol - 1]->getThreatVect().size(); i++) {
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = board[unitrow][unitcol - 1]->getThreatVect()[i];
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if (threatColor != color && threatColor != 0) {
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if (!threat) {
					validMoves.push_back(to_string(unitrow) += to_string(unitcol - 1));
				}
			}
		}
		// Up
		if (unitrow + 1 <= 7) {
			if (board[unitrow + 1][unitcol]->getType() == FREE || board[unitrow + 1][unitcol]->getColor() != color) {
				// Check if it is under threat
				for (int i = 0; i < board[unitrow + 1][unitcol]->getThreatVect().size(); i++) {
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = board[unitrow + 1][unitcol]->getThreatVect()[i];
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if (threatColor != color && threatColor != 0) {
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if (!threat) {
					validMoves.push_back(to_string(unitrow + 1) += to_string(unitcol));
				}
			}
		}
		// Right
		if (unitcol + 1 <= 7) {
			if (board[unitrow][unitcol + 1]->getType() == FREE || board[unitrow][unitcol + 1]->getColor() != color) {
				// Check if it is under threat
				for (int i = 0; i < board[unitrow][unitcol + 1]->getThreatVect().size(); i++) {
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = board[unitrow][unitcol + 1]->getThreatVect()[i];
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if (threatColor != color && threatColor != 0) {
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if (!threat) {
					validMoves.push_back(to_string(unitrow) += to_string(unitcol + 1));
				}
			}
		}
		// Down
		if (unitrow - 1 >= 0) {
			if (board[unitrow - 1][unitcol]->getType() == FREE || board[unitrow - 1][unitcol]->getColor() != color) {
				// Check if it is under threat
				for (int i = 0; i < board[unitrow - 1][unitcol]->getThreatVect().size(); i++) {
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = board[unitrow - 1][unitcol]->getThreatVect()[i];
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if (threatColor != color && threatColor != 0) {
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if (!threat) {
					validMoves.push_back(to_string(unitrow - 1) += to_string(unitcol));
				}
			}
		}
	}
	return validMoves;
}

void chessBoard::printBoard(void)
{
	/* Function for printing the game board every turn */

	system("CLS");
	cout << "\n\t\t 1  2  3  4  5  6  7  8" << endl;
	cout << "\t\t ________________________" << endl;
	for (int i = 0; i <= 7; i++) {
		for (int j = 0; j <= 7; j++) {
			if (j == 0)
				cout << "\t\t|";
			if (board[i][j]->getType() == FREE)
				cout << "0  ";
			else
				cout << numToPiece(board[i][j]->getType()) << board[i][j]->getColor() << " ";
			if (j == 7)
				if (i == 0)
					cout << "|   " << "A" << endl;
				else if (i == 1)
					cout << "|   " << "B" << endl;
				else if (i == 2)
					cout << "|   " << "C" << endl;
				else if (i == 3)
					cout << "|   " << "D" << endl;
				else if (i == 4)
					cout << "|   " << "E" << endl;
				else if (i == 5)
					cout << "|   " << "F" << endl;
				else if (i == 6)
					cout << "|   " << "G" << endl;
				else if (i == 7)
					cout << "|   " << "H" << endl;
		}
	}
	cout << "\t\t ------------------------" << endl;
}

void chessBoard::checkForMate(player* p, player* e)
{
	// Create a temporary chessboard for simulating all possible moves for next turn
	chessBoard* tempBoard = new chessBoard;
	tempBoard = this;

	vector<string> enemyMoves = e->getThreatMoves();
	vector<string> moves = p->getMoves();

	for (unsigned i = 0; i < moves.size(); i++);

}

Piece* chessBoard::getBoard(void)
{
	return board[8][8];
}

string chessBoard::numToPiece(int num)
{
	string piece;
	if (num == 0) {
		piece = "-";
	}
	if (num == 1) {
		piece = "P";
	}
	if (num == 2) {
		piece = "R";
	}
	if (num == 3) {
		piece = "H";
	}
	if (num == 4) {
		piece = "B";
	}
	if (num == 5) {
		piece = "Q";
	}
	if (num == 6) {
		piece = "K";
	}
	return piece;
}

void chessBoard::checkCheck(player* p, player* e)
{
	/* REWRITE */
	vector<int> threat;

	for (int i = 0; i <= 7; i++)
		for (int j = 0; j <= 7; j++)
			if (board[i][j]->getType() == KING) {
				threat = board[i][j]->getThreatVect();
				if (board[i][j]->getColor() == p->getColor())
					for (int k = 0; k < threat.size(); k++) {
						if (threat[k] == e->getColor()) {
							p->setChecked(true, this, e);
							return;
						}
					}
			}
}



string chessBoard::returnRowC(int row)
{
	string rrow;

	if (row == 0)
		rrow = 'A';
	else if (row == 1)
		rrow = 'B';
	else if (row == 2)
		rrow = 'C';
	else if (row == 3)
		rrow = 'D';
	else if (row == 4)
		rrow = 'E';
	else if (row == 5)
		rrow = 'F';
	else if (row == 6)
		rrow = 'G';
	else if (row == 7)
		rrow = 'H';

	return rrow;
}

string chessBoard::returnColC(int col)
{
	string column;

	if (col == 0)
		column = '1';
	else if (col == 1)
		column = '2';
	else if (col == 2)
		column = '3';
	else if (col == 3)
		column = '4';
	else if (col == 4)
		column = '5';
	else if (col == 5)
		column = '6';
	else if (col == 6)
		column = '7';
	else if (col == 7)
		column = '8';

	return column;

}

void chessBoard::addAllPossibleMoves(player* p)
{
	int color = p->getColor();
	vector<string> moves;
	vector<string> pieceMoves;
	string pos;

	for (int i = 0; i <= 7; i++) {
		for (int j = 0; j <= 7; j++) {
			if (board[i][j]->getColor() == color) {
				Piece* piece = board[i][j];
				string col = returnColC(j);
				string row = returnRowC(i);
				pos = returnRowC(i) += returnColC(j);
				// Get piece's possible movements
				pieceMoves = validMoves(piece, pos);
				moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
			}
		}
	}
	// Add the moves to player's available move list
	p->addMoves(moves);
}
