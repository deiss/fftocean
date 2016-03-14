/*

Project: Ocean
Author: DEISS Olivier

This software is offered under the GPL license. See COPYING for more information.

*/

#include <algorithm>
#include <cmath>
#include <iostream>

#include "GLUT/glut.h"

#include "Height.hpp"
#include "Ocean.hpp"

/* Ocean constructor */
Ocean::Ocean(const double lx, const double ly, const int nx, const int ny, const double windSpeed, const int windAlignment, const double minWaveSize, const double A) :
    _lx(lx),
	_ly(ly),
	_nx(nx),
	_ny(ny) {
	_height0I.resize(_nx+1);
	_height0R.resize(_nx+1);
	_hRf.resize(_nx+1);
	_hIf.resize(_nx+1);
	_hRt.resize(_ny+1);
	_hIt.resize(_ny+1);
	for(std::vector<std::vector<double> >::iterator it = _hRf.begin() ; it != _hRf.end() ; it++) it->resize(_ny+1);
	for(std::vector<std::vector<double> >::iterator it = _hIf.begin() ; it != _hIf.end() ; it++) it->resize(_ny+1);
	for(std::vector<std::vector<double> >::iterator it = _hRt.begin() ; it != _hRt.end() ; it++) it->resize(_nx+1);
	for(std::vector<std::vector<double> >::iterator it = _hIt.begin() ; it != _hIt.end() ; it++) it->resize(_nx+1);
    _philipps = new Philipps(windSpeed, windAlignment, minWaveSize, A);
	_height.setSize(_nx, _ny);							 
	_philipps->setSize(_lx, _ly, _nx, _ny);
}

/* Initial random height field */
void Ocean::generateHeight0() {
	_height.generatePhilipps(_philipps);
    // real part
	for(std::vector<std::vector<double> >::iterator itx = _height0R.begin() ; itx != _height0R.end() ; itx++) {
		itx->resize(_ny+1);
		_height.init(std::distance(_height0R.begin(), itx));
		std::generate(itx->begin(), itx->end(), _height);
	}
    // imaginary part
	for(std::vector<std::vector<double> >::iterator itx = _height0I.begin() ; itx != _height0I.end() ; itx++) {
		itx->resize(_ny+1);
		_height.init(std::distance(_height0I.begin(), itx));
		std::generate(itx->begin(), itx->end(), _height);
	}
}

/* Computes the height field at a given time */
void Ocean::getSineAmp(int x, double time, std::vector<double> *hRf, std::vector<double> *hIf) {
	double A, L(0.1);
	std::vector<double>::iterator itR;
	std::vector<double>::iterator itI;
	int y;
	for(itR = hRf->begin(), itI = hIf->begin(), y = 0 ; itR != hRf->end() ; itR++, itI++, y++) {
		A = time * sqrt(9.81 * sqrt(pow((2*M_PI*x)/_lx, 2)+pow((2*M_PI*y)/_ly, 2))*(1+(pow((2*M_PI*x)/_lx, 2)+pow((2*M_PI*y)/_ly, 2))*pow(L, 2)));
		*itR = _height0R[x][y] * cos(A) - _height0I[x][y] * sin(A) + _height0R[_nx-x][_ny-y] * cos(-A) + _height0I[_nx-x][_ny-y] * sin(-A);
		*itI = _height0I[x][y] * cos(A) + _height0R[x][y] * sin(A) - _height0I[_nx-x][_ny-y] * cos(-A) + _height0R[_nx-x][_ny-y] * sin(-A);
	}
}

/* Creates an array that OpenGL can directly use - X */
void Ocean::glVertexArrayX(int y, double *vectVertex, int offsetX, int offsetY) {
	for(int x = 0 ; x < _nx ; x++) {
		vectVertex[3*x]   = (_lx/_nx)*x + offsetX*_lx;
		vectVertex[3*x+1] = pow(-1, x+y)*_hRt[y][x];
		vectVertex[3*x+2] = (_ly/_ny)*y + offsetY*_ly;
	}
	vectVertex[3*_nx]   = (1 + offsetX)*_lx;
	vectVertex[3*_nx+1] = pow(-1, _nx+y)*_hRt[y][0]; 
	vectVertex[3*_nx+2] = (_ly/_ny)*y + offsetY*_ly;
}

/* Creates an array that OpenGL can directly use - Y */
void Ocean::glVertexArrayY(int x, double *vectVertex, int offsetX, int offsetY) {
	for(int y = 0 ; y < _ny ; y++) {
		vectVertex[3*y]   = (_lx/_nx)*x + offsetX*_lx;
		vectVertex[3*y+1] = pow(-1, x+y)*_hRt[y][x];
		vectVertex[3*y+2] = (_ly/_ny)*y + offsetY*_ly;
	}
	vectVertex[3*_ny]   = (_lx/_nx)*x + offsetX*_lx;
	vectVertex[3*_ny+1] = pow(-1, x+_ny)*_hRt[0][x]; 
	vectVertex[3*_ny+2] = (1 + offsetY)*_ly;
}

/* Does all the calculus needed for the ocean */
void Ocean::mainComputation() {
	// first FFT
	for(int n = 0 ; n < _nx ; n++) {
        // puts heights in _hRf and _hIf
		getSineAmp(n, (double)glutGet(GLUT_ELAPSED_TIME)/1000, &_hRf[n], &_hIf[n]);
		_fft = FFT(_ny, _hRf[n], _hIf[n]);
		_fft.calculR();
		_fft.getResult(&_hRf[n], &_hIf[n]);
	}
	// second one, since it is a 2D FFT
	for(int y = 0 ; y < _ny ; y++) {
		int n;
		std::vector<double>::iterator it;
        // puts heights in _hRf and _hIf
		for(it = _hRt[y].begin(), n = 0 ; it != _hRt[y].end() ; it++, n++) *it = _hRf[n][y];
		for(it = _hIt[y].begin(), n = 0 ; it != _hIt[y].end() ; it++, n++) *it = _hIf[n][y];
		_fft = FFT(_nx, _hRt[y], _hIt[y]);
		_fft.calculR();
		_fft.getResult(&_hRt[y], &_hIt[y]);
	}
}
