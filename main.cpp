#include "Fenetre.hpp"
#include "Ocean.hpp"

#include <ctime>
#include <iostream>

Ocean *ocean = new Ocean(170, 350, 64, 128, 60, 1, 0, 0.000002);

int main (int argc, char **argv) {
	
	srand(time(NULL));
	
	ocean->generateHeight0();
	
	Fenetre::init(WIDTH, HEIGHT, "Ocean Simulation", argc, argv);
	Fenetre::setFPS(35);
	Fenetre::launch();
	
	Fenetre::quit();
	
	delete ocean;
	
    return 0;
	
}