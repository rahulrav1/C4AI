#include <iostream>
#include "../include/nnplayer.h"
#include "../include/connect_four_visualizer.h"

using connect4::visualizer::ConnectFourApp;



void prepareSettings(ConnectFourApp::Settings* settings) {
    settings->setResizable(false);
}
CINDER_APP(ConnectFourApp, ci::app::RendererGl, prepareSettings);




