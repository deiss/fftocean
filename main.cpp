/* DEISS Olivier            */
/* File : main.cpp          */
/* Last Update : 12/28/2014 */

#include "Fenetre.hpp"
#include "Ocean.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

// Ocean(lx, ly, nx, ny, windSpeed,  windAlignment, minWaveSize, A)
// See Philipps.hpp for more details about these parameters
Ocean *ocean = new Ocean(170, 350, 64, 128, 50, 2, 0, 0.000003);

// handle for the window
int mainwindow;

int main (int argc, char **argv) {
	
    // random generator for gaussian numbers
	srand(time(NULL));
	
    // initial ocean wave height field
	ocean->generateHeight0();
	
    // set up the window
	Fenetre::init(WIDTH, HEIGHT, "Ocean Simulation", argc, argv);
	Fenetre::setFPS(35);
	Fenetre::launch();
	
	Fenetre::quit();
	
	delete ocean;
	
    return 0;
	
}