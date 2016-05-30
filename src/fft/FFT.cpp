/*
FFTOcean - Copyright (C) 2016 - Olivier Deiss - olivier.deiss@gmail.com

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

#include <cmath>
#include <iostream>
#include <vector>

#include "FFT.hpp"

/*
Initializes the variables and computes p so that n = 2^p.
*/
FFT::FFT(const int p_n, std::vector<double>* const p_real, std::vector<double>* const p_imag) :
    n(p_n),
    p(log2(p_n)),
    real(p_real),
    imag(p_imag) {
}

/*
Direct FFT transform. The algorithm computes the spectrum for
the time-domain signal in the real and imag vectors, and stores
the result in these same vectors.
*/
void FFT::radix_direct() {
    int                 n_copy = n;
    std::vector<double> real_copy; real_copy.resize(n);
    std::vector<double> imag_copy; imag_copy.resize(n);
    /* repeat the process p times */
    for(int i=0 ; i<p ; i++) {
        /* compute n/2 values and use them twice */
        for(int j=0 ; j<n_copy/2 ; j++) {
            for(int k=0 ; k<pow(2, i) ; k++) {
                const int    index1 = k+j*pow(2, i+1);
                const int    index2 = index1 + pow(2, i);
                const double var    = static_cast<double>(-(2*M_PI)/pow(2, i+1))*index1;
                const double v_cos  = cos(var);
                const double v_sin  = sin(var);
                const double imag2  = imag->at(index2);
                const double real2  = real->at(index2);
                const double real1  = real->at(index1);
                const double imag1  = imag->at(index1);
                real_copy[index1] = real1 + v_cos*real2 - v_sin*imag2;
                real_copy[index2] = real1 - v_cos*real2 + v_sin*imag2;
                imag_copy[index1] = imag1 + v_cos*imag2 + v_sin*real2;
                imag_copy[index2] = imag1 - v_cos*imag2 - v_sin*real2;
            }
        }
        swap(real_copy, *real);
        swap(imag_copy, *imag);
        n_copy /= 2;
    }
}

/*
Reverse FFT transform using the radix algorithm. The algorithm computes the
time-domain signal from the spectrum in the real and imag vectors, and stores
the result in these same vectors.
*/
void FFT::radix_reverse() {
    int                 n_copy = n;
    std::vector<double> real_copy; real_copy.resize(n);
    std::vector<double> imag_copy; imag_copy.resize(n);
    /* repeat the process p times */
    for(int i=0 ; i<p ; i++) {
        /* compute n/2 values and use them twice */
        for(int j=0 ; j<n_copy/2 ; j++) {
            for(int k=0 ; k<pow(2, i) ; k++) {
                const int    index1 = k+j*pow(2, i+1);
                const int    index2 = index1 + pow(2, i);
                const double var    = static_cast<double>((2*M_PI)/pow(2, i+1))*index1;
                const double v_cos  = cos(var);
                const double v_sin  = sin(var);
                const double imag2  = imag->at(index2);
                const double real2  = real->at(index2);
                const double real1  = real->at(index1);
                const double imag1  = imag->at(index1);
                real_copy[index1] = real1 + v_cos*real2 - v_sin*imag2;
                real_copy[index2] = real1 - v_cos*real2 + v_sin*imag2;
                imag_copy[index1] = imag1 + v_cos*imag2 + v_sin*real2;
                imag_copy[index2] = imag1 - v_cos*imag2 - v_sin*real2;
            }
        }
        swap(real_copy, *real);
        swap(imag_copy, *imag);
        n_copy /= 2;
    }
}

/*
Sorts the data so that the radix algorithm can be applied. In the first step,
the sorting puts all the evenly indexed values first and the oddly indexed
values second in the array. For the following steps, the same process is applied
to arrays of length l/2 with l the length of the previous array. At the end all
the values are interleaved.
*/
void FFT::sort() {
    int n_copy = n;
    /* repeat the process p-1 times */
    for(int i=0 ; i<p-1 ; i++) {
        std::vector<double> sorted_R; sorted_R.reserve(n);
        std::vector<double> sorted_I; sorted_I.reserve(n);
        std::vector<double> vectRp;   vectRp.resize(n_copy/2);
        std::vector<double> vectIp;   vectIp.resize(n_copy/2);
        std::vector<double> vectRi;   vectRi.resize(n_copy/2);
        std::vector<double> vectIi;   vectIi.resize(n_copy/2);
        std::vector<double>::iterator itR(sorted_R.begin());
        std::vector<double>::iterator itI(sorted_I.begin());
        for(int j=0 ; j<n/n_copy ; j++) {
            /* reorganize sub array */
            for(int k=0 ; k<n_copy/2 ; k++) {
                const double index = 2*k+j*n_copy;
                vectRp[k]    = real->at(index);
                vectIp[k]    = imag->at(index);
                vectRi[k]    = real->at(index+1);
                vectIi[k]    = imag->at(index+1);
            }
            sorted_R.insert(itR, vectRp.begin(), vectRp.end());
            sorted_I.insert(itI, vectIp.begin(), vectIp.end());
            sorted_R.insert(sorted_R.end(), vectRi.begin(), vectRi.end());
            sorted_I.insert(sorted_I.end(), vectIi.begin(), vectIi.end());
            itR = sorted_R.end();
            itI = sorted_I.end();
        }
        swap(sorted_R, *real);
        swap(sorted_I, *imag);
        n_copy /= 2;
    }
}
