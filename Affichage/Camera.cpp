#ifndef CAMERAHPP
#define CAMERAHPP

#include "Camera.hpp"

#ifdef __linux__
    #include <GL/glut.h>
#else
    #include <GLUT/glut.h>
#endif

#include <iostream>

Camera::Camera(float X, float Y, float Z, float theta, float psi, float rotationSpeed, float translationSpeed, int width, int height) : _mouseX(width/2),
																																		_mouseY(height/2),
																																		_psi(psi),
																																		_rotationSpeed(rotationSpeed),
																																		_theta(theta),
																																		_translationSpeed(translationSpeed),
																																		_X(X),
																																		_Y(Y),
																																		_Z(Z) {
																																		
}

void Camera::rotation(int x, int y) {
	
	_theta -= (float)(x - _mouseX) * _rotationSpeed;
	_psi   += (float)(y - _mouseY) * _rotationSpeed;
	
	if(_psi <= 0.1)			   _psi = 0.1;
	else if(_psi >= 0.95*M_PI) _psi = 0.95*M_PI;
	
	_mouseX = x;
	_mouseY = y;
	
}

void Camera::translation() {
	
	 float t = (float)(glutGet(GLUT_ELAPSED_TIME) - _time);
	_time = glutGet(GLUT_ELAPSED_TIME);
	
	if(_keyboard[100]) { // d
		
		_X -= sin(_theta + M_PI/2)*sin(_psi) * _translationSpeed * t;
		_Z -= cos(_theta + M_PI/2)*sin(_psi) * _translationSpeed * t;
		
	}
	
	if(_keyboard[113]) { // q
		
		_X -= sin(_theta - M_PI/2)*sin(_psi) * _translationSpeed * t;
		_Z -= cos(_theta - M_PI/2)*sin(_psi) * _translationSpeed * t;
		
	}
 
	 if(_keyboard[115]) { // s
	 
		 _X -= sin(_theta)*sin(_psi) * _translationSpeed * t;
		 _Y -= cos(_psi)			 * _translationSpeed * t;
		 _Z -= cos(_theta)*sin(_psi) * _translationSpeed * t;
	 
	 }
	 
	 if(_keyboard[122]) { // z
	 
		 _X += sin(_theta)*sin(_psi) * _translationSpeed * t;
		 _Y += cos(_psi)			 * _translationSpeed * t;
		 _Z += cos(_theta)*sin(_psi) * _translationSpeed * t;
	 
	 }
 
 }
																						  
#endif
