#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

// Piece class representing a checkers piece or an empty tile
class Piece {
	private:
		// this is the color of the piece: "black", "white", or "null" for empty tile
		string color;
		string type;
		// graphical representation of the piece
		CircleShape shape;
	public:
		// default constructor resorts to a empty tile
		Piece() : color("null"), type("tile") {}
		// parameterized constructor
		Piece(const string& c, const string& t);
		// getters
		string GetColor() const { return this->color; }
		string GetType() const { return this->type; }
		// promotion to king
		void Promotion();
		// set position and draw functions
		void SetPosition(float x, float y);
		void Draw(RenderWindow& window) const;
};

#endif