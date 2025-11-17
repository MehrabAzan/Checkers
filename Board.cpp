#include <string>
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Board.h"
using namespace std;
using namespace sf;

void Board::InitializeBoard() {
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++) {
            tiles[r][c].setSize(Vector2f(80.f, 80.f));
			tiles[r][c].setPosition(Vector2f(c * 80.f, r * 80.f));

            if ((r + c) % 2 == 0) {
                tiles[r][c].setFillColor(Color::White);
            } else {
                tiles[r][c].setFillColor(Color(139, 69, 19));
            }

            if ((r % 2 == 1 && c % 2 == 0 && r < 3) || (r % 2 == 0 && c % 2 == 1 && r < 3)) {
                pieces[r][c] = Piece("black", "man");
            } else if ((r % 2 == 1 && c % 2 == 0 && r > 4) || (r % 2 == 0 && c % 2 == 1 && r > 4)) {
                pieces[r][c] = Piece("white", "man");
            } else {
                pieces[r][c] = Piece("null", "tile");
            }

			pieces[r][c].SetPosition(c * 80.f + 20.f, r * 80.f + 20.f);
        }
    }
}

void Board::PrintBoard(RenderWindow& window) const {
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++) {
			window.draw(tiles[r][c]);
           if (pieces[r][c].GetColor() != "null") {
                pieces[r][c].Draw(window);
		   }
        }
    }
}

bool Board::Capture(int currR, int currC, int newR, int newC, int numR, int numC) {
    if (abs(numR) != 2 || abs(numC) != 2) {
        return true;
    }

    int midR = (currR + newR) / 2;
    int midC = (currC + newC) / 2;

    if (pieces[midR][midC].GetColor() == "null" || pieces[midR][midC].GetColor() == pieces[currR][currC].GetColor()) {
        cout << "Invalid move: No opponent piece to capture." << endl;
        return false;
    }

    pieces[midR][midC] = Piece("null", "tile");
    return true;
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
    if (pieces[currR][currC].GetColor() == "null") {
        cout << "Invalid move: No piece at the current position." << endl;
        return false;
	}
    if (pieces[newR][newC].GetColor() != "null") {
        cout << "Invalid move: Destination is not empty." << endl;
        return false;
	}
    if (currR == newR && currC == newC) {
        cout << "Invalid move: Same source and destination." << endl;
        return false;
    }
    if (pieces[currR][currC].GetType() == "man") {
        if (pieces[currR][currC].GetColor() == "white" && newR > currR) {
            cout << "Invalid move: White pieces (unless king) can only move up." << endl;
            return false;
        }
        if (pieces[currR][currC].GetColor() == "black" && newR < currR) {
            cout << "Invalid move: Black pieces (unless king) can only move down." << endl;
            return false;
        }
    }
    if (pieces[currR][currC].GetType() == "man" && abs(numR) > 2 && abs(numC) > 2) {
        cout << "Invalid move: Man pieces can only move one space diagonally." << endl;
        return false;
    }
    if (!Capture(currR, currC, newR, newC, numR, numC)) {
        return false;
    }

    Piece movingPiece = pieces[currR][currC];
    pieces[newR][newC] = movingPiece;
    pieces[newR][newC].SetPosition(newC * 80.f + 20.f, newR * 80.f + 20.f);
    pieces[currR][currC] = Piece("null", "tile");

    if (movingPiece.GetType() == "man") {
        if ((movingPiece.GetColor() == "white" && newR == 0) || (movingPiece.GetColor() == "black" && newR == row - 1)) {
            pieces[newR][newC].Promotion();
        }
    }

	return true;
}
