/*

Project: Ocean
Author: DEISS Olivier

This software is offered under the GPL license. See COPYING for more information.

*/

#include <cmath>
#include <iostream>

#include "Philipps.hpp"

/* Philips constructor */
Philipps::Philipps(const double windSpeed, const int windAlignment, const double minWaveSize, const double A) :
    _A(A),
    _windAlignment(windAlignment),
    _minWaveSize(minWaveSize),
    _windSpeed(windSpeed) {
}

/* Philips spectrum fonctor */
double Philipps::operator()() {
	double var, g(9.81);
	double kx((2*M_PI*_x) / _lx), ky((2*M_PI*_y) / _ly);
	double k_sq(kx*kx + ky*ky);
	double L_sq(pow((_windSpeed*_windSpeed) / g, 2));
	_y++;
	if(k_sq == 0) return 0;
	else {
		var = _A*exp((-1/(k_sq*L_sq)));
		var *= exp(-k_sq*pow(_minWaveSize, 2));
		var *= pow((kx*kx) / k_sq, _windAlignment);    // wind : y direction
		var /= k_sq*k_sq;
		return var;
	}
}
