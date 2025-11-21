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
		// will always play black pieces
		const string color = "black";
	public:
		// returns a vector of integers representing the bot's move
		vector<int> MakeMove(Board& board);
};

#endif