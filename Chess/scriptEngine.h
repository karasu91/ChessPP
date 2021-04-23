#pragma once
#include <thread>
#include <string>
#include "player.h"
#include "coordinates.h"
#include "chessBoard.h"


class Player;
class Piece;

class ScriptEngine {
public:
	std::string convertToUpper(std::string str) {
		std::string ret = "";
		for (auto& c : str)
			ret += toupper(c);
		return ret;
	}
	ScriptEngine();
	~ScriptEngine();

	Player* currentPlayer = NULL;
	chessBoardManager* mgr = NULL;
	std::vector<std::vector<std::shared_ptr<Piece>>> board;
	int autoPlayDelayMs = 250;

	bool game_script_multiples_moves_checkmate(void);
	bool game_script_enpassant_test(void);

	void swapTurn() {
		currentPlayer = currentPlayer->getOpponent();
	}
	bool playMove(std::string start, std::string end) {
		while (true)
		{
			start = convertToUpper(start);
			end = convertToUpper(end);
			if (mgr->validateAndMove(currentPlayer, Coordinates(start), Coordinates(end)) == true)
			{
				swapTurn();
				std::this_thread::sleep_for(std::chrono::milliseconds(autoPlayDelayMs));
				return true;
			}
			else
			{
				std::cout << "FIX THIS LATER ON!!!1" << std::endl;
				std::cin.ignore();
			}
		}
		return false;
	}
};