#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Piece.h"
using namespace std;

Piece::Piece() : color("null"), type("tile") {}

Piece::Piece(const string c, const string t) : color(c), type(t) {
	shape.setRadius(20.f);
	if (color == "black") {
		shape.setFillColor(sf::Color::Black);
	} else if (color == "white") {
		shape.setFillColor(sf::Color::White);
	} else {
		shape.setFillColor(sf::Color::Transparent);
	}
}

void Piece::SetPosition(float x, float y) {
	shape.setPosition(sf::Vector2f(x, y));
}

void Piece::Draw(sf::RenderWindow& window) const {
	window.draw(shape);
}