/*

Project: Ocean
Author: DEISS Olivier

This software is offered under the GPL license. See COPYING for more information.

*/

#include <algorithm>
#include <cmath>
#include <ctime>

#include "Height.hpp"

/* Operator overloading to use Height as a fonctor */
double Height::operator()() {
    y++;
    // computes the initial random h0
    return sqrt(philipps[x+(nx/2)][y+(ny/2)]/2) * gaussian();
}

/* Generates the Philips spectrum */
void Height::generate_philipps(Philipps *p) {
    philipps.resize(nx+1);
    for(std::vector<std::vector<double> >::iterator itx=philipps.begin() ; itx!=philipps.end() ; itx++) {
        itx->resize(ny+1);
        p->init_fonctor(std::distance(philipps.begin(), itx));
        std::generate(itx->begin(), itx->end(), *p);
    }
}

/* Gaussian random generator - Box-Muller method */
double Height::gaussian() {
    double var1;
    double var2;
    double s;
    do {
        var1 = (rand() % 201 - 100)/static_cast<double>(100);
        var2 = (rand() % 201 - 100)/static_cast<double>(100);
        s    = var1*var1 + var2*var2;
    } while(s>=1 || s==0);
    return var1*sqrt(-log(s)/s);
}
