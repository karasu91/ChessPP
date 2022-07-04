 #pragma once
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "coordinates.h"
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
	Piece(void) {};
	Piece(Colors, PieceType, Coordinates);
	Piece(const Piece&, PieceType);
	Piece(std::shared_ptr<Piece>, PieceType);
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
	std::string getPieceIcon(void);
	Player* getOwner(void);
	std::shared_ptr<Piece> pinnedBy = NULL;	
	bool setPinInfo(std::vector<Coordinates>, std::shared_ptr<Piece>);
	void resetPinInfo();
	void checkPins();
protected:
	bool hasCalculated = false;
	int pinIt = 0; // pin propagation filter
	int pinChecks = 0;
	PieceType _type;
	Player* _owner = NULL;
	std::vector<std::shared_ptr<Piece>> _threats;
	std::vector<Coordinates> _availableMoves;
	std::vector<Coordinates> _pinVector;
	Coordinates _coords;
	Colors _color = (Colors)2;
	Colors _enemyColor;
	bool _hasMoved = false;
};


class Pawn : public virtual Piece {
public:
	Pawn(Colors color, Coordinates coords) : Piece(color, PieceType::PAWN, coords) {};
	Pawn(const Piece& piece) : Piece(piece, PieceType::PAWN) {};
	Pawn(std::shared_ptr<Piece> derived) : Piece(derived, PieceType::PAWN) {};
	std::shared_ptr<Piece> Clone(void) override {
		return std::make_shared<Pawn>(*this);
	}
	void calculateAvailableMoves(std::vector<std::vector<std::shared_ptr<Piece>>>) override;
};

class Knight : public virtual Piece {
public:
	Knight(Colors color, Coordinates coords) : Piece(color, PieceType::KNIGHT, coords) {};
	Knight(const Piece& piece) : Piece(piece, PieceType::KNIGHT) {};
	Knight(std::shared_ptr<Piece> derived) : Piece(derived, PieceType::KNIGHT) {};
	std::shared_ptr<Piece> Clone(void) {
		return std::make_shared<Knight>(*this);
	}
	void calculateAvailableMoves(std::vector<std::vector<std::shared_ptr<Piece>>>) override;
};


class Rook : public virtual Piece {
public:
	Rook(Colors color, Coordinates coords) : Piece(color, PieceType::ROOK, coords) {};
	Rook(const Piece& piece) : Piece(piece, PieceType::ROOK) {};
	Rook(std::shared_ptr<Piece> derived) : Piece(derived, PieceType::ROOK) {};
	Rook() {};
	std::shared_ptr<Piece> Clone(void) {
		return std::make_shared<Rook>(*this);
	}
	void calculateAvailableMoves(std::vector<std::vector<std::shared_ptr<Piece>>>) override;
	//~Rook() {};
};

class Bishop : public virtual Piece {
public:
	Bishop(Colors color, Coordinates coords) : Piece(color, PieceType::BISHOP, coords) {};
	Bishop(const Piece& piece) : Piece(piece, PieceType::BISHOP) {};
	Bishop(std::shared_ptr<Piece> derived) : Piece(derived, PieceType::BISHOP) {};
	Bishop() {};
	std::shared_ptr<Piece> Clone(void) {
		return std::make_shared<Bishop>(*this);
	}
	void calculateAvailableMoves(std::vector<std::vector<std::shared_ptr<Piece>>>) override;
};

class Queen : public virtual Piece {
public:
	Queen(Colors color, Coordinates coords) 
		: Piece(color, PieceType::QUEEN, coords) {};

	Queen(const Piece& piece) 
		: Piece(piece, PieceType::QUEEN) {};

	Queen(std::shared_ptr<Piece> derived) 
		: Piece(derived, PieceType::QUEEN) {};

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


