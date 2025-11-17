#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Piece {
	private:
		string color;
		string type;
		CircleShape shape;
	public:
		Piece() : color("null"), type("tile") {}
		Piece(string c, string t);
		string GetColor() const { return this->color; }
		string GetType() const { return this->type; }
		void Promotion();
		void SetPosition(float x, float y);
		void Draw(RenderWindow& window) const;
};

#endif