#include "chessBoard.h"
#include <vector>
#include "Piece.h"
#include "player.h"
#include "defines.h"
#include <thread>

using namespace std;

extern int charToInt(char c);
vector<Piece*> removeNonKingableTiles(vector<Piece*> tiles, int color);

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
			_board[row][col] = new Piece(EMPTYTILE, EMPTYTILE, coordinates(col, row));
		}
	}
}


chessBoardManager::~chessBoardManager() {
	for(int i = 0; i < _players.size(); i++)
		delete _players[i];
	_players.clear();
}

int convertColumnCharToIndex(string column) {

	if(column == "A")
		return 0;
	else if(column == "B")
		return 1;
	else if(column == "C")
		return 2;
	else if(column == "D")
		return 3;
	else if(column == "E")
		return 4;
	else if(column == "F")
		return 5;
	else if(column == "G")
		return 6;
	else if(column == "H")
		return 7;
	else
		return 99;
}

string convertColumnIndexToChar(int index) {
	switch(index)
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
		return "X";
	}
}

int convertRowCharToIndex(string row) {
	return atoi(row.c_str()) - 1;
}

string convertRowIndexToChar(int row) {
	return to_string(row + 1);
}

void chessBoardManager::initBoard(Player* p) {
	// Initialize the board with players' pieces
	vector<Piece*> playerPieces = p->getPieces();

	for(int i = 0; i < playerPieces.size(); i++)
	{
		coordinates coords = playerPieces[i]->getCoordinates();
		int row = coords.getBoardRowIndex();
		int column = coords.getBoardColumnIndex();
		_board[row][column] = playerPieces[i];
	}
}



Piece* chessBoardManager::getPiece(int row, int column) {
	return _board[row][column];
}

void upgradePawnCheck(Piece* pawn) {
	char selection;

	int row = pawn->getCoordinates().getBoardRowIndex();
	if((pawn->getColor() == WHITE && row == 0) ||
		(pawn->getColor() == BLACK && row == 7))
	{
		//std::cout << "Select piece type [P H B R Q]: " << endl;
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
		updatePlayerCheckedStatus(players[i]);
}

void chessBoardManager::setPieceTo(Piece* piece, coordinates finalCoords, bool simulate, bool updateState) {

	coordinates startCoordinates = piece->getCoordinates();
	int startX = startCoordinates.getBoardRowIndex();
	int startY = startCoordinates.getBoardColumnIndex();
	int endX = finalCoords.getBoardRowIndex();
	int endY = finalCoords.getBoardColumnIndex();

	if(!simulate)
	{
#if _DEBUG
		std::cout << "NOT simulating movement!" << endl;
#endif
		piece->setCoordinates(finalCoords);
		piece->setMoved(true);

		// Delete actual piece (that is not empty) board position
		if(_board[endX][endY]->getType() != EMPTYTILE)
			delete _board[endX][endY];

		// Move piece to the destination
		_board[endX][endY] = piece;

		// Assign empty tile to the piece's starting position now as it is free
		_board[startX][startY] = new Piece(EMPTYTILE, EMPTYTILE, coordinates(startX, startY));
		
		if(updateState)
		{
			printBoard(_board, false);
			updateGameState();
		}
	}
	else
	{
#if _DEBUG
		std::cout << "Simulating movement!" << endl;
#endif
		Piece* cacheTargetTile = _board[endX][endY];

		piece->setCoordinates(finalCoords);

		_board[endX][endY] = piece;
		_board[startX][startY] = new Piece(EMPTYTILE, EMPTYTILE, coordinates(startX, startY));

		printBoard(_board, true);
		updateGameState();

		delete _board[startX][startY];
		_board[startX][startY] = piece;
		_board[endX][endY] = cacheTargetTile;
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


bool chessBoardManager::tryMove(Piece* piece, coordinates target, bool simulate) {

	vector<coordinates> availableMoves;
	availableMoves = calculateAvailableMovesForPiece(piece);

	if(availableMoves.size() > 0)
	{
		int targetRow = target.getBoardRowIndex();
		int targetCol = target.getBoardColumnIndex();

		// If targeted tile is within board limits
		if(boeq(targetRow, 0, 7) && boeq(targetCol, 0, 7))
		{
			// Make string indicator from the targeted tile so we can compare it with available moves
			coordinates targetTile = coordinates(targetCol, targetRow);

			// Check if the targeted tile is in available moves. If yes -> move
			for(int i = 0; i < availableMoves.size(); i++)
			{
#if _DEBUG
				std::cout << "availableMoves[i]: " << availableMoves[i].toCharString() << " targetTile: " << targetTile.toCharString() << endl;
#endif
				if(availableMoves[i] == targetTile)
				{
					if(piece->getType() != KING) // avoid checking for castling
						setPieceTo(piece, coordinates(targetCol, targetRow), simulate, true);
					else
					{
						Piece* king = piece;
						// check if the target coordinates equal coordinates for castling equivalent move
						if(abs(targetCol - king->getCoordinates().getBoardColumnIndex()) == 2)
						{
							std::cout << "Castling..." << endl;
							// move king
							setPieceTo(king, coordinates(targetCol, targetRow), simulate, false);
							// move rook
							Piece* rook;
							if(targetCol == 2)
							{
								rook = _board[targetRow][0];
								setPieceTo(rook, coordinates(targetCol + 1, targetRow), simulate, true);
							}
							else if(targetCol == 6)
							{
								rook = _board[targetRow][7];
								setPieceTo(rook, coordinates(targetCol - 1, targetRow), simulate, true);
							}
						}
						else
							setPieceTo(piece, coordinates(targetCol, targetRow), simulate, true);
					}

					// Upgrade pawn logic
					if(piece->getType() == PAWN && !simulate)
						upgradePawnCheck(piece);

					return true;
				}
			}
			std::cout << "Invalid move!" << endl;
		}
		// Else break cycle
		else
		{
			std::cout << "Target selection is faulty!, try again! (out of bounds)" << endl;
		}
	}
	else
	{
		std::cout << "Cannot move this piece! (available moves count is 0)" << endl;
	}
	return false;
}

bool chessBoardManager::playMove(Player* player, coordinates startCoord, coordinates targetCoord) {

	int startrow = startCoord.getBoardRowIndex();
	int startColumn = startCoord.getBoardColumnIndex();

	Piece* tempPiece = getPiece(startrow, startColumn);

	if(tempPiece != NULL)
	{
		if(!(tempPiece->getColor() == player->getColor()))
		{
			std::cout << "Selected piece is not valid!" << endl;
			return false;
		}

		while(true)
		{
			if(tryMove(tempPiece, targetCoord, false) == true)
			{
#if _DEBUG
				std::cout << player->getOpponent()->toString() << " checked? " << player->getOpponent()->isChecked() << endl;
				std::cout << player->toString() << " checked? " << player->isChecked() << endl;
#endif
				// Check if checkmate (start simulation process)
				if(player->getOpponent()->isChecked() == true)
				{
					bool isMate = checkForMate(player->getOpponent());
					std::cout << "Checkmate simulation result: " << isMate << endl;
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

bool chessBoardManager::simulateMove(Player* player, coordinates startCoord, coordinates targetCoord) {
	int startrow = startCoord.getBoardRowIndex();
	int startColumn = startCoord.getBoardColumnIndex();
	Piece* tempPiece = getPiece(startrow, startColumn);

	if(tempPiece != NULL)
	{
		if(!(tempPiece->getColor() == player->getColor()))
		{
			std::cout << "Selected piece is not valid!" << endl;
			return false;
		}
		tryMove(tempPiece, targetCoord, true);
		return true;		
	}
	return false;
}


vector<coordinates> chessBoardManager::calculateAvailableMovesForPiece(Piece* piece) {
	/*	This function returns a vector containing every possible
		move for a chosen piece */

	coordinates coords = piece->getCoordinates();
	int row = coords.getBoardRowIndex();
	int col = coords.getBoardColumnIndex();

#if _DEBUG
	std::cout << "Calculating available moves for piece " << piece->toString() << " at " << coords.toCharString() << endl;
#endif
	int type = piece->getType();
	int color = piece->getColor();

	vector<coordinates> validMoves;

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
						validMoves.push_back(coordinates(col, row - 1));
					}
					// If pawn is on a starting position
					if(piece->isMoved() == false)
					{
						if(_board[row - 1][col]->getType() == EMPTYTILE && _board[row - 2][col]->getType() == EMPTYTILE)
						{
							validMoves.push_back(coordinates(col, row - 2));
						}
					}
					// If enemy is on a killable tile
					if(_board[row - 1][col + 1]->getColor() == BLACK)
					{
						validMoves.push_back(coordinates(col + 1, row - 1));
					}
				}
				else
					std::cout << "Cannot move!" << endl;
			}
			// If the pawn is on the right side column
			else if(col == 7)
			{
				if(row - 1 >= 0)
				{
					// Basic one or two moves in front, default situation
					if(_board[row - 1][col]->getType() == EMPTYTILE)
					{
						validMoves.push_back(coordinates(col, row - 1));
					}
					// If pawn has not moved before
					if(piece->isMoved() == false)
					{
						if(_board[row - 1][col]->getType() == EMPTYTILE && _board[row - 2][col]->getType() == EMPTYTILE)
						{
							validMoves.push_back(coordinates(col, row - 2));
						}
					}
					// If enemy is on a killable FREE
					if(_board[row - 1][col - 1]->getColor() == BLACK)
					{
						validMoves.push_back(coordinates(col - 1, row - 1));
					}
				}
				else
					std::cout << "Cannot move!" << endl;
			}
			// Pawn is not on the side columns
			else
			{
				if(row - 1 >= 0)
				{
					if(_board[row - 1][col]->getType() == EMPTYTILE)
					{
						validMoves.push_back(coordinates(col, row - 1));
					}
					if(piece->isMoved() == false)
					{
						if(_board[row - 1][col]->getType() == EMPTYTILE && _board[row - 2][col]->getType() == EMPTYTILE)
						{
							validMoves.push_back(coordinates(col, row - 2));
						}
					}
					// If enemy is on a killable tile
					if(_board[row - 1][col - 1]->getColor() == BLACK)
					{
						validMoves.push_back(coordinates(col - 1, row - 1));
					}
					if(_board[row - 1][col + 1]->getColor() == BLACK)
					{
						validMoves.push_back(coordinates(col + 1, row - 1));
					}
				}
				else
					std::cout << "Cannot move!" << endl;
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
					validMoves.push_back(coordinates(col, row + 1));
				}
				// If pawn is on a starting position
				if(piece->isMoved() == false)
				{
					if(_board[row + 1][col]->getType() == EMPTYTILE && _board[row + 2][col]->getType() == EMPTYTILE)
					{
						validMoves.push_back(coordinates(col, row + 2));
					}
				}
				// If enemy is on a killable FREE
				if(_board[row + 1][col + 1]->getColor() == WHITE)
				{
					validMoves.push_back(coordinates(col + 1, row + 1));
				}
			}
			// If the pawn is on the right side column
			else if(col == 7)
			{
				// Basic one or two moves in front, default situation
				if(_board[row + 1][col]->getType() == EMPTYTILE)
				{
					validMoves.push_back(coordinates(col, row + 1));
				}
				// If pawn has not moved before
				if(piece->isMoved() == false)
				{
					if(_board[row + 1][col]->getType() == EMPTYTILE && _board[row + 2][col]->getType() == EMPTYTILE)
					{
						validMoves.push_back(coordinates(col, row + 2));
					}
				}
				// If enemy is on a killable FREE
				if(_board[row + 1][col - 1]->getColor() == WHITE)
				{
					validMoves.push_back(coordinates(col - 1, row + 1));
				}
			}
			// Pawn is not on the side columns
			else
			{
				if(_board[row + 1][col]->getType() == EMPTYTILE)
				{
					validMoves.push_back(coordinates(col, row + 1));
				}
				if(piece->isMoved() == false)
				{
					if(_board[row + 1][col]->getType() == EMPTYTILE && _board[row + 2][col]->getType() == EMPTYTILE)
					{
						validMoves.push_back(coordinates(col, row + 2));
					}
				}
				// If enemy is on a killable FREEs
				if(_board[row + 1][col - 1]->getColor() == WHITE)
				{
					validMoves.push_back(coordinates(col - 1, row + 1));
				}
				if(_board[row + 1][col + 1]->getColor() == WHITE)
				{
					validMoves.push_back(coordinates(col + 1, row + 1));
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
					validMoves.push_back(coordinates(col - i, row));
				}
				else
				{
					if(_board[row][col - i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(coordinates(col - i, row));
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
					validMoves.push_back(coordinates(col + i, row));
				}
				else
				{
					if(_board[row][col + i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(coordinates(col + i, row));
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
					validMoves.push_back(coordinates(col, row - i));
				}
				else
				{
					if(_board[row - i][col]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(coordinates(col, row - i));
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
					validMoves.push_back(coordinates(col, row + i));
				}
				else
				{
					if(_board[row + i][col]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(coordinates(col, row + i));
						break;
					}
				}
			}
		}
	}
	// Bishop, both colors
	else if(type == BISHOP)
	{
		// Left up diagonal			
		for(int i = 1; i <= 7; i++)
		{

			if(col - i >= 0 && row - i >= 0)
			{
				if(_board[row - i][col - i]->getType() == EMPTYTILE)
				{
					validMoves.push_back(coordinates(col - i, row - i));
				}
				else
				{
					if(_board[row - i][col - i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(coordinates(col - i, row - i));
						break;
					}
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
					validMoves.push_back(coordinates(col + i, row - i));
				}
				else
				{
					if(_board[row - i][col + i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(coordinates(col + i, row - i));
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
					validMoves.push_back(coordinates(col + i, row + i));
				}
				else
				{
					if(_board[row + i][col + i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(coordinates(col + i, row + i));
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
					validMoves.push_back(coordinates(col - i, row + i));
				}
				else
				{
					if(_board[row + i][col - i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(coordinates(col - i, row + i));
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
				validMoves.push_back(coordinates(col - 2, row + 1));
			}
		}
		if(col - 2 >= 0 && row - 1 >= 0)
		{
			if(_board[row - 1][col - 2]->getColor() != color)
			{
				validMoves.push_back(coordinates(col - 2, row - 1));
			}
		}
		// Up
		if(col - 1 >= 0 && row - 2 >= 0)
		{
			if(_board[row - 2][col - 1]->getColor() != color)
			{
				validMoves.push_back(coordinates(col - 1, row - 2));
			}
		}
		if(col + 1 <= 7 && row - 2 >= 0)
		{
			if(_board[row - 2][col + 1]->getColor() != color)
			{
				validMoves.push_back(coordinates(col + 1, row - 2));
			}
		}
		// Right
		if(col + 2 <= 7 && row - 1 >= 0)
		{
			if(_board[row - 1][col + 2]->getColor() != color)
			{
				validMoves.push_back(coordinates(col + 2, row - 1));
			}
		}
		if(col + 2 <= 7 && row + 1 <= 7)
		{
			if(_board[row + 1][col + 2]->getColor() != color)
			{
				validMoves.push_back(coordinates(col + 2, row + 1));
			}
		}
		// Down
		if(col - 1 >= 0 && row + 2 <= 7)
		{
			if(_board[row + 2][col - 1]->getColor() != color)
			{
				validMoves.push_back(coordinates(col - 1, row + 2));
			}
		}
		if(col + 1 <= 7 && row + 2 <= 7)
		{
			if(_board[row + 2][col + 1]->getColor() != color)
			{
				validMoves.push_back(coordinates(col + 1, row + 2));
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
					validMoves.push_back(coordinates(col - i, row));
				}
				else
				{
					if(_board[row][col - i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(coordinates(col - i, row));
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
					validMoves.push_back(coordinates(col + i, row));
				}
				else
				{
					if(_board[row][col + i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(coordinates(col + i, row));
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
					validMoves.push_back(coordinates(col, row - i));
				}
				else
				{
					if(_board[row - i][col]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(coordinates(col, row - i));
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
					validMoves.push_back(coordinates(col, row + i));
				}
				else
				{
					if(_board[row + i][col]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(coordinates(col, row + i));
						break;
					}
				}
			}
		}
		// Left up diagonal			
		for(int i = 1; i <= 7; i++)
		{

			if(col - i >= 0 && row - i >= 0)
			{
				if(_board[row - i][col - i]->getType() == EMPTYTILE)
				{
					validMoves.push_back(coordinates(col - i, row - i));
				}
				else
				{
					if(_board[row - i][col - i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(coordinates(col - i, row - i));
						break;
					}
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
					validMoves.push_back(coordinates(col + i, row - i));
				}
				else
				{
					if(_board[row - i][col + i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(coordinates(col + i, row - i));
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
					validMoves.push_back(coordinates(col + i, row + i));
				}
				else
				{
					if(_board[row + i][col + i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(coordinates(col + i, row + i));
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
					validMoves.push_back(coordinates(col - i, row + i));
				}
				else
				{
					if(_board[row + i][col - i]->getColor() == color)
					{
						break;
					}
					else
					{
						validMoves.push_back(coordinates(col - i, row + i));
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
		// Left up diagonal
		vector<Piece*> surroundingTiles;

		if(col - 1 >= 0 && row - 1 >= 0)
		{
			surroundingTiles.push_back(_board[row - 1][col - 1]);
		}
		// Left down diagonal
		else if(col - 1 >= 0 && row + 1 <= 7)
		{
			surroundingTiles.push_back(_board[row + 1][col - 1]);
		}
		// Right up diagonal
		if(col + 1 <= 7 && row - 1 >= 0)
		{
			surroundingTiles.push_back(_board[row - 1][col + 1]);

		}
		// Right down diagonal
		if(col + 1 <= 7 && row + 1 <= 7)
		{
			surroundingTiles.push_back(_board[row + 1][col + 1]);
		}
		// Left
		if(col - 1 >= 0)
		{
			surroundingTiles.push_back(_board[row][col - 1]);
		}
		// Up
		if(row - 1 >= 0)
		{
			surroundingTiles.push_back(_board[row - 1][col]);

		}
		// Right
		if(col + 1 <= 7)
		{
			surroundingTiles.push_back(_board[row][col + 1]);

		}
		// Down
		if(row + 1 <= 7)
		{
			surroundingTiles.push_back(_board[row + 1][col]);
		}

		auto suitableTiles = removeNonKingableTiles(surroundingTiles, color);
		for(int i = 0; i < suitableTiles.size(); i++)
		{
			validMoves.push_back(suitableTiles[i]->getCoordinates());
		}

		// Check for castling 
		// To left
		
		auto castlingTiles = getSuitableCastlingTiles(piece);
		for(int i = 0; i < castlingTiles.size(); i++)
		{
			validMoves.push_back(castlingTiles[i]);
		}		
	}
	cout << "avilable move size: " << validMoves.size() << endl;
	return validMoves;	
}


vector<coordinates> chessBoardManager::getSuitableCastlingTiles(Piece* king)
{	
	int kingRow = king->getCoordinates().getBoardRowIndex();
	int kingColumn = king->getCoordinates().getBoardColumnIndex();
	vector<coordinates> suitableTiles;

	if(king->isMoved() == false && _board[kingRow][0]->getType() == ROOK && _board[kingRow][0]->isMoved() == false)
	{
		int offset = -2; // target tile offset (2 tiles to the left from the king for both colors)
		bool canCastle = true; // initialize castling to true, try to change it to false in the following iterative checks
		for(int i = 1; i < 4; i++)
		{
			Piece* tile = _board[kingRow][kingColumn - i];
			auto threatVector = tile->getThreatVector();
			bool tileUnderEnemyThreat = false;
			for(int i = 0; i < tile->getThreatVector().size(); i++)
			{
				if(threatVector[i]->getColor() != king->getColor())
					tileUnderEnemyThreat = true;
			}

			if(tile->getType() != EMPTYTILE || tileUnderEnemyThreat == true)
			{// piece is blocked by a piece or is under enemy threat 
				canCastle = false;
				break;
			}
		}
		if(canCastle)
		{
			suitableTiles.push_back(coordinates(kingColumn + offset, kingRow));
		}
	}

	// To right
	if(king->isMoved() == false && _board[kingRow][7]->getType() == ROOK && _board[kingRow][7]->isMoved() == false)
	{
		int offset = 2; // target tile offset (2 tiles to the right from the king for both colors)
		bool canCastle = true; // initialize castling to true, try to change it to false in the following iterative checks
		for(int i = 1; i < 3; i++)
		{
			Piece* tile = _board[kingRow][kingColumn + i];
			auto threatVector = tile->getThreatVector();
			bool tileUnderEnemyThreat = false;
			for(int i = 0; i < tile->getThreatVector().size(); i++)
			{
				if(threatVector[i]->getColor() != king->getColor())
					tileUnderEnemyThreat = true;
			}

			if(tile->getType() != EMPTYTILE || tileUnderEnemyThreat == true)
			{// piece is blocked by a piece or is under enemy threat 
				canCastle = false;
				break;
			}
		}
		if(canCastle)
		{
			suitableTiles.push_back(coordinates(kingColumn + offset, kingRow));
		}
	}
	return suitableTiles;

}

vector<Piece*> removeNonKingableTiles(vector<Piece*> tiles, int color) {
	vector<Piece*> suitableTiles;
	for(int i = 0; i < tiles.size(); i++)
	{
		auto target = tiles[i];
		bool threat = false;
		// If the position is free or contains an enemy
		if(target->getType() == EMPTYTILE || target->getColor() != color)
		{
			// Check if it is also under threat
			for(int i = 0; i < target->getThreatVector().size(); i++)
			{
				// Get targeted piece's threat vector that contains threat colors
				int threatColor = target->getThreatVector()[i]->getColor();
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
				suitableTiles.push_back(target);
			}
		}
	}
	return suitableTiles;
}

void chessBoardManager::addPlayer(Player* p) {
	_players.push_back(p);
}

vector<Player*> chessBoardManager::getPlayers() {
	return _players;
}


void chessBoardManager::printBoard(Board* board, bool simulation) {
	/* Function for printing the game board every turn */
	int simuColor = 3;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// TODO: ADD THREATS ON BOARD 

	COORD coord;
	coord.X = 0;
	coord.Y = 0;

	SetConsoleCursorPosition(hConsole, coord);

	//system("CLS");
	if(simulation)
		SetConsoleTextAttribute(hConsole, 3);

	std::cout << "\n\t\t  A  B  C  D  E  F  G  H" << endl;
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

			if((j + i + 1) % 2 == 0)
				TILE_COLOR = BACKGROUND_BLUE;
			else
				TILE_COLOR = BACKGROUND_BLUE | BACKGROUND_INTENSITY;


			if(j == 0)
				std::cout << "\t\t ";
			if(piece->getType() == EMPTYTILE)
			{
				SetConsoleTextAttribute(hConsole, TILE_COLOR);
				std::cout << "   ";
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
				std::cout << " " << numToPiece(piece->getType()) << /* piece->getColor() */  " ";
			}
			if(simulation)
				SetConsoleTextAttribute(hConsole, 3); // light blue, cyan
			else
				SetConsoleTextAttribute(hConsole, 15);
			if(j == 7)
				std::cout << " " << i + 1 << endl;
		}
	}
	std::cout << endl;
	std::cout << endl;
}

extern int charToInt(char c);

bool chessBoardManager::checkForMate(Player* realPlayer) {
	// Create a temporary chessboard for simulating all possible moves for next turn
	std::cout << "Entering mate simulation.." << endl;

	Piece* king;
	bool simulationResult = false;
	bool isChecked = true;
	auto tempBoard = this->_board;

	vector<Piece*> pieces = realPlayer->getPieces();
	for(int i = 0; i < pieces.size(); i++)
	{
		if(pieces[i]->getType() == KING)
		{
			king = pieces[i];
		}
	}

	std::cout << "Checking for mate status..." << endl;

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

	std::cout << "================ SIMULATION ================ " << endl;

	printBoard(simBoardMgr->getBoard(), true);


	vector<Piece*> simPieces = simCurrentPlayer->getPieces();

	for(int i = 0; i < simPieces.size(); i++)
	{
		Piece* pc = simPieces[i];
		vector<coordinates> moves = simBoardMgr->calculateAvailableMovesForPiece(pc);

		for(int j = 0; j < moves.size(); j++)
		{
			coordinates coords = pc->getCoordinates();
			coordinates startCoords = coords;
			coordinates endCoords = moves[j];

			if(simBoardMgr->simulateMove(simCurrentPlayer, startCoords, endCoords) == true)
			{
				isChecked = simCurrentPlayer->isChecked();
				if(!isChecked) // game is not checkmate -> we can return
					break;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(50));

		};
		if(!isChecked) // not checked -> there is a move that makes checkmate 
			break;
	}

	printBoard(simBoardMgr->getBoard(), false);
	simulationResult = isChecked;
	std::cout << "================ END OF SIMULATION ================ " << endl;

	/* if king is STILL threatened -> mate */

	return simulationResult;
}

Board* chessBoardManager::getBoard(void) {
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
	std::cout << "Checking if player " << player->toString() << " is checked.." << endl;
#endif
	size_t kingThreatsCount = 0;
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


void chessBoardManager::calculateAllPossibleMoves(Player* p) {
	int color = p->getColor();
	vector<coordinates> moves;
	vector<coordinates> availableMoves;

	std::cout << "updating all possible moves for player " << to_string(p->getColor()) << endl;
	for(int i = 0; i <= 7; i++)
	{
		for(int j = 0; j <= 7; j++)
		{
			if(_board[i][j]->getColor() == color)
			{
				Piece* piece = _board[i][j];

				// Get piece's possible movements
				availableMoves = calculateAvailableMovesForPiece(piece);
				moves.insert(moves.end(), availableMoves.begin(), availableMoves.end());
				piece->setAvailableMoves(moves);
			}
		}
	}
}

