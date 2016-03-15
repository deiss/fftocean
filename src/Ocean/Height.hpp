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
    
        double operator()();
    
        void   set_size(double p_nx, double p_ny) { nx = p_nx; ny = p_ny; }
        void   init_fonctor(int i)                { x = i - nx/2; y = -ny/2; }
        void   generate_philipps(Philipps*);
        double gaussian();
     
    private :
    
        int                               nx;        /* nb of x points - must be a power of 2 */
        int                               ny;        /* nb of y points - must be a power of 2 */
        std::vector<std::vector<double> > philipps;  /* Philips spectrum _philipps[y][x] */
        int                               x;
        int                               y;
    
};

#endif
