#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>
#include "Piece.h"
#include "Board.h"
#include "Bot.h"
using namespace std;
using namespace sf;

vector<int> Bot::Move(Board& board) {
	// vector that will hold all black pieces' positions
	vector<vector<int>> blackPieces;
	// vector that will hold all possible captures
	vector<vector<int>> captures;

	// iterate through the board to find all black pieces
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			// get the piece at the current position
			Piece piece = board.GetPiece(r, c);
			// check if the piece is black
			if (piece.GetColor() == color) {
				blackPieces.push_back({r, c});
			}
		}
	}

	// failsafe if there are no black pieces
	if (blackPieces.empty()) {
		// no black pieces available to move
		return {-1, -1, -1, -1};
	}

	// select a random black piece
	random_device rd;
	mt19937 gen(rd());
	shuffle(blackPieces.begin(), blackPieces.end(), gen);

	// iterate through the black pieces to find a valid move
	for (const vector<int>& i : blackPieces) {
		// current row and column of the selected piece
		int r = i[0];
		int c = i[1];

		// get the piece at the current position
		Piece piece = board.GetPiece(r, c);

		// check if the piece belongs to the bot
		if (piece.GetColor() == color) {
			// check if diagonal left is within bounds
			if (r + 1 < 8 && c - 1 >= 0) {
				// get the piece at the diagonal left position
				Piece diagonalLeft = board.GetPiece(r + 1, c - 1);
				// check if the piece is white to the left
				if (diagonalLeft.GetColor() == "white") {
					// tries to capture left
					int newR = r + 2;
					int newC = c - 2;
					// check if the new position is within bounds
					if (newC >= 0 && newC < 8 && newR >= 0 && newR < 8) {
						// check if the move is valid
						if (board.MovePiece(r, c, newR, newC)) {
							return { r, c, newR, newC };
						}
					}
				}
			}
			// check if diagonal right is within bounds
			if (r + 1 < 8 && c + 1 < 8) {
				// get the piece at the diagonal right position
				Piece diagonalRight = board.GetPiece(r + 1, c + 1);
				// check if the piece is white to the right
				if (diagonalRight.GetColor() == "white") {
					// tries to capture right
					int newR = r + 2;
					int newC = c + 2;
					// check if the new position is within bounds
					if (newC >= 0 && newC < 8 && newR >= 0 && newR < 8) {
						// check if the move is valid
						if (board.MovePiece(r, c, newR, newC)) {
							return { r, c, newR, newC };
						}
					}
				}
			}
			// check for if the current piece is a king
			if (piece.GetType() == "king") {
				// kings can move up
				int newR = r - 1;
				// tries to move left or right
				vector<int> newCs = { c - 1, c + 1 };
				for (int newC : newCs) {
					// check if the new position is within bounds
					if (newC >= 0 && newC < 8 && newR >= 0 && newR < 8) {
						// check if the move is valid
						if (board.MovePiece(r, c, newR, newC)) {
							return { r, c, newR, newC };
						}
					}
				}
			}
			// default move
			if (piece.GetType() == "man") {
				// moves the piece down
				int newR = r + 1;
				// tries to move left or right
				vector<int> newCs = { c - 1, c + 1 };
				for (int newC : newCs) {
					// check if the new position is within bounds
					if (newC >= 0 && newC < 8 && newR >= 0 && newR < 8) {
						// check if the move is valid
						if (board.MovePiece(r, c, newR, newC)) {
							return { r, c, newR, newC };
						}
					}
				}
			}
		}
	}
	// failsafe return if no move is possible
	return {-1, -1, -1, -1};
}