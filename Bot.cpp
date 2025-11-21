#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Piece.h"
#include "Board.h"
#include "Bot.h"
using namespace std;
using namespace sf;

vector<int> Bot::MakeMove(Board& board) {
	// iterate through the board
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			// get the piece at the current position
			Piece piece = board.GetPiece(r, c);
			// check if the piece belongs to the bot
			if (piece.GetColor() == color) {
				// moves the piece down
				int newR = r + 1;
				// tries to move left or right
				vector<int> newCs = {c - 1, c + 1};
				for (int newC : newCs) {
					// check if the new position is within bounds
					if (newC >= 0 && newC < 8 && newR >= 0 && newR < 8) {
						// check if the move is valid
						if (board.MovePiece(r, c, newR, newC)) {
							return {r, c, newR, newC};
						}
					}
				}
			}
		}
	}
	// failsafe return if no move is possible
	return {-1, -1, -1, -1};
}