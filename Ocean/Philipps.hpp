#ifndef PHILIPPSHPP
#define PHILIPPSHPP

class Philipps {
	
	public :
	
		Philipps(const double, const int, const double, const double);
		double operator()();
		void   init(int i)										   { _x = i - _nx/2; _y = -_ny/2; }
		void   setSize(double lx, double ly, double nx, double ny) { _lx = lx; _ly = ly; _nx = nx; _ny = ny; }
	
	private :
	
  const double _A;
  const int	   _alignementVent;
		double _lx;
		double _ly;
		int    _nx;
		int    _ny;
  const double _tailleMinVague;
  const double _vitesseVent;
		int    _x;
		int    _y;
	
};

#endif

/* foncteur qui calcule le spectre de Philipps */