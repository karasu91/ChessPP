#pragma once
#include <vector>
#include <memory>

class Piece;
enum class Colors;

class Player {
public:
	void removePiece(std::shared_ptr<Piece>);
	Player(Colors);
	~Player();
	void addPiece(std::shared_ptr<Piece>);
	Colors getColor(void);
	void initPieces(void);
	void printPieces(void);
	std::string toCharString();
	//vector<string> getMoves(void);
	std::vector<std::shared_ptr<Piece>> getPieces(void);
	void updatePieceAt(std::shared_ptr<Piece>, int);
	void copyPieces(std::vector<std::shared_ptr<Piece>>);
	void setChecked(bool);
	bool isChecked(void);
	void setOpponent(Player*);
	Player* getOpponent(void);
	bool isWinner = false;

private:
	Colors color;
	std::vector<std::shared_ptr<Piece>> pieces;
	Player* opponent = NULL;
	bool _checked = false;
};
