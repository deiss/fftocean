/*
Project: Ocean
Author:  DEISS Olivier
License: This software is offered under the GPL license. See COPYING for more information.
*/

/*
This class defines the Cooley-Tukey algorithm for the Fourier Transform computation.
The data (time domain or spectrum) has to be stored in the real and imag vectors. Then
the direct FFT transform can be computed with a call to reverse(), and the reverse FFT
transform can be computed with a call to reverse(). To fetch the results, just call 
get_result. The FFT computes the Fourier transform in O(nlog(n)) instead of O(n^2).
*/

#ifndef FFTHPP
#define FFTHPP

#include <iostream>
#include <vector>

class FFT {

    public :
    
        FFT() { }
        FFT(int, std::vector<double>, std::vector<double>);
    
        void direct()                                                             { sort(); radix_direct(); }
        void reverse()                                                            { sort(); radix_reverse(); }
        void get_result(std::vector<double>* p_real, std::vector<double>* p_imag) { *p_real = real; *p_imag = imag; }
    
    private :
    
        void radix_direct();
        void radix_reverse();
        void sort();

        int                 n;      /* power of two, the size of the vector */
        int                 p;      /* so that n = 2^p */
        std::vector<double> real;   /* data vector, real values */
        std::vector<double> imag;   /* data vectorn imaginary values */
    
};

#endif
