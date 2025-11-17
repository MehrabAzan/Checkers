#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Piece.h"
using namespace std;
using namespace sf;

class Board {
	private:
		static const int row = 8;
		static const int column = 8;
		Piece pieces[row][column];
		RectangleShape tiles[row][column];
	public:
		Board() { InitializeBoard(); }
		void InitializeBoard();
		void PrintBoard(RenderWindow& window) const;
		bool MovePiece(int currR, int currC, int newR, int newC);
		bool Capture(int currR, int currC, int newR, int newC, int numR, int numC);
		Piece GetPiece(int r, int c) { return pieces[r][c]; }
};

#endif