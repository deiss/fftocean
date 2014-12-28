/* DEISS Olivier                                                                                  */
/* Class : Height                                                                                 */
/* Last Update : 28/12/2014                                                                       */

/* This class defines a fonctor that will generate the initial random ocean wave height field h0. */
/* The fonctor is to be used in std generate() function.                                          */

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
	
		int								  _nx;        // nb of x points - must be a power of 2
		int								  _ny;        // nb of y points - must be a power of 2
		std::vector<std::vector<double> > _philipps;  // Philips spectrum _philipps[y][x]
		int								  _x;
		int								  _y;
	
};

#endif