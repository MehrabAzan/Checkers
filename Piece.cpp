#include <string>
#include <SFML/Graphics.hpp>
#include "Piece.h"
using namespace std;
using namespace sf;

Piece::Piece(const string& c, const string& t) : color(c), type(t) {
	// sets up a circle shape to represent the piece
	shape.setRadius(20.f);
	if (color == "black") {
		// color the piece black
		shape.setFillColor(Color::Black);
	} else if (color == "white") {
		// color the piece white
		shape.setFillColor(Color::White);
	}
}

void Piece::SetPosition(float x, float y) {
	// set the position of the piece's shape
	shape.setPosition(Vector2f(x, y));
}

void Piece::Draw(RenderWindow& window) const {
	// draw the piece only if it's not an empty tile
	if (color == "black" || color == "white"){
		window.draw(shape);
	}
}

void Piece::Promotion() {
	// promote the piece to a king by changing its type and outline
	type = "king";
	shape.setOutlineThickness(3.f);
	shape.setOutlineColor(Color::Yellow);
}