/*
Project: Ocean
Author:  DEISS Olivier
License: This software is offered under the GPL license. See COPYING for more information.
*/

#include <iostream>

#include "GLUT/glut.h"

#include "Camera.hpp"

Camera::Camera(float p_X, float p_Y, float p_Z, float p_psi, float p_theta, float p_rotation_speed, float p_translation_speed, int p_window_width, int p_window_height) :
    X(p_X),
    Y(p_Y),
    Z(p_Z),
    mouse_x(p_window_width/2),
    mouse_y(p_window_height/2),
    psi(p_psi),
    theta(p_theta),
    rotation_speed(p_rotation_speed),
    translation_speed(p_translation_speed),
    time(0) {
    for(int i=0 ; i<255 ; i++) { keyboard[i] = false; }
}

void Camera::rotation(int x, int y) {
    theta -= static_cast<float>(x - mouse_x) * rotation_speed;
    psi   += static_cast<float>(y - mouse_y) * rotation_speed;
    if(psi<=0.1)            psi = 0.1;
    else if(psi>=0.95*M_PI) psi = 0.95*M_PI;
    mouse_x = x;
    mouse_y = y;
}

void Camera::translation() {
    float t = static_cast<float>(glutGet(GLUT_ELAPSED_TIME) - time);
    time    = glutGet(GLUT_ELAPSED_TIME);
    if(keyboard[102]) { // f
        X -= sin(theta + M_PI/2)*sin(psi) * translation_speed * t;
        Z -= cos(
        theta + M_PI/2)*sin(psi) * translation_speed * t;
    }
    if(keyboard[115]) { // s
        X -= sin(theta - M_PI/2)*sin(psi) * translation_speed * t;
        Z -= cos(theta - M_PI/2)*sin(psi) * translation_speed * t;
    }
    if(keyboard[100]) { // d
        X -= sin(theta)*sin(psi) * translation_speed * t;
        Y -= cos(psi)            * translation_speed * t;
        Z -= cos(theta)*sin(psi) * translation_speed * t;
    }
    if(keyboard[101]) { // e
        X += sin(theta)*sin(psi) * translation_speed * t;
        Y += cos(psi)            * translation_speed * t;
        Z += cos(theta)*sin(psi) * translation_speed * t;
    }
}
