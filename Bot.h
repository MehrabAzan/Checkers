#ifndef BOT_H
#define BOT_H
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Piece.h"
#include "Board.h"
using namespace std;
using namespace sf;

class Bot {
	private:
		const string color = "black";
	public:
		pair<pair<int, int>, pair<int, int>> MakeMove(Board& board);
};

#endif