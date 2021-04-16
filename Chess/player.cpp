#include "player.h"
#include "Piece.h"
#include <string>
#include "chessBoard.h"
#include <locale> 
#include "defines.h"

using namespace std;

player::player(int col)
{
	this->color = col;
}

void player::initPieces(int color)
{
	validMoves.clear();
	if (color == WHITE) {
		/* Pawns */
		addPiece(new Piece(WHITE, PAWN));
		addPiece(new Piece(WHITE, PAWN));
		addPiece(new Piece(WHITE, PAWN));
		addPiece(new Piece(WHITE, PAWN));
		addPiece(new Piece(WHITE, PAWN));
		addPiece(new Piece(WHITE, PAWN));
		addPiece(new Piece(WHITE, PAWN));
		addPiece(new Piece(WHITE, PAWN));

		/* The rest */
		addPiece(new Piece(WHITE, ROOK));
		addPiece(new Piece(WHITE, HORSE));
		addPiece(new Piece(WHITE, BISHOP));
		addPiece(new Piece(WHITE, KING));
		addPiece(new Piece(WHITE, QUEEN));
		addPiece(new Piece(WHITE, BISHOP));
		addPiece(new Piece(WHITE, HORSE));
		addPiece(new Piece(WHITE, ROOK));
	}
	else { // Color == Black
		/* Pawns */
		addPiece(new Piece(BLACK, PAWN));
		addPiece(new Piece(BLACK, PAWN));
		addPiece(new Piece(BLACK, PAWN));
		addPiece(new Piece(BLACK, PAWN));
		addPiece(new Piece(BLACK, PAWN));
		addPiece(new Piece(BLACK, PAWN));
		addPiece(new Piece(BLACK, PAWN));
		addPiece(new Piece(BLACK, PAWN));

		/* The rest */
		addPiece(new Piece(BLACK, ROOK));
		addPiece(new Piece(BLACK, HORSE));
		addPiece(new Piece(BLACK, BISHOP));
		addPiece(new Piece(BLACK, QUEEN));
		addPiece(new Piece(BLACK, KING));
		addPiece(new Piece(BLACK, BISHOP));
		addPiece(new Piece(BLACK, HORSE));
		addPiece(new Piece(BLACK, ROOK));
	}	
}

vector<Piece*> player::getPieces(void) {
	return pieces;
}

player::~player()
{
}

void player::addPiece(Piece* piece)
{
	pieces.push_back(piece);	
}

void player::printPieces(void)
{
	for (int i = 0; i < (int)pieces.size(); i++) {
		cout << getPieces()[i]->getColor() << " " << getPieces()[i]->getType() << endl;
	}
}

vector<string> player::getMoves(void)
{
	return validMoves;
}

void player::setChecked(bool state, chessBoard* b, player* e)
{
	bool check = state;
	if (this->checked == false && check == true) {
		cout << this->getColor() << " is checked!" << endl; cin.ignore();
		checked = check;
		b->checkForMate(this, e);
		return;
	}
	else if (this->checked == true && check == false)
		cout << this->getColor() << " not checked anymore!" << endl; cin.ignore();
		checked = check;
}

vector<string> player::getThreatMoves(void) 
{
	return threatMoves;
}

void player::checkGame(player* p, player* e, chessBoard* board) 
{
	board->createThreatVector(); // Assigns every threat into all pieces on the board
	board->checkCheck(p, e);
}

void player::makeMove(chessBoard* board, player* enemy)
{	
	checkGame(this, enemy, board);
	checkGame(enemy, this, board);

	string unitCoordinates;
	string target;
	string targetTile;
	vector<string> availableMoves;
	bool movePass = false;
	
	/*for (unsigned i = 0; i < this->getMoves().size(); i++) {
		cout << this->getMoves()[i] << " ";
	}*/
	

	while (!movePass) {
		// Get player's coordinates
		cout << this->color << ": choose unit (row, column): "; 
		cin >> unitCoordinates;		

		int unitrow = board->returnRow(unitCoordinates);
		int unitcol = board->returnCol(unitCoordinates);		

		Piece* tempPiece = board->getPiece(unitrow, unitcol);

		// Check if the choices are INSIDE the board area, static 8x8 board
		if (unitrow >= 0 && unitrow <= 7 && unitcol >= 0 && unitrow <= 7) {
			// If the targeted piece matches the player's color
			if (board->getPiece(unitrow, unitcol)->getColor() == this->color) {	
				// Check for valid moves here
				availableMoves = board->validMoves(tempPiece, unitCoordinates);
			}
			else {
				cout << "Faulty choice, try again!" << endl;
				continue;
			}
		}
		else {
			cout << "Faulty choice, try again!" << endl;
			continue;
		}
		if (availableMoves.size()) {
			while (movePass == false) {
				cout << "\n" << this->color << ": choose target tile (row, column): "; 
				cin >> target;

				int targetrow = board->returnRow(target); int targetcol = board->returnCol(target);				
				
				// If targeted tile is withing board limits
				if (targetrow >= 0 && targetrow <= 7 && targetcol >= 0 && targetcol <= 7) {

					// Make string indicator from the targeted tile so we can compare it with available moves
					targetTile = to_string(targetrow) += to_string(targetcol);

					// Check if the targeted tile is in available moves. If yes -> move
					for (unsigned i = 0; i < availableMoves.size(); i++) {
						if (targetTile == availableMoves[i]) {							
							board->setPiece(tempPiece, unitrow, unitcol, targetrow, targetcol);								
							board->printBoard();
							tempPiece->setMoved(YES);
							movePass = true;
							break;
						}
						else if (targetTile != availableMoves[i] && i == availableMoves.size() - 1) {
							cout << "Faulty move!" << endl;
						}
					}
				}
				// Else break cycle
				else
				{
					cout << "Move is faulty!, try again!" << endl;
					continue;
				}	
			}
		}
		else {
			cout << "Cannot move this piece!" << endl;
		}
		// Calculate all possible moves for this player this turn
		// New round -> nullify availableMoves	
		this->validMoves.clear();
		board->addAllPossibleMoves(this);		
		checkGame(enemy, this, board);
		checkGame(this, enemy, board);		
	}
}

void player::validMovesTotal(vector<string> moves) 
{
	validMoves.clear();
	validMoves = moves;
}

int player::getColor(void)
{
	return color;
}

void player::addMoves(vector<string> moves)
{
	validMoves.insert(validMoves.end(), moves.begin(), moves.end());
}
