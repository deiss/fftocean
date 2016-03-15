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
    
        void set_size(double p_lx, double p_ly, double p_nx, double p_ny) { lx = p_lx; ly = p_ly; nx = p_nx; ny = p_ny; }
        void init_fonctor(int i)                                          { x = i - nx/2; y = -ny/2; }
    
    private :
    
  const double wind_speed;         // wind speed
  const int    wind_alignment;     // the greater it is, the better waves are in the wind's direction
  const double min_wave_size;      // waves are deleted if below this size
  const double A;                  // numeric constant to adjust
  
        double lx;                 // real width
        double ly;                 // real height
        int    nx;                 // nb of x points - must be a power of 2
        int    ny;                 // nb of x points - must be a power of 2
        
        int    x;
        int    y;
    
};

#endif
