#ifndef OCEANHPP
#define OCEANHPP

#include "FFT.hpp"
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
		void mainCalcul();
	
	private : 
	
		void getSineAmp(int, double, std::vector<double>*, std::vector<double>*);
	
		FFT												_fft;
		Height											_height;
		std::vector<std::vector<double> >				_height0I;    // vect[x][y]
		std::vector<std::vector<double> >				_height0R;
		std::vector<std::vector<double> >				_hRf;         // hRf[n][y]
		std::vector<std::vector<double> >				_hIf;
		std::vector<std::vector<double> >				_hRt;         // hRt[y][x]
		std::vector<std::vector<double> >				_hIt;
  const double											_lx;
  const double											_ly;
  const int												_nx;
  const int												_ny;
		Philipps									   *_philipps;
	
};

#endif

/* Classe qui contient toutes les informations pour la création d'un océan. */
/* Les amplitudes auxquelles elle donne accès doivent être traitées par une FFT */