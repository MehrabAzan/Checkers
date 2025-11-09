#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

class Piece {
	private:
		string color;
		string type;
		sf::CircleShape shape;
	public:
		Piece();
		Piece(string c, string t);
		string GetColor() const { return this->color; }
		string GetType() const { return this->type; }
		void Promotion() { this->type = "king"; }
		void SetPosition(float x, float y);
		void Draw(sf::RenderWindow& window) const;
};

#endif