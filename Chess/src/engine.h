#pragma once
#include <thread>
#include <string>
#include "player.h"
#include "coordinates.h"
#include "chessBoardManager.h"

class Player;
class Piece;

class Engine {

public:
	Engine();
	~Engine();

	std::string convertToUpper(std::string str) {
		std::string ret = "";
		for (auto& c : str)
			ret += toupper(c);
		return ret;
	}	

	chessBoardManager* mgr = NULL;

	std::vector<std::vector<std::shared_ptr<Piece>>> board;
	int autoPlayDelayMs = 1000;

	bool game_script_multiples_moves_checkmate(void);
	bool game_script_enpassant_test(void);
	bool game_script_twopins_test(void);

	void swapTurn();

	bool playMove(std::string start, std::string end);
	bool playMove(Coordinates start, Coordinates end);

	void initializeMultiplayer(Player* localPlayer);
	void setCurrentPlayer(Player* player);

	void run(void);

	int localPort;
	int targetPort;

private:
	Server* _srv;
	Client* _cli;

	Player* _currentPlayer = NULL;
	Player* _localPlayer = NULL;
};