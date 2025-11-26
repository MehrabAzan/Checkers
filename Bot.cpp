#include <string>
#include <iostream>
#include <vector>
#include <random>
#include "Piece.h"
#include "Board.h"
#include "Bot.h"
using namespace std;
using namespace sf;

vector<int> Bot::Move(Board& board) {
	// vector that will hold all possible captures
	vector<vector<int>> captures;
	// vector will hold all possible normal moves
	vector<vector<int>> moves;
	// vector will hold all possible king moves
	vector<vector<int>> kingMoves;
	// random number generator
	random_device rd;
	mt19937 gen(rd());

	// iterate through the board
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			// get the piece at the current position
			Piece piece = board.GetPiece(r, c);
			// check if the piece is black
			if (piece.GetColor() == color) {
				// direction for capture
				vector<vector<int>> captureDirections;
				// direction for normal moves
				vector<vector<int>> moveDirections;

				// assign directions based on the piece
				if (piece.GetType() == "king") {
					captureDirections = { { 2, -2 }, { 2, 2 }, { -2, -2 }, { -2, 2 } };
					moveDirections = { { 1, -1 }, { 1, 1 }, { -1, -1 }, { -1, 1 } };
				} else {
					captureDirections = { { 2, -2 }, { 2, 2 } };
					moveDirections = { { 1, -1 }, { 1, 1 } };
				}

				// interate through capture directions
				for (const vector<int>& i : captureDirections) {
					// gets the current row and adds 1 to get the victim's position
					int midR = r + i[0] / 2;
					// gets the current column and adds 1 to get the victim's position
					int midC = c + i[1] / 2;
					// the new row after the capture
					int newR = r + i[0];
					// the new column after the capture
					int newC = c + i[1];
					// check if the mid position and new position are within bounds
					if (midR >= 0 && midR < 8 && midC >= 0 && midC < 8 && newR >= 0 && newR < 8 && newC >= 0 && newC < 8) {
						// get the victim's piece
						Piece victim = board.GetPiece(midR, midC);
						// check if the victim piece is white
						if (victim.GetColor() == "white") {
							// check if the move is valid
							if (board.MovePiece(r, c, newR, newC)) {
								// add to captures vector
								captures.push_back({ r, c, newR, newC });
							}
						}
					}
				}

				if (piece.GetType() == "king") {
					// iterate through king move directions
					for (const vector<int>& i : moveDirections) {
						// the new row after the move
						int newR = r + i[0];
						// the new column after the move
						int newC = c + i[1];
						// check if the new position is within bounds
						if (newR >= 0 && newR < 8 && newC >= 0 && newC < 8) {
							// check if the move is valid
							if (board.MovePiece(r, c, newR, newC)) {
								// add to kingMoves vector
								kingMoves.push_back({ r, c, newR, newC });
							}
						}
					}
				} else if (piece.GetType() == "man") {
					// iterate through move directions
					for (const vector<int>& i : moveDirections) {
						// the new row after the move
						int newR = r + i[0];
						// the new column after the move
						int newC = c + i[1];
						// check if the new position is within bounds
						if (newR >= 0 && newR < 8 && newC >= 0 && newC < 8) {
							// check if the move is valid
							if (board.MovePiece(r, c, newR, newC)) {
								// add to moves vector
								moves.push_back({ r, c, newR, newC });
							}
						}
					}
				}
			}
		}
	}

	// failsafe if there are no black pieces
	if (moves.empty()) {
		// no black pieces available to move
		return { -1, -1, -1, -1 };
	}

	// prioritize captures
	if (!captures.empty()) {
		// select a random capture from the captures vector
		uniform_int_distribution<> captureDistance(0, captures.size() - 1);
		vector<int> selectedCapture = captures[captureDistance(gen)];
		// assign the selected capture values
		int r = selectedCapture[0];
		int c = selectedCapture[1];
		int newR = selectedCapture[2];
		int newC = selectedCapture[3];
		return selectedCapture;
	}

	// prioritize king moves
	if (!kingMoves.empty()) {
		// select a random king move from the kingMoves vector
		uniform_int_distribution<> kingMoveDistance(0, kingMoves.size() - 1);
		vector<int> selectedKingMove = kingMoves[kingMoveDistance(gen)];
		// assign the selected king move values
		int r = selectedKingMove[0];
		int c = selectedKingMove[1];
		int newR = selectedKingMove[2];
		int newC = selectedKingMove[3];
		return selectedKingMove;
	}
	
	// select a random move from the moves vector
	uniform_int_distribution<> moveDistance(0, moves.size() - 1);
	vector<int> selectedMove = moves[moveDistance(gen)];
	// assign the selected move values
	int r = selectedMove[0];
	int c = selectedMove[1];
	int newR = selectedMove[2];
	int newC = selectedMove[3];
	return selectedMove;

	// failsafe return if no move is possible
	return { -1, -1, -1, -1 };
}