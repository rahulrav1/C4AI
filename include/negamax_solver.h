#pragma once
#include <iostream>
#include <vector>
//#include "../include/board.h"
class Board;
class NegamaxSolver {
    public:
        NegamaxSolver();
        std::pair<int, int> negamax(Board board, int depth, char player, char opponent); // Returns column corresponding to best move
        int MaxAlpha(Board board, int depth, int alpha, int beta, char player, char opponent);
        int MinBeta(Board board, int depth, int alpha, int beta, char player, char opponent);
    private:


};


