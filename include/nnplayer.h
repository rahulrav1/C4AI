#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <fstream>
//#include "board.h"
class Board;
class NNPlayer {
    public:
        NNPlayer();
        void ReadData();
        void TrainNetwork();
        void ComputeProbabilities(std::vector<std::vector<int>> &piece_counts, std::string &board);
        std::pair<int, int> TestNetwork(Board &current_board);

    private:
        std::string data_path_ = "/Users/rahulnathan/Documents/CS 126/NaiveBayes/cinder_0.9.2_mac/my-projects/final-project-rahulrav1/data/connect-4.data";
        std::vector<Board> training_data_;
        std::vector<std::vector<int>> piece_probabilities;
        const int kRows = 6;
        const int kCols = 7;
};
