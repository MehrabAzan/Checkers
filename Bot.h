#ifndef BOT_H
#define BOT_H
#include <string>
#include <iostream>
#include <vector>
#include "Piece.h"
#include "Board.h"
using namespace std;

// Bot class to handle AI moves
class Bot {
	private:
		// the color of the bot's pieces
		const string color = "black";
		int maxDepth = 3;
	public:
		// returns a vector of integers representing the bot's move
		vector<int> Move(Board& board);
		// takes a look at the board and returns a score
		// positive score is good for black, negative score is good for white
		int EvaluateBoard(Board& board);
		int MiniMax(Board& board, int depth, bool isMaximizing, int alpha, int beta);
		vector<vector<int>> AllPossibleMoves(Board& board);
};

#endif