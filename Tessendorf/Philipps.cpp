#include "Philipps.hpp"

#include <cmath>
#include <iostream>

Philipps::Philipps(const double vitesseVent, const int alignementVent, const double tailleMinVague, const double A) : _A(A),
																													  _alignementVent(alignementVent),
																													  _tailleMinVague(tailleMinVague),
																													  _vitesseVent(vitesseVent) {

}

double Philipps::operator()() {
	
	double var;
	double g(9.81);
	 
	double kx((2*M_PI*_x) / _lx);
	double ky((2*M_PI*_y) / _ly);
	double k_sq(kx*kx + ky*ky);
	
	double L_sq(pow((_vitesseVent*_vitesseVent) / g, 2));
	
	_y++;
	
	if(k_sq == 0) return 0;
	
	else {
	
		var = _A*exp((-1/(k_sq*L_sq)));
		var *= exp(-k_sq*pow(_tailleMinVague, 2));
		var *= pow((kx*kx) / k_sq, _alignementVent);    // vent selon êy
		var /= k_sq*k_sq;
	
		return var;
	
	}
	
}