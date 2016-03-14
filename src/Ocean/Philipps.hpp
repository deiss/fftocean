/*

Project: Ocean
Author: DEISS Olivier

This software is offered under the GPL license. See COPYING for more information.

*/

#ifndef PHILIPPSHPP
#define PHILIPPSHPP

class Philipps {
	
	public :
	
		Philipps(const double, const int, const double, const double);
    
		double operator()();
    
		void   init(int i)										   { _x = i - _nx/2; _y = -_ny/2; }
		void   setSize(double lx, double ly, double nx, double ny) { _lx = lx; _ly = ly; _nx = nx; _ny = ny; }
	
	private :
	
  const double _A;                  // numeric constant to adjust
  const int	   _windAlignment;      // the greater it is, the better waves are in the wind's direction
		double _lx;                 // real width
		double _ly;                 // real height
		int    _nx;                 // nb of x points - must be a power of 2
		int    _ny;                 // nb of x points - must be a power of 2
  const double _minWaveSize;        // waves are deleted if below this size
  const double _windSpeed;          // wind speed
		int    _x;
		int    _y;
	
};

#endif
