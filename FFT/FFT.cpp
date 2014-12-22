#ifndef FFTHPP
#define FFTHPP

#include "FFT.hpp"

#include <cmath>
#include <iostream>
#include <vector>

FFT::FFT(int n, std::vector<double> vectR, std::vector<double> vectI) : _n(n),
																		_p(0),
																		_xR(vectR),
																		_xI(vectI) {

	while(n != 1) {
																		
		n /= 2;
		_p++;
																		
	}
																			
	_vectR.resize(_n);
	_vectI.resize(_n);	
																			
}

void FFT::radixDirect() {
	
	int    n(_n);
	
	std::vector<double> vectR(_n);
	std::vector<double> vectI(_n);
	
	for(int i = 0 ; i < _p ; i++) {                   // processus à faire _p fois
		
		for(int j = 0 ; j < n/2 ; j++) {              // calculer pour n/2 sous parties 
			
			for(int k = 0 ; k < pow(2, i) ; k++) {    // calcul
				
				_index1 = k+j*pow(2, i+1);
				_index2 = _index1 + pow(2, i);
				
				_var1 = (double)(-(2*M_PI)/pow(2, i+1))*_index1;
				_cos = cos(_var1);
				_sin = sin(_var1);
				
				_var2 = _xI[_index2];
				_var3 = _xR[_index2];
				_var4 = _xR[_index1];
				_var5 = _xI[_index1];
				
				_vectR[_index1] = _var4 + _cos*_var3 - _sin*_var2;
				_vectR[_index2] = _var4 - _cos*_var3 + _sin*_var2;
				
				_vectI[_index1] = _var5 + _cos*_var2 + _sin*_var3;
				_vectI[_index2] = _var5 - _cos*_var2 - _sin*_var3;
				
			}
			
		}
		
		swap(_vectR, _xR);
		swap(_vectI, _xI);
		
		n /= 2;
		
	}
	
}

void FFT::radixReverse() {
	
	int    n(_n);
	
	for(int i = 0 ; i < _p ; i++) {                   // processus à faire _p - 1 fois
		
		for(int j = 0 ; j < n/2 ; j++) {              // calculer pour n/2 sous parties 
			
			for(int k = 0 ; k < pow(2, i) ; k++) {    // calcul
				
				_index1 = k+j*pow(2, i+1);
				_index2 = _index1 + pow(2, i);
				
				_var1 = (double)((2*M_PI)/pow(2, i+1))*_index1;
				_cos = cos(_var1);
				_sin = sin(_var1);
				
				_var2 = _xI[_index2];
				_var3 = _xR[_index2];
				_var4 = _xR[_index1];
				_var5 = _xI[_index1];
				
				_vectR[_index1] = _var4 + _cos*_var3 - _sin*_var2;
				_vectR[_index2] = _var4 - _cos*_var3 + _sin*_var2;
				
				_vectI[_index1] = _var5 + _cos*_var2 + _sin*_var3;
				_vectI[_index2] = _var5 - _cos*_var2 - _sin*_var3;
			
			}
			
		}
		
		swap(_vectR, _xR);
		swap(_vectI, _xI);
		
		n /= 2;
		
	}
	
}

void FFT::tri() {
	
	int n(_n);
 
	for(int i = 0 ; i < _p - 1 ; i++) {        // processus à répéter _p - 1 fois
 
		 std::vector<double> XR;
		 XR.reserve(_n);
		 
		 std::vector<double> XI;
		 XI.reserve(_n);
		
		 _vectRp.resize(n/2);
		 _vectIp.resize(n/2);													
		 _vectRi.resize(n/2);
		 _vectIi.resize(n/2);
		 
		 std::vector<double>::iterator itR(XR.begin());
		 std::vector<double>::iterator itI(XI.begin());
		 
		 for(int j = 0 ; j < _n/n ; j++) {      // réorganiser -n/n sous parties
		 
			 for(int k = 0 ; k < n/2 ; k++) {   // réorganisation
				 
				 _index1 = 2*k+j*n;
			 
				 _vectRp[k] = _xR[_index1];
				 _vectIp[k] = _xI[_index1];
				 
				 _vectRi[k] = _xR[_index1+1];
				 _vectIi[k] = _xI[_index1+1];
				 
			 }
	    
			 XR.insert(itR, _vectRp.begin(), _vectRp.end());
			 XR.insert(XR.end(), _vectRi.begin(), _vectRi.end());
			 
			 XI.insert(itI, _vectIp.begin(), _vectIp.end());
			 XI.insert(XI.end(), _vectIi.begin(), _vectIi.end());
			 
			 itR = XR.end();
			 itI = XI.end();
		 
		 }
	 
		 swap(XR, _xR);
		 swap(XI, _xI);
		 
		 n /= 2;
	 
	 }

}

#endif