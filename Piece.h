#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <iostream>
using namespace std;

class Piece {
	private:
		string color;
		string type;
	public:
		Piece();
		Piece(const string& c, const string& t);
		string GetColor() const { return color; }
		string GetType() const { return type; }
		void SetColor(const string& c) { this->color = c; }
		void SetType(const string& t) { this->type = t; }
		void Promotion() { this->type = "king"; }
};

#endif