/* DEISS Olivier            */
/* Class : Height           */
/* Last Update : 12/28/2014 */

#include "Height.hpp"

#include <cmath>
#include <ctime>
#include <algorithm>

/* operator overloading to use Height as a fonctor */
double Height::operator()() {
	
	_y++;
	
    // computes the initial random h0
	return sqrt(_philipps[_x+(_nx/2)][_y+(_ny/2)]/2) * nbGauss();
	
}

/* generates the Philips spectrum */
void Height::generatePhilipps(Philipps *p) {
	
	_philipps.resize(_nx+1);
	
	for(std::vector<std::vector<double> >::iterator itx = _philipps.begin() ; itx != _philipps.end() ; itx++) {
		
		itx->resize(_ny+1);
		p->init(std::distance(_philipps.begin(), itx));
        std::generate(itx->begin(), itx->end(), *p);
		
	}
	
}

/* Gaussian random generator */
/* Box-Muller method */
double Height::nbGauss() {
	
	double var1, var2, s;
	
	do {
		
		var1 = (rand() % 201 - 100)/(double)100;
		var2 = (rand() % 201 - 100)/(double)100;
		s = var1*var1 + var2*var2;
	
	} while(s >= 1 || s == 0);
	
	return var1*sqrt((-log(s))/s);
	
}
