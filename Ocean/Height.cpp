#include "Height.hpp"

#include <cmath>
#include <ctime>

double Height::operator()() {
	
	_y++;
	
	return sqrt(_philipps[_x+(_nx/2)][_y+(_ny/2)]/2) * nbGauss();
	
}

void Height::generatePhilipps(Philipps *p) {
	
	_philipps.resize(_nx+1);
	
	for(std::vector<std::vector<double> >::iterator itx = _philipps.begin() ; itx != _philipps.end() ; itx++) {
		
		itx->resize(_ny+1);
		p->init(std::distance(_philipps.begin(), itx));
		generate(itx->begin(), itx->end(), *p);
		
	}
	
}

double Height::nbGauss() {
	
	double var1, var2, s;
	
	do {
		
		var1 = (rand() % 201 - 100)/(double)100;
		var2 = (rand() % 201 - 100)/(double)100;
		s = var1*var1 + var2*var2;
	
	} while(s >= 1 || s == 0);
	
	return var1*sqrt((-log(s))/s);
	
}