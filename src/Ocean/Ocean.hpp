/*
Project: Ocean
Author:  DEISS Olivier
License: This software is offered under the GPL license. See COPYING for more information.
*/

/*
This class gathers all the work needed to create an ocean. It includes a wave
height field, a Philipps spectrum to initialize this wave height field, and an
fft object to get the time-domain signal out of the wave spectrum.
*/

#ifndef OCEANHPP
#define OCEANHPP

#include <vector>

#include "../FFT/FFT.hpp"
#include "Height.hpp"
#include "Philipps.hpp"

class Ocean {
    
    public :
    
        Ocean(const double, const double, const int, const int);
        //Ocean(const double, const double, const int, const int, const double, const int, const double, const double);
        ~Ocean();
    
        int  get_nx() { return nx; }
        int  get_ny() { return ny; }
    
        void generate_height(Height*);
        void main_computation();
        void gl_vertex_array_x(int, double*, int, int);
        void gl_vertex_array_y(int, double*, int, int);
    
    private :

        typedef std::vector<double>::iterator               vec_d_it;
        typedef std::vector<std::vector<double> >           vec_vec_d;
        typedef std::vector<std::vector<double> >::iterator vec_vec_d_it;
    
        void get_sine_amp(int, double, std::vector<double>*, std::vector<double>*);
    
  const double lx;           /* actual width */
  const double ly;           /* actual height */
  const int    nx;           /* nb of x points - must be a power of 2 */
  const int    ny;           /* nb of y points - must be a power of 2 */
  
        vec_vec_d height0R;  /* initial wave height field (spectrum) - real part */
        vec_vec_d height0I;  /* initial wave height field (spectrum) - imaginary part */
    
        FFT       fft;       /* fft structure to compute the FFT */
        vec_vec_d HR;        /* frequency domain, real part      - [y][x] */
        vec_vec_d HI;        /* frequency domain, imaginary part - [y][x] */
        vec_vec_d hr;        /* time domain, real part      - [y][x] */
        vec_vec_d hi;        /* time domain, imaginary part - [y][x] */
    
};

#endif
