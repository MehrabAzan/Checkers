#include <string>
#include <iostream>
#include <vector>
#include <random>
#include "Piece.h"
#include "Board.h"
#include "Bot.h"
using namespace std;

int Bot::EvaluateBoard(Board& board) {
	// declare score variable
	int score = 0;

	// iterate through the board
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			// get the piece at the current position
			Piece piece = board.GetPiece(r, c);
			// evaluate based on piece type and color
			string color = piece.GetColor();
			string type = piece.GetType();
			int value = 0;

			// assign piece value based on type
			if (type == "man") {
				value = 1;
			}
			else if (type == "king") {
				value = 2;
			}
			else {
				value = 0;
			}

			// adjust score based on color
			if (color == "black") {
				score += value;
			}
			else if (color == "white") {
				score -= value;
			}
		}
	}

	// return the final score
	return score;
}

vector<int> Bot::Move(Board& board) {
	// vector that will hold all possible captures
	vector<vector<int>> captures;
	// vector will hold all possible normal moves
	vector<vector<int>> moves;
	// random number generator
	random_device rd;
	mt19937 gen(rd());
	// lowest possible score so any score will be higher
	int score = INT_MIN;
	// possible moves the bot can make
	vector<vector<int>> possibleMoves;
	// best move the bot will make
	vector<vector<int>> bestMoves;

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
				}
				else {
					captureDirections = { { 2, -2 }, { 2, 2 } };
					moveDirections = { { 1, -1 }, { 1, 1 } };
				}

				// interate through capture directions
				for (const vector<int>& i : captureDirections) {
					// the new row after the capture
					int newR = r + i[0];
					// the new column after the capture
					int newC = c + i[1];
					// check if the mid position and new position are within bounds
					if (newR >= 0 && newR < 8 && newC >= 0 && newC < 8) {
						// create a copy of the board to simulate the move
						Board tempBoard = board;
						// check if the capture move is valid
						if (tempBoard.MovePiece(r, c, newR, newC)) {
							// add to captures vector
							captures.push_back({ r, c, newR, newC });
						}
					}
				}

				// iterate through normal move directions
				for (const vector<int>& i : moveDirections) {
					// the new row after the move
					int newR = r + i[0];
					// the new column after the move
					int newC = c + i[1];
					// check if the new position is within bounds
					if (newR >= 0 && newR < 8 && newC >= 0 && newC < 8) {
						// create a copy of the board to simulate the move
						Board tempBoard = board;
						// check if the move is valid
						if (tempBoard.MovePiece(r, c, newR, newC)) {
							// add to moves vector
							moves.push_back({ r, c, newR, newC });
						}
					}
				}
			}
		}
	}

	// failsafe move if no moves are possible
	if (captures.empty() && moves.empty()) {
		return { -1, -1, -1, -1 };
	}

	// prioritize captures over normal moves
	if (!captures.empty()) {
		possibleMoves = captures;
	} else {
		possibleMoves = moves;
	}

	for (const vector<int>& i : possibleMoves) {
		// create a copy of the board to simulate the move
		Board tempBoard = board;
		// make the move on the temporary board
		tempBoard.MovePiece(i[0], i[1], i[2], i[3]);
		// evaluate the board after the move
		int currentScore = EvaluateBoard(tempBoard);
		// if the current score is better than the best score found
		if (currentScore > score) {
			// update the best score and reset best moves
			score = currentScore;
			bestMoves.clear();
			// add the current move to best moves
			bestMoves.push_back(i);
		} else if (currentScore == score) {
			// if the score is equal, add to best moves
			bestMoves.push_back(i);
		}
	}

	// failsafe in case no best move is found
	if (bestMoves.empty()) {
		return { -1, -1, -1, -1 };
	}

	// randomly select one of the best moves
	uniform_int_distribution<> dis(0, bestMoves.size() - 1);
	// return the selected move
	return bestMoves[dis(gen)];
}


// unemplemented code
// kept this here for potential future use
// was not able to solve minimax implementation within time constraints
/**
vector<vector<int>> Bot::AllPossibleMoves(Board& board) {
	// vector to hold all possible moves
	vector<vector<int>> moves;
	// iterate through the board
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			// get the piece at the current position
			Piece piece = board.GetPiece(r, c);
			// check if the piece is black
			if (piece.GetColor() == "black") {
				vector<vector<int>> directions;

				// assign directions based on the piece
				if (piece.GetType() == "king") {
					directions = { { 1, -1 }, { 1, 1 }, { -1, -1 }, { -1, 1 } };
				} else {
					directions = { { 1, -1 }, { 1, 1 } };
				}

				// iterate through possible move directions
				for (const vector<int>& i : directions) {
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

					// check for possible captures
					// the victim's position
					int midR = r + i[0];
					int midC = c + i[1];
					// the position after the capture
					int captureR = r + 2 * i[0];
					int captureC = c + 2 * i[1];

					// check if the mid position and capture position are within bounds
					if (midR >= 0 && midR < 8 && midC >= 0 && midC < 8 && captureR >= 0 && captureR < 8 && captureC >= 0 && captureC < 8) {
						// get the victim's piece
						Piece victim = board.GetPiece(midR, midC);
						// check if the victim piece is white
						if (victim.GetColor() == "white") {
							// check if the capture move is valid
							if (board.MovePiece(r, c, captureR, captureC)) {
								// add to moves vector
								moves.push_back({ r, c, captureR, captureC });
							}
						}
					}
				}
			}
		}
	}

	// return all possible moves
	return moves;
}

int Bot::MiniMax(Board& board, int depth, bool isMaximizing, int alpha, int beta) {

}
**/