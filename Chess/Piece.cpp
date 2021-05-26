#include "defines.h"
#include "Piece.h"



Piece::Piece(Colors color, PieceType type, Coordinates coordinates) {

	if (type != PieceType::EMPTY)
		switch (color)
		{
		case Colors::WHITE:
			_enemyColor = Colors::BLACK;
			break;
		case Colors::BLACK:
			_enemyColor = Colors::WHITE;
			break;
		default:
			break;
		}

	_color = color;
	_type = type;
	_hasMoved = false;
	_coords = coordinates;
}

Piece::Piece(const Piece& p, PieceType type) {

	_color = p._color;
	_type = p._type;
	_hasMoved = p._hasMoved;
	_coords = p._coords;
	_owner = p._owner;
	_enemyColor = p._enemyColor;

	_type = type;

	int a = 1;
}

Piece::~Piece() {
	//if (_owner != NULL)
		//_owner->removePiece(this);
#if _DEBUG
	std::cout << "deleting Piece: " << this->toString() << " at " << getCoordinates().toCharString() << std::endl;
#endif
}

Colors Piece::getColor(void) {
	return _color;
}

std::vector<std::shared_ptr<Piece>> Piece::getThreatVector(void) {
	return _threats;
}

Coordinates Piece::getCoordinates() {
	return _coords;
}

void Piece::setCoordinates(const Coordinates& coords) {
#if _DEBUG
	std::cout << "Setting new coordinates..." << std::endl;
#endif
	_coords = coords;
}

void Piece::operator=(const Piece& right) {

	this->_availableMoves = right._availableMoves;
	this->_threats = right._threats;
	this->_coords = right._coords;
	this->_color = right._color;
	this->_type = right._type;
	this->_hasMoved = right._hasMoved;
}

Player* Piece::getOwner() {
	return _owner;
}

void Piece::resetThreatVector(void) {
	_threats.clear();
}

void Piece::setAvailableMoves(std::vector<Coordinates> moves) {
	_availableMoves = moves;
}

void Piece::convertTo(std::shared_ptr<Piece> p) {

}

void Piece::clearAvailableMoves() {
	_availableMoves.clear();
}

std::vector<Coordinates> Piece::getAvailableMoves() {
	return _availableMoves;
}

std::string Piece::toString(void) {
	PieceType num = this->getType();
	std::string str = "";

	switch (num)
	{
	case PieceType::EMPTY:
		str = "[]";
		break;
	case PieceType::PAWN:
		str = "P";
		break;
	case PieceType::ROOK:
		str = "R";
		break;
	case PieceType::KNIGHT:
		str = "H";
		break;
	case PieceType::BISHOP:
		str = "B";
		break;
	case PieceType::QUEEN:
		str = "Q";
		break;
	case PieceType::KING:
		str = "K";
		break;
	default:
		break;
	}

	// Only display number evaluation for black or white players (skip empty tiles)
	return str += (_color == Colors::BLACK || _color == Colors::WHITE) ? std::to_string((int) _color) : "" ;
}

void Piece::addThreat(std::shared_ptr<Piece> piece) {
	//string msg = piece->getColor() + " type: " + piece->getType();
	////std::cout << msg << endl;
	//msg = "";
	if (piece->getType() == PieceType::EMPTY)
		return;

	if (piece->getColor() == this->getColor()) // friendly pieces do not matter
		return;

	// Check if threats array already contains the piece
	if (std::find(_threats.begin(), _threats.end(), piece) != _threats.end())
	{
		// Element in vector.
	}
	else
	{
		_threats.push_back(piece);
#if _DEBUG
		if (this->getType() == PieceType::KING)
		{
			std::string msg = "Check! " + this->toString() + " is threatened by " + piece->toString();
			std::cout << msg << std::endl;
			std::cout << "KING threat count: " << _threats.size() << std::endl;
		}
#endif
	}
}

void Piece::setOwner(Player* p) {
	_owner = p;
}

PieceType Piece::getType(void) {
	return _type;
}

void Piece::changeType(PieceType type) {
	_type = type;
}

bool Piece::isMoved(void) {
	return _hasMoved;
}

void Piece::setMoved(bool state) {
	_hasMoved = state;
}

extern bool boeq(int, int, int);

void Pawn::calculateAvailableMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board) {
	_availableMoves.clear();
	int sd = _color == Colors::WHITE ? -1 : 1; // scandirection (white moves top, black moves down)
	int row = _coords.getBoardRowIndex();
	int col = _coords.getBoardColumnIndex();
	Coordinates coords = _coords;
	Colors color = _color;
	if (boeq(row + sd, 0, 7))
	{
		// one or two moves to front
		if (board[row + sd][col]->getType() == PieceType::EMPTY)
			_availableMoves.push_back(Coordinates(col, row + sd));

		if (this->_hasMoved == false)
			if (board[row + sd][col]->getType() == PieceType::EMPTY && board[row + sd * 2][col]->getType() == PieceType::EMPTY)
				_availableMoves.push_back(Coordinates(col, row + sd * 2));

		// If the pawn is on the left side column
		if (col == 0)
		{
			if (board[row + sd][col + 1]->getColor() == _enemyColor)
				_availableMoves.push_back(Coordinates(col + 1, row + sd));

			//en passant check
			if (board[row][col + 1]->getColor() == _enemyColor && board[row][col + 1]->enPassantable == true)
				_availableMoves.push_back(Coordinates(col + 1, row + sd));
		}
		// If the pawn is on the right side column
		else if (col == 7)
		{
			if (boeq(row + sd, 0, 7))
				if (board[row + sd][col - 1]->getColor() == _enemyColor)
					_availableMoves.push_back(Coordinates(col - 1, row + sd));

			//en passant check
			if (board[row][col - 1]->getColor() == _enemyColor && board[row][col - 1]->enPassantable == true)
				_availableMoves.push_back(Coordinates(col - 1, row + sd));
		}
		// Pawn is not near borders
		else
		{
			if (boeq(row + sd, 0, 7))
			{
				if (board[row + sd][col - 1]->getColor() == _enemyColor)
					_availableMoves.push_back(Coordinates(col - 1, row + sd));
				if (board[row + sd][col + 1]->getColor() == _enemyColor)
					_availableMoves.push_back(Coordinates(col + 1, row + sd));
			}

			//en passant check
			if (board[row][col - 1]->getColor() == _enemyColor && board[row][col - 1]->enPassantable == true)
				_availableMoves.push_back(Coordinates(col - 1, row + sd));
			//en passant check
			if (board[row][col + 1]->getColor() == _enemyColor && board[row][col + 1]->enPassantable == true)
				_availableMoves.push_back(Coordinates(col + 1, row + sd));
		}
	}
}

void Rook::calculateAvailableMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board) {

	_availableMoves.clear();
	int row = _coords.getBoardRowIndex();
	int col = _coords.getBoardColumnIndex();

	for (int i = 1; i <= 7; i++)
	{
		// Left
		if (col - i >= 0)
		{
			if (board[row][col - i]->getType() == PieceType::EMPTY)
				_availableMoves.push_back(Coordinates(col - i, row));

			else
			{
				if (board[row][col - i]->getColor() == _color)
					break;
				else
				{
					_availableMoves.push_back(Coordinates(col - i, row));
					break;
				}
			}
		}
	}
	for (int i = 1; i <= 7; i++)
	{
		// Right
		if (col + i <= 7)
		{
			if (board[row][col + i]->getType() == PieceType::EMPTY)
				_availableMoves.push_back(Coordinates(col + i, row));
			else
			{
				if (board[row][col + i]->getColor() == _color)
					break;
				else
				{
					_availableMoves.push_back(Coordinates(col + i, row));
					break;
				}
			}
		}
	}
	for (int i = 1; i <= 7; i++)
	{
		// Up
		if (row - i >= 0)
		{
			if (board[row - i][col]->getType() == PieceType::EMPTY)
				_availableMoves.push_back(Coordinates(col, row - i));
			else
			{
				if (board[row - i][col]->getColor() == _color)
					break;
				else
				{
					_availableMoves.push_back(Coordinates(col, row - i));
					break;
				}
			}
		}
	}
	for (int i = 1; i <= 7; i++)
	{
		// Down
		if (row + i <= 7)
		{
			if (board[row + i][col]->getType() == PieceType::EMPTY)
				_availableMoves.push_back(Coordinates(col, row + i));
			else
			{
				if (board[row + i][col]->getColor() == _color)
					break;
				else
				{
					_availableMoves.push_back(Coordinates(col, row + i));
					break;
				}
			}
		}
	}
}

void Knight::calculateAvailableMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board) {

	_availableMoves.clear();
	int row = _coords.getBoardRowIndex();
	int col = _coords.getBoardColumnIndex();

	// Left
	if (col - 2 >= 0 && row + 1 <= 7)
		if (board[row + 1][col - 2]->getColor() != _color)
			_availableMoves.push_back(Coordinates(col - 2, row + 1));
	if (col - 2 >= 0 && row - 1 >= 0)
		if (board[row - 1][col - 2]->getColor() != _color)
			_availableMoves.push_back(Coordinates(col - 2, row - 1));

	// Up
	if (col - 1 >= 0 && row - 2 >= 0)
		if (board[row - 2][col - 1]->getColor() != _color)
			_availableMoves.push_back(Coordinates(col - 1, row - 2));

	if (col + 1 <= 7 && row - 2 >= 0)
		if (board[row - 2][col + 1]->getColor() != _color)
			_availableMoves.push_back(Coordinates(col + 1, row - 2));

	// Right
	if (col + 2 <= 7 && row - 1 >= 0)
		if (board[row - 1][col + 2]->getColor() != _color)
			_availableMoves.push_back(Coordinates(col + 2, row - 1));
	if (col + 2 <= 7 && row + 1 <= 7)
		if (board[row + 1][col + 2]->getColor() != _color)
			_availableMoves.push_back(Coordinates(col + 2, row + 1));

	// Down
	if (col - 1 >= 0 && row + 2 <= 7)
		if (board[row + 2][col - 1]->getColor() != _color)
			_availableMoves.push_back(Coordinates(col - 1, row + 2));
	if (col + 1 <= 7 && row + 2 <= 7)
		if (board[row + 2][col + 1]->getColor() != _color)
			_availableMoves.push_back(Coordinates(col + 1, row + 2));
}

void Bishop::calculateAvailableMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board) {

	std::cout << "Calculating available moves for QUEEN piece type!" << std::endl;
	_availableMoves.clear();
	int row = _coords.getBoardRowIndex();
	int col = _coords.getBoardColumnIndex();

	// Left up diagonal
	for (int i = 1; i <= 7; i++)
	{

		if (col - i >= 0 && row - i >= 0)
		{
			if (board[row - i][col - i]->getType() == PieceType::EMPTY)
			{
				_availableMoves.push_back(Coordinates(col - i, row - i));
			}
			else
			{
				if (board[row - i][col - i]->getColor() == _color)
				{
					break;
				}
				else
				{
					_availableMoves.push_back(Coordinates(col - i, row - i));
					break;
				}
			}
		}
	}
	for (int i = 1; i <= 7; i++)
	{
		// Right up diagonal
		if (col + i <= 7 && row - i >= 0)
		{
			if (board[row - i][col + i]->getType() == PieceType::EMPTY)
			{
				_availableMoves.push_back(Coordinates(col + i, row - i));
			}
			else
			{
				if (board[row - i][col + i]->getColor() == _color)
				{
					break;
				}
				else
				{
					_availableMoves.push_back(Coordinates(col + i, row - i));
					break;
				}
			}
		}
	}
	for (int i = 1; i <= 7; i++)
	{
		// Right down diagonal
		if (col + i <= 7 && row + i <= 7)
		{
			if (board[row + i][col + i]->getType() == PieceType::EMPTY)
			{
				_availableMoves.push_back(Coordinates(col + i, row + i));
			}
			else
			{
				if (board[row + i][col + i]->getColor() == _color)
				{
					break;
				}
				else
				{
					_availableMoves.push_back(Coordinates(col + i, row + i));
					break;
				}
			}
		}
	}
	for (int i = 1; i <= 7; i++)
	{
		// Left down diagonal
		if (col - i >= 0 && row + i <= 7)
		{
			if (board[row + i][col - i]->getType() == PieceType::EMPTY)
			{
				_availableMoves.push_back(Coordinates(col - i, row + i));
			}
			else
			{
				if (board[row + i][col - i]->getColor() == _color)
				{
					break;
				}
				else
				{
					_availableMoves.push_back(Coordinates(col - i, row + i));
					break;
				}
			}
		}
	}
}


void Queen::calculateAvailableMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board) {

	std::cout << "Calculating available moves for Queen at " << _coords.toCharString() << std::endl;
	_availableMoves.clear();
	int row = _coords.getBoardRowIndex();
	int col = _coords.getBoardColumnIndex();

	// Left up diagonal
	for (int i = 1; i <= 7; i++)
	{
		if (col - i >= 0 && row - i >= 0)
		{
			if (board[row - i][col - i]->getType() == PieceType::EMPTY)
			{
				_availableMoves.push_back(Coordinates(col - i, row - i));
			}
			else
			{
				if (board[row - i][col - i]->getColor() == _color)
				{
					break;
				}
				else
				{
					_availableMoves.push_back(Coordinates(col - i, row - i));
					break;
				}
			}
		}
	}
	for (int i = 1; i <= 7; i++)
	{
		// Right up diagonal
		if (col + i <= 7 && row - i >= 0)
		{
			if (board[row - i][col + i]->getType() == PieceType::EMPTY)
			{
				_availableMoves.push_back(Coordinates(col + i, row - i));
			}
			else
			{
				if (board[row - i][col + i]->getColor() == _color)
				{
					break;
				}
				else
				{
					_availableMoves.push_back(Coordinates(col + i, row - i));
					break;
				}
			}
		}
	}
	for (int i = 1; i <= 7; i++)
	{
		// Right down diagonal
		if (col + i <= 7 && row + i <= 7)
		{
			if (board[row + i][col + i]->getType() == PieceType::EMPTY)
			{
				_availableMoves.push_back(Coordinates(col + i, row + i));
			}
			else
			{
				if (board[row + i][col + i]->getColor() == _color)
				{
					break;
				}
				else
				{
					_availableMoves.push_back(Coordinates(col + i, row + i));
					break;
				}
			}
		}
	}
	for (int i = 1; i <= 7; i++)
	{
		// Left down diagonal
		if (col - i >= 0 && row + i <= 7)
		{
			if (board[row + i][col - i]->getType() == PieceType::EMPTY)
			{
				_availableMoves.push_back(Coordinates(col - i, row + i));
			}
			else
			{
				if (board[row + i][col - i]->getColor() == _color)
				{
					break;
				}
				else
				{
					_availableMoves.push_back(Coordinates(col - i, row + i));
					break;
				}
			}
		}
	}


	for (int i = 1; i <= 7; i++)
	{
		// Left
		if (col - i >= 0)
		{
			if (board[row][col - i]->getType() == PieceType::EMPTY)
				_availableMoves.push_back(Coordinates(col - i, row));

			else
			{
				if (board[row][col - i]->getColor() == _color)
					break;
				else
				{
					_availableMoves.push_back(Coordinates(col - i, row));
					break;
				}
			}
		}
	}
	for (int i = 1; i <= 7; i++)
	{
		// Right
		if (col + i <= 7)
		{
			if (board[row][col + i]->getType() == PieceType::EMPTY)
				_availableMoves.push_back(Coordinates(col + i, row));
			else
			{
				if (board[row][col + i]->getColor() == _color)
					break;
				else
				{
					_availableMoves.push_back(Coordinates(col + i, row));
					break;
				}
			}
		}
	}
	for (int i = 1; i <= 7; i++)
	{
		// Up
		if (row - i >= 0)
		{
			if (board[row - i][col]->getType() == PieceType::EMPTY)
				_availableMoves.push_back(Coordinates(col, row - i));
			else
			{
				if (board[row - i][col]->getColor() == _color)
					break;
				else
				{
					_availableMoves.push_back(Coordinates(col, row - i));
					break;
				}
			}
		}
	}
	for (int i = 1; i <= 7; i++)
	{
		// Down
		if (row + i <= 7)
		{
			if (board[row + i][col]->getType() == PieceType::EMPTY)
				_availableMoves.push_back(Coordinates(col, row + i));
			else
			{
				if (board[row + i][col]->getColor() == _color)
					break;
				else
				{
					_availableMoves.push_back(Coordinates(col, row + i));
					break;
				}
			}
		}
	}

	//((Bishop*) this)->calculateAvailableMoves(board);
	//((Rook*) this)->calculateAvailableMoves(board);
	//
};


void King::calculateAvailableMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board) {

	// Moving a king requires to check if the position is free as well as checking if it is under threat
	_availableMoves.clear();
	int row = _coords.getBoardRowIndex();
	int col = _coords.getBoardColumnIndex();

	// Left up diagonal
	std::vector<std::shared_ptr<Piece>> surroundingTiles;

	if (col - 1 >= 0 && row - 1 >= 0)	
		surroundingTiles.push_back(board[row - 1][col - 1]);
	
	// Left down diagonal
	if (col - 1 >= 0 && row + 1 <= 7)	
		surroundingTiles.push_back(board[row + 1][col - 1]);
	
	// Right up diagonal
	if (col + 1 <= 7 && row - 1 >= 0)	
		surroundingTiles.push_back(board[row - 1][col + 1]);
	
	// Right down diagonal
	if (col + 1 <= 7 && row + 1 <= 7)	
		surroundingTiles.push_back(board[row + 1][col + 1]);
	
	// Left
	if (col - 1 >= 0)	
		surroundingTiles.push_back(board[row][col - 1]);
	
	// Up
	if (row - 1 >= 0)	
		surroundingTiles.push_back(board[row - 1][col]);

	// Right
	if (col + 1 <= 7)	
		surroundingTiles.push_back(board[row][col + 1]);
	
	// Down
	if (row + 1 <= 7)	
		surroundingTiles.push_back(board[row + 1][col]);
	

	auto suitableTiles = filterNonKingableTiles(surroundingTiles);
	for (int i = 0; i < suitableTiles.size(); i++)
		_availableMoves.push_back(suitableTiles[i]->getCoordinates());

	// Check for castling
	// To left

	auto castlingTiles = getSuitableCastlingTiles(board);
	for (int i = 0; i < castlingTiles.size(); i++)
	{
		_availableMoves.push_back(castlingTiles[i]);
	}
}


std::vector<Coordinates> King::getSuitableCastlingTiles(std::vector<std::vector<std::shared_ptr<Piece>>> board) {
	int kingRow = _coords.getBoardRowIndex();
	int kingColumn = _coords.getBoardColumnIndex();
	std::vector<Coordinates> suitableTiles;

	if (this->_hasMoved == false && board[kingRow][0]->getType() == PieceType::ROOK && board[kingRow][0]->isMoved() == false)
	{
		int offset = -2; // target tile offset (2 tiles to the left from the this for both colors)
		bool canCastle = true; // initialize castling to true, try to change it to false in the following iterative checks
		// Start scanning the tiles between rook and the king
		for (int i = 1; i < 4; i++)
		{
			Piece* tile = board[kingRow][kingColumn - i].get();
			auto threatVector = tile->getThreatVector();
			bool tileUnderEnemyThreat = false;
			for (int i = 0; i < threatVector.size(); i++)
			{
				if (threatVector[i]->getColor() != this->getColor())
					tileUnderEnemyThreat = true;
			}

			if (tile->getType() != PieceType::EMPTY || tileUnderEnemyThreat == true)
			{// piece is blocked by a piece or is under enemy threat
				canCastle = false;
				break;
			}
		}
		if (canCastle)
		{
			suitableTiles.push_back(Coordinates(kingColumn + offset, kingRow));
		}
	}

	// To right
	if (this->isMoved() == false && board[kingRow][7]->getType() == PieceType::ROOK && board[kingRow][7]->isMoved() == false)
	{
		int offset = 2; // target tile offset (2 tiles to the right from the this for both colors)
		bool canCastle = true; // initialize castling to true, try to change it to false in the following iterative checks
		// Start scanning the tiles between rook and the king
		for (int i = 1; i < 3; i++)
		{
			Piece* tile = board[kingRow][kingColumn + i].get();
			auto threatVector = tile->getThreatVector();
			bool tileUnderEnemyThreat = false;
			for (int i = 0; i < tile->getThreatVector().size(); i++)
			{
				if (threatVector[i]->getColor() != this->getColor())
					tileUnderEnemyThreat = true;
			}

			if (tile->getType() != PieceType::EMPTY || tileUnderEnemyThreat == true)
			{// piece is blocked by a piece or is under enemy threat
				canCastle = false;
				break;
			}
		}
		if (canCastle)
			suitableTiles.push_back(Coordinates(kingColumn + offset, kingRow));
	}
	return suitableTiles;
}

std::vector<std::shared_ptr<Piece>> King::filterNonKingableTiles(const std::vector<std::shared_ptr<Piece>>& tiles) {
	std::vector<std::shared_ptr<Piece>> suitableTiles;
	for (int i = 0; i < tiles.size(); i++)
	{
		auto target = tiles[i];
		bool threat = false;
		if (target->getColor() != _color)
		{
			// Check if the tile is under threat
			auto threatVector = target->getThreatVector();
			for (int i = 0; i < threatVector.size(); i++)
			{
				// Get targeted piece's threat vector that contains threat colors
				Colors threatColor = threatVector[i]->getColor();
				// If the piece contains threat that is not equal to ours -> break and don't add to valid moves
				if (threatColor != this->_color && threatColor != Colors::EMPTY)
				{
					threat = true;
					break;
				}
			}
			// If the piece is free and not under threat -> add position to valid moves
			if (!threat)
				suitableTiles.push_back(target);
		}
	}
	return suitableTiles;
}

void EmptyPiece::calculateAvailableMoves(std::vector<std::vector<std::shared_ptr<Piece>>> board) {
	return;
};
