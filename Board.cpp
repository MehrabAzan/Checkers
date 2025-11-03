#include <string>
#include <iostream>
#include <cstdlib>
#include "Board.h"
using namespace std;

Board::Board() : row(8), column(8) {}

Board::Board(int r, int c) : row(r), column(c) {}

void Board::InitializeBoard() {
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++) {
            if ((r % 2 == 1 && c % 2 == 0 && r < 3) || (r % 2 == 0 && c % 2 == 1 && r < 3)) {
                pieces[r][c] = Piece("b", "man");
            } else if ((r % 2 == 1 && c % 2 == 0 && r > 4) || (r % 2 == 0 && c % 2 == 1 && r > 4)) {
                pieces[r][c] = Piece("w", "man");
            } else {
                pieces[r][c] = Piece(".", "tile");
            }
        }
    }
}

void Board::PrintBoard() const {
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++) {
            cout << pieces[r][c].GetColor() << " ";
        }
        cout << endl;
    }
}

Piece Board::GetPiece(int r, int c) const {
    return pieces[r][c];
}

void Board::SetPiece(int r, int c, Piece p) {
    pieces[r][c] = p;
}

bool Board::MovePiece(int currR, int currC, int newR, int newC) {
	int numR = newR - currR;
	int numC = newC - currC;

	if (abs(numR) != abs(numC)) {
        cout << "Invalid move: Must move diagonally." << endl;
        return false;
    }
    if (currR < 0 || currR >= row || currC < 0 || currC >= column || newR < 0 || newR >= row || newC < 0 || newC >= column) {
        cout << "Invalid move: Out of bounds." << endl;
        return false;
    }
    if (pieces[currR][currC].GetColor() == ".") {
        cout << "Invalid move: No piece at the current position." << endl;
        return false;
	}
    if (pieces[newR][newC].GetColor() != ".") {
        cout << "Invalid move: Destination is not empty." << endl;
        return false;
	}
    if (currR == newR && currC == newC) {
        cout << "Invalid move: Same source and destination." << endl;
        return false;
    }
    if (pieces[currR][currC].GetType() == "man") {
        if (pieces[currR][currC].GetColor() == "w" && newR > currR) {
            cout << "Invalid move: White pieces (unless king) can only move up." << endl;
            return false;
        }
        if (pieces[currR][currC].GetColor() == "b" && newR < currR) {
            cout << "Invalid move: Black pieces (unless king) can only move down." << endl;
            return false;
        }
    }
    if (pieces[currR][currC].GetType() == "man" && abs(numR) > 2 && abs(numC) > 2) {
        cout << "Invalid move: Man pieces can only move one space diagonally." << endl;
        return false;
    }
    if (abs(numR) == 2 && abs(numC) == 2) {
        int captureR = (currR + newR) / 2;
        int captureC = (currC + newC) / 2;
        if (pieces[captureR][captureC].GetColor() == "." || pieces[captureR][captureC].GetColor() == pieces[currR][currC].GetColor()) {
            cout << "Invalid move: No opponent piece to capture." << endl;
            return false;
        }
        pieces[captureR][captureC] = Piece(".", "tile");
	}

    Piece movingPiece = pieces[currR][currC];
    pieces[newR][newC] = movingPiece;
    pieces[currR][currC] = Piece(".", "tile");

    if (movingPiece.GetType() == "man") {
        if ((movingPiece.GetColor() == "w" && newR == 0) || (movingPiece.GetColor() == "b" && newR == row - 1)) {
            pieces[newR][newC].Promotion();
        }
    }

	return true;
}
