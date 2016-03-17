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
This class defines the Cooley-Tukey algorithm for the Fourier Transform computation.
The data (time domain or spectrum) has to be stored in the real and imag vectors. Then
the direct FFT transform can be computed with a call to reverse(), and the reverse FFT
transform can be computed with a call to reverse(). The result is computed on-site, i.e.
in the vectors given to the FFT object. FFT computes the Fourier transform in O(nlog(n))
instead of O(n^2).
*/

#ifndef FFTHPP
#define FFTHPP

#include <iostream>
#include <vector>

class FFT {

    public:
    
        FFT() {}
        FFT(int, std::vector<double>*, std::vector<double>*);
    
        void direct()  { sort(); radix_direct(); }
        void reverse() { sort(); radix_reverse(); }
    
    private:
    
        typedef std::vector<double>* vec_d_p;
    
        void radix_direct();
        void radix_reverse();
        void sort();

        int     n;      /* power of two, the size of the vector */
        int     p;      /* so that n = 2^p */
        vec_d_p real;   /* data vector, real values */
        vec_d_p imag;   /* data vectorn imaginary values */
    
};

#endif
