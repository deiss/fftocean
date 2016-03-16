/*
Project: Ocean
Author:  DEISS Olivier
License: This software is offered under the GPL license. See COPYING for more information.
*/

#include <algorithm>
#include <cmath>
#include <ctime>

#include "Height.hpp"

Height::Height(const int p_nx, const int p_ny) :
    nx(p_nx),
    ny(p_ny) {
}

/*
This function initializes the variables to the right values before
a series of calls to the functor.
*/
void Height::init_fonctor(int i) {
    x = i - nx/2;
    y = -ny/2;
}

/*
Computes the original spectrum. This uses the Philipps spectrum
and a gaussian number so that the scene is different every time.
*/
double Height::operator()() {
    y++;
    return sqrt(philipps[x+(nx/2)][y+(ny/2)]/2) * gaussian();
}

/*
Generates the Philips spectrum using the Philipps fonctor.
*/
void Height::generate_philipps(Philipps *p) {
    philipps.resize(nx+1);
    for(std::vector<std::vector<double> >::iterator itx=philipps.begin() ; itx!=philipps.end() ; itx++) {
        itx->resize(ny+1);
        p->init_fonctor(std::distance(philipps.begin(), itx));
        std::generate(itx->begin(), itx->end(), *p);
    }
}

/*
Gaussian random generator. The numbers are generated
using the Box-Muller method.
*/
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
