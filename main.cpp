#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Board.h"
#include "Piece.h"
using namespace std;

int main() {
	Board board;
	board.InitializeBoard();

	sf::RenderWindow window(sf::VideoMode({640, 640}), "Checkers Game");
	while (window.isOpen()) {
		while (const optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		window.clear();
		board.PrintBoard(window);
		window.display();
	}
}