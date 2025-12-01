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
	public:
		// returns a vector of integers representing the bot's move
		vector<int> Move(Board& board);
		// takes a look at the board and returns a score
		// positive score is good for black, negative score is good for white
		int EvaluateBoard(Board& board);
};

#endif

// unemplemented code
// kept this here for potential future use
// was not able to solve minimax implementationBo
// the maximum number of moves it will look ahead
//int maxDepth = 3;
/**
// algorithm to determine the best move by simulating possible moves to choose the optimal one
int MiniMax(Board& board, int depth, bool isMaximizing, int alpha, int beta);
// gets all possible moves for black pieces
vector<vector<int>> AllPossibleMoves(Board& board);
**/