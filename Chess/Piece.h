#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "coordinates.h"
#include "defines.h"
#include "player.h"

enum class Colors;
class Player;


enum class PieceType {
	PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING, EMPTY
};

enum class Colors {
	WHITE = 0, 
	BLACK = 1,
	EMPTY = 2
};


class Piece {
public:
	Piece(Colors, PieceType, Coordinates);
	Piece(const Piece&, PieceType);
	~Piece();
	Colors getColor(void);
	PieceType getType(void);
	void changeType(PieceType);
	bool isMoved(void);
	void setMoved(bool);
	void addThreat(std::shared_ptr<Piece>);
	void setOwner(Player*);
	void resetThreatVector(void);
	void setAvailableMoves(std::vector<Coordinates>);
	void convertTo(std::shared_ptr<Piece>);
	std::vector<Coordinates> getAvailableMoves(void);
	virtual void calculateAvailableMoves(std::vector<std::vector<std::shared_ptr<Piece>>>) = 0;
	virtual std::shared_ptr<Piece> Clone(void) = 0;
	void clearAvailableMoves(void);
	std::string toString(void);
	std::vector<std::shared_ptr<Piece>> getThreatVector(void);
	Coordinates getCoordinates(void);
	void setCoordinates(const Coordinates& coords);
	void operator =(const Piece& right);
	bool enPassantable = false;
	bool isPinned = false;
	Player* getOwner(void);
protected:
	PieceType _type;
	Player* _owner = NULL;
	std::vector<std::shared_ptr<Piece>> _threats;
	std::vector<Coordinates> _availableMoves;
	Coordinates _coords;
	Colors _color = (Colors)2;
	Colors _enemyColor;
	bool _hasMoved = false;
};



class Rook : public virtual Piece {
public:
	Rook(Colors color, Coordinates coords) : Piece(color, PieceType::ROOK, coords) {};
	Rook(const Piece& piece) : Piece(piece, PieceType::ROOK) {};
	std::shared_ptr<Piece> Clone(void) {
		return std::make_shared<Rook>(*this);
	}
	void calculateAvailableMoves(std::vector<std::vector<std::shared_ptr<Piece>>>) override;
};


class Pawn : public virtual Piece {
public:
	Pawn(Colors color, Coordinates coords) : Piece(color, PieceType::PAWN, coords) {};
	Pawn(const Piece& piece) : Piece(piece, PieceType::PAWN) {};
	std::shared_ptr<Piece> Clone(void) override {
		return std::make_shared<Pawn>(*this);
	}
	void calculateAvailableMoves(std::vector<std::vector<std::shared_ptr<Piece>>>) override;
};


class Knight : public virtual Piece {
public:
	Knight(Colors color, Coordinates coords) : Piece(color, PieceType::KNIGHT, coords) {};
	Knight(const Piece& piece) : Piece(piece, PieceType::KNIGHT) {};
	std::shared_ptr<Piece> Clone(void) {
		return std::make_shared<Knight>(*this);
	}
	void calculateAvailableMoves(std::vector<std::vector<std::shared_ptr<Piece>>>) override;
};

class Bishop : public virtual Piece {
public:
	Bishop(Colors color, Coordinates coords) : Piece(color, PieceType::BISHOP, coords) {};
	Bishop(const Piece& piece) : Piece(piece, PieceType::BISHOP) {};
	std::shared_ptr<Piece> Clone(void) {
		return std::make_shared<Bishop>(*this);
	}
	void calculateAvailableMoves(std::vector<std::vector<std::shared_ptr<Piece>>>) override;
};

class Queen : public virtual Piece {
public:
	Queen(Colors color, Coordinates coords) : Piece(color, PieceType::QUEEN, coords) {};
	Queen(const Piece& piece) : Piece(piece, PieceType::QUEEN) {
		std::cout << "constructing new Queen!" << std::endl;
	};
	Queen(const std::shared_ptr<Piece> piece) : Piece(*piece, PieceType::QUEEN) {};
	std::shared_ptr<Piece> Clone(void) {
		return std::make_shared<Queen>(*this);
	}
	void calculateAvailableMoves(std::vector<std::vector<std::shared_ptr<Piece>>>) override;
};




class King : public virtual Piece {
public:
	King(Colors color, Coordinates coords) : Piece(color, PieceType::KING, coords) {};
	std::shared_ptr<Piece> Clone(void) {
		return std::make_shared<King>(*this);
	}
	void calculateAvailableMoves(std::vector<std::vector<std::shared_ptr<Piece>>>) override;
private:
	std::vector<std::shared_ptr<Piece>> filterNonKingableTiles(const std::vector<std::shared_ptr<Piece>>&);
	std::vector<Coordinates> getSuitableCastlingTiles(std::vector<std::vector<std::shared_ptr<Piece>>>);
};

class EmptyPiece : public virtual Piece {
public:
	EmptyPiece(Coordinates coords) : Piece(Colors::EMPTY, PieceType::EMPTY, coords) {};
	std::shared_ptr<Piece> Clone(void) {
		return std::make_shared<EmptyPiece>(*this);
	}
	void calculateAvailableMoves(std::vector<std::vector<std::shared_ptr<Piece>>>) override;
};


