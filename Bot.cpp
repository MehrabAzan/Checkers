#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Piece.h"
#include "Board.h"
#include "Bot.h"
using namespace std;

vector<int> Bot::Move(Board& board) {
    vector<vector<int>> possibleMoves = AllPossibleMoves(board);
    if (possibleMoves.empty()) {
        return {};
    }

    int bestScore = INT_MIN;
    vector<int> bestMove;

    for (const auto& move : possibleMoves) {
        Board tempBoard = board;
        if (!tempBoard.MovePiece(move[0], move[1], move[2], move[3])) {
            continue;
        }
        int score = MiniMax(tempBoard, maxDepth, false, INT_MIN, INT_MAX);
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }

    return bestMove;
}

int Bot::EvaluateBoard(Board& board) {
    int score = 0;

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece piece = board.GetPiece(r, c);
            if (piece.GetColor() == "null") {
                continue;
            }

            int value = 0;
            if (piece.GetType() == "man") value = 1;
            else if (piece.GetType() == "king") value = 2;

            if (piece.GetColor() == "black") score += value;
            else if (piece.GetColor() == "white") score -= value;
        }
    }

    return score;
}

vector<vector<int>> Bot::AllPossibleMoves(Board& board) {
    vector<vector<int>> possibleMoves;

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece piece = board.GetPiece(r, c);
            if (piece.GetColor() != color) {
                continue;
            }

            if (piece.GetType() == "man") {
                int dr = (color == "black") ? 1 : -1;

                for (int dc : {-1, 1}) {
                    int nr = r + dr;
                    int nc = c + dc;
                    if (nr >= 0 && nr < 8 && nc >= 0 && nc < 8) {
                        if (board.GetPiece(nr, nc).GetColor() == "null") {
                            possibleMoves.push_back({ r, c, nr, nc });
                        }
                    }

                    int cr = r + 2 * dr;
                    int cc = c + 2 * dc;
                    int mr = r + dr;
                    int mc = c + dc;
                    if (cr >= 0 && cr < 8 && cc >= 0 && cc < 8 && mr >= 0 && mr < 8 && mc >= 0 && mc < 8) {
                        if (board.GetPiece(cr, cc).GetColor() == "null") {
                            string midColor = board.GetPiece(mr, mc).GetColor();
                            if (midColor != "null" && midColor != color) {
                                possibleMoves.push_back({ r, c, cr, cc });
                            }
                        }
                    }
                }
            }
            else if (piece.GetType() == "king") {
                for (int dr : {-1, 1}) {
                    for (int dc : {-1, 1}) {
                        for (int step = 1; step < 8; step++) {
                            int nr = r + dr * step;
                            int nc = c + dc * step;
                            if (nr < 0 || nr >= 8 || nc < 0 || nc >= 8) {
                                break;
                            }
                            if (board.GetPiece(nr, nc).GetColor() != "null") {
                                continue;
                            }

                            if (step == 2) {
                                int mr = r + dr;
                                int mc = c + dc;
                                string midColor = board.GetPiece(mr, mc).GetColor();
                                if (midColor != "null" && midColor != color) {
                                    possibleMoves.push_back({ r, c, nr, nc });
                                }
                            }
                            else {
                                possibleMoves.push_back({ r, c, nr, nc });
                            }
                        }
                    }
                }
            }
        }
    }

    return possibleMoves;
}

int Bot::MiniMax(Board& board, int depth, bool isMaximizing, int alpha, int beta) {
    if (depth == 0) {
        return EvaluateBoard(board);
    }

    const string sideColor = isMaximizing ? "black" : "white";
    vector<vector<int>> possibleMoves;

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece piece = board.GetPiece(r, c);
            if (piece.GetColor() != sideColor) {
                continue;
            }

            if (piece.GetType() == "man") {
                int dr = (sideColor == "black") ? 1 : -1;

                for (int dc : {-1, 1}) {
                    int nr = r + dr;
                    int nc = c + dc;
                    if (nr >= 0 && nr < 8 && nc >= 0 && nc < 8) {
                        if (board.GetPiece(nr, nc).GetColor() == "null") {
                            possibleMoves.push_back({ r, c, nr, nc });
                        }
                    }

                    int cr = r + 2 * dr;
                    int cc = c + 2 * dc;
                    int mr = r + dr;
                    int mc = c + dc;
                    if (cr >= 0 && cr < 8 && cc >= 0 && cc < 8 && mr >= 0 && mr < 8 && mc >= 0 && mc < 8) {
                        if (board.GetPiece(cr, cc).GetColor() == "null") {
                            string midColor = board.GetPiece(mr, mc).GetColor();
                            if (midColor != "null" && midColor != sideColor) {
                                possibleMoves.push_back({ r, c, cr, cc });
                            }
                        }
                    }
                }
            }
            else if (piece.GetType() == "king") {
                for (int dr : {-1, 1}) {
                    for (int dc : {-1, 1}) {
                        for (int step = 1; step < 8; step++) {
                            int nr = r + dr * step;
                            int nc = c + dc * step;
                            if (nr < 0 || nr >= 8 || nc < 0 || nc >= 8) {
                                break;
                            }
                            if (board.GetPiece(nr, nc).GetColor() != "null") {
                                continue;
                            }

                            if (step == 2) {
                                int mr = r + dr;
                                int mc = c + dc;
                                string midColor = board.GetPiece(mr, mc).GetColor();
                                if (midColor != "null" && midColor != sideColor) {
                                    possibleMoves.push_back({ r, c, nr, nc });
                                }
                            }
                            else {
                                possibleMoves.push_back({ r, c, nr, nc });
                            }
                        }
                    }
                }
            }
        }
    }

    if (possibleMoves.empty()) {
        return EvaluateBoard(board);
    }

    if (isMaximizing) {
        int bestEval = INT_MIN;
        for (const auto& move : possibleMoves) {
            Board tempBoard = board;
            if (!tempBoard.MovePiece(move[0], move[1], move[2], move[3])) {
                continue;
            }
            int eval = MiniMax(tempBoard, depth - 1, false, alpha, beta);
            bestEval = max(bestEval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha) {
                break;
            }
        }
        return bestEval;
    }
    else {
        int bestEval = INT_MAX;
        for (const auto& move : possibleMoves) {
            Board tempBoard = board;
            if (!tempBoard.MovePiece(move[0], move[1], move[2], move[3])) {
                continue;
            }
            int eval = MiniMax(tempBoard, depth - 1, true, alpha, beta);
            bestEval = min(bestEval, eval);
            beta = min(beta, eval);
            if (beta <= alpha) {
                break;
            }
        }
        return bestEval;
    }
}
