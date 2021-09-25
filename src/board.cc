#include "../include/board.h"
using glm::vec2;

Board::Board(std::string string_board) {
    board_ = string_board;
}
void Board::Draw() {
    ci::gl::color(ci::Color8u(30, 144, 255));
    ci::Rectf pixel_bounding_box(vec2(min_x_, min_y_), vec2(max_x_, max_y_));
    ci::gl::drawSolidRect(pixel_bounding_box);


    float current_x = 352.5;
    float current_y = 171.43;
    int pieces_drawn = 0;
    int row = 0;
    int col = 0;
    while(pieces_drawn < kMaxBoardPieces) {
        if(current_x > max_x_) {
            current_x = 352.5;
            current_y += 101.43;
            row++;
            col = 0;
        }
        if(board_[(col) * kBoardRows + (row)] == 'x') {
            ci::gl::color(ci::Color("red"));
        }
        else if(board_[(col) * kBoardRows + (row)] == 'o') {
            ci::gl::color(ci::Color("yellow"));
        }
        else {
            ci::gl::color(ci::Color8u(173, 216, 230));
        }
        ci::gl::drawSolidCircle(vec2(current_x, current_y), 30);
        piece_centers_.emplace_back(std::make_pair(vec2(current_x, current_y), std::make_pair(row, col)));
        current_x += 82.5;
        pieces_drawn++;
        col++;
    }


}
std::vector<std::vector<bool>> Board::FindValidMoves() {
    std::vector<std::vector<bool>> valid_moves(kBoardRows, std::vector<bool> (kBoardCols, false));
    std::vector<bool> free_cols(kBoardCols, false);
    for(int col = 0; col<kBoardCols; col++) {
        for(int row = 0; row<kBoardRows; row++) {
            if(board_[(col * kBoardRows) + (kBoardRows-row-1)] == 'b') {
                valid_moves[kBoardRows-row-1][col] = true;
                free_cols[col] = true;
                break;
            }
        }
    }
    free_columns = free_cols;
    return valid_moves;
}
std::vector<std::vector<char>> Board::CreateVectorBoard() {
    std::vector<std::vector<char>> array_board(kBoardRows, std::vector<char>(kBoardCols));
    int index = 0;
    for(int j = 0; j<kBoardCols; j++) {
        for(int i = 0; i<kBoardRows; i++) {
            array_board[i][j] = board_[index];
            index++;
        }
    }
    return array_board;
}
void Board::UpdateBoardScore(int length, char player) {
    if(length == 2) {
        if(player == 'x') {
            std::get<0>(player_one_score) = 1;
        }
        else {
            std::get<0>(player_two_score) = 1;
        }
    }
    else if(length == 3) {
        if(player == 'x') {
            std::get<1>(player_one_score) = 1;
        }
        else {
            std::get<1>(player_two_score) = 1;
        }
    }
    else {
        if(player == 'x') {
            std::get<2>(player_one_score) = 1;
        }
        else {
            std::get<2>(player_two_score) = 1;
        }
    }
}
bool Board::CheckHorizontal(Board board, int length, char player) {
    std::vector<std::vector<char>> vec_board = board.CreateVectorBoard();
    bool sequence_found = false;
    for(int row=0; row<kBoardRows; row++) {
        int seq_len = 0;
        for(int col=0; col<kBoardCols; col++) {
            seq_len = vec_board[row][col] == player ? seq_len+1 : 0;
            if(seq_len >= length) {
                UpdateBoardScore(length, player);
                sequence_found = true;
            }
        }
    }
    return sequence_found;
}
bool Board::CheckVertical(Board board, int length, char player) {
    std::vector<std::vector<char>> vec_board = board.CreateVectorBoard();
    bool sequence_found = false;
    for(int col=0; col<kBoardCols; col++) {
        int seq_len = 0;
        for(int row=0; row<kBoardRows; row++) {
            seq_len = vec_board[row][col] == player ? seq_len+1 : 0;
            if(seq_len >= length) {
                UpdateBoardScore(length, player);
                sequence_found = true;
            }
        }
    }
    return sequence_found;
}
bool Board::CheckAscDiagonals(Board board, int length, char player) {
    std::vector<std::vector<char>> vec_board = board.CreateVectorBoard();
    bool sequence_found = false;
    int diagonal_count = 0;
    int row = kBoardRows - 1;
    int col = 6;
    while(diagonal_count < kBoardRows + kBoardCols - 1) {
        int temp_row = row;
        int temp_col = col;
        int seq_length = 0;
        while(temp_row >= 0 && temp_col < kBoardCols) {
            if(vec_board[temp_row][temp_col] == player) {
                seq_length++;
            }
            else {
                seq_length = 0;
            }
            if(seq_length >= length) {
                UpdateBoardScore(length, player);
                sequence_found = true;
            }
            temp_row--;
            temp_col++;
        }
        diagonal_count++;
        if(col > 0) {
            col--;
        }
        else if(diagonal_count >= (kBoardRows + kBoardCols - 1)/2) {
            row--;
        }
    }
    return sequence_found;
}
bool Board::CheckDescDiagonals(Board board, int length, char player) {
    std::vector<std::vector<char>> vec_board = board.CreateVectorBoard();
    bool sequence_found = false;
    int diagonal_count = 0;
    int row = kBoardRows - 1;
    int col = 0;
    while(diagonal_count < kBoardRows + kBoardCols - 1) {
        int temp_row = row;
        int temp_col = col;
        int seq_length = 0;
        while(temp_row < kBoardRows && temp_col < kBoardCols) {
            if(vec_board[temp_row][temp_col] == player) {
                seq_length++;
            }
            else {
                seq_length = 0;
            }
            if(seq_length >= length) {
                UpdateBoardScore(length, player);
                sequence_found = true;
            }
            temp_row++;
            temp_col++;
        }
        diagonal_count++;
        if(row > 0) {
            row--;
        }
        else if(diagonal_count >= (kBoardRows + kBoardCols - 1)/2) {
            col++;
        }
    }
    return sequence_found;
}
// Make sure move ordering is correct, correct player goes first, etc
bool Board::CheckForWinner(char player, int length) {
    bool horizontal = CheckHorizontal(*this, length, player);
    bool vertical = CheckVertical(*this, length, player);
    bool ascending = CheckAscDiagonals(*this, length, player);
    bool descending = CheckDescDiagonals(*this, length, player);
    return (horizontal || vertical || ascending || descending);
}
int Board::ComputeBoardScore(Board board, char player) {
    player_one_score = {};
    player_two_score = {};
    bool player_one_won = board.CheckForWinner('x', 4);
    board.CheckForWinner('x', 3);
    board.CheckForWinner('x', 2);
    bool player_two_won =  board.CheckForWinner('o', 4);
    board.CheckForWinner('o', 3);
    board.CheckForWinner('o', 2);
    if(player == 'x') {
        if(player_two_won) {
            return INT32_MIN;
        }
    }
    if(player == 'o') {
        if(player_one_won) {
            return INT32_MIN;
        }
    }
    int first_score = (std::get<2>(player_one_score)*99999) *
            (std::get<1>(player_one_score)*999) * (std::get<0>(player_one_score)*99);
    int second_score = (std::get<2>(player_two_score)*99999) *
                      (std::get<1>(player_two_score)*999) * (std::get<0>(player_two_score)*99);
    return (first_score - second_score);
}
void Board::HandleMove(const vec2& click_screen_coords, NNPlayer nnp, NegamaxSolver solver, bool negamax) {
    std::vector<std::pair<vec2, std::pair<int, int>>> piece_centers = this->GetPieceCenters();
    std::vector<std::vector<bool>> valid_moves = this->FindValidMoves();
    for(int piece = 0; piece<piece_centers.size(); piece++) {
        vec2 pos = piece_centers[piece].first;
        int row =  piece_centers[piece].second.first;
        int col =  piece_centers[piece].second.second;
        if(glm::distance(pos, click_screen_coords) <= 30 && valid_moves[row][col]) {
            this->UpdateBoard(row, col, 'x');
            if(negamax) {
                std::pair<int, int> best_move = solver.negamax(*this, 3, 'o', 'x');
                this->UpdateBoard(best_move.first, best_move.second, 'o');
            }
            else {
                std::pair<int, int> opponent_move = nnp.TestNetwork(*this);
                this->UpdateBoard(opponent_move.first, opponent_move.second, 'o');
            }
            break;
        }
    }
}
bool Board::ValidMove(int col) {
    FindValidMoves();
    return free_columns[col];
}
void Board::UpdateBoard(int row, int col, char player) {
    board_[col * kBoardRows + row] = player;
    moves_++;
}
std::string & Board::GetBoard() {
    return board_;
}
std::vector<std::pair<vec2, std::pair<int, int>>> & Board::GetPieceCenters() {
    return piece_centers_;
}
void Board::ResetBoard(std::string new_board) {
    board_ = new_board;
}
int Board::MovesMade() {
    return moves_;
}