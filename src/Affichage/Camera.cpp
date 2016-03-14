/*

Project: Ocean
Author: DEISS Olivier

This software is offered under the GPL license. See COPYING for more information.

*/

#ifndef CAMERAHPP
#define CAMERAHPP

#include <iostream>

#include "GLUT/glut.h"

#include "Camera.hpp"
#include "Window.hpp"

/* Camera constructor */
Camera::Camera(float X, float Y, float Z, float theta, float psi, float rotationSpeed, float translationSpeed, int width, int height) : 
	_mouseX(width/2),
	_mouseY(height/2),
	_psi(psi),
	_rotationSpeed(rotationSpeed),
	_theta(theta),
	_translationSpeed(translationSpeed),
	_X(X),
	_Y(Y),
	_Z(Z) {
    for(int i=0 ; i<255 ; i++) {
        _keyboard[i] = false;
    }
}

/* Rotates the Camera */
void Camera::rotation(int x, int y) {
	_theta -= (float)(x - _mouseX) * _rotationSpeed;
	_psi   += (float)(y - _mouseY) * _rotationSpeed;
	if(_psi <= 0.1)			   _psi = 0.1;
	else if(_psi >= 0.95*M_PI) _psi = 0.95*M_PI;
	_mouseX = x;
	_mouseY = y;
}

/* Translates the Camera */
void Camera::translation() {
	float t = (float)(glutGet(GLUT_ELAPSED_TIME) - _time);
	_time   = glutGet(GLUT_ELAPSED_TIME);
    if(_keyboard[27]) { // escape
        glutDestroyWindow(mainwindow);
    }
    // previous configuration : z(122), q(113), s(115), d(100)
    // switched to e, s, d, f to fit both AZERTY and QWERTY configurations
	if(_keyboard[102]) { // f = right
		_X -= sin(_theta + M_PI/2)*sin(_psi) * _translationSpeed * t;
		_Z -= cos(_theta + M_PI/2)*sin(_psi) * _translationSpeed * t;
	}
	if(_keyboard[115]) { // s = left
		_X -= sin(_theta - M_PI/2)*sin(_psi) * _translationSpeed * t;
		_Z -= cos(_theta - M_PI/2)*sin(_psi) * _translationSpeed * t;
	}
	if(_keyboard[100]) { // d = backward
		_X -= sin(_theta)*sin(_psi) * _translationSpeed * t;
		_Y -= cos(_psi)			    * _translationSpeed * t;
		_Z -= cos(_theta)*sin(_psi) * _translationSpeed * t;
	}
	if(_keyboard[101]) { // e = forward
		_X += sin(_theta)*sin(_psi) * _translationSpeed * t;
		_Y += cos(_psi)			    * _translationSpeed * t;
		_Z += cos(_theta)*sin(_psi) * _translationSpeed * t;
	}
}
																						  
#endif
