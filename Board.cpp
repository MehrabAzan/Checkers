#include <string>
#include <iostream>
#include <cstdlib>
#include "Board.h"
using namespace std;

void Board::InitializeBoard() {
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++) {
			// set up the tile size
            tiles[r][c].setSize(Vector2f(80.f, 80.f));
			// center the tiles on the board
			tiles[r][c].setPosition(Vector2f(c * 80.f, r * 80.f));

			// color the tiles in a checkerboard pattern
            if ((r + c) % 2 == 0) {
                tiles[r][c].setFillColor(Color::White);
            } else {
				// I chose brown for the dark tiles so the black pieces are visible
                tiles[r][c].setFillColor(Color(139, 69, 19));
            }

			// place the pieces in their starting positions
            if ((r % 2 == 1 && c % 2 == 0 && r < 3) || (r % 2 == 0 && c % 2 == 1 && r < 3)) {
                pieces[r][c] = Piece("black", "man");
            } else if ((r % 2 == 1 && c % 2 == 0 && r > 4) || (r % 2 == 0 && c % 2 == 1 && r > 4)) {
                pieces[r][c] = Piece("white", "man");
            } else {
                pieces[r][c] = Piece();
            }

			// center the pieces within their tiles
			pieces[r][c].SetPosition(c * 80.f + 20.f, r * 80.f + 20.f);
        }
    }
}

void Board::PrintBoard(RenderWindow& window) const {
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < column; c++) {
			// draw the tile
			window.draw(tiles[r][c]);
           if (pieces[r][c].GetColor() != "null") {
			   // draw the piece if it's not an empty tile
                pieces[r][c].Draw(window);
		   }
        }
    }
}

bool Board::MovePiece(int currR, int currC, int newR, int newC) {
	// calculate the row and column differences
	int numR = newR - currR;
	int numC = newC - currC;

	// check if the move is diagonal
	if (abs(numR) != abs(numC)) {
        cout << "Invalid move: Must move diagonally." << endl;
        return false;
    }
	// check if the move is within bounds
    if (currR < 0 || currR >= row || currC < 0 || currC >= column || newR < 0 || newR >= row || newC < 0 || newC >= column) {
        cout << "Invalid move: Out of bounds." << endl;
        return false;
    }
	// check if there is a piece at the current position that the player clicked
    if (pieces[currR][currC].GetColor() == "null") {
        cout << "Invalid move: No piece at the current position." << endl;
        return false;
	}
	// check if the final destination is empty
    if (pieces[newR][newC].GetColor() != "null") {
        cout << "Invalid move: Destination is not empty." << endl;
        return false;
	}
	// cannot move to the same position
    if (currR == newR && currC == newC) {
        cout << "Invalid move: Same source and destination." << endl;
        return false;
    }
	// check to see if it is a man piece
    if (pieces[currR][currC].GetType() == "man") {
		// white men can only move up the board, black men can only move down
        if (pieces[currR][currC].GetColor() == "white" && newR > currR) {
            cout << "Invalid move: White pieces (unless king) can only move up." << endl;
            return false;
        }
        if (pieces[currR][currC].GetColor() == "black" && newR < currR) {
            cout << "Invalid move: Black pieces (unless king) can only move down." << endl;
            return false;
        }
    }
	// men can only move one space diagonally unless capturing
    if (pieces[currR][currC].GetType() == "man" && abs(numR) > 2 && abs(numC) > 2) {
        cout << "Invalid move: Man pieces can only move one space diagonally." << endl;
        return false;
    }
	// check if the player is moving two spaces diagonally for a capture
    if (abs(numR) == 2 && abs(numC) == 2) {
        // find the position of the piece being captured
        int midR = (currR + newR) / 2;
        int midC = (currC + newC) / 2;

        if (pieces[midR][midC].GetColor() == "null" || pieces[midR][midC].GetColor() == pieces[currR][currC].GetColor()) {
            // if it's an empty tile or same color piece, invalid capture
            cout << "Invalid move: No opponent piece to capture." << endl;
            return false;
        }

        // remove the captured piece
        pieces[midR][midC] = Piece("null", "tile");
    }

	// sets movingPiece to current piece
    Piece movingPiece = pieces[currR][currC];
	// set new position to movingPiece
    pieces[newR][newC] = movingPiece;
	// center the piece in the new tile
    pieces[newR][newC].SetPosition(newC * 80.f + 20.f, newR * 80.f + 20.f);
	// set current position to empty tile
    pieces[currR][currC] = Piece("null", "tile");

	// check for promotion to king if a man reaches the opposite end
    if (movingPiece.GetType() == "man") {
        if ((movingPiece.GetColor() == "white" && newR == 0) || (movingPiece.GetColor() == "black" && newR == row - 1)) {
            pieces[newR][newC].Promotion();
        }
    }

	return true;
}
