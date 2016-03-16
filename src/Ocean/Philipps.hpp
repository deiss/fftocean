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
    
        Philipps(const double, const double, const int, const int, const double, const int, const double, const double);
        ~Philipps() {}
    
        double operator()();
    
        void init_fonctor(int);
    
    private :
  
        const double lx;         /* actual width of the scene */
        const double ly;         /* actual height of the scene */
        const int    nx;         /* nb of x points - must be a power of 2 */
        const int    ny;         /* nb of y points - must be a power of 2 */
    
  const double wind_speed;       /* wind speed */
  const int    wind_alignment;   /* the greater it is, the better waves are in the wind's direction */
  const double min_wave_size;    /* waves are deleted if below this size */
  const double A;                /* numeric constant to adjust the waves height */
        
        int x;                   /* equals i-nx/2 in a series of calls to the functor  */
        int y;                   /* goes in the range [-ny/2 ; ny/2] in a series of calls to the functor */
    
};

#endif
