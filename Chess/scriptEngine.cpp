#include "scriptEngine.h"
#include <iostream>

bool ScriptEngine::game_script_multiples_moves_checkmate() {



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

bool ScriptEngine::game_script_enpassant_test(void) {

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
		// playMove("D8", "C8");
		// playMove("E2", "E3");
		// playMove("C8", "D7");
		// playMove("F1", "B5");



		// playMove("A7", "A5");
		// playMove("D2", "D3");
		// playMove("A5", "A4");
		// playMove("B2", "B4");
		// playMove("A4", "B3");
		// playMove("F2", "F4");
		// playMove("B3", "B2");
		// playMove("F4", "F5");
		// playMove("B2", "C1");
		return true;
	} catch (const std::exception& exc)
	{
		std::cout << "Exception happened: " << exc.what() << std::endl;
		return false;
	}
}


bool ScriptEngine::game_script_twopins_test(void) {

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

		// playMove("D8", "C8");
		// playMove("E2", "E3");
		// playMove("C8", "D7");
		// playMove("F1", "B5");


		
		// playMove("A7", "A5");
		// playMove("D2", "D3");
		// playMove("A5", "A4");
		// playMove("B2", "B4");
		// playMove("A4", "B3");
		// playMove("F2", "F4");
		// playMove("B3", "B2");
		// playMove("F4", "F5");
		// playMove("B2", "C1");
		return true;
	} catch (const std::exception& exc)
	{
		std::cout << "Exception happened: " << exc.what() << std::endl;
		return false;
	}
}