/*
Project: Ocean
Author:  DEISS Olivier
License: This software is offered under the GPL license. See COPYING for more information.
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
    
    public :
    
        Height(const int, const int);
        ~Height() {}
    
        double operator()();
    
        void   init_fonctor(int);
        void   generate_philipps(Philipps*);
        double gaussian();
     
    private :
    
        typedef std::vector<std::vector<double> > vec_vec_d;
    
        const int nx;        /* nb of x points - must be a power of 2 */
        const int ny;        /* nb of y points - must be a power of 2 */
        vec_vec_d philipps;  /* Philips spectrum _philipps[y][x] */
        int       x;
        int       y;
    
};

#endif
