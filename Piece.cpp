#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Piece.h"
using namespace std;
using namespace sf;

Piece::Piece() : color("null"), type("tile") {}

Piece::Piece(const string c, const string t) : color(c), type(t) {
	shape.setRadius(20.f);
	if (color == "black") {
		shape.setFillColor(Color::Black);
		if (type == "king") {
			shape.setOutlineThickness(3.f);
			shape.setOutlineColor(Color::Yellow);
		}
	} else if (color == "white") {
		shape.setFillColor(Color::White);
		if (type == "king") {
			shape.setOutlineThickness(3.f);
			shape.setOutlineColor(Color::Yellow);
		}
	}
}

void Piece::SetPosition(float x, float y) {
	shape.setPosition(Vector2f(x, y));
}

void Piece::Draw(RenderWindow& window) const {
	if (color == "black" || color == "white"){
		window.draw(shape);
	}
}