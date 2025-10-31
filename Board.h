#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <iostream>
#include "Piece.h"
using namespace std;

class Board {
	private:
		int row;
		int column;
		Piece pieces[8][8];
	public:
		Board();
		Board(int r, int c);
		int GetRow() const { return row; }
		int GetColumn() const { return column; }
		void SetRow(int r) { this->row = r; }
		void SetColumn(int c) { this->column = c; }
		void InitializeBoard();
		void PrintBoard() const;
		Piece GetPiece(int r, int c) const;
		void SetPiece(int r, int c, const Piece& p);
		bool MovePiece(int currR, int currC, int newR, int newC);
};

#endif