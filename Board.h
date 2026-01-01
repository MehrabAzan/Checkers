#ifndef BOARD_H
#define BOARD_H
#include <SFML/Graphics.hpp>
#include "Piece.h"
using namespace std;
using namespace sf;

// Board class representing the checkers board
class Board {
	private:
		// 2D array of pieces
		Piece pieces[8][8];
		// 2D array of tile shapes
		RectangleShape tiles[8][8];
	public:
		// default constructor
		Board() { InitializeBoard(); }
		// initializes the board with pieces in starting positions
		void InitializeBoard();
		// prints the board to the window
		void PrintBoard(RenderWindow& window) const;
		// moves a piece from current position to new position
		bool MovePiece(int currR, int currC, int newR, int newC);
		// getter for a piece at a specific position
		Piece GetPiece(int r, int c) { return pieces[r][c]; }
};

#endif