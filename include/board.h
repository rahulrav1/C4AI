#pragma once

#include <vector>
#include <iostream>
#include <tuple>
#include <string>
#include "nnplayer.h"
#include "negamax_solver.h"
#include "cinder/gl/gl.h"

using glm::vec2;

class Board {
    public:
        Board(std::string string_board);
        void UpdateBoard(int row, int col, char player);
        std::vector<std::vector<bool>> FindValidMoves();
        void Draw();
        void HandleMove(const vec2& click_screen_coords, NNPlayer nnp, NegamaxSolver solver, bool negamax);
        bool CheckForWinner(char player, int length);
        bool ValidMove(int col);
        int ComputeBoardScore(Board board, char player);
        std::vector<std::vector<char>> CreateVectorBoard();
        bool CheckHorizontal(Board board, int length, char player);
        bool CheckVertical(Board board, int length, char player);
        bool CheckAscDiagonals(Board board, int length, char player);
        bool CheckDescDiagonals(Board board, int length, char player);
        void UpdateBoardScore(int length, char player);
        std::string &GetBoard();
        std::vector<std::pair<vec2, std::pair<int, int>>> &GetPieceCenters();
        void ResetBoard(std::string new_board);
        int MovesMade();

    private:
        std::string board_;
        std::vector<std::pair<vec2, std::pair<int, int>>> piece_centers_;
        std::vector<bool> free_columns;
        int moves_ = 0;
        std::tuple<int, int, int> player_one_score = {};
        std::tuple<int, int, int> player_two_score = {};
        size_t kBoardRows = 6;
        size_t kBoardCols = 7;
        size_t kMaxBoardPieces = 42;
        float min_x_ = 300;
        float max_x_ = 900;
        float min_y_ = 100;
        float max_y_ = 750;

};


