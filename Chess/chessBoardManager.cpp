#include "chessBoard.h"
#include <vector>
#include "Piece.h"
#include "player.h"
#include "defines.h"


Piece* emptyTile = new Piece(EMPTYTILE, EMPTYTILE);

using namespace std;

chessBoardManager::chessBoardManager()
{
	// Set the whole board completely empty
	for (int i = 0; i <= 7; i++)
		for (int j = 0; j <= 7; j++) {
			board[i][j] = emptyTile;
		}
}

chessBoardManager::~chessBoardManager()
{
}

void chessBoardManager::initBoard(Player* p)
{
	// Initialize the board with players' pieces
	for (int i = 0; i < p->getPieces().size(); i++) {

		// White pawns
		if (p->getPieces()[i]->getColor() == WHITE && p->getPieces()[i]->getType() == PAWN) {
			for (int j = 0; j <= 7; j++) {
				if (board[6][j]->getType() == EMPTYTILE) {
					board[6][j] = p->getPieces()[i];
					break;
				}
			}
		}
		// White rooks
		if (p->getPieces()[i]->getColor() == WHITE && p->getPieces()[i]->getType() == ROOK) {
			if (board[7][0]->getType() == EMPTYTILE)
				board[7][0] = p->getPieces()[i];
			else if (board[7][7]->getType() == EMPTYTILE)
				board[7][7] = p->getPieces()[i];
			else
				cout << "ERROR IN W ROOK INIT" << endl;
		}
		// White horses
		else if (p->getPieces()[i]->getColor() == WHITE && p->getPieces()[i]->getType() == HORSE) {
			if (board[7][1]->getType() == EMPTYTILE)
				board[7][1] = p->getPieces()[i];
			else if (board[7][6]->getType() == EMPTYTILE)
				board[7][6] = p->getPieces()[i];
			else
				cout << "ERROR IN W HORSE INIT" << endl;
		}
		// White bishops
		else if (p->getPieces()[i]->getColor() == WHITE && p->getPieces()[i]->getType() == BISHOP) {
			if (board[7][2]->getType() == EMPTYTILE)
				board[7][2] = p->getPieces()[i];
			else if (board[7][5]->getType() == EMPTYTILE)
				board[7][5] = p->getPieces()[i];
			else
				cout << "ERROR IN W BISHOP INIT" << endl;
		}
		// White queen
		else if (p->getPieces()[i]->getColor() == WHITE && p->getPieces()[i]->getType() == QUEEN) {
			// THIS SHOULD AWLAYS BE FREE!!	
			if (board[7][3]->getType() == EMPTYTILE)
				board[7][3] = p->getPieces()[i];
			else
				cout << "ERROR IN W QUEEN INIT" << endl;
		}
		// White king 
		else if (p->getPieces()[i]->getColor() == WHITE && p->getPieces()[i]->getType() == KING) {
			// THIS SHOULD AWLAYS BE FREE!!	
			if (board[7][4]->getType() == EMPTYTILE)
				board[7][4] = p->getPieces()[i];
			else
				cout << "ERROR IN W KING INIT" << endl;
		}
		// Black pawns
		if (p->getPieces()[i]->getColor() == BLACK && p->getPieces()[i]->getType() == PAWN) {
			for (int j = 0; j <= 7; j++) {
				// If an empty square is available in the last two rows, get square number in string and s				end new pawn piece in these coordinates //
				if (board[1][j]->getType() == EMPTYTILE) {
					board[1][j] = p->getPieces()[i];
					break;
				}
			}
		}
		// Black rooks
		else if (p->getPieces()[i]->getColor() == BLACK && p->getPieces()[i]->getType() == ROOK) {
			if (board[0][0]->getType() == EMPTYTILE)
				board[0][0] = p->getPieces()[i];
			else if (board[0][7]->getType() == EMPTYTILE)
				board[0][7] = p->getPieces()[i];
			else
				cout << "ERROR IN B ROOK INIT" << endl;
		}
		// Black horses
		else if (p->getPieces()[i]->getColor() == BLACK && p->getPieces()[i]->getType() == HORSE) {
			if (board[0][1]->getType() == EMPTYTILE)
				board[0][1] = p->getPieces()[i];
			else if (board[0][6]->getType() == EMPTYTILE)
				board[0][6] = p->getPieces()[i];
			else
				cout << "ERROR IN B HORSE INIT" << endl;
		}
		// Black bishops
		else if (p->getPieces()[i]->getColor() == BLACK && p->getPieces()[i]->getType() == BISHOP) {
			if (board[0][2]->getType() == EMPTYTILE)
				board[0][2] = p->getPieces()[i];
			else if (board[0][5]->getType() == EMPTYTILE)
				board[0][5] = p->getPieces()[i];
			else
				cout << "ERROR IN B BISHOP INIT" << endl;
		}
		// Black queen
		else if (p->getPieces()[i]->getColor() == BLACK && p->getPieces()[i]->getType() == QUEEN) {
			// THIS SHOULD AWLAYS BE FREE!!	
			if (board[0][3]->getType() == EMPTYTILE)
				board[0][3] = p->getPieces()[i];
			else
				cout << "ERROR IN B QUEEN INIT" << endl;
		}
		// Black king
		else if (p->getPieces()[i]->getColor() == BLACK && p->getPieces()[i]->getType() == KING) {
			// THIS SHOULD AWLAYS BE FREE!!	
			if (board[0][4]->getType() == EMPTYTILE)
				board[0][4] = p->getPieces()[i];
			else
				cout << "ERROR IN B KING INIT" << endl;
		}
	}
}

int chessBoardManager::returnCol(string col)

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

int chessBoardManager::returnRow(string row)

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

Piece* chessBoardManager::getPiece(int row, int column)
{
	return board[row][column];
}

void chessBoardManager::setPiece(Piece* piece, int startRow, int startColumn, int endRow, int endColumn)
{
	//board[endRow][endColumn] = NULL;
	board[endRow][endColumn] = piece;
	board[startRow][startColumn] = emptyTile;
}

void chessBoardManager::recalculatePieceThreats(void)
{
	/* This function always runs the board empty of threat
		and then recalculates every piece's threat */
	int type;
	int color;
	int pColor;
	Piece* piece;

	for (int i = 0; i <= 7; i++) {
		int row = i;

		for (int j = 0; j <= 7; j++) {
			int col = j;
			piece = board[i][j];

			piece->resetThreatVector();
			color = piece->getColor();
			type = piece->getType();

			if (type == PAWN) {
				if (color == WHITE) {
					// If the pawn is on the left side column
					if (col == 0) {
						if (row - 1 >= 0)
							// If enemy is on a killable tile
							if (board[row - 1][col + 1]->getColor() != color) {
								board[row - 1][col + 1]->addThreat(piece);
							}
					}
					// If the pawn is on the right side column
					else if (col == 7) {
						if (row - 1 >= 0)
							if (board[row - 1][col - 1]->getColor() != color) {
								board[row - 1][col - 1]->addThreat(piece);
							}
					}
					// Pawn is not on the side columns
					else {
						if (row - 1 >= 0) {
							// Add threat to tiles that are under threat (row +-1 depending on color; column +-1)
							if (board[row - 1][col - 1]->getColor() != color) {
								board[row - 1][col - 1]->addThreat(piece);
							}
							if (board[row - 1][col + 1]->getColor() != color) {
								board[row - 1][col + 1]->addThreat(piece);
							}
						}
					}
				}
				else if (color == BLACK) {
					// If the pawn is on the	 left side column
					if (col == 0) {
						if (row + 1 <= 7)
							// If enemy is on a killable tile	
							if (board[row + 1][col + 1]->getColor() != color) {
								board[row + 1][col + 1]->addThreat(piece);
							}
					}
					// If the pawn is on the right side column
					else if (col == 7) {
						if (row + 1 <= 7)
							if (board[row + 1][col - 1]->getColor() != color) {
								board[row + 1][col - 1]->addThreat(piece);
							}
					}
					// Pawn is not on the side columns
					else {
						if (row + 1 <= 7) {
							// If enemy is on a killable	 tile
							if (board[row + 1][col - 1]->getColor() != color) {
								board[row + 1][col - 1]->addThreat(piece);
							}
							if (board[row + 1][col + 1]->getColor() != color) {
								board[row + 1][col - 1]->addThreat(piece);
							}
						}
					}
				}
			}
			// Rook
			else if (type == ROOK) {
				for (int k = 1; k <= 7; k++) {
					// Left							
					if (col - k >= 0) {
						if (board[row][col - k]->getType() == EMPTYTILE) {
							board[row][col - k]->addThreat(piece);
						}
						else {
							board[row][col - k]->addThreat(piece);
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Right							
					if (col + k <= 7) {
						if (board[row][col + k]->getType() == EMPTYTILE) {
							board[row][col + k]->addThreat(piece);
						}
						else {
							board[row][col + k]->addThreat(piece);
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Up							
					if (row - k >= 0) {
						if (board[row - k][col]->getType() == EMPTYTILE) {
							board[row - k][col]->addThreat(piece);
						}
						else 
						{
							board[row - k][col]->addThreat(piece);
							break;
						}

					}
				}

				for (int k = 1; k <= 7; k++) {
					// Down	

					if (row + k <= 7) {
						if (board[row + k][col]->getType() == EMPTYTILE) {
							board[row + k][col]->addThreat(piece);
						}
						else 
						{
							board[row + k][col]->addThreat(piece);
							break;
						}
					}
				}
			}
			// Bishop, both colors
			else if (type == BISHOP) {
				for (int k = 1; k <= 7; k++) {
					// Left up diagonal						
					if (col - k >= 0 && row - k >= 0) {
						if (board[row - k][col - k]->getType() == EMPTYTILE) {
							board[row - k][col - k]->addThreat(piece);
						}
						else {

							board[row - k][col - k]->addThreat(piece);
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Right up diagonal			
					if (col + k <= 7 && row - k >= 0) {
						if (board[row - k][col + k]->getType() == EMPTYTILE) {
							board[row - k][col + k]->addThreat(piece);
						}
						else {
							cout << "debug row: " << row-k << " col: " << col+k << endl;
							board[row - k][col + k]->addThreat(piece);
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					//	Right down di	agonal
					if (col + k <= 7 && row + k <= 7) {
						if (board[row + k][col + k]->getType() == EMPTYTILE) {
							board[row + k][col + k]->addThreat(piece);
						}
						else {
							board[row + k][col + k]->addThreat(piece);
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					//	Left down diagonal
					if (col - k >= 0 && row + k <= 7) {
						if (board[row + k][col - k]->getType() == EMPTYTILE) {
							board[row + k][col - k]->addThreat(piece);
						}
						else {
							board[row + k][col - k]->addThreat(piece);
							break;
						}
					}
				}
			}
			// Horse, both colors
			else if (type == HORSE) {
				// Left	
				if (col - 2 >= 0 && row + 1 <= 7)
					board[row + 1][col - 2]->addThreat(piece);
				if (col - 2 >= 0 && row - 1 >= 0)
					board[row - 1][col - 2]->addThreat(piece);
				// Up		
				if (col - 1 >= 0 && row - 2 >= 0)
					board[row - 2][col - 1]->addThreat(piece);
				if (col + 1 <= 7 && row - 2 >= 0)
					board[row - 2][col + 1]->addThreat(piece);
				// Right	
				if (col + 2 <= 7 && row - 1 >= 0)
					board[row - 1][col + 2]->addThreat(piece);
				if (col + 2 <= 7 && row + 1 <= 7)
					board[row + 1][col + 2]->addThreat(piece);
				// Down		
				if (col - 1 >= 0 && row + 2 <= 7)
					board[row + 2][col - 1]->addThreat(piece);
				if (col + 1 <= 7 && row + 2 <= 7)
					board[row + 2][col + 1]->addThreat(piece);
			}
			// Queen, both colors
			else if (type == QUEEN) {
				for (int k = 1; k <= 7; k++) {
					// Left
					if (col - k >= 0) {
						if (board[row][col - k]->getType() == EMPTYTILE) {
							board[row][col - k]->addThreat(piece);
						}
						else {
							board[row][col - k]->addThreat(piece);
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Right							
					if (col + k <= 7) {
						if (board[row][col + k]->getType() == EMPTYTILE) {
							board[row][col + k]->addThreat(piece);
						}
						else {
							board[row][col + k]->addThreat(piece);
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Up							
					if (row - k >= 0) {
						if (board[row - k][col]->getType() == EMPTYTILE) {
							board[row - k][col]->addThreat(piece);
						}
						else {
							board[row - k][col]->addThreat(piece);
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Down	
					if (row + k <= 7) {
						if (board[row + k][col]->getType() == EMPTYTILE) {
							board[row + k][col]->addThreat(piece);
						}
						else {
							board[row + k][col]->addThreat(piece);
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Left up diagonal						
					if (col - k >= 0 && row - k >= 0) {
						if (board[row - k][col - k]->getType() == EMPTYTILE) {
							board[row - k][col - k]->addThreat(piece);
						}
						else {
							board[row - k][col - k]->addThreat(piece);
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Right up diagonal			
					if (col + k <= 7 && row - k >= 0) {
						if (board[row - k][col + k]->getType() == EMPTYTILE) {
							board[row - k][col + k]->addThreat(piece);
						}
						else {
							board[row - k][col + k]->addThreat(piece);
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Right d	own d	iagonal
					if (col + k <= 7 && row + k <= 7) {
						if (board[row + k][col + k]->getType() == EMPTYTILE) {
							board[row + k][col + k]->addThreat(piece);
						}
						else {
							board[row + k][col + k]->addThreat(piece);
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Left do	wn di	agonal
					if (col - k >= 0 && row + k <= 7) {
						if (board[row + k][col - k]->getType() == EMPTYTILE) {
							board[row + k][col - k]->addThreat(piece);
						}
						else {
							board[row + k][col - k]->addThreat(piece);
							break;
						}
					}
				}
			}
			// King,	both colors

			// TODO

			//else if (type == KING) {
				//if (col - 1 >= 0)
					//if (board[row][col - 1])
						//int i = 0;
			//}
		}
	}
}



vector<string> chessBoardManager::calculateAvailableMoves(Piece* piece, string pos)
{
	/*	This function returns a vector containing every possible
		move for a chosen piece */

	int row = returnRow(pos);
	int col = returnCol(pos);
	vector<string> validMoves;
	int type = piece->getType();
	int color = piece->getColor();

	// Pawn, white
	if (type == PAWN) {
		if (color == WHITE) {
			// If the pawn is on the left side column
			if (col == 0) {
				// Basic one or two moves in front, default situation
				if (row - 1 >= 0) {
					if (board[row - 1][col]->getType() == EMPTYTILE) {
						validMoves.push_back(to_string(row - 1) += to_string(col));
					}
					// If pawn is on a starting position
					if (piece->isMoved() == NO) {
						if (board[row - 1][col]->getType() == EMPTYTILE && board[row - 2][col]->getType() == EMPTYTILE) {
							validMoves.push_back(to_string(row - 2) += to_string(col));
						}
					}
					// If enemy is on a killable tile
					if (board[row - 1][col + 1]->getColor() == BLACK) {
						validMoves.push_back(to_string(row - 1) += to_string(col + 1));
					}
				}
				else
					cout << "Cannot move!" << endl;
			}
			// If the pawn is on the right side column
			else if (col == 7) {
				if (row - 1 >= 0) {
					// Basic one or two moves in front, default situation
					if (board[row - 1][col]->getType() == EMPTYTILE) {
						validMoves.push_back(to_string(row - 1) += to_string(col));
					}
					// If pawn has not moved before
					if (piece->isMoved() == NO) {
						if (board[row - 1][col]->getType() == EMPTYTILE && board[row - 2][col]->getType() == EMPTYTILE) {
							validMoves.push_back(to_string(row - 2) += to_string(col));
						}
					}
					// If enemy is on a killable FREE
					if (board[row - 1][col - 1]->getColor() == BLACK) {
						validMoves.push_back(to_string(row - 1) += to_string(col - 1));
					}
				}
				else
					cout << "Cannot move!" << endl;
			}
			// Pawn is not on the side columns
			else {
				if (row - 1 >= 0) {
					if (board[row - 1][col]->getType() == EMPTYTILE) {
						validMoves.push_back(to_string(row - 1) += to_string(col));
					}
					if (piece->isMoved() == NO) {
						if (board[row - 1][col]->getType() == EMPTYTILE && board[row - 2][col]->getType() == EMPTYTILE) {
							validMoves.push_back(to_string(row - 2) += to_string(col));
						}
					}
					// If enemy is on a killable tile
					if (board[row - 1][col - 1]->getColor() == BLACK) {
						validMoves.push_back(to_string(row - 1) += to_string(col - 1));
					}
					if (board[row - 1][col + 1]->getColor() == BLACK) {
						validMoves.push_back(to_string(row - 1) += to_string(col + 1));
					}
				}
				else
					cout << "Cannot move!" << endl;
			}
		}
		// Black case, pawn
		else if (color == BLACK) {
			// If the pawn is on the left side column
			if (col == 0) {
				// Basic one or two moves in front, default situation
				if (board[row + 1][col]->getType() == EMPTYTILE) {
					validMoves.push_back(to_string(row + 1) += to_string(col));
				}
				// If pawn is on a starting position
				if (piece->isMoved() == NO) {
					if (board[row + 1][col]->getType() == EMPTYTILE && board[row + 2][col]->getType() == EMPTYTILE) {
						validMoves.push_back(to_string(row + 2) += to_string(col));
					}
				}
				// If enemy is on a killable FREE
				if (board[row + 1][col + 1]->getColor() == WHITE) {
					validMoves.push_back(to_string(row + 1) += to_string(col + 1));
				}
			}
			// If the pawn is on the right side column
			else if (col == 7) {
				// Basic one or two moves in front, default situation
				if (board[row + 1][col]->getType() == EMPTYTILE) {
					validMoves.push_back(to_string(row + 1) += to_string(col));
				}
				// If pawn has not moved before
				if (piece->isMoved() == NO) {
					if (board[row + 1][col]->getType() == EMPTYTILE && board[row + 2][col]->getType() == EMPTYTILE) {
						validMoves.push_back(to_string(row + 2) += to_string(col));
					}
				}
				// If enemy is on a killable FREE
				if (board[row + 1][col - 1]->getColor() == WHITE) {
					validMoves.push_back(to_string(row + 1) += to_string(col - 1));
				}
			}
			// Pawn is not on the side columns
			else {
				if (board[row + 1][col]->getType() == EMPTYTILE) {
					validMoves.push_back(to_string(row + 1) += to_string(col));
				}
				if (piece->isMoved() == NO) {
					if (board[row + 1][col]->getType() == EMPTYTILE && board[row + 2][col]->getType() == EMPTYTILE) {
						validMoves.push_back(to_string(row + 2) += to_string(col));
					}
				}
				// If enemy is on a killable FREEs
				if (board[row + 1][col - 1]->getColor() == WHITE) {
					validMoves.push_back(to_string(row + 1) += to_string(col - 1));
				}
				if (board[row + 1][col + 1]->getColor() == WHITE) {
					validMoves.push_back(to_string(row + 1) += to_string(col + 1));
				}
			}
		}


		// OHESTALYÖNTI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


	}
	// Rook, both colors
	else if (type == ROOK) {
		for (int i = 1; i <= 7; i++) {
			// Left
			if (col - i >= 0) {
				if (board[row][col - i]->getType() == EMPTYTILE) {
					validMoves.push_back(to_string(row) += to_string(col - i));
				}
				else {
					if (board[row][col - i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(row) += to_string(col - i));
						break;
					}
				}
			}
		}
		for (int i = 1; i <= 7; i++) {
			// Right
			if (col + i <= 7) {
				if (board[row][col + i]->getType() == EMPTYTILE) {
					validMoves.push_back(to_string(row) += to_string(col + i));
				}
				else {
					if (board[row][col + i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(row) += to_string(col + i));
						break;
					}
				}
			}
		}
		for (int i = 1; i <= 7; i++) {
			// Up
			if (row - i >= 0) {
				if (board[row - i][col]->getType() == EMPTYTILE) {
					validMoves.push_back(to_string(row - i) += to_string(col));
				}
				else {
					if (board[row - i][col]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(row - i) += to_string(col));
						break;
					}
				}
			}
		}
		for (int i = 1; i <= 7; i++) {
			// Down
			if (row + i <= 7) {
				if (board[row + i][col]->getType() == EMPTYTILE) {
					validMoves.push_back(to_string(row + i) += to_string(col));
				}
				else {
					if (board[row + i][col]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(row + i) += to_string(col));
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
			if (col - i >= 0 && row - i >= 0) {
				if (board[row - i][col - i]->getType() == EMPTYTILE) {
					validMoves.push_back(to_string(row - i) += to_string(col - i));
				}
				else {
					if (board[row - i][col - i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(row - i) += to_string(col - i));
						break;
					}
				}
			}
		for (int i = 1; i <= 7; i++) {
			// Right up diagonal		
			if (col + i <= 7 && row - i >= 0) {
				if (board[row - i][col + i]->getType() == EMPTYTILE) {
					validMoves.push_back(to_string(row - i) += to_string(col + i));
				}
				else {
					if (board[row - i][col + i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(row - i) += to_string(col + i));
						break;
					}
				}
			}
		}
		for (int i = 1; i <= 7; i++) {
			// Right down diagonal
			if (col + i <= 7 && row + i <= 7) {
				if (board[row + i][col + i]->getType() == EMPTYTILE) {
					validMoves.push_back(to_string(row + i) += to_string(col + i));
				}
				else {
					if (board[row + i][col + i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(row + i) += to_string(col + i));
						break;
					}
				}
			}
		}
		for (int i = 1; i <= 7; i++) {
			// Left down diagonal
			if (col - i >= 0 && row + i <= 7) {
				if (board[row + i][col - i]->getType() == EMPTYTILE) {
					validMoves.push_back(to_string(row + i) += to_string(col - i));
				}
				else {
					if (board[row + i][col - i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(row + i) += to_string(col - i));
						break;
					}
				}
			}
		}
	}
	// Horse, both colors
	else if (type == HORSE) {
		// Left
		if (col - 2 >= 0 && row + 1 <= 7) {
			if (board[row + 1][col - 2]->getColor() != color) {
				validMoves.push_back(to_string(row + 1) += to_string(col - 2));
			}
		}
		if (col - 2 >= 0 && row - 1 >= 0) {
			if (board[row - 1][col - 2]->getColor() != color) {
				validMoves.push_back(to_string(row - 1) += to_string(col - 2));
			}
		}
		// Up
		if (col - 1 >= 0 && row - 2 >= 0) {
			if (board[row - 2][col - 1]->getColor() != color) {
				validMoves.push_back(to_string(row - 2) += to_string(col - 1));
			}
		}
		if (col + 1 <= 7 && row - 2 >= 0) {
			if (board[row - 2][col + 1]->getColor() != color) {
				validMoves.push_back(to_string(row - 2) += to_string(col + 1));
			}
		}
		// Right
		if (col + 2 <= 7 && row - 1 >= 0) {
			if (board[row - 1][col + 2]->getColor() != color) {
				validMoves.push_back(to_string(row - 1) += to_string(col + 2));
			}
		}
		if (col + 2 <= 7 && row + 1 <= 7) {
			if (board[row + 1][col + 2]->getColor() != color) {
				validMoves.push_back(to_string(row + 1) += to_string(col + 2));
			}
		}
		// Down
		if (col - 1 >= 0 && row + 2 <= 7) {
			if (board[row + 2][col - 1]->getColor() != color) {
				validMoves.push_back(to_string(row + 2) += to_string(col - 1));
			}
		}
		if (col + 1 <= 7 && row + 2 <= 7) {
			if (board[row + 2][col + 1]->getColor() != color) {
				validMoves.push_back(to_string(row + 2) += to_string(col + 1));
			}
		}
	}
	// Queen, both colors
	else if (type == QUEEN) {
		// Works the same way as bishop + rook combined -> copy paste rook and bishop functionalities
		for (int i = 1; i <= 7; i++) {
			// Left
			if (col - i >= 0) {
				if (board[row][col - i]->getType() == EMPTYTILE) {
					validMoves.push_back(to_string(row) += to_string(col - i));
				}
				else {
					if (board[row][col - i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(row) += to_string(col - i));
						break;
					}
				}
			}
		}
		for (int i = 1; i <= 7; i++) {
			// Right
			if (col + i <= 7) {
				if (board[row][col + i]->getType() == EMPTYTILE) {
					validMoves.push_back(to_string(row) += to_string(col + i));
				}
				else {
					if (board[row][col + i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(row) += to_string(col + i));
						break;
					}
				}
			}
		}
		for (int i = 1; i <= 7; i++) {
			// Up
			if (row - i >= 0) {
				if (board[row - i][col]->getType() == EMPTYTILE) {
					validMoves.push_back(to_string(row - i) += to_string(col));
				}
				else {
					if (board[row - i][col]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(row - i) += to_string(col));
						break;
					}
				}
			}
		}
		for (int i = 1; i <= 7; i++) {
			// Down
			if (row + i <= 7) {
				if (board[row + i][col]->getType() == EMPTYTILE) {
					validMoves.push_back(to_string(row + i) += to_string(col));
				}
				else {
					if (board[row + i][col]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(row + i) += to_string(col));
						break;
					}
				}
			}
		}
		for (int i = 1; i <= 7; i++)
			// Left up diagonal					
			if (col - i >= 0 && row - i >= 0) {
				if (board[row - i][col - i]->getType() == EMPTYTILE) {
					validMoves.push_back(to_string(row - i) += to_string(col - i));
				}
				else {
					if (board[row - i][col - i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(row - i) += to_string(col - i));
						break;
					}
				}
			}
		for (int i = 1; i <= 7; i++) {
			// Right up diagonal		
			if (col + i <= 7 && row - i >= 0) {
				if (board[row - i][col + i]->getType() == EMPTYTILE) {
					validMoves.push_back(to_string(row - i) += to_string(col + i));
				}
				else {
					if (board[row - i][col + i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(row - i) += to_string(col + i));
						break;
					}
				}
			}
		}
		for (int i = 1; i <= 7; i++) {
			// Right down diagonal
			if (col + i <= 7 && row + i <= 7) {
				if (board[row + i][col + i]->getType() == EMPTYTILE) {
					validMoves.push_back(to_string(row + i) += to_string(col + i));
				}
				else {
					if (board[row + i][col + i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(row + i) += to_string(col + i));
						break;
					}
				}
			}
		}
		for (int i = 1; i <= 7; i++) {
			// Left down diagonal
			if (col - i >= 0 && row + i <= 7) {
				if (board[row + i][col - i]->getType() == EMPTYTILE) {
					validMoves.push_back(to_string(row + i) += to_string(col - i));
				}
				else {
					if (board[row + i][col - i]->getColor() == color) {
						break;
					}
					else {
						validMoves.push_back(to_string(row + i) += to_string(col - i));
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
		if (col - 1 >= 0 && row + 1 <= 7) {
			// If the position is free or contains an enemy
			if (board[row + 1][col - 1]->getType() == EMPTYTILE || board[row + 1][col - 1]->getColor() != color) {
				// Check if it is also under threat
				for (int i = 0; i < board[row + 1][col - 1]->getThreatVector().size(); i++) {
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = board[row + 1][col - 1]->getThreatVector()[i]->getColor();
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if (threatColor != color && threatColor != 0) {
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if (!threat) {
					validMoves.push_back(to_string(row + 1) += to_string(col - 1));
				}
			}
		}
		// Left down diagonal
		else if (col - 1 >= 0 && row - 1 >= 0) {
			if (board[row - 1][col - 1]->getType() == EMPTYTILE || board[row - 1][col - 1]->getColor() != color) {
				// Check if it is under threat
				for (int i = 0; i < board[row - 1][col - 1]->getThreatVector().size(); i++) {
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = board[row - 1][col - 1]->getThreatVector()[i]->getColor();
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if (threatColor != color && threatColor != 0) {
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if (!threat) {
					validMoves.push_back(to_string(row - 1) += to_string(col - 1));
				}
			}
		}
		// Right up diagonal
		if (col - 1 >= 0 && row + 1 <= 7) {
			if (board[row + 1][col - 1]->getType() == EMPTYTILE || board[row + 1][col - 1]->getColor() != color) {
				// Check if it is under threat
				for (int i = 0; i < board[row + 1][col - 1]->getThreatVector().size(); i++) {
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = board[row + 1][col - 1]->getThreatVector()[i]->getColor();
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if (threatColor != color && threatColor != 0) {
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if (!threat) {
					validMoves.push_back(to_string(row + 1) += to_string(col - 1));
				}
			}
		}
		// Right down diagonal
		if (col + 1 <= 7 && row - 1 >= 0) {
			if (board[row - 1][col + 1]->getType() == EMPTYTILE || board[row - 1][col + 1]->getColor() != color) {
				// Check if it is under threat
				for (int i = 0; i < board[row - 1][col + 1]->getThreatVector().size(); i++) {
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = board[row - 1][col + 1]->getThreatVector()[i]->getColor();
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if (threatColor != color && threatColor != 0) {
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if (!threat) {
					validMoves.push_back(to_string(row - 1) += to_string(col + 1));
				}
			}
		}
		// Left
		if (col - 1 >= 0) {
			if (board[row][col - 1]->getType() == EMPTYTILE || board[row][col - 1]->getColor() != color) {
				// Check if it is under threat
				for (int i = 0; i < board[row][col - 1]->getThreatVector().size(); i++) {
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = board[row][col - 1]->getThreatVector()[i]->getColor();
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if (threatColor != color && threatColor != 0) {
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if (!threat) {
					validMoves.push_back(to_string(row) += to_string(col - 1));
				}
			}
		}
		// Up
		if (row + 1 <= 7) {
			if (board[row + 1][col]->getType() == EMPTYTILE || board[row + 1][col]->getColor() != color) {
				// Check if it is under threat
				for (int i = 0; i < board[row + 1][col]->getThreatVector().size(); i++) {
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = board[row + 1][col]->getThreatVector()[i]->getColor();
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if (threatColor != color && threatColor != 0) {
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if (!threat) {
					validMoves.push_back(to_string(row + 1) += to_string(col));
				}
			}
		}
		// Right
		if (col + 1 <= 7) {
			if (board[row][col + 1]->getType() == EMPTYTILE || board[row][col + 1]->getColor() != color) {
				// Check if it is under threat
				for (int i = 0; i < board[row][col + 1]->getThreatVector().size(); i++) {
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = board[row][col + 1]->getThreatVector()[i]->getColor();
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if (threatColor != color && threatColor != 0) {
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if (!threat) {
					validMoves.push_back(to_string(row) += to_string(col + 1));
				}
			}
		}
		// Down
		if (row - 1 >= 0) {
			if (board[row - 1][col]->getType() == EMPTYTILE || board[row - 1][col]->getColor() != color) {
				// Check if it is under threat
				for (int i = 0; i < board[row - 1][col]->getThreatVector().size(); i++) {
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = board[row - 1][col]->getThreatVector()[i]->getColor();
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if (threatColor != color && threatColor != 0) {
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if (!threat) {
					validMoves.push_back(to_string(row - 1) += to_string(col));
				}
			}
		}
	}
	return validMoves;
}

void chessBoardManager::addPlayer(Player* p) {
	players.push_back(p);
}

vector<Player*> chessBoardManager::getPlayers() {
	return players;
}

void chessBoardManager::printBoard(void)
{
	/* Function for printing the game board every turn */

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	system("CLS");
	
	cout << "\n\t\t 1  2  3  4  5  6  7  8" << endl;
	cout << "\t\t ________________________" << endl;
	for (int i = 0; i <= 7; i++) {
		for (int j = 0; j <= 7; j++) {
			Piece* piece = board[i][j];

			if (j == 0)
				cout << "\t\t|";
			if (piece->getType() == EMPTYTILE)
				cout << "0  ";
			else 
			{
				switch(piece->getColor()) 
				{
					case WHITE:
						SetConsoleTextAttribute(hConsole, 10);
						break;
					case BLACK:
						SetConsoleTextAttribute(hConsole, 12);
						break;
					default:
						SetConsoleTextAttribute(hConsole, 15);
				}
				cout << numToPiece(piece->getType()) << piece->getColor() << " ";
			}
			SetConsoleTextAttribute(hConsole, 15);
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

void chessBoardManager::checkForMate(Player* p)
{
	// Create a temporary chessboard for simulating all possible moves for next turn
	Piece* king;
	auto tempBoard = this->board;

	vector<Piece*> pieces = p->getPieces();
	for(int i = 0; i < pieces.size(); i++) {
		if(pieces[i]->getType() == KING) {
			king = pieces[i];
		}
	}

	Piece* piece;

	/* automatically move all of the pieces to their corrersponding available move*/
	for(int i = 0; i < pieces.size(); i++) {
		piece = pieces[i];

	}




	/* if king is STILL threatened -> mate */




}

Piece* chessBoardManager::getBoard(void)
{
	return board[8][8];
}

string chessBoardManager::numToPiece(int num)
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

void chessBoardManager::updatePlayerCheckedStatus(Player* player) {
	/* REWRITE */

	int kingThreatsCount = 0;
	Piece* friendlyKing = NULL;
	Player* opponent = player->getOpponent();

	// Find friendly king piece from the board
	for(int i = 0; i <= 7; i++) {
		for(int j = 0; j <= 7; j++) {
			if(board[i][j]->getType() == KING && board[i][j]->getColor() == player->getColor()) {
				friendlyKing = board[i][j];
				break;
			}
		}
	}

	if(friendlyKing)
		kingThreatsCount = friendlyKing->getThreatVector().size();

	player->setChecked(kingThreatsCount > 0);
}




string chessBoardManager::returnRowC(int row)
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

string chessBoardManager::returnColC(int col)
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

void chessBoardManager::calculateAllPossibleMoves(Player* p)
{
	int color = p->getColor();
	vector<string> moves;
	vector<string> availableMoves;
	string pos;

	for (int i = 0; i <= 7; i++) {
		for (int j = 0; j <= 7; j++) {
			if (board[i][j]->getColor() == color) {
				Piece* piece = board[i][j];
				string col = returnColC(j);
				string row = returnRowC(i);
				pos = returnRowC(i) += returnColC(j);
				// Get piece's possible movements
				availableMoves = calculateAvailableMoves(piece, pos);
				moves.insert(moves.end(), availableMoves.begin(), availableMoves.end());
				piece->setAvailableMoves(moves);
			}
		}
	}
}
