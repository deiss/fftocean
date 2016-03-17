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
This class computes the initial spectrum for the scene. Using random gaussian
numbers, it makes sure the ocean is different everytime the software is run.
This class needs the Philipps spectrum to run, and defines a fonctor to be used
with std::generate algorithm.
*/

#ifndef HEIGHTHPP
#define HEIGHTHPP

#include <iostream>
#include <vector>

#include "Philipps.hpp"

class Height {
    
    public:
    
        Height(const int, const int);
        ~Height() {}
    
        double operator()();
    
        void   init_fonctor(int);
        void   generate_philipps(Philipps*);
        double gaussian();
     
    private:
    
        typedef std::vector<std::vector<double> > vec_vec_d;
    
        const int nx;        /* nb of x points - must be a power of 2 */
        const int ny;        /* nb of y points - must be a power of 2 */
        vec_vec_d philipps;  /* Philips spectrum _philipps[y][x] */
        int       x;
        int       y;
    
};

#endif
