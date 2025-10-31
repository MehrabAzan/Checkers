#include <iostream>
#include <string>
#include "Board.h"
#include "Piece.h"
using namespace std;

int main() {
    Board board(8, 8);
    board.InitializeBoard();
	board.PrintBoard();
}
