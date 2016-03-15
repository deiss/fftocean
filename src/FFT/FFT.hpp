/*

Project: Ocean
Author: DEISS Olivier

This software is offered under the GPL license. See COPYING for more information.

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

        int                 n;
        int                 p;
        std::vector<double> real;
        std::vector<double> imag;
    
};

#endif
