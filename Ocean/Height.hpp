#ifndef HEIGHTHPP
#define HEIGHTHPP

#include "Philipps.hpp"

#include <iostream>
#include <vector>

class Height {
	
	public :
	
		double operator()();
		void   generatePhilipps(Philipps*);
		void   init(int i)					 { _x = i - _nx/2; _y = -_ny/2; }
		double nbGauss();
		void   setSize(double nx, double ny) { _nx = nx; _ny = ny; }
	 
	private :
	
		int								  _nx;
		int								  _ny;
		std::vector<std::vector<double> > _philipps;
		int								  _x;
		int								  _y;
	
};

#endif

/* foncteur qui calcule les ~h0 nécessaires */