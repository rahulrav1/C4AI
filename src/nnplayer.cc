#include <sstream>
#include "../include/nnplayer.h"
#include "../include/board.h"

NNPlayer::NNPlayer() = default;

void NNPlayer::ReadData() {
    std::ifstream data(data_path_);
    std::string line;
    int row = 0;
    while (std::getline(data, line)) {
        std::stringstream s_stream(line); //create string stream from the string
        std::string parsed_board = "";
        while(s_stream.good()) {
            std::string tok;
            getline(s_stream, tok, ',');
            if(tok == "x" || tok == "o" || tok == "d") {
                parsed_board += tok;
            }
            else {
                parsed_board += tok[0];
            }
        }
        training_data_.emplace_back(Board(parsed_board));
        row++;
    }
}
void NNPlayer::TrainNetwork() {
    // Calculate probability that piece at position i, j is in winning position
    std::vector<std::vector<int>> piece_counts(kRows, std::vector<int> (kCols, 0));
    for(Board &b : training_data_) {
        std::string board = b.GetBoard();
        ComputeProbabilities(piece_counts, board);
    }
    piece_probabilities = piece_counts;
}
void NNPlayer::ComputeProbabilities(std::vector<std::vector<int>> &piece_counts, std::string &board) {
    for(int col = 0; col<kCols; col++) {
        for(int row = 0; row<kRows; row++) {
            if(std::string(1, board[(col * kRows) + row]) == "o" &&
                std::string(1, board[board.size() - 1]) == "w") {
                piece_counts[row][col]++;
            }
        }
    }
}
std::pair<int, int> NNPlayer::TestNetwork(Board &current_board) {
    std::pair<int, int> best_move = {};
    size_t best_move_count = 0;
    std::vector<std::vector<bool>> valid_moves = current_board.FindValidMoves();
    for(int row = 0; row<kRows; row++) {
        for(int col = 0; col<kCols; col++) {
            if(valid_moves[row][col]) {
                if(piece_probabilities[row][col] > best_move_count) {
                    best_move = std::make_pair(row, col);
                    best_move_count = piece_probabilities[row][col];
                }
            }
        }
    }
    //best_move.first = kRows - best_move.first - 1;
    //best_move.second = kCols - best_move.second - 1;
    return best_move;
}

