#include "negamax_solver.h"
#include "../include/board.h"

NegamaxSolver::NegamaxSolver() = default;


std::pair<int, int> NegamaxSolver::negamax(Board board, int depth, char player, char opponent) {
    std::pair<int, int> best_move = {};
    std::vector<int> moves_to_consider;
    std::vector<std::vector<bool>> moves = board.FindValidMoves();
    int best_score = INT32_MIN;
    int alpha = INT32_MIN;
    int beta = INT32_MAX;
    for(int col = 0; col<7; col++) {
        if(board.ValidMove(col)) {
            moves_to_consider.push_back(col);
            for(int row = 0; row<6; row++) {
                if(moves[row][col]) {
                    best_move = std::make_pair(row, col);
                }
            }
        }
    }
    for(int move : moves_to_consider) {
        Board copy = board;
        int row;
        for(row = 0; row<6; row++) {
            if(moves[row][move]) {
                break;
            }
        }
        copy.UpdateBoard(row, move, player);
        int board_score = MinBeta(copy, depth-1, alpha, beta, player, opponent);
        if(board_score > best_score) {
            best_score = board_score;
            best_move = {row, move};
        }
    }
    return best_move;
}
int NegamaxSolver::MaxAlpha(Board board, int depth, int alpha, int beta, char player, char opponent) {
    std::vector<int> moves_to_consider;
    std::vector<std::vector<bool>> valid_moves = board.FindValidMoves();
    for(int col = 0; col<7; col++) {
        if(board.ValidMove(col)) {
            Board copy = board;
            for(int row = 0; row<6; row++) {
                if(valid_moves[row][col]) {
                    copy.UpdateBoard(row, col, player);
                    moves_to_consider.push_back(col);
                    break;
                }
            }
        }
    }
    if(depth == 0 || moves_to_consider.empty()
        || board.CheckForWinner('x', 4) || board.CheckForWinner('o', 4)) {
        return board.ComputeBoardScore(board, player);
    }
    int new_alpha = alpha;
    for(int move : moves_to_consider) {
        int cur_score = INT32_MIN;
        if(new_alpha < beta) {
            Board copy = board;
            int row;
            for(row = 0; row<6; row++) {
                if(valid_moves[row][move]) {
                    break;
                }
            }
            copy.UpdateBoard(row, move, player);
            cur_score = MinBeta(copy, depth-1, new_alpha, beta, player, opponent);
        }
        if(cur_score > new_alpha) {
            new_alpha = cur_score;
        }
    }
    return new_alpha;
}
int NegamaxSolver::MinBeta(Board board, int depth, int alpha, int beta, char player, char opponent) {
    std::vector<int> moves_to_consider;
    std::vector<std::vector<bool>> valid_moves = board.FindValidMoves();
    for(int col = 0; col<7; col++) {
        if(board.ValidMove(col)) {
            Board copy = board;
            for(int row = 0; row<6; row++) {
                if(valid_moves[row][col]) {
                    copy.UpdateBoard(row, col, player);
                    moves_to_consider.push_back(col);
                    break;
                }
            }
        }
    }
    if(depth == 0 || moves_to_consider.empty()
       || board.CheckForWinner('x', 4) || board.CheckForWinner('o', 4)) {
        return board.ComputeBoardScore(board, player);
    }
    int cur_beta = beta;
    for(int move : moves_to_consider) {
        int cur_score = INT32_MIN;
        if(alpha < cur_beta) {
            Board copy = board;
            int row;
            for(row = 0; row<6; row++) {
                if(valid_moves[row][move]) {
                    break;
                }
            }
            copy.UpdateBoard(row, move, opponent);
            cur_score = MaxAlpha(copy, depth-1, alpha, cur_beta, player, opponent);
        }
        if(cur_score < cur_beta) {
            cur_beta = cur_score;
        }
    }
    return cur_beta;
}
