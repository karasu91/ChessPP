#pragma once
#include "player.h"
#include "chessBoard.h"
#include <thread>

class ScriptEngine {
public:
	string convertToUpper(string str) {
		string ret = "";
		for(auto& c : str)
			ret += toupper(c);
		return ret;
	}
	ScriptEngine();
	~ScriptEngine();
	Player* currentPlayer = NULL;
	chessBoardManager* mgr = NULL;
	int autoPlayDelayMs = 100;

	bool game_script_multiples_moves_checkmate(void);
	bool game_script_enpassant_test(void);

	void swapTurn() {
		currentPlayer = currentPlayer->getOpponent();
	}
	bool playMove(string start, string end) 	{
		start = convertToUpper(start);
		end = convertToUpper(end);
		if(mgr->playMove(currentPlayer, coordinates(start), coordinates(end)) == true)
		{
			swapTurn();
			std::this_thread::sleep_for(std::chrono::milliseconds(autoPlayDelayMs));
			return true;
		}
		return false;
	}
};