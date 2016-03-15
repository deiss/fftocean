/*

Project: Ocean
Author: DEISS Olivier

This software is offered under the GPL license. See COPYING for more information.

*/

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Affichage/Window.hpp"
#include "Ocean/Ocean.hpp"

/* Ocean(lx, ly, nx, ny, windSpeed,  windAlignment, minWaveSize, A) */
// See Philipps.hpp for more details about these parameters
Ocean* ocean = new Ocean(170, 350, 64, 128, 50, 2, 0, 0.000003);
//Ocean *ocean = new Ocean(128, 128, 128, 128, 10, 2, 0, 0.00005);

/* handle for the window */
int mainwindow;

int main (int argc, char** argv) {
    /* random for gaussian numbers */
    srand(time(NULL));
    
    /* initial ocean wave height field */
    ocean->generateHeight0();
    
    /* set up of the window */
    Window::init(WIDTH, HEIGHT, "Ocean Simulation", argc, argv);
    Window::setFPS(35);
    Window::launch();
    
    Window::quit();
    delete ocean;
    
    return 0;
}
