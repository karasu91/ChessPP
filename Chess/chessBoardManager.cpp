#include <vector>
#include <thread>
#include "chessBoard.h"
#include "Piece.h"


// Between or equal
bool boeq(int compare, int lhs, int rhs) {
	return compare >= lhs && compare <= rhs;
}

chessBoardManager::chessBoardManager() {

	if (_hConsoleHandle == NULL)
		_hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i <= 7; i++)
		_board.push_back(std::vector<std::shared_ptr<Piece>>(8));

	// Set the whole board completely empty
	for (int row = 0; row <= 7; row++) {
		for (int col = 0; col <= 7; col++) {
			_board[row][col] = std::make_shared<EmptyPiece>(EmptyPiece(Coordinates(col, row)));
		}
	}
}

chessBoardManager::~chessBoardManager() {
	for (int i = 0; i < _players.size(); i++)
		delete _players[i];
	_players.clear();
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

int convertRowCharToIndex(std::string row) {
	return atoi(row.c_str()) - 1;
}

std::string convertRowIndexToChar(int row) {
	return std::to_string(row + 1);
}
// Initialize the board with players' pieces
void chessBoardManager::initBoard(Player* p) {
	
	auto playerPieces = p->getPieces();

	for (int i = 0; i < playerPieces.size(); i++) {
		Coordinates coords = playerPieces[i]->getCoordinates();
		int row = coords.getBoardRowIndex();
		int column = coords.getBoardColumnIndex();
		_board[row][column] = playerPieces[i];
	}

	int a = 1;
}

std::shared_ptr<Piece> chessBoardManager::getPiece(int row, int column) {
	return _board[row][column];
}

void chessBoardManager::upgradePawnCheck(std::shared_ptr<Piece> pawn) {
	char selection;
	Coordinates coords = pawn->getCoordinates();
	int row = coords.getBoardRowIndex();
	bool selection_ok = false;
	
	if ((row == 0 && pawn->getColor() == Colors::WHITE) || 
		(row == 7 && pawn->getColor() == Colors::BLACK)) 
	{
		// Find the index in the owner player's list which contains the selected piece. This needs to be updated after the pointer has been upgraded.
		Player* owner = pawn->getOwner();
		auto pieces = owner->getPieces();
		int ownerIndex = 0;

		for (int i = 0; i < pieces.size(); i++)
		{
			if (pieces[i] == pawn)
			{
				ownerIndex = i;
				break;
			}
		}





		while (selection_ok == false)
		{
			std::cout << "Select piece type [H B R Q]: " << std::endl;
			std::cin >> selection;

			PieceType newType;
			switch (selection) {
			case 'P':
				selection_ok = true;
				break;
			case 'H':
				pawn = std::make_shared<Knight>(Knight(*pawn)); 
				selection_ok = true;
				break;
			case 'B':
				pawn = std::make_shared<Bishop>(Bishop(*pawn));
				selection_ok = true;
				break;
			case 'R':
				pawn = std::make_shared<Rook>(Rook(*pawn));
				selection_ok = true;
				break;
			case 'Q':				
				pawn = std::make_shared<Queen>(Queen(*pawn));		
				selection_ok = true;
				break;
			default:
				std::cout << "Invalid selection!" << std::endl;
			}			
		}	
		// Update pointer in chessboard
		_board[row][coords.getBoardColumnIndex()] = pawn;

		// Then update owner's pointer
		//owner->updatePieceAt(pawn, ownerIndex);
		*(owner->getPieces())[ownerIndex] = *pawn;

		std::cout << "Pawn is now upgraded to (on board): " << _board[row][coords.getBoardColumnIndex()]->toString() << std::endl;
		std::cout << "Pawn is now upgraded to (on owner): " << owner->getPieces()[ownerIndex]->toString() << std::endl;
		printBoard(_board, false);
		updateGameState();
	}
}

void chessBoardManager::updateGameState() {
	auto players = getPlayers();

	// Assigns every threat into all pieces on the board
	recalculatePieceThreats();

	for (int i = 0; i < players.size(); i++)
		updatePlayerCheckedStatus(players[i]);
}


void chessBoardManager::setPieceTo(std::shared_ptr<Piece> piece, Coordinates finalCoords, bool simulate, bool updateState) {
	auto startCoordinates = piece->getCoordinates();
	int startRow = startCoordinates.getBoardRowIndex();
	int startColumn = startCoordinates.getBoardColumnIndex();
	int endRow = finalCoords.getBoardRowIndex();
	int endColumn = finalCoords.getBoardColumnIndex();

	if (!simulate) {
#if _DEBUG
		std::cout << "NOT simulating movement!" << std::endl;
#endif
		piece->setCoordinates(finalCoords);
		piece->setMoved(true);

		// Delete actual piece (that is not empty) board position
		//if (_board[endRow][endColumn]->getType() != PieceType::EMPTY)
		_board[endRow][endColumn] = piece;

		// Move piece to the destination
		//_board[endRow][endColumn] = std::move(piece);

		// Assign empty tile to the piece's starting position now as it is free
		_board[startRow][startColumn] = std::make_shared<EmptyPiece>(EmptyPiece(Coordinates(startColumn, startRow)));

		if (updateState) {
			printBoard(_board, false);
			updateGameState();
		}
	}
	else {
#if _DEBUG
		std::cout << "Simulating movement!" << std::endl;
#endif
		std::shared_ptr<Piece> cacheTargetTile = _board[endRow][endColumn];

		piece->setCoordinates(finalCoords);

		_board[endRow][endColumn] = piece;
		_board[startRow][startColumn] = EmptyPiece(Coordinates(startColumn, startRow)).Clone();

#if _NDEBUG
		printBoard(_board, true);
#endif
		updateGameState();

		//_board[startRow][startColumn].release();
		_board[startRow][startColumn] = piece;
		_board[endRow][endColumn] = cacheTargetTile;
		piece->setCoordinates(startCoordinates);
	}
}

/* This function always runs the board empty of threat
	and then recalculates every piece's threat */
void chessBoardManager::recalculatePieceThreats(void) {
	PieceType type;
	Colors color;

	for (int i = 0; i <= 7; i++)
		for (int j = 0; j <= 7; j++)
			_board[i][j]->resetThreatVector();

	for (int i = 0; i <= 7; i++) {
		for (int j = 0; j <= 7; j++) {
			std::shared_ptr<Piece> threat = _board[i][j];
			color = threat->getColor();
			type = threat->getType();

			if (type == PieceType::PAWN) {
				if (color == Colors::WHITE) {
					// If the pawn is on the left side column
					if (j == 0) {
						if (i - 1 >= 0)
						{
							// If enemy is on a killable tile
							if (_board[i - 1][j + 1]->getColor() != color)
							{
								_board[i - 1][j + 1]->addThreat(threat);
							}
						}
					}
					// If the pawn is on the right side column
					else if (j == 7) {
						if (i - 1 >= 0)
							if (_board[i - 1][j - 1]->getColor() != color) {
								_board[i - 1][j - 1]->addThreat(threat);
							}
					}
					// Pawn is not on the side columns
					else {
						if (i - 1 >= 0) {
							// Add threat to tiles that are under threat (row +-1 depending on color; column +-1)
							if (_board[i - 1][j - 1]->getColor() != color) {
								_board[i - 1][j - 1]->addThreat(threat);
							}
							if (_board[i - 1][j + 1]->getColor() != color) {
								_board[i - 1][j + 1]->addThreat(threat);
							}
						}
					}
				}
				else if (color == Colors::BLACK) {
					// If the pawn is on the	 left side column
					if (j == 0) {
						if (i + 1 <= 7)
							// If enemy is on a killable tile
							if (_board[i + 1][j + 1]->getColor() != color) {
								_board[i + 1][j + 1]->addThreat(threat);
							}
					}
					// If the pawn is on the right side column
					else if (j == 7) {
						if (i + 1 <= 7)
							if (_board[i + 1][j - 1]->getColor() != color) {
								_board[i + 1][j - 1]->addThreat(threat);
							}
					}
					// Pawn is not on the side columns
					else {
						if (i + 1 <= 7) {
							// If enemy is on a killable	 tile
							if (_board[i + 1][j - 1]->getColor() != color) {
								_board[i + 1][j - 1]->addThreat(threat);
							}
							if (_board[i + 1][j + 1]->getColor() != color) {
								_board[i + 1][j - 1]->addThreat(threat);
							}
						}
					}
				}
			}
			// Rook
			else if (type == PieceType::ROOK) {
				for (int k = 1; k <= 7; k++) {
					// Left
					if (j - k >= 0) {
						if (_board[i][j - k]->getType() == PieceType::EMPTY) {
							_board[i][j - k]->addThreat(threat);
						}
						else {
							_board[i][j - k]->addThreat(threat);
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Right
					if (j + k <= 7) {
						if (_board[i][j + k]->getType() == PieceType::EMPTY) {
							_board[i][j + k]->addThreat(threat);
						}
						else {
							_board[i][j + k]->addThreat(threat);
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Up
					if (i - k >= 0) {
						if (_board[i - k][j]->getType() == PieceType::EMPTY) {
							_board[i - k][j]->addThreat(threat);
						}
						else {
							_board[i - k][j]->addThreat(threat);
							break;
						}
					}
				}

				for (int k = 1; k <= 7; k++) {
					// Down

					if (i + k <= 7) {
						if (_board[i + k][j]->getType() == PieceType::EMPTY) {
							_board[i + k][j]->addThreat(threat);
						}
						else {
							_board[i + k][j]->addThreat(threat);
							break;
						}
					}
				}
			}
			// Bishop, both colors
			else if (type == PieceType::BISHOP) {
				for (int k = 1; k <= 7; k++) {
					// Left up diagonal
					if (j - k >= 0 && i - k >= 0) {
						if (_board[i - k][j - k]->getType() == PieceType::EMPTY) {
							_board[i - k][j - k]->addThreat(threat);
						}
						else {
							_board[i - k][j - k]->addThreat(threat);
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Right up diagonal
					if (j + k <= 7 && i - k >= 0) {
						if (_board[i - k][j + k]->getType() == PieceType::EMPTY) {
							_board[i - k][j + k]->addThreat(threat);
						}
						else {
							_board[i - k][j + k]->addThreat(threat);
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					//	Right down di	agonal
					if (j + k <= 7 && i + k <= 7) {
						if (_board[i + k][j + k]->getType() == PieceType::EMPTY) {
							_board[i + k][j + k]->addThreat(threat);
						}
						else {
							_board[i + k][j + k]->addThreat(threat);
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					//	Left down diagonal
					if (j - k >= 0 && i + k <= 7) {
						if (_board[i + k][j - k]->getType() == PieceType::EMPTY) {
							_board[i + k][j - k]->addThreat(threat);
						}
						else {
							_board[i + k][j - k]->addThreat(threat);
							break;
						}
					}
				}
			}
			// Horse, both colors
			else if (type == PieceType::KNIGHT) {
				// Left
				if (j - 2 >= 0 && i + 1 <= 7)
					_board[i + 1][j - 2]->addThreat(threat);
				if (j - 2 >= 0 && i - 1 >= 0)
					_board[i - 1][j - 2]->addThreat(threat);
				// Up
				if (j - 1 >= 0 && i - 2 >= 0)
					_board[i - 2][j - 1]->addThreat(threat);
				if (j + 1 <= 7 && i - 2 >= 0)
					_board[i - 2][j + 1]->addThreat(threat);
				// Right
				if (j + 2 <= 7 && i - 1 >= 0)
					_board[i - 1][j + 2]->addThreat(threat);
				if (j + 2 <= 7 && i + 1 <= 7)
					_board[i + 1][j + 2]->addThreat(threat);
				// Down
				if (j - 1 >= 0 && i + 2 <= 7)
					_board[i + 2][j - 1]->addThreat(threat);
				if (j + 1 <= 7 && i + 2 <= 7)
					_board[i + 2][j + 1]->addThreat(threat);
			}
			// Queen, both colors
			else if (type == PieceType::QUEEN) {
				for (int k = 1; k <= 7; k++) {
					// Left
					if (j - k >= 0)
						if (_board[i][j - k]->getType() == PieceType::EMPTY) {
							_board[i][j - k]->addThreat(threat);
						}
						else {
							_board[i][j - k]->addThreat(threat);
							break;
						}
				}
				for (int k = 1; k <= 7; k++) {
					// Right
					if (j + k <= 7) {
						if (_board[i][j + k]->getType() == PieceType::EMPTY) {
							_board[i][j + k]->addThreat(threat);
						}
						else {
							_board[i][j + k]->addThreat(threat);
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Up
					if (i - k >= 0) {
						if (_board[i - k][j]->getType() == PieceType::EMPTY) {
							_board[i - k][j]->addThreat(threat);
						}
						else {
							_board[i - k][j]->addThreat(threat);
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Down
					if (i + k <= 7) {
						if (_board[i + k][j]->getType() == PieceType::EMPTY) {
							_board[i + k][j]->addThreat(threat);
						}
						else {
							_board[i + k][j]->addThreat(threat);
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Left up diagonal
					if (j - k >= 0 && i - k >= 0) {
						if (_board[i - k][j - k]->getType() == PieceType::EMPTY) {
							_board[i - k][j - k]->addThreat(threat);
						}
						else {
							_board[i - k][j - k]->addThreat(threat);
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Right up diagonal
					if (j + k <= 7 && i - k >= 0) {
						if (_board[i - k][j + k]->getType() == PieceType::EMPTY) {
							_board[i - k][j + k]->addThreat(threat);
						}
						else {
							_board[i - k][j + k]->addThreat(threat);
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Right down diagonal
					if (j + k <= 7 && i + k <= 7) {
						if (_board[i + k][j + k]->getType() == PieceType::EMPTY) {
							_board[i + k][j + k]->addThreat(threat);
						}
						else {
							_board[i + k][j + k]->addThreat(threat);
							break;
						}
					}
				}
				for (int k = 1; k <= 7; k++) {
					// Left down diagonal
					if (j - k >= 0 && i + k <= 7) {
						if (_board[i + k][j - k]->getType() == PieceType::EMPTY) {
							_board[i + k][j - k]->addThreat(threat);
						}
						else {
							_board[i + k][j - k]->addThreat(threat);
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

// Returns true/false depending on whether the move was successful or not.
bool chessBoardManager::tryMove(std::shared_ptr<Piece> piece, Coordinates target, bool simulate) {
	piece->calculateAvailableMoves(_board);
	auto availableMoves = piece->getAvailableMoves();
	auto pieceType = piece->getType();

	if (availableMoves.size() > 0) {
		int targetRow = target.getBoardRowIndex();
		int targetColumn = target.getBoardColumnIndex();

		// If targeted tile is within board limits
		if (boeq(targetRow, 0, 7) && boeq(targetColumn, 0, 7) && availableMoves.size() > 0) {
			// Make string indicator from the targeted tile so we can compare it with available moves
			Coordinates targetTile = Coordinates(targetColumn, targetRow);

#if _DEBUG
			std::cout << piece->toString() << " available moves: [";
			for (int i = 0; i < availableMoves.size(); i++) {
				std::cout << availableMoves[i].toCharString();
				if (i < availableMoves.size() - 1)
					std::cout << ", ";
			}

			std::cout << "], target tile: " << targetTile.toCharString() << std::endl;
#endif

			// Check if the targeted tile is in available moves. If yes -> move
			for (int i = 0; i < availableMoves.size(); i++) {
				if (availableMoves[i] == targetTile) {
					if (pieceType != PieceType::KING && pieceType != PieceType::PAWN) // avoid checking for castling or en passant
						setPieceTo(piece, Coordinates(targetColumn, targetRow), simulate, true);

					if (pieceType == PieceType::PAWN) {
						int sd = piece->getColor() == Colors::WHITE ? -1 : 1; // scandirection
						Coordinates coords = piece->getCoordinates();
						bool movesTwo = abs(targetRow - coords.getBoardRowIndex()) == 2;
						if (movesTwo)
							piece->enPassantable = true;
						// Do en passant move if possible
						int pawnRow = targetRow - sd;
						if (targetColumn != coords.getBoardColumnIndex() && _board[pawnRow][targetColumn]->enPassantable == true) {
							_board[pawnRow][targetColumn].reset();
							_board[pawnRow][targetColumn] = std::make_shared<EmptyPiece>(EmptyPiece(Coordinates(targetColumn, pawnRow)));
							printBoard(_board, false);
							setPieceTo(piece, Coordinates(targetColumn, targetRow), simulate, true);
						}
						else {
							setPieceTo(piece, Coordinates(targetColumn, targetRow), simulate, true);
							// Promote pawn check
							upgradePawnCheck(piece);							
						}

						// Reset en passant status after moving the piece
						if (piece->enPassantable == true && !movesTwo)
							piece->enPassantable = false;
					}
					else if (pieceType == PieceType::KING) {
						std::shared_ptr<Rook> rook;
						// check if the target coordinates equal coordinates for castling equivalent move
						if (abs(targetColumn - piece->getCoordinates().getBoardColumnIndex()) == 2) {
							std::cout << "Castling..." << std::endl;
							// move king
							setPieceTo(piece, Coordinates(targetColumn, targetRow), simulate, false);

							// move rook
							if (targetColumn == 2) {

								setPieceTo(_board[targetRow][0], Coordinates(targetColumn + 1, targetRow), simulate, true);
							}
							else if (targetColumn == 6) {
								setPieceTo(_board[targetRow][7], Coordinates(targetColumn - 1, targetRow), simulate, true);
							}
						}
						else
							setPieceTo(piece, Coordinates(targetColumn, targetRow), simulate, true);
					}
					return true;
				}
			}
			std::cout << "Invalid move!" << std::endl;
			return false;
		}
		// Else break cycle
		else {
			std::cout << "Target selection is faulty!, try again! (out of bounds)" << std::endl;
		}
	}
	else {
		std::cout << "Cannot move this piece! (available moves count is 0)" << std::endl;
	}
	return false;
}

bool chessBoardManager::validateAndMove(Player* player, Coordinates startCoord, Coordinates targetCoord) {
	std::cout << "Turn: [" << turnNumber << "]" << std::endl;
	int startrow = startCoord.getBoardRowIndex();
	int startColumn = startCoord.getBoardColumnIndex();
	std::shared_ptr<Piece> tempPiece = getPiece(startrow, startColumn);

	std::cout << player->toCharString() << " selecting piece from tile: " << startCoord.toCharString() << "(" << tempPiece->toString() << ")" << std::endl;
	

	if (tempPiece != NULL) {
		if (tempPiece->getColor() != player->getColor()) {
			std::cout << "Selected piece is not valid!" << std::endl;
			return false;
		}

		while (true) 
			if (tryMove(tempPiece, targetCoord, false) == true) 
			{
				// Check if checkmate (start simulation process)
				if (player->getOpponent()->isChecked() == true) {
					bool isMate = checkForMate(player->getOpponent());
					std::cout << "Checkmate simulation result: " << isMate << std::endl;
					if (isMate == true) {
						player->isWinner = true;
						gameOver = true;
					}
				}
				printBoard(_board, false);
				turnNumber++;
				return true;
			}
			else
				return false;
		
	}
	return false;
}

bool chessBoardManager::simulateMove(Player* player, Coordinates startCoord, Coordinates targetCoord) {
	int startrow = startCoord.getBoardRowIndex();
	int startColumn = startCoord.getBoardColumnIndex();
	std::shared_ptr<Piece> tempPiece = getPiece(startrow, startColumn);

	if (tempPiece != NULL) {
		if (!(tempPiece->getColor() == player->getColor())) {
			std::cout << "Selected piece is not valid!" << std::endl;
			return false;
		}
		tryMove(tempPiece, targetCoord, true);
		return true;
	}
	return false;
}


void chessBoardManager::addPlayer(Player* p) {
	_players.push_back(p);
}

std::vector<Player*> chessBoardManager::getPlayers() {
	return _players;
}

// Function for printing the game board every turn
void chessBoardManager::printBoard(std::vector<std::vector<std::shared_ptr<Piece>>> board, bool simulation) {
	
	int simuColor = 3;
	

	// TODO: ADD THREATS ON BOARD	
#if _NDEBUG
	SetConsoleCursorPosition(_hConsoleHandle, _resetCoordinates);
#endif
	//system("CLS");
	if (simulation)
		SetConsoleTextAttribute(_hConsoleHandle, 3);

	std::cout << "\n\t\t  A  B  C  D  E  F  G  H" << std::endl;
	int TILE_COLOR;

	int COLOR_BLACK = 16;
	int COLOR_WHITE = 23;
	int COLOR_EVILRED = 4;
	int COLOR_GREEN = 2;

	char pipe = (char) 179;

	for (int i = 0; i <= 7; i++) {
		for (int j = 0; j <= 7; j++) {
			std::shared_ptr<Piece> piece = board[i][j];

			if ((j + i + 1) % 2 == 0)
				TILE_COLOR = BACKGROUND_BLUE;
			else
				TILE_COLOR = BACKGROUND_BLUE | BACKGROUND_INTENSITY;

			if (j == 0)
				std::cout << "\t\t ";
			if (piece->getType() == PieceType::EMPTY) {
				SetConsoleTextAttribute(_hConsoleHandle, TILE_COLOR);
				std::cout << "   ";
			}
			else {
				switch (piece->getColor()) {
				case Colors::WHITE:
					SetConsoleTextAttribute(_hConsoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | TILE_COLOR);
					break;
				case Colors::BLACK:
					SetConsoleTextAttribute(_hConsoleHandle, TILE_COLOR);
					break;
				default:
					SetConsoleTextAttribute(_hConsoleHandle, COLOR_BLACK | TILE_COLOR);
				}
				std::cout << " " << numToPiece(piece->getType()) << /* piece->getColor() */  " ";
			}
			if (simulation)
				SetConsoleTextAttribute(_hConsoleHandle, 3); // light blue, cyan
			else
				SetConsoleTextAttribute(_hConsoleHandle, 15);
			if (j == 7)
				std::cout << " " << i + 1 << std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

bool chessBoardManager::checkForMate(Player* realPlayer) {
	// Create a temporary chessboard for simulating all possible moves for next turn
	std::cout << "Entering mate simulation.." << std::endl;

	std::shared_ptr<Piece> king;
	bool simulationResult = false;
	bool isChecked = true;
	auto tempBoard = this->_board;

	auto pieces = realPlayer->getPieces();
	for (int i = 0; i < pieces.size(); i++) {
		if (pieces[i]->getType() == PieceType::KING) {
			king = pieces[i];
		}
	}

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

	std::cout << "================ SIMULATION ================ " << std::endl;

	//printBoard(simBoardMgr->getBoard(), true);

	auto simPieces = simCurrentPlayer->getPieces();

	for (int i = 0; i < simPieces.size(); i++) {
		std::shared_ptr<Piece> pc = simPieces[i];
		pc->calculateAvailableMoves(_board);
		auto moves = pc->getAvailableMoves();

		for (int j = 0; j < moves.size(); j++) {
			Coordinates coords = pc->getCoordinates();
			Coordinates startCoords = coords;
			Coordinates endCoords = moves[j];

			if (simBoardMgr->simulateMove(simCurrentPlayer, startCoords, endCoords) == true) {
				isChecked = simCurrentPlayer->isChecked();
				if (!isChecked) // game is not checkmate -> we can return
					break;
			}
#if _DEBUG
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
#endif
		};
		if (!isChecked) // not checked -> there is a move that makes checkmate
			break;
	}

	simulationResult = isChecked;
	std::cout << "================ END OF SIMULATION ================ " << std::endl;

	/* if king is STILL threatened -> mate */
	return simulationResult;
}

std::vector<std::vector<std::shared_ptr<Piece>>> chessBoardManager::getBoard(void) {
	return _board;
}

std::string chessBoardManager::numToPiece(PieceType type) {
	std::string piece;
	if (type == PieceType::EMPTY) {
		piece = "-";
	}
	if (type == PieceType::PAWN) {
		piece = (char) 254;// pawn
	}
	if (type == PieceType::ROOK) {
		piece = (char) 227; // rook
	}
	if (type == PieceType::KNIGHT) {
		piece = (char) 226;// horse
	}
	if (type == PieceType::BISHOP) {
		piece = "X";// bishop
	}
	if (type == PieceType::QUEEN) {
		piece = (char) 157;// queen
	}
	if (type == PieceType::KING) {
		piece = (char) 233; // king
	}
	return piece;
}

void chessBoardManager::updatePlayerCheckedStatus(Player* player) {
#if _DEBUG
	std::cout << "Checking if player " << player->toCharString() << " is checked.." << std::endl;
#endif
	size_t kingThreatsCount = 0;
	std::shared_ptr<Piece> friendlyKing = NULL;
	std::vector<std::shared_ptr<Piece>> pieces = player->getPieces();

	// Select player's king piece
	for (int i = 0; i < pieces.size(); i++)
		if (pieces[i]->getType() == PieceType::KING)
			friendlyKing = pieces[i];

	if (friendlyKing != NULL) {
		kingThreatsCount = friendlyKing->getThreatVector().size();
	}

	player->setChecked(kingThreatsCount > 0);
}

void chessBoardManager::calculateAllPossibleMoves(Player* p) {
	auto color = p->getColor();
	std::vector<Coordinates> moves;
	std::vector<Coordinates> availableMoves;

	std::cout << "updating all possible moves for player " << std::to_string(static_cast<int>(p->getColor())) << std::endl;
	for (int i = 0; i <= 7; i++) {
		for (int j = 0; j <= 7; j++) {
			if (_board[i][j]->getColor() == color) {
				std::shared_ptr<Piece> piece = _board[i][j];

				// Get piece's possible movements
				piece->calculateAvailableMoves(_board);
				availableMoves = piece->getAvailableMoves();
				moves.insert(moves.end(), availableMoves.begin(), availableMoves.end());
				piece->setAvailableMoves(moves);
			}
		}
	}
}