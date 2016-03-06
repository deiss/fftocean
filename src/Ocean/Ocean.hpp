/* This class defines a an ocean. It contains all the data required to its computation.            */
/* First a philipps spectrum is created. It is used to create the initial ocean wave height field. */
/* From this initial wave height field, it is possible to compute the next ones.                   */
/* To render, FFT is used to obtain time-domain data drom these wave height field.  (FFT-1)        */

#ifndef OCEANHPP
#define OCEANHPP

#include "../FFT/FFT.hpp"
#include "Height.hpp"
#include "Philipps.hpp"

#include <vector>

class Ocean {
	
	public :
	
		Ocean(const double, const double, const int, const int, const double, const int, const double, const double);
		~Ocean()	 { delete _philipps; }
		
        void generateHeight0();
		int  getNx() { return _nx; }
		int  getNy() { return _ny; }
		void glVertexArrayX(int, double*, int, int);
		void glVertexArrayY(int, double*, int, int);
		void mainComputation();
	
	private : 
	
		void getSineAmp(int, double, std::vector<double>*, std::vector<double>*);
	
		FFT												_fft;       // fft structure to computes the transformation
		Height											_height;    // initial random ocean wave height field - [x][y]
		std::vector<std::vector<double> >				_height0I;  // tmp wave height field
        std::vector<std::vector<double> >				_height0R;  // I : imaginary - R : real
		std::vector<std::vector<double> >				_hRf;       // real part - frequency domain - [y][x]
		std::vector<std::vector<double> >				_hIf;       // imaginary part - time domain - [y][x]
		std::vector<std::vector<double> >				_hRt;       // real part - frequency domain - [y][x]
		std::vector<std::vector<double> >				_hIt;       // imaginary part - time domain - [y][x]
  const double											_lx;        // real width
  const double											_ly;        // real height
  const int												_nx;        // nb of x points - must be a power of 2
  const int												_ny;        // nb of y points - must be a power of 2
		Philipps									   *_philipps;  // philips spectrum
	
};

#endif