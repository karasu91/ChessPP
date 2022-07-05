#include "engine.h"
#include <iostream>


bool Engine::game_script_multiples_moves_checkmate() {
	try
	{
		playMove("F7", "F6");
		playMove("E2", "E3");
		playMove("G7", "G5");
		playMove("F2", "F4");
		playMove("E7", "E6");
		playMove("D1", "F3");
		playMove("G8", "H6");
		playMove("B1", "C3");
		playMove("F8", "B4");
		playMove("A2", "A3");
		playMove("D8", "E7");
		playMove("A3", "B4");

		playMove("B7", "B5");
		playMove("C3", "B5");
		playMove("C8", "A6");
		playMove("C2", "C4");
		playMove("B8", "C6");
		playMove("G1", "H3");
		playMove("E8", "C8");
		playMove("f1", "e2");
		playMove("D8", "G8");
		playMove("E1", "G1"); // castle to right
		playMove("C6", "D4");
		playMove("F3", "A8");
		return true;
	} catch (const std::exception& exc)
	{
		std::cout << "Exception happened: " << exc.what() << std::endl;
		return false;
	}
}

bool Engine::game_script_enpassant_test(void) {

	auto players = mgr->getPlayers();
	int a = 1;

	try
	{
		playMove("A2", "A4");
		playMove("D7", "D6");
		playMove("A4", "A5");
		playMove("B7", "B5");
		playMove("A5", "B6");
		playMove("F7", "F5");
		playMove("B6", "B7");
		playMove("F5", "F4");
		playMove("B7", "C8");

		return true;
	} catch (const std::exception& exc)
	{
		std::cout << "Exception happened: " << exc.what() << std::endl;
		return false;
	}
}


bool Engine::game_script_twopins_test(void) {

	auto players = mgr->getPlayers();
	int a = 1;

	try
	{
		playMove("E2", "E4");
		playMove("D7", "D5");
		playMove("E4", "D5");
		playMove("E7", "E5");
		playMove("A5", "B6");
		playMove("D1", "E2");
		playMove("D8", "E7");
		playMove("E2", "E5");
		return true;
	} catch (const std::exception& exc)
	{
		std::cout << "Exception happened: " << exc.what() << std::endl;
		return false;
	}
}

bool Engine::playMove(std::string start, std::string end)
{
	while (true)
	{
		start = convertToUpper(start);
		end = convertToUpper(end);
		if (mgr->validateAndMove(_currentPlayer, start, end) == true)
		{

			mgr->updateGameState();
			swapTurn();
			//mgr->updateGameState();
			//std::this_thread::sleep_for(std::chrono::milliseconds(autoPlayDelayMs));
			return true;
		}
		else // Failed to move.
			return false;
	}
}

bool Engine::playMove(Coordinates start, Coordinates end)
{
	while (true)
	{
		if (mgr->validateAndMove(_currentPlayer, start, end) == true)
		{
			mgr->updateGameState();
			swapTurn();
			//mgr->updateGameState();
			//std::this_thread::sleep_for(std::chrono::milliseconds(autoPlayDelayMs));
			return true;
		}
		else // Failed to move.
			return false;
	}
}

void Engine::setCurrentPlayer(Player* player)
{
	_currentPlayer = player;
}

void Engine::initializeMultiplayer(Player* player) {

	_localPlayer = player;

//	if (_localPlayer->getColor() == Colors::WHITE)
//	{
//		_currentPlayer = _localPlayer;
//			// Initialize TCP/IP network stack
//		_srv = new Server();
//		_srv->localPort = localPort;
//		if (_srv->initialize() == false) {
//			std::cout << "Failed to initialize tcp/ip server" << std::endl;
//			return;
//		}
//
//		_cli = new Client();
//		_cli->targetPort = targetPort;
//		if (_cli->connectServer(targetIp) == false)
//		{
//			std::cout << "Failed to initialize tcp/ip client"  << std::endl;
//			return;
//		}
//	}

	 // This else clause is for localhost simulation since the server/client do not work truly in parallel
//	else
	
	//{
	//	std::cout << "Initializing client..." << std::endl;
	//	_currentPlayer = player->getOpponent();
	//	_cli = new Client();
	//	_cli->targetPort = targetPort;
	//	if (_cli->connectServer(targetIp) == false)
	//	{
	//		std::cout << "Failed to initialize tcp/ip client" << std::endl;
	//		return;
	//	}

		// Initialize TCP/IP network stack
		std::cout << "initializing TCP/IP..." << std::endl;
		_srv = new NetServer();
		_srv->localPort = localPort;
		if (_srv->initialize() == false) {
			std::cout << "Failed to initialize tcp/ip server"  << std::endl;
			return;
		}
	

}

void Engine::swapTurn() {
	_currentPlayer = _currentPlayer->getOpponent();
}


// Split a basic string with a defined delimiter.
// String manipulation poop stolen from: https://stackoverflow.com/a/46931770
std::vector<std::string> split (std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}


void Engine::run() {
	while (!(mgr->gameOver))
	{
//		if (_currentPlayer == _localPlayer) {
//			std::cout << _currentPlayer->toCharString() << ": Select piece (press space/enter to accept)";
//			Coordinates start = mgr->handleSelection();
//			std::cout << _currentPlayer->toCharString() << ": Select target (press space/enter to accept)";
//			Coordinates end = mgr->handleSelection();
//
//			// Send data to another player with somewhat of a failsafe mechanics
//			int n = 0;
//			while (true)
//			{
//				if (_cli->sendData(start.toCharString()+"->"+end.toCharString()) == false) {
//					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//					n++;
//					if (n == 4)
//						break;
//				}
//				else
//					break;
//			}
//
//			playMove(start, end);
//		}
//		else
		{
			std::cout << "Waiting for player to move..." << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(autoPlayDelayMs));

			// Wait for data from player
			std::string rcvData(_srv->receiveData());
			if (rcvData == "err")
			{
				std::cout << "error reading rcvData input. exiting." << std::endl;
				break;
			}

			std::string delim = "->";
			std::vector<std::string> moves;
			moves = split(rcvData, delim);
			if (moves.size() < 2) {
				_srv->sendData("Data faulty! Try again.");
				rcvData = "";
				continue;
			}



			playMove(Coordinates(moves[0]), Coordinates(moves[1]));
		}
	}

	std::cout << "Cleaning up..." << std::endl;
	delete _srv;
	delete _cli;
}

