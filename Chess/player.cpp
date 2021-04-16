#include "player.h"
#include "Piece.h"
#include <string>
#include "chessBoard.h"
#include <locale> 
#include "defines.h"

using namespace std;

Player::Player(int col)
{
	this->color = col;
}

void Player::initPieces(int color)
{

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

vector<Piece*> Player::getPieces(void) {
	return pieces;
}

Player::~Player()
{
}

void Player::addPiece(Piece* piece)
{
	pieces.push_back(piece);	
}

void Player::printPieces(void)
{
	for (int i = 0; i < (int)pieces.size(); i++) {
		cout << getPieces()[i]->getColor() << " " << getPieces()[i]->getType() << endl;
	}
}


void Player::checkGame(chessBoardManager* board) {

	vector<Player*> players = board->getPlayers();

	board->recalculatePieceThreats(); // Assigns every threat into all pieces on the board

	for(int i = 0; i < players.size(); i++)
		board->updatePlayerCheckedStatus(players[i]);	
}

bool Player::getChecked() {
	return checked;
}

void Player::setChecked(bool newCheck) {

	if(checked == false && newCheck == true) {
		cout << color << " is checked!" << endl; cin.ignore();
	} 
	else if(checked == true && newCheck == false)
		cout << color << " not checked anymore!" << endl; cin.ignore();

	checked = newCheck;
}

void Player::setOpponent(Player* p) 
{
	if(p != this)
		opponent = p;
	else
		cout << "Cant set myself as an opponent!" << endl;
}

Player* Player::getOpponent() 
{
	return opponent;
}

void Player::makeMove(chessBoardManager* board, Player* enemy)
{	
	checkGame(board);

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

		int row = board->returnRow(unitCoordinates);
		int col = board->returnCol(unitCoordinates);		

		Piece* tempPiece = board->getPiece(row, col);

		// Check if the choices are INSIDE the board area, static 8x8 board
		if (row >= 0 && row <= 7 && col >= 0 && row <= 7) {
			// If the targeted piece matches the player's color
			if (board->getPiece(row, col)->getColor() == this->color) {	
				// Check for valid moves here
				availableMoves = board->calculateAvailableMoves(tempPiece, unitCoordinates);
				tempPiece->setAvailableMoves(availableMoves);
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
							board->setPiece(tempPiece, row, col, targetrow, targetcol);								
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
		board->calculateAllPossibleMoves(this);		
		checkGame(board);
		//checkGame(board);		
	}
}

int Player::getColor(void)
{
	return color;
}