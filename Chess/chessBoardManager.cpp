#include "chessBoard.h"
#include <vector>
#include "Piece.h"
#include "player.h"
#include "defines.h"
#include <thread>

using namespace std;


// Between or equal 
bool boeq(int compare, int lhs, int rhs) {
	return compare >= lhs && compare <= rhs;
}


chessBoardManager::chessBoardManager() {
	_board = new Board[8]; // board consists of 8 rows

	for(int i = 0; i <= 7; i++)
		_board[i] = new Row[8];

	// Set the whole board completely empty
	for(int row = 0; row <= 7; row++)
	{
		for(int col = 0; col <= 7; col++)
		{
			_board[row][col] = new Piece(EMPTYTILE, EMPTYTILE, row, col);
		}
	}
}


chessBoardManager::~chessBoardManager() {
}

void chessBoardManager::initBoard(Player* p) {
	// Initialize the board with players' pieces
	vector<Piece*> playerPieces = p->getPieces();

	int color;
	int type;

	for(int i = 0; i < playerPieces.size(); i++)
	{
		coordinates coords = playerPieces[i]->getCoordinates();
		_board[coords.x][coords.y] = playerPieces[i];
	}
}

extern int charToInt(char c);

int chessBoardManager::returnCol(string col) {
	int icol = charToInt(col[1]);
	return icol - 1;
}

int chessBoardManager::returnRow(string row)

{
	switch(row[0])
	{
	case 'A':
		return 0;
	case 'B':
		return 1;
	case 'C':
		return 2;
	case 'D':
		return 3;
	case 'E':
		return 4;
	case 'F':
		return 5;
	case 'G':
		return 6;
	case 'H':
		return 7;
	}
}

Piece* chessBoardManager::getPiece(int row, int column) {
	return _board[row][column];
}

void upgradePawnCheck(Piece* pawn) 
{
	char selection;

	if((pawn->getColor() == WHITE && pawn->getCoordinates().x == 0) ||
		(pawn->getColor() == BLACK && pawn->getCoordinates().x == 7))
	{
		cout << "Select piece type [P H B R Q]: " << endl;
		cin >> selection;

		switch(selection)
		{
		case 'P':
			pawn->setType(PAWN);
		case 'H':
			pawn->setType(HORSE);
		case 'B':
			pawn->setType(BISHOP);
		case 'R':
			pawn->setType(ROOK);
		case 'Q':
			pawn->setType(QUEEN);
		}
	}
}

void chessBoardManager::updateGameState() {
	vector<Player*> players = getPlayers();

	// Assigns every threat into all pieces on the board	
	recalculatePieceThreats();

	for(int i = 0; i < players.size(); i++)
	{
		updatePlayerCheckedStatus(players[i]);
	}
}

void chessBoardManager::setPieceTo(Piece* piece, coordinates finalCoords, bool simulate) {
	if(!simulate)
	{
#if _DEBUG
		cout << "NOT simulating movement!" << endl;
#endif
		coordinates startCoordinates = piece->getCoordinates();
		int startX = startCoordinates.x;
		int startY = startCoordinates.y;

		piece->setCoordinates(finalCoords);
		piece->setMoved(true);

		// Delete actual piece (that is not empty) board position
		if(_board[finalCoords.x][finalCoords.y]->getType() != EMPTYTILE)
			delete _board[finalCoords.x][finalCoords.y];

		// Move piece to the destination
		_board[finalCoords.x][finalCoords.y] = piece;

		// Assign empty tile to the piece's starting position now as it is free
		_board[startX][startY] = new Piece(EMPTYTILE, EMPTYTILE, startX, startY);

		// clear screen once and avoid flicker on frame repeat

		printBoard(_board, false);
		updateGameState();
	}
	else
	{
#if _DEBUG
		cout << "Simulating movement!" << endl;
#endif
		coordinates startCoordinates = piece->getCoordinates();
		Piece* cacheTargetTile = _board[finalCoords.x][finalCoords.y];

		int startX = startCoordinates.x;
		int startY = startCoordinates.y;

		piece->setCoordinates(finalCoords);

		_board[finalCoords.x][finalCoords.y] = piece;
		_board[startX][startY] = new Piece(EMPTYTILE, EMPTYTILE, startX, startY);

		printBoard(_board, true);
		updateGameState();

		_board[startX][startY] = piece;
		_board[finalCoords.x][finalCoords.y] = cacheTargetTile;
		piece->setCoordinates(startCoordinates);
	}
}

/* This function always runs the board empty of threat
	and then recalculates every piece's threat */
void chessBoardManager::recalculatePieceThreats(void) {

	int type;
	int color;

	for(int i = 0; i <= 7; i++)
		for(int j = 0; j <= 7; j++)
			_board[i][j]->resetThreatVector();


	for(int i = 0; i <= 7; i++)
	{
		for(int j = 0; j <= 7; j++)
		{
			Piece* piece = _board[i][j];
			color = piece->getColor();
			type = piece->getType();

			if(type == PAWN)
			{
				if(color == WHITE)
				{
					// If the pawn is on the left side column
					if(j == 0)
					{
						if(i - 1 >= 0)
							// If enemy is on a killable tile
							if(_board[i - 1][j + 1]->getColor() != color)
							{
								_board[i - 1][j + 1]->addThreat(piece);
							}
					}
					// If the pawn is on the right side column
					else if(j == 7)
					{
						if(i - 1 >= 0)
							if(_board[i - 1][j - 1]->getColor() != color)
							{
								_board[i - 1][j - 1]->addThreat(piece);
							}
					}
					// Pawn is not on the side columns
					else
					{
						if(i - 1 >= 0)
						{
							// Add threat to tiles that are under threat (row +-1 depending on color; column +-1)
							if(_board[i - 1][j - 1]->getColor() != color)
							{
								_board[i - 1][j - 1]->addThreat(piece);
							}
							if(_board[i - 1][j + 1]->getColor() != color)
							{
								_board[i - 1][j + 1]->addThreat(piece);
							}
						}
					}
				}
				else if(color == BLACK)
				{
					// If the pawn is on the	 left side column
					if(j == 0)
					{
						if(i + 1 <= 7)
							// If enemy is on a killable tile	
							if(_board[i + 1][j + 1]->getColor() != color)
							{
								_board[i + 1][j + 1]->addThreat(piece);
							}
					}
					// If the pawn is on the right side column
					else if(j == 7)
					{
						if(i + 1 <= 7)
							if(_board[i + 1][j - 1]->getColor() != color)
							{
								_board[i + 1][j - 1]->addThreat(piece);
							}
					}
					// Pawn is not on the side columns
					else
					{
						if(i + 1 <= 7)
						{
							// If enemy is on a killable	 tile
							if(_board[i + 1][j - 1]->getColor() != color)
							{
								_board[i + 1][j - 1]->addThreat(piece);
							}
							if(_board[i + 1][j + 1]->getColor() != color)
							{
								_board[i + 1][j - 1]->addThreat(piece);
							}
						}
					}
				}
			}
			// Rook
			else if(type == ROOK)
			{
				for(int k = 1; k <= 7; k++)
				{
					// Left							
					if(j - k >= 0)
					{
						if(_board[i][j - k]->getType() == EMPTYTILE)
						{
							_board[i][j - k]->addThreat(piece);
						}
						else
						{
							_board[i][j - k]->addThreat(piece);
							break;
						}
					}
				}
				for(int k = 1; k <= 7; k++)
				{
					// Right							
					if(j + k <= 7)
					{
						if(_board[i][j + k]->getType() == EMPTYTILE)
						{
							_board[i][j + k]->addThreat(piece);
						}
						else
						{
							_board[i][j + k]->addThreat(piece);
							break;
						}
					}
				}
				for(int k = 1; k <= 7; k++)
				{
					// Up							
					if(i - k >= 0)
					{
						if(_board[i - k][j]->getType() == EMPTYTILE)
						{
							_board[i - k][j]->addThreat(piece);
						}
						else
						{
							_board[i - k][j]->addThreat(piece);
							break;
						}

					}
				}

				for(int k = 1; k <= 7; k++)
				{
					// Down	

					if(i + k <= 7)
					{
						if(_board[i + k][j]->getType() == EMPTYTILE)
						{
							_board[i + k][j]->addThreat(piece);
						}
						else
						{
							_board[i + k][j]->addThreat(piece);
							break;
						}
					}
				}
			}
			// Bishop, both colors
			else if(type == BISHOP)
			{
				for(int k = 1; k <= 7; k++)
				{
					// Left up diagonal						
					if(j - k >= 0 && i - k >= 0)
					{
						if(_board[i - k][j - k]->getType() == EMPTYTILE)
						{
							_board[i - k][j - k]->addThreat(piece);
						}
						else
						{

							_board[i - k][j - k]->addThreat(piece);
							break;
						}
					}
				}
				for(int k = 1; k <= 7; k++)
				{
					// Right up diagonal			
					if(j + k <= 7 && i - k >= 0)
					{
						if(_board[i - k][j + k]->getType() == EMPTYTILE)
						{
							_board[i - k][j + k]->addThreat(piece);
						}
						else
						{
							_board[i - k][j + k]->addThreat(piece);
							break;
						}
					}
				}
				for(int k = 1; k <= 7; k++)
				{
					//	Right down di	agonal
					if(j + k <= 7 && i + k <= 7)
					{
						if(_board[i + k][j + k]->getType() == EMPTYTILE)
						{
							_board[i + k][j + k]->addThreat(piece);
						}
						else
						{
							_board[i + k][j + k]->addThreat(piece);
							break;
						}
					}
				}
				for(int k = 1; k <= 7; k++)
				{
					//	Left down diagonal
					if(j - k >= 0 && i + k <= 7)
					{
						if(_board[i + k][j - k]->getType() == EMPTYTILE)
						{
							_board[i + k][j - k]->addThreat(piece);
						}
						else
						{
							_board[i + k][j - k]->addThreat(piece);
							break;
						}
					}
				}
			}
			// Horse, both colors
			else if(type == HORSE)
			{
				// Left	
				if(j - 2 >= 0 && i + 1 <= 7)
					_board[i + 1][j - 2]->addThreat(piece);
				if(j - 2 >= 0 && i - 1 >= 0)
					_board[i - 1][j - 2]->addThreat(piece);
				// Up		
				if(j - 1 >= 0 && i - 2 >= 0)
					_board[i - 2][j - 1]->addThreat(piece);
				if(j + 1 <= 7 && i - 2 >= 0)
					_board[i - 2][j + 1]->addThreat(piece);
				// Right	
				if(j + 2 <= 7 && i - 1 >= 0)
					_board[i - 1][j + 2]->addThreat(piece);
				if(j + 2 <= 7 && i + 1 <= 7)
					_board[i + 1][j + 2]->addThreat(piece);
				// Down		
				if(j - 1 >= 0 && i + 2 <= 7)
					_board[i + 2][j - 1]->addThreat(piece);
				if(j + 1 <= 7 && i + 2 <= 7)
					_board[i + 2][j + 1]->addThreat(piece);
			}
			// Queen, both colors
			else if(type == QUEEN)
			{
				for(int k = 1; k <= 7; k++)
				{
					// Left
					if(j - k >= 0)
						if(_board[i][j - k]->getType() == EMPTYTILE)
						{
							_board[i][j - k]->addThreat(piece);
						}
						else
						{
							_board[i][j - k]->addThreat(piece);
							break;
						}
				}
				for(int k = 1; k <= 7; k++)
				{
					// Right							
					if(j + k <= 7)
					{
						if(_board[i][j + k]->getType() == EMPTYTILE)
						{
							_board[i][j + k]->addThreat(piece);
						}
						else
						{
							_board[i][j + k]->addThreat(piece);
							break;
						}
					}
				}
				for(int k = 1; k <= 7; k++)
				{
					// Up							
					if(i - k >= 0)
					{
						if(_board[i - k][j]->getType() == EMPTYTILE)
						{
							_board[i - k][j]->addThreat(piece);
						}
						else
						{
							_board[i - k][j]->addThreat(piece);
							break;
						}

					}
				}
				for(int k = 1; k <= 7; k++)
				{
					// Down	
					if(i + k <= 7)
					{
						if(_board[i + k][j]->getType() == EMPTYTILE)
						{
							_board[i + k][j]->addThreat(piece);
						}
						else
						{
							_board[i + k][j]->addThreat(piece);
							break;
						}
					}
				}
				for(int k = 1; k <= 7; k++)
				{
					// Left up diagonal						
					if(j - k >= 0 && i - k >= 0)
					{
						if(_board[i - k][j - k]->getType() == EMPTYTILE)
						{
							_board[i - k][j - k]->addThreat(piece);
						}
						else
						{

							_board[i - k][j - k]->addThreat(piece);
							break;
						}
					}
				}
				for(int k = 1; k <= 7; k++)
				{
					// Right up diagonal			
					if(j + k <= 7 && i - k >= 0)
					{
						if(_board[i - k][j + k]->getType() == EMPTYTILE)
						{
							_board[i - k][j + k]->addThreat(piece);
						}
						else
						{
							_board[i - k][j + k]->addThreat(piece);
							break;
						}
					}
				}
				for(int k = 1; k <= 7; k++)
				{
					// Right down diagonal
					if(j + k <= 7 && i + k <= 7)
					{
						if(_board[i + k][j + k]->getType() == EMPTYTILE)
						{
							_board[i + k][j + k]->addThreat(piece);
						}
						else
						{
							_board[i + k][j + k]->addThreat(piece);
							break;
						}
					}
				}
				for(int k = 1; k <= 7; k++)
				{
					// Left down diagonal
					if(j - k >= 0 && i + k <= 7)
					{
						if(_board[i + k][j - k]->getType() == EMPTYTILE)
						{
							_board[i + k][j - k]->addThreat(piece);
						}
						else
						{
							_board[i + k][j - k]->addThreat(piece);
							break;
						}
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


bool chessBoardManager::tryMove(Piece* piece, string target, bool simulate) {
	vector<string> availableMoves;

	availableMoves = calculateAvailableMovesForPiece(piece);

	if(availableMoves.size() > 0)
	{
		int targetRow = returnRow(target);
		int targetCol = returnCol(target);

		// If targeted tile is within board limits
		if(boeq(targetRow, 0, 7) && boeq(targetCol, 0, 7))
		{
			// Make string indicator from the targeted tile so we can compare it with available moves
			string targetTile = to_string(targetRow) += to_string(targetCol);

			// Check if the targeted tile is in available moves. If yes -> move
			for(int i = 0; i < availableMoves.size(); i++)
			{
#if _DEBUG
				cout << "availableMoves[i]: " << availableMoves[i] << "targetTile: " << targetTile << endl;
#endif
				if(availableMoves[i] == targetTile)
				{
					coordinates coords;
					coords.x = targetRow;
					coords.y = targetCol;

					setPieceTo(piece, coords, simulate);

					// Upgrade pawn logic
					if(piece->getType() == PAWN && !simulate)
						upgradePawnCheck(piece);

					return true;
				}
			}
			cout << "Faulty move!" << endl;
		}
		// Else break cycle
		else
		{
			cout << "Target selection is faulty!, try again! (out of bounds)" << endl;
		}
}
	else
	{
		cout << "Cannot move this piece! (available moves count is 0)" << endl;
	}
	return false;
}

bool chessBoardManager::playMove(Player* player, string startCoord, string targetCoord) {
	int startrow = returnRow(startCoord);
	int startColumn = returnCol(startCoord);
	Piece* tempPiece = getPiece(startrow, startColumn);

	if(tempPiece != NULL)
	{
		if(!(tempPiece->getColor() == player->getColor()))
		{
			cout << "Selected piece is not valid!" << endl;
			return false;
		}

		while(true)
		{
			if(tryMove(tempPiece, targetCoord, false) == true)
			{
#if _DEBUG
				cout << player->getOpponent()->toString() << " checked? " << player->getOpponent()->isChecked() << endl;
				cout << player->toString() << " checked? " << player->isChecked() << endl;
#endif
				// Check if checkmate (start simulation process)
				if(player->getOpponent()->isChecked() == true)
				{
					bool isMate = checkForMate(player->getOpponent());
					cout << "Checkmate simulation result: " << isMate << endl;
					if(isMate == true)
					{
						player->isWinner = true;
						gameOver = true;
					}
				}
				return true;
			}
		}
}
	return false;
}

bool chessBoardManager::simulateMove(Player* player, string startCoord, string targetCoord) {
	int startrow = returnRow(startCoord);
	int startColumn = returnCol(startCoord);
	Piece* tempPiece = getPiece(startrow, startColumn);

	if(tempPiece != NULL)
	{
		if(!(tempPiece->getColor() == player->getColor()))
		{
			cout << "Selected piece is not valid!" << endl;
			return false;
		}

		while(true)
		{
			if(tryMove(tempPiece, targetCoord, true) == true)
			{
				return true;
			}
		}
	}
	return false;
}


vector<string> chessBoardManager::calculateAvailableMovesForPiece(Piece* piece) {
	/*	This function returns a vector containing every possible
		move for a chosen piece */

	int row = piece->getCoordinates().x;
	int col = piece->getCoordinates().y;
#if _DEBUG
	cout << "Calculating available moves for piece " << piece->toString() << " at " << piece->getCoordinates().toString() << endl;
#endif
	int type = piece->getType();
	int color = piece->getColor();

	vector<string> validMoves;

	// Pawn, white
	if(type == PAWN)
	{
		if(color == WHITE)
		{
			// If the pawn is on the left side column
			if(col == 0)
			{
				// Basic one or two moves in front, default situation
				if(row - 1 >= 0)
				{
					if(_board[row - 1][col]->getType() == EMPTYTILE)
					{
						validMoves.push_back(to_string(row - 1) += to_string(col));
					}
					// If pawn is on a starting position
					if(piece->isMoved() == false)
					{
						if(_board[row - 1][col]->getType() == EMPTYTILE && _board[row - 2][col]->getType() == EMPTYTILE)
						{
							validMoves.push_back(to_string(row - 2) += to_string(col));
						}
					}
					// If enemy is on a killable tile
					if(_board[row - 1][col + 1]->getColor() == BLACK)
					{
						validMoves.push_back(to_string(row - 1) += to_string(col + 1));
					}
				}
				else
					cout << "Cannot move!" << endl;
			}
			// If the pawn is on the right side column
			else if(col == 7)
			{
				if(row - 1 >= 0)
				{
					// Basic one or two moves in front, default situation
					if(_board[row - 1][col]->getType() == EMPTYTILE)
					{
						validMoves.push_back(to_string(row - 1) += to_string(col));
					}
					// If pawn has not moved before
					if(piece->isMoved() == false)
					{
						if(_board[row - 1][col]->getType() == EMPTYTILE && _board[row - 2][col]->getType() == EMPTYTILE)
						{
							validMoves.push_back(to_string(row - 2) += to_string(col));
						}
					}
					// If enemy is on a killable FREE
					if(_board[row - 1][col - 1]->getColor() == BLACK)
					{
						validMoves.push_back(to_string(row - 1) += to_string(col - 1));
					}
				}
				else
					cout << "Cannot move!" << endl;
			}
			// Pawn is not on the side columns
			else
			{
				if(row - 1 >= 0)
				{
					if(_board[row - 1][col]->getType() == EMPTYTILE)
					{
						validMoves.push_back(to_string(row - 1) += to_string(col));
					}
					if(piece->isMoved() == false)
					{
						if(_board[row - 1][col]->getType() == EMPTYTILE && _board[row - 2][col]->getType() == EMPTYTILE)
						{
							validMoves.push_back(to_string(row - 2) += to_string(col));
						}
					}
					// If enemy is on a killable tile
					if(_board[row - 1][col - 1]->getColor() == BLACK)
					{
						validMoves.push_back(to_string(row - 1) += to_string(col - 1));
					}
					if(_board[row - 1][col + 1]->getColor() == BLACK)
					{
						validMoves.push_back(to_string(row - 1) += to_string(col + 1));
					}
				}
				else
					cout << "Cannot move!" << endl;
			}
		}
		// Black case, pawn
		else if(color == BLACK)
		{
			// If the pawn is on the left side column
			if(col == 0)
			{
				// Basic one or two moves in front, default situation
				if(_board[row + 1][col]->getType() == EMPTYTILE)
				{
					validMoves.push_back(to_string(row + 1) += to_string(col));
				}
				// If pawn is on a starting position
				if(piece->isMoved() == false)
				{
					if(_board[row + 1][col]->getType() == EMPTYTILE && _board[row + 2][col]->getType() == EMPTYTILE)
					{
						validMoves.push_back(to_string(row + 2) += to_string(col));
					}
				}
				// If enemy is on a killable FREE
				if(_board[row + 1][col + 1]->getColor() == WHITE)
				{
					validMoves.push_back(to_string(row + 1) += to_string(col + 1));
				}
			}
			// If the pawn is on the right side column
			else if(col == 7)
			{
				// Basic one or two moves in front, default situation
				if(_board[row + 1][col]->getType() == EMPTYTILE)
				{
					validMoves.push_back(to_string(row + 1) += to_string(col));
				}
				// If pawn has not moved before
				if(piece->isMoved() == false)
				{
					if(_board[row + 1][col]->getType() == EMPTYTILE && _board[row + 2][col]->getType() == EMPTYTILE)
					{
						validMoves.push_back(to_string(row + 2) += to_string(col));
					}
				}
				// If enemy is on a killable FREE
				if(_board[row + 1][col - 1]->getColor() == WHITE)
				{
					validMoves.push_back(to_string(row + 1) += to_string(col - 1));
				}
			}
			// Pawn is not on the side columns
			else
			{
				if(_board[row + 1][col]->getType() == EMPTYTILE)
				{
					validMoves.push_back(to_string(row + 1) += to_string(col));
				}
				if(piece->isMoved() == false)
				{
					if(_board[row + 1][col]->getType() == EMPTYTILE && _board[row + 2][col]->getType() == EMPTYTILE)
					{
						validMoves.push_back(to_string(row + 2) += to_string(col));
					}
				}
				// If enemy is on a killable FREEs
				if(_board[row + 1][col - 1]->getColor() == WHITE)
				{
					validMoves.push_back(to_string(row + 1) += to_string(col - 1));
				}
				if(_board[row + 1][col + 1]->getColor() == WHITE)
				{
					validMoves.push_back(to_string(row + 1) += to_string(col + 1));
				}
			}
		}


		// OHESTALYÖNTI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	}
	// Rook, both colors
	else if(type == ROOK)
	{
		for(int i = 1; i <= 7; i++)
		{
			// Left
			if(col - i >= 0)
			{
				if(_board[row][col - i]->getType() == EMPTYTILE)
				{
					validMoves.push_back(to_string(row) += to_string(col - i));
				}
				else
				{
					if(_board[row][col - i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(to_string(row) += to_string(col - i));
						break;
					}
				}
			}
		}
		for(int i = 1; i <= 7; i++)
		{
			// Right
			if(col + i <= 7)
			{
				if(_board[row][col + i]->getType() == EMPTYTILE)
				{
					validMoves.push_back(to_string(row) += to_string(col + i));
				}
				else
				{
					if(_board[row][col + i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(to_string(row) += to_string(col + i));
						break;
					}
				}
			}
		}
		for(int i = 1; i <= 7; i++)
		{
			// Up
			if(row - i >= 0)
			{
				if(_board[row - i][col]->getType() == EMPTYTILE)
				{
					validMoves.push_back(to_string(row - i) += to_string(col));
				}
				else
				{
					if(_board[row - i][col]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(to_string(row - i) += to_string(col));
						break;
					}
				}
			}
		}
		for(int i = 1; i <= 7; i++)
		{
			// Down
			if(row + i <= 7)
			{
				if(_board[row + i][col]->getType() == EMPTYTILE)
				{
					validMoves.push_back(to_string(row + i) += to_string(col));
				}
				else
				{
					if(_board[row + i][col]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(to_string(row + i) += to_string(col));
						break;
					}
				}
			}
		}
	}
	// Bishop, both colors
	else if(type == BISHOP)
	{
		for(int i = 1; i <= 7; i++)
			// Left up diagonal					
			if(col - i >= 0 && row - i >= 0)
			{
				if(_board[row - i][col - i]->getType() == EMPTYTILE)
				{
					validMoves.push_back(to_string(row - i) += to_string(col - i));
				}
				else
				{
					if(_board[row - i][col - i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(to_string(row - i) += to_string(col - i));
						break;
					}
				}
			}
		for(int i = 1; i <= 7; i++)
		{
			// Right up diagonal		
			if(col + i <= 7 && row - i >= 0)
			{
				if(_board[row - i][col + i]->getType() == EMPTYTILE)
				{
					validMoves.push_back(to_string(row - i) += to_string(col + i));
				}
				else
				{
					if(_board[row - i][col + i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(to_string(row - i) += to_string(col + i));
						break;
					}
				}
			}
		}
		for(int i = 1; i <= 7; i++)
		{
			// Right down diagonal
			if(col + i <= 7 && row + i <= 7)
			{
				if(_board[row + i][col + i]->getType() == EMPTYTILE)
				{
					validMoves.push_back(to_string(row + i) += to_string(col + i));
				}
				else
				{
					if(_board[row + i][col + i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(to_string(row + i) += to_string(col + i));
						break;
					}
				}
			}
		}
		for(int i = 1; i <= 7; i++)
		{
			// Left down diagonal
			if(col - i >= 0 && row + i <= 7)
			{
				if(_board[row + i][col - i]->getType() == EMPTYTILE)
				{
					validMoves.push_back(to_string(row + i) += to_string(col - i));
				}
				else
				{
					if(_board[row + i][col - i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(to_string(row + i) += to_string(col - i));
						break;
					}
				}
			}
		}
	}
	// Horse, both colors
	else if(type == HORSE)
	{
		// Left
		if(col - 2 >= 0 && row + 1 <= 7)
		{
			if(_board[row + 1][col - 2]->getColor() != color)
			{
				validMoves.push_back(to_string(row + 1) += to_string(col - 2));
			}
		}
		if(col - 2 >= 0 && row - 1 >= 0)
		{
			if(_board[row - 1][col - 2]->getColor() != color)
			{
				validMoves.push_back(to_string(row - 1) += to_string(col - 2));
			}
		}
		// Up
		if(col - 1 >= 0 && row - 2 >= 0)
		{
			if(_board[row - 2][col - 1]->getColor() != color)
			{
				validMoves.push_back(to_string(row - 2) += to_string(col - 1));
			}
		}
		if(col + 1 <= 7 && row - 2 >= 0)
		{
			if(_board[row - 2][col + 1]->getColor() != color)
			{
				validMoves.push_back(to_string(row - 2) += to_string(col + 1));
			}
		}
		// Right
		if(col + 2 <= 7 && row - 1 >= 0)
		{
			if(_board[row - 1][col + 2]->getColor() != color)
			{
				validMoves.push_back(to_string(row - 1) += to_string(col + 2));
			}
		}
		if(col + 2 <= 7 && row + 1 <= 7)
		{
			if(_board[row + 1][col + 2]->getColor() != color)
			{
				validMoves.push_back(to_string(row + 1) += to_string(col + 2));
			}
		}
		// Down
		if(col - 1 >= 0 && row + 2 <= 7)
		{
			if(_board[row + 2][col - 1]->getColor() != color)
			{
				validMoves.push_back(to_string(row + 2) += to_string(col - 1));
			}
		}
		if(col + 1 <= 7 && row + 2 <= 7)
		{
			if(_board[row + 2][col + 1]->getColor() != color)
			{
				validMoves.push_back(to_string(row + 2) += to_string(col + 1));
			}
		}
	}
	// Queen, both colors
	else if(type == QUEEN)
	{
		// Works the same way as bishop + rook combined -> copy paste rook and bishop functionalities
		for(int i = 1; i <= 7; i++)
		{
			// Left
			if(col - i >= 0)
			{
				if(_board[row][col - i]->getType() == EMPTYTILE)
				{
					validMoves.push_back(to_string(row) += to_string(col - i));
				}
				else
				{
					if(_board[row][col - i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(to_string(row) += to_string(col - i));
						break;
					}
				}
			}
		}
		for(int i = 1; i <= 7; i++)
		{
			// Right
			if(col + i <= 7)
			{
				if(_board[row][col + i]->getType() == EMPTYTILE)
				{
					validMoves.push_back(to_string(row) += to_string(col + i));
				}
				else
				{
					if(_board[row][col + i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(to_string(row) += to_string(col + i));
						break;
					}
				}
			}
		}
		for(int i = 1; i <= 7; i++)
		{
			// Up
			if(row - i >= 0)
			{
				if(_board[row - i][col]->getType() == EMPTYTILE)
				{
					validMoves.push_back(to_string(row - i) += to_string(col));
				}
				else
				{
					if(_board[row - i][col]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(to_string(row - i) += to_string(col));
						break;
					}
				}
			}
		}
		for(int i = 1; i <= 7; i++)
		{
			// Down
			if(row + i <= 7)
			{
				if(_board[row + i][col]->getType() == EMPTYTILE)
				{
					validMoves.push_back(to_string(row + i) += to_string(col));
				}
				else
				{
					if(_board[row + i][col]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(to_string(row + i) += to_string(col));
						break;
					}
				}
			}
		}
		for(int i = 1; i <= 7; i++)
			// Left up diagonal					
			if(col - i >= 0 && row - i >= 0)
			{
				if(_board[row - i][col - i]->getType() == EMPTYTILE)
				{
					validMoves.push_back(to_string(row - i) += to_string(col - i));
				}
				else
				{
					if(_board[row - i][col - i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(to_string(row - i) += to_string(col - i));
						break;
					}
				}
			}
		for(int i = 1; i <= 7; i++)
		{
			// Right up diagonal		
			if(col + i <= 7 && row - i >= 0)
			{
				if(_board[row - i][col + i]->getType() == EMPTYTILE)
				{
					validMoves.push_back(to_string(row - i) += to_string(col + i));
				}
				else
				{
					if(_board[row - i][col + i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(to_string(row - i) += to_string(col + i));
						break;
					}
				}
			}
		}
		for(int i = 1; i <= 7; i++)
		{
			// Right down diagonal
			if(col + i <= 7 && row + i <= 7)
			{
				if(_board[row + i][col + i]->getType() == EMPTYTILE)
				{
					validMoves.push_back(to_string(row + i) += to_string(col + i));
				}
				else
				{
					if(_board[row + i][col + i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(to_string(row + i) += to_string(col + i));
						break;
					}
				}
			}
		}
		for(int i = 1; i <= 7; i++)
		{
			// Left down diagonal
			if(col - i >= 0 && row + i <= 7)
			{
				if(_board[row + i][col - i]->getType() == EMPTYTILE)
				{
					validMoves.push_back(to_string(row + i) += to_string(col - i));
				}
				else
				{
					if(_board[row + i][col - i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(to_string(row + i) += to_string(col - i));
						break;
					}
				}
			}
		}
	}
	// King, both colors
	// Moving a king requires to check if the position is free as well as checking if it is under threat
	else if(type == KING)
	{
		bool threat = false; // Flag for checking threat
		// Left up diagonal
		if(col - 1 >= 0 && row + 1 <= 7)
		{
			// If the position is free or contains an enemy
			if(_board[row + 1][col - 1]->getType() == EMPTYTILE || _board[row + 1][col - 1]->getColor() != color)
			{
				// Check if it is also under threat
				for(int i = 0; i < _board[row + 1][col - 1]->getThreatVector().size(); i++)
				{
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = _board[row + 1][col - 1]->getThreatVector()[i]->getColor();
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if(threatColor != color && threatColor != 0)
					{
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if(!threat)
				{
					validMoves.push_back(to_string(row + 1) += to_string(col - 1));
				}
			}
		}
		// Left down diagonal
		else if(col - 1 >= 0 && row - 1 >= 0)
		{
			if(_board[row - 1][col - 1]->getType() == EMPTYTILE || _board[row - 1][col - 1]->getColor() != color)
			{
				// Check if it is under threat
				for(int i = 0; i < _board[row - 1][col - 1]->getThreatVector().size(); i++)
				{
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = _board[row - 1][col - 1]->getThreatVector()[i]->getColor();
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if(threatColor != color && threatColor != 0)
					{
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if(!threat)
				{
					validMoves.push_back(to_string(row - 1) += to_string(col - 1));
				}
			}
		}
		// Right up diagonal
		if(col - 1 >= 0 && row + 1 <= 7)
		{
			if(_board[row + 1][col - 1]->getType() == EMPTYTILE || _board[row + 1][col - 1]->getColor() != color)
			{
				// Check if it is under threat
				for(int i = 0; i < _board[row + 1][col - 1]->getThreatVector().size(); i++)
				{
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = _board[row + 1][col - 1]->getThreatVector()[i]->getColor();
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if(threatColor != color && threatColor != 0)
					{
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if(!threat)
				{
					validMoves.push_back(to_string(row + 1) += to_string(col - 1));
				}
			}
		}
		// Right down diagonal
		if(col + 1 <= 7 && row - 1 >= 0)
		{
			if(_board[row - 1][col + 1]->getType() == EMPTYTILE || _board[row - 1][col + 1]->getColor() != color)
			{
				// Check if it is under threat
				for(int i = 0; i < _board[row - 1][col + 1]->getThreatVector().size(); i++)
				{
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = _board[row - 1][col + 1]->getThreatVector()[i]->getColor();
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if(threatColor != color && threatColor != 0)
					{
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if(!threat)
				{
					validMoves.push_back(to_string(row - 1) += to_string(col + 1));
				}
			}
		}
		// Left
		if(col - 1 >= 0)
		{
			if(_board[row][col - 1]->getType() == EMPTYTILE || _board[row][col - 1]->getColor() != color)
			{
				// Check if it is under threat
				for(int i = 0; i < _board[row][col - 1]->getThreatVector().size(); i++)
				{
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = _board[row][col - 1]->getThreatVector()[i]->getColor();
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if(threatColor != color && threatColor != 0)
					{
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if(!threat)
				{
					validMoves.push_back(to_string(row) += to_string(col - 1));
				}
			}
		}
		// Up
		if(row + 1 <= 7)
		{
			if(_board[row + 1][col]->getType() == EMPTYTILE || _board[row + 1][col]->getColor() != color)
			{
				// Check if it is under threat
				for(int i = 0; i < _board[row + 1][col]->getThreatVector().size(); i++)
				{
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = _board[row + 1][col]->getThreatVector()[i]->getColor();
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if(threatColor != color && threatColor != 0)
					{
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if(!threat)
				{
					validMoves.push_back(to_string(row + 1) += to_string(col));
				}
			}
		}
		// Right
		if(col + 1 <= 7)
		{
			if(_board[row][col + 1]->getType() == EMPTYTILE || _board[row][col + 1]->getColor() != color)
			{
				// Check if it is under threat
				for(int i = 0; i < _board[row][col + 1]->getThreatVector().size(); i++)
				{
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = _board[row][col + 1]->getThreatVector()[i]->getColor();
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if(threatColor != color && threatColor != 0)
					{
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if(!threat)
				{
					validMoves.push_back(to_string(row) += to_string(col + 1));
				}
			}
		}
		// Down
		if(row - 1 >= 0)
		{
			if(_board[row - 1][col]->getType() == EMPTYTILE || _board[row - 1][col]->getColor() != color)
			{
				// Check if it is under threat
				for(int i = 0; i < _board[row - 1][col]->getThreatVector().size(); i++)
				{
					// Get targeted piece's threat vector that contains threat colors
					int threatColor = _board[row - 1][col]->getThreatVector()[i]->getColor();
					// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
					if(threatColor != color && threatColor != 0)
					{
						threat = true;
						break;
					}
				}
				// If the piece is free and not under threat -> add position to valid moves
				if(!threat)
				{
					validMoves.push_back(to_string(row - 1) += to_string(col));
				}
			}
		}
	}
	return validMoves;
}

void chessBoardManager::addPlayer(Player* p) {
	_players.push_back(p);
}

vector<Player*> chessBoardManager::getPlayers() {
	return _players;
}

string rowToBoardChar(int row) {
	switch(row)
	{
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
		return "?";
	}
}

string columnToBoardInt(int col) {
	return to_string(col + 1);
}


void chessBoardManager::printBoard(Board* board, bool simulation) {
	/* Function for printing the game board every turn */
	int simuColor = 3;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(hConsole, coord);

	if(simulation)
		SetConsoleTextAttribute(hConsole, 3);

	cout << "\n\t\t  1  2  3  4  5  6  7  8" << endl;
	int TILE_COLOR;

	int COLOR_BLACK = 16;
	int COLOR_WHITE = 23;
	int COLOR_EVILRED = 4;
	int COLOR_GREEN = 2;

	char pipe = (char)179;

	for(int i = 0; i <= 7; i++)
	{
		for(int j = 0; j <= 7; j++)
		{
			Piece* piece = board[i][j];

			if((j + i) % 2 == 0) 
				TILE_COLOR = BACKGROUND_BLUE;			
			else
				TILE_COLOR = BACKGROUND_BLUE | BACKGROUND_INTENSITY;

			
			if(j == 0)
				cout << "\t\t ";
			if(piece->getType() == EMPTYTILE)
			{
				SetConsoleTextAttribute(hConsole, TILE_COLOR);
				cout << "   ";
			}
			else
			{
				switch(piece->getColor())
				{
				case WHITE:
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | TILE_COLOR);
					break;
				case BLACK:
					SetConsoleTextAttribute(hConsole, TILE_COLOR);
					break;
				default:
					SetConsoleTextAttribute(hConsole, COLOR_BLACK | TILE_COLOR);
				}
				cout << " " <<  numToPiece(piece->getType()) << /* piece->getColor() */  " ";
			}
			if(simulation)
				SetConsoleTextAttribute(hConsole, 3); // light blue, cyan
			else
				SetConsoleTextAttribute(hConsole, 15);
			if(j == 7)
				cout << " " << rowToBoardChar(i) << endl;
		}
	}
	cout << endl;
	cout << endl;
}

extern int charToInt(char c);

bool chessBoardManager::checkForMate(Player* realPlayer) {
	// Create a temporary chessboard for simulating all possible moves for next turn
	cout << "Entering mate simulation.." << endl;

	Piece* king;
	bool simulationResult = false;
	bool isChecked = false;
	auto tempBoard = this->_board;

	vector<Piece*> pieces = realPlayer->getPieces();
	for(int i = 0; i < pieces.size(); i++)
	{
		if(pieces[i]->getType() == KING)
		{
			king = pieces[i];
		}
	}

	cout << "Checking for mate status..." << endl;

	Player* simCurrentPlayer = new Player(realPlayer->getColor());
	Player* simOpponent = new Player(realPlayer->getOpponent()->getColor());

	simCurrentPlayer->copyPieces(realPlayer->getPieces());
	simOpponent->copyPieces(realPlayer->getOpponent()->getPieces());

	simCurrentPlayer->setOpponent(simOpponent);
	simOpponent->setOpponent(simCurrentPlayer);

	chessBoardManager* simBoardMgr = new chessBoardManager();
	simBoardMgr->addPlayer(simCurrentPlayer);
	simBoardMgr->addPlayer(simOpponent);

	simBoardMgr->initBoard(simCurrentPlayer);
	simBoardMgr->initBoard(simOpponent);

	cout << "================ SIMULATION ================ " << endl;
	printBoard(simBoardMgr->getBoard(), true);
	vector<Piece*> simPieces = simCurrentPlayer->getPieces();

	for(int i = 0; i < simPieces.size(); i++)
	{
		Piece* pc = simPieces[i];
		vector<string> moves = simBoardMgr->calculateAvailableMovesForPiece(pc);

		for(int j = 0; j < moves.size(); j++)
		{
			coordinates coords = pc->getCoordinates();
			string startCoords = rowToBoardChar(coords.x) + columnToBoardInt(coords.y);
			string endCoords = rowToBoardChar(charToInt(moves[j][0])) + columnToBoardInt(charToInt(moves[j][1]));

			if(simBoardMgr->simulateMove(simCurrentPlayer, startCoords, endCoords) == true)
			{
				isChecked = simCurrentPlayer->isChecked();
				if(!isChecked) // game is not checkmate -> we can return
					break;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(250));

		};
		if(!isChecked)
			break;
	}

	printBoard(simBoardMgr->getBoard(), false);
	simulationResult = isChecked;
	cout << "================ END OF SIMULATION ================ " << endl;

	/* if king is STILL threatened -> mate */
	return simulationResult;
}

Piece*** chessBoardManager::getBoard(void) {
	return _board;
}

string chessBoardManager::numToPiece(int num) {
	string piece;
	if(num == 0)
	{
		piece = "-";
	}
	if(num == 1)
	{
		piece = (char)254;// pawn
	}
	if(num == 2)
	{
		piece = (char)227; // rook
	}
	if(num == 3)
	{
		piece = (char)226;// horse
	}
	if(num == 4)
	{
		piece = "X";// bishop
	}
	if(num == 5)
	{
		piece = (char)157;// queen 
	}
	if(num == 6)
	{
		piece = (char)233; // king
	}
	return piece;
	}

void chessBoardManager::updatePlayerCheckedStatus(Player* player) {

#if _DEBUG
	cout << "Checking if player " << player->toString() << " is checked.." << endl;
#endif
	int kingThreatsCount = 0;
	Piece* friendlyKing = NULL;
	vector<Piece*> pieces = player->getPieces();

	// Select player's king piece
	for(int i = 0; i < pieces.size(); i++)
		if(pieces[i]->getType() == KING)
			friendlyKing = pieces[i];

	if(friendlyKing != NULL)
	{
		kingThreatsCount = friendlyKing->getThreatVector().size();
	}

	player->setChecked(kingThreatsCount > 0);
}

string chessBoardManager::returnRowC(int row) {
	string rrow;

	if(row == 0)
		rrow = 'A';
	else if(row == 1)
		rrow = 'B';
	else if(row == 2)
		rrow = 'C';
	else if(row == 3)
		rrow = 'D';
	else if(row == 4)
		rrow = 'E';
	else if(row == 5)
		rrow = 'F';
	else if(row == 6)
		rrow = 'G';
	else if(row == 7)
		rrow = 'H';

	return rrow;
}

string chessBoardManager::returnColC(int col) {
	string column;

	if(col == 0)
		column = '1';
	else if(col == 1)
		column = '2';
	else if(col == 2)
		column = '3';
	else if(col == 3)
		column = '4';
	else if(col == 4)
		column = '5';
	else if(col == 5)
		column = '6';
	else if(col == 6)
		column = '7';
	else if(col == 7)
		column = '8';

	return column;

}

void chessBoardManager::calculateAllPossibleMoves(Player* p) {
	int color = p->getColor();
	vector<string> moves;
	vector<string> availableMoves;
	string pos;
	cout << "updating all possible moves for player " << to_string(p->getColor()) << endl;
	for(int i = 0; i <= 7; i++)
	{
		for(int j = 0; j <= 7; j++)
		{
			if(_board[i][j]->getColor() == color)
			{
				Piece* piece = _board[i][j];

				string col = returnColC(j);
				string row = returnRowC(i);
				pos = returnRowC(i) += returnColC(j);

				// Get piece's possible movements
				availableMoves = calculateAvailableMovesForPiece(piece);
				moves.insert(moves.end(), availableMoves.begin(), availableMoves.end());
				piece->setAvailableMoves(moves);
			}
		}
	}
}
