#include "connect_four_visualizer.h"
#include "../include/board.h"
#include "../include/nnplayer.h"
#include "../include/negamax_solver.h"
using glm::vec2;
namespace connect4 {
    namespace visualizer {

        ConnectFourApp::ConnectFourApp() : current_board_(starting_board_) {
            ci::app::setWindowSize(1200, 1200);
            nnp_.ReadData();
            nnp_.TrainNetwork();
        }
        void ConnectFourApp::draw() {
            if(game_has_started_) {
                int moves_made = current_board_.MovesMade();
                if(!selected_opponent_) {
                    ci::Color8u background_color(173, 216, 230);
                    ci::gl::clear(background_color);

                    ci::gl::drawStringCentered("Choose your opponent!", vec2(600, 300),
                                               ci::Color8u(30, 144, 255),
                                               ci::Font("Optima", 60));

                    ci::gl::color(ci::Color8u(70, 130, 100));

                    ci::gl::drawLine(vec2(470, 400), vec2(570, 400));
                    ci::gl::drawLine(vec2(470, 450), vec2(570, 450));
                    ci::gl::drawLine(vec2(470, 400), vec2(470, 450));
                    ci::gl::drawLine(vec2(570, 400), vec2(570, 450));
                    ci::gl::drawStringCentered("Negamax", vec2(520, 420),
                                               ci::Color8u(70, 130, 180),
                                               ci::Font("Optima", 20));


                    ci::gl::drawLine(vec2(620, 400), vec2(720, 400));
                    ci::gl::drawLine(vec2(620, 450), vec2(720, 450));
                    ci::gl::drawLine(vec2(620, 400), vec2(620, 450));
                    ci::gl::drawLine(vec2(720, 400), vec2(720, 450));
                    ci::gl::drawStringCentered("Neural Net", vec2(670, 420),
                                               ci::Color8u(70, 130, 180),
                                               ci::Font("Optima", 20));
                }
                else if(user_won_ || nnp_won_) {
                    ci::Color8u background_color(173, 216, 230);
                    ci::gl::clear(background_color);
                    ci::gl::color(ci::Color8u(30, 144, 255));
                    if(user_won_) {
                        ci::gl::drawStringCentered("You won the game!", vec2(600, 400),
                                                   ci::Color8u(30, 144, 255),
                                                   ci::Font("Optima", 100));
                    }
                    else {
                        ci::gl::drawStringCentered("Opponent won the game!", vec2(600, 400),
                                                   ci::Color8u(30, 144, 255),
                                                   ci::Font("Optima", 100));
                    }

                    ci::gl::color(ci::Color8u(70, 130, 100));
                    ci::gl::drawLine(vec2(530, 550), vec2(670, 550));
                    ci::gl::drawLine(vec2(530, 600), vec2(670, 600));
                    ci::gl::drawLine(vec2(530, 550), vec2(530, 600));
                    ci::gl::drawLine(vec2(670, 550), vec2(670, 600));
                    ci::gl::drawStringCentered("PLAY AGAIN", vec2(600, 570),
                                               ci::Color8u(70, 130, 180),
                                               ci::Font("Optima", 20));

                }
                else if(moves_made == starting_board_.size()) {
                    ci::Color8u background_color(173, 216, 230);
                    ci::gl::clear(background_color);
                    ci::gl::color(ci::Color8u(30, 144, 255));
                    ci::gl::drawStringCentered("Draw Game!", vec2(600, 400),
                                               ci::Color8u(30, 144, 255),
                                               ci::Font("Optima", 100));
                }
                else {
                    ci::Color8u background_color(173, 216, 230);
                    ci::gl::clear(background_color);
                    ci::gl::color(ci::Color8u(30, 144, 255));
                    ci::Rectf pixel_bounding_box(vec2(300, 100), vec2(900, 750));
                    ci::gl::drawSolidRect(pixel_bounding_box);
                    current_board_.Draw();
                    if(current_board_.CheckForWinner('x', 4)) {
                        std::cout << "X won" << std::endl;
                        user_won_ = true;
                    }
                    if(current_board_.CheckForWinner('o', 4)) {
                        std::cout << "O won" << std::endl;
                        nnp_won_ = true;
                    }
                }
            }
            else {
                ci::Color8u background_color(173, 216, 230);
                ci::gl::clear(background_color);
                ci::gl::drawStringCentered("Connect Four", vec2(600, 400),
                                           ci::Color8u(70, 130, 180),
                                           ci::Font("Optima", 100));

                ci::gl::color(ci::Color8u(70, 130, 100));
                ci::gl::drawLine(vec2(550, 550), vec2(650, 550));
                ci::gl::drawLine(vec2(550, 600), vec2(650, 600));
                ci::gl::drawLine(vec2(550, 550), vec2(550, 600));
                ci::gl::drawLine(vec2(650, 550), vec2(650, 600));
                ci::gl::drawStringCentered("PLAY", vec2(600, 570),
                                           ci::Color8u(70, 130, 180),
                                           ci::Font("Optima", 20));


            }
        }

        void ConnectFourApp::mouseDown(ci::app::MouseEvent event) {
            if(!game_has_started_) {
                vec2 click_screen_coords = event.getPos();
                if(click_screen_coords[0] >= 550 && click_screen_coords[0] <= 650 &&
                    click_screen_coords[1] >= 550 && click_screen_coords[1] <= 600) {
                    game_has_started_ = true;
                }
            }
            else if(!selected_opponent_) {
                vec2 click_screen_coords = event.getPos();
                if(click_screen_coords[0] >= 470 && click_screen_coords[0] <= 570 &&
                   click_screen_coords[1] >= 400 && click_screen_coords[1] <= 450) {
                    negamax_ = true;
                    selected_opponent_ = true;
                }
                else if(click_screen_coords[0] >= 620 && click_screen_coords[0] <= 720 &&
                        click_screen_coords[1] >= 400 && click_screen_coords[1] <= 450) {
                    negamax_ = false;
                    selected_opponent_ = true;
                }
            }
            else if(user_won_ || nnp_won_) {
                vec2 click_screen_coords = event.getPos();
                if(click_screen_coords[0] >= 530 && click_screen_coords[0] <= 670 &&
                   click_screen_coords[1] >= 550 && click_screen_coords[1] <= 600) {
                    user_won_ = false;
                    nnp_won_ = false;
                    Board blank_board(starting_board_);
                    current_board_ = blank_board;
                }
            }
            else {
                current_board_.HandleMove(event.getPos(), nnp_, solver_, negamax_);
            }
        }

        void ConnectFourApp::mouseDrag(ci::app::MouseEvent event) {

        }

        void ConnectFourApp::keyDown(ci::app::KeyEvent event) {

        }
    } //namespace visualizer
}  //namespace connectfourapp