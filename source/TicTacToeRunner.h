#pragma once

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class TicTacToeRunner
{
public:
	TicTacToeRunner() {}

	void StartGame();
	string getCurrentBoardString();
	void updateBoardString(string board);
	string getAIMove();
	bool isGameOver();
	bool didWin(char c);
	bool didDraw();

private:
	string boardString;
};