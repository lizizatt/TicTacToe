#include <iostream>
#include "TicTacToeRunner.h"

void TicTacToeRunner::StartGame()
{
	boardString = "         ";
}

string TicTacToeRunner::getCurrentBoardString()
{
	return boardString;
}

void TicTacToeRunner::updateBoardString(string board)
{
	boardString = board;
}

string TicTacToeRunner::getAIMove()
{
	vector<int> choices;
	for (int i = 0; i < 9; i++) {
		if (boardString[i] == ' ') {
			choices.push_back(i);
		}
	}
	if (choices.size() == 0) {
		return boardString;
	}
	boardString[choices.at(rand() % choices.size())] = 'O';
	return boardString;
}

bool TicTacToeRunner::isGameOver()
{
	return didWin('X') || didWin('O') || didDraw();
}

bool TicTacToeRunner::didWin(char c)
{
	//review rows
	for (int i = 0; i < 3; i++) {
		bool allMatch = true;
		for (int j = 0; j < 3; j++) {
			if (boardString[j + 3 * i] != c) {
				allMatch = false;
				break;
			}
		}
		if (allMatch) {
			return true;
		}
	}

	//review columns
	for (int i = 0; i < 3; i++) {
		bool allMatch = true;
		for (int j = 0; j < 3; j++) {
			if (boardString[j * 3 + i] != c) {
				allMatch = false;
				break;
			}
		}
		if (allMatch) {
			return true;
		}
	}

	//review diagonals
	bool allMatch = true;
	for (int i = 0; i < 9; i+=4) {
		if (boardString[i] != c) {
			allMatch = false;
			break;
		}
	}
	if (allMatch) {
		return true;
	}

	allMatch = true;
	for (int i = 2; i < 9; i+=2) {
		if (boardString[i] != c) {
			allMatch = false;
			break;
		}
	}
	if (allMatch) {
		return true;
	}

	return false;
}

bool TicTacToeRunner::didDraw() {
	for (int i = 0; i < 9; i++) {
		if (boardString[i] == ' ') {
			return false;
		}
	}
	return true;
}