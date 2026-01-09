#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Board.h"
#include "Piece.h"
#include "Bot.h"
using namespace std;
using namespace sf;

int main() {
	// create a board object
	Board board;

	// render the board
	RenderWindow window(VideoMode({ 640, 640 }), "Checkers");

	// check if the player is clicking for the first time
	bool firstClick = true;
	// current row and column of the selected piece
	int currC;
	int currR;
	// track whose turn it is
	bool playerTurn = true;
	// create a bot object
	Bot bot;
	// how many pieces bot and player have at the start
	int blackPieces = 12;
	int whitePieces = 12;

	Font font("arial.ttf");
	Text text(font);
	text.setCharacterSize(24);
	text.setFillColor(Color(139, 69, 19));
	text.setPosition({10.f, 10.f});

	Clock clock;
	bool showMessage = true;

	// while the window is open
	while (window.isOpen()) {
		// process events
		while (const optional event = window.pollEvent()) {
			// close window event
			if (event->is<Event::Closed>()) {
				window.close();
			}

			// if player's turn
			if (playerTurn) {
				// handle mouse button pressed event
				if (const auto* mouseButtonPressed = event->getIf<Event::MouseButtonPressed>()) {
					if (mouseButtonPressed->button == Mouse::Button::Left) {
						// get the x and y position of the mouse click
						int x = mouseButtonPressed->position.x;
						int y = mouseButtonPressed->position.y;

						// if the player is clicking for the first time
						if (firstClick) {
							// determine the row and column of the clicked tile
							currC = x / 80;
							currR = y / 80;
							// set firstClick to false
							firstClick = false;
							// get the piece at the clicked position
							Piece selectedPiece = board.GetPiece(currR, currC);

							// check if the player clicked outside the board
							if (currC < 0 || currC >= 8 || currR < 0 || currR >= 8) {
								text.setString("Please click within the board.");
								// reset firstClick to true if player clicked outside the board
								firstClick = true;
							}
							// ensure the player is only moving white pieces
							if (selectedPiece.GetColor() != "white") {
								text.setString("Please click white piece.");
								// reset firstClick to true if player clicked on invalid piece
								firstClick = true;
							}
						} else {
							// determine the new row and column the next tile the player clicked on
							int newC = x / 80;
							int newR = y / 80;

							// check if the move is valid
							// attempt to move the piece
							if (!board.MovePiece(currR, currC, newR, newC)) {
								text.setString("Invalid move. Try again.");
							} else {
								// switch to bot's turn
								playerTurn = false;
							}
							// reset back to first click when it goes back to player's turn
							firstClick = true;
						}
					}
				}
			} else {
				// creates a vector to hold the bot's move
				vector<int> move = bot.Move(board);
				// if it does not return the failsafe move, then the bot moves
				if (move[0] != -1) {
					board.MovePiece(move[0], move[1], move[2], move[3]);
				}
				// switch back to player's turn
				playerTurn = true;
			}
		}
		// these will check current piece counts to determine if someone has won
		int whiteCount = 0;
		int blackCount = 0;

		for (int r = 0; r < 8; r++) {
			for (int c = 0; c < 8; c++) {
				// grabs current piece at position
				Piece checkColor = board.GetPiece(r, c);

				// increments the appropriate color count
				if (checkColor.GetColor() == "black") {
					blackCount++;
				} else if (checkColor.GetColor() == "white") {
					whiteCount++;
				}
			}
		}

		// updates piece counts
		blackPieces = blackCount;
		whitePieces = whiteCount;

		// checks for win condition
		if (blackPieces == 0) {
			text.setString("White wins!");
			window.close();
		} else if (whitePieces == 0) {
			text.setString("Black wins!");
			window.close();
		}

		// clear the window and print the board
		window.clear();
		board.PrintBoard(window);
		// display the contents of the window
		window.draw(text);
		window.display();
	}
}