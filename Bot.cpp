#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Piece.h"
#include "Board.h"
#include "Bot.h"
using namespace std;
using namespace sf;

pair<pair<int, int>, pair<int, int>> Bot::MakeMove(Board& board) {
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			Piece piece = board.GetPiece(r, c);
			if (piece.GetColor() == color) {
				int direction = (color == "white") ? -1 : 1;
				int newR = r + direction;
				for (int newC : {c - 1, c + 1}) {
					if (newC >= 0 && newC < 8 && newR >= 0 && newR < 8) {
						if (board.MovePiece(r, c, newR, newC)) {
							return {{r, c}, {newR, newC}};
						}
					}
				}
			}
		}
	}
	return {{-1, -1}, {-1, -1}};
}