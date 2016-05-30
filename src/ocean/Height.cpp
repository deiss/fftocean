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

#include <algorithm>
#include <cmath>
#include <ctime>

#include "Height.hpp"

/*
Initializes the variables.
*/
Height::Height(const int p_nx, const int p_ny) :
    nx(p_nx),
    ny(p_ny) {
}

/*
This function initializes the variables to the right values before
a series of calls to the functor.
*/
void Height::init_fonctor(const int i) {
    x = i - nx/2;
    y = -ny/2;
}

/*
Computes the original spectrum. This uses the Philipps spectrum
and a gaussian number so that the scene is different every time.
*/
const double Height::operator()() {
    y++;
    return sqrt(philipps[x+(nx/2)][y+(ny/2)]/2) * gaussian();
}

/*
Generates the Philips spectrum using the Philipps fonctor.
*/
void Height::generate_philipps(Philipps* const p) {
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
const double Height::gaussian() {
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
