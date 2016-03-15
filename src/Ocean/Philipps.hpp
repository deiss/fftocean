/*
Project: Ocean
Author:  DEISS Olivier
License: This software is offered under the GPL license. See COPYING for more information.
*/

/*
This class implements the Philipps spectrum, a spectrum representative of the spectrum
of ocean waves. The spectrum can be obtained with the operator (). This choice makes it
available for use with std::generate algorithm. This spectrum contains the scene parameters,
as they have an impact of the waves shape, so on their spectrum too. Such parameters are
wind speed, wind force (how the waves align with the wind direction) and the minimum wave size.
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
    
  const double wind_speed;         /* wind speed */
  const int    wind_alignment;     /* the greater it is, the better waves are in the wind's direction */
  const double min_wave_size;      /* waves are deleted if below this size */
  const double A;                  /* numeric constant to adjust the waves height */
  
        double lx;                 /* actual width of the scene */
        double ly;                 /* actual height of the scene */
        int    nx;                 /* nb of x points - must be a power of 2 */
        int    ny;                 /* nb of y points - must be a power of 2 */
        
        int    x;
        int    y;
    
};

#endif
