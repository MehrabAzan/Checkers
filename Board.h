#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Piece.h"
using namespace std;

class Board {
	private:
		static const int row = 8;
		static const int column = 8;
		Piece pieces[row][column];
		sf::RectangleShape tiles[row][column];
	public:
		Board();
		void InitializeBoard();
		void PrintBoard(sf::RenderWindow& window) const;
		Piece GetPiece(int r, int c) const;
		void SetPiece(int r, int c, Piece p);
		bool MovePiece(int currR, int currC, int newR, int newC);
};

#endif