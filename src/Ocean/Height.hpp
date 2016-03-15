/*
Project: Ocean
Author:  DEISS Olivier
License: This software is offered under the GPL license. See COPYING for more information.
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
    
        int                               nx;        // nb of x points - must be a power of 2
        int                               ny;        // nb of y points - must be a power of 2
        std::vector<std::vector<double> > philipps;  // Philips spectrum _philipps[y][x]
        int                               x;
        int                               y;
    
};

#endif
