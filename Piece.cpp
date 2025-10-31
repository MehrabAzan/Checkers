#include <string>
#include <iostream>
#include "Piece.h"
using namespace std;

Piece::Piece() : color(""), type("man") {}

Piece::Piece(const string& c, const string& t) : color(c), type(t) {}