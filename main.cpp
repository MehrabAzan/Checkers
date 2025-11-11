#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Board.h"
#include "Piece.h"
using namespace std;
using namespace sf;
using std::optional;

int main() {
	Board board;
	board.InitializeBoard();

	RenderWindow window(VideoMode({640, 640}), "Checkers");
	window.setFramerateLimit(60);

	bool firstClick = true;
	int currC;
	int currR;

	while (window.isOpen()) {
		while (const optional event = window.pollEvent()) {
			if (event->is<Event::Closed>()) {
				window.close();
			}

			if (const auto* mouseButtonPressed = event->getIf<Event::MouseButtonPressed>()) {
				if (mouseButtonPressed->button == Mouse::Button::Left) {
					int x = mouseButtonPressed->position.x;
					int y = mouseButtonPressed->position.y;

					if (firstClick) {
						currC = x / 80;
						currR = y / 80;
						firstClick = false;
					} else {
						int newC = x / 80;
						int newR = y / 80;

						if (!board.MovePiece(currR, currC, newR, newC)) {
							cout << "Move failed. Try again." << endl;
						}

						firstClick = true;
					}
				}
			}
		}

		window.clear();
		board.PrintBoard(window);
		window.display();
	}
}