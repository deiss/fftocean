/*
FFTOcean - Copyright (C) 2016 -  Olivier Deiss - olivier.deiss@gmail.com

FFTOcean is a C++ implementation of researcher J. Tessendorf's paper
"Simulating Ocean Water". It is a real-time simulation of ocean water
in a 3D world. The (reverse) FFT is used to compute the 2D wave height
field from the Philipps spectrum. It is possible to adjust parameters
such as wind speed, direction and strength, wave choppiness, and sea depth.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
This class implements an ocean. The initial spectrum is computed with generate_height_0(), and
stored into HR/HI vectors. An fft object can trasform this into a time-domain signal that is
stored in the hr/hi vectors. Over time, the spectrum is updated with get_sine_amp to give an
impression of movement.
*/

#ifndef OCEANHPP
#define OCEANHPP

#include <vector>

#include "fft/FFT.hpp"
#include "Height.hpp"
#include "Philipps.hpp"

class Ocean {
    
    public:
    
        Ocean(const double, const double, const int, const int, const double);
        ~Ocean() {}
    
        int  get_lx() { return lx; }
        int  get_ly() { return ly; }
        int  get_nx() { return nx; }
        int  get_ny() { return ny; }
    
        void generate_height(Height*);
        void main_computation();
        void gl_vertex_array_x(int, double*, int, int);
        void gl_vertex_array_y(int, double*, int, int);
    
    private:

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
    
        double motion_factor;
    
};

#endif
