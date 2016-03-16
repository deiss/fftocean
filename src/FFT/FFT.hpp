/*
Project: Ocean
Author:  DEISS Olivier
License: This software is offered under the GPL license. See COPYING for more information.
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

    public :
    
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
