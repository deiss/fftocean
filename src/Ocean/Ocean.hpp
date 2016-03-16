/*
Project: Ocean
Author:  DEISS Olivier
License: This software is offered under the GPL license. See COPYING for more information.
*/

#ifndef OCEANHPP
#define OCEANHPP

#include <vector>

#include "../FFT/FFT.hpp"
#include "Height.hpp"
#include "Philipps.hpp"

class Ocean {
    
    public :
    
        Ocean(const double, const double, const int, const int, const double, const int, const double, const double);
        ~Ocean();
    
        int  getNx() { return nx; }
        int  getNy() { return ny; }
        void generate_height_0();
        void gl_vertex_array_x(int, double*, int, int);
        void gl_vertex_array_y(int, double*, int, int);
        void main_computation();
    
    private :

        typedef std::vector<double>::iterator               vec_d_it;
        typedef std::vector<std::vector<double> >           vec_vec_d;
        typedef std::vector<std::vector<double> >::iterator vec_vec_d_it;
    
        void get_sine_amp(int, double, std::vector<double>*, std::vector<double>*);
    
        FFT       fft;       // fft structure to computes the transformation
    
  const double    lx;        // real width
  const double    ly;        // real height
  const int       nx;        // nb of x points - must be a power of 2
  const int       ny;        // nb of y points - must be a power of 2
  
        Philipps* philipps;  // philips spectrum
        Height    height;    // initial random ocean wave height field - [x][y]
        vec_vec_d height0I;  // tmp wave height field
        vec_vec_d height0R;  // I : imaginary - R : real
    
        vec_vec_d HR;        // real part - frequency domain - [y][x]
        vec_vec_d HI;        // imaginary part - time domain - [y][x]
        vec_vec_d hr;        // real part - frequency domain - [y][x]
        vec_vec_d hi;        // imaginary part - time domain - [y][x]
    
};

#endif
