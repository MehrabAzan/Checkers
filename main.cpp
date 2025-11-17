#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Board.h"
#include "Piece.h"
#include "Bot.h"
using namespace std;
using namespace sf;

int main() {
	Board board;
	board.InitializeBoard();

	RenderWindow window(VideoMode({ 640, 640 }), "Checkers");
	window.setFramerateLimit(60);

	bool firstClick = true;
	int currC;
	int currR;
	bool playerTurn = true;
	Bot bot;
	int blackPieces = 12;
	int whitePieces = 12;

	while (window.isOpen()) {
		while (const optional event = window.pollEvent()) {
			if (event->is<Event::Closed>()) {
				window.close();
			}

			if (playerTurn) {
				if (const auto* mouseButtonPressed = event->getIf<Event::MouseButtonPressed>()) {
					if (mouseButtonPressed->button == Mouse::Button::Left) {
						int x = mouseButtonPressed->position.x;
						int y = mouseButtonPressed->position.y;

						if (firstClick) {
							currC = x / 80;
							currR = y / 80;
							firstClick = false;
							Piece selectedPiece = board.GetPiece(currR, currC);

							if (selectedPiece.GetColor() == "black") {
								cout << "Cannot move black." << endl;
								firstClick = true;
							}
						}
						else {
							int newC = x / 80;
							int newR = y / 80;

							if (!board.MovePiece(currR, currC, newR, newC)) {
								cout << "Move failed. Try again." << endl;
							} else {
								playerTurn = false;
							}

							firstClick = true;
						}
					}
				}
			} else {
				auto [from, to] = bot.MakeMove(board);
				if (from.first != -1) {
					board.MovePiece(from.first, from.second, to.first, to.second);
				}
				playerTurn = true;
			}
		}

		int whiteCount = 0;
		int blackCount = 0;

		for (int r = 0; r < 8; r++) {
			for (int c = 0; c < 8; c++) {
				Piece checkColor = board.GetPiece(r, c);

				if (checkColor.GetColor() == "black") {
					blackCount++;
				}
				else if (checkColor.GetColor() == "white") {
					whiteCount++;
				}
			}
		}

		blackPieces = blackCount;
		whitePieces = whiteCount;

		if (blackPieces == 0) {
			cout << "White wins!" << endl;
			window.close();
		}
		else if (whitePieces == 0) {
			cout << "Black wins!" << endl;
			window.close();
		}


		window.clear();
		board.PrintBoard(window);
		window.display();
	}
}