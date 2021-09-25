#pragma once


#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <vector>
#include "../include/board.h"
namespace connect4 {
    namespace visualizer {

        class ConnectFourApp : public ci::app::App {
            public:
                ConnectFourApp();
                void draw() override;
                void mouseDown(ci::app::MouseEvent event) override;
                void mouseDrag(ci::app::MouseEvent event) override;
                void keyDown(ci::app::KeyEvent event) override;

            private:
                NNPlayer nnp_;
                NegamaxSolver solver_;
                const std::string starting_board_ = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
                Board current_board_;
                bool selected_opponent_ = false;
                bool negamax_ = false;
                bool game_has_started_ = false;
                bool user_won_ = false;
                bool nnp_won_ = false;
        };

    }  // namespace visualizer

}  // namespace connect4

