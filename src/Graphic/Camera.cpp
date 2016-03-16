/*
Project: Ocean
Author:  DEISS Olivier
License: This software is offered under the GPL license. See COPYING for more information.
*/

#include <iostream>

#include "GLUT/glut.h"

#include "Camera.hpp"

/*
Initializes the variables and creates the key map according to the
given keyboard configuration. On azerty keyboards, 'z', 'q', 's', 'd'
and on qwerty keyboards, 'w', 'a', 's', 'd', allow the user to move
in the 3D world with the left hand while controling the mouse with
the right hand. Indeed, these letters are on the left-hand side of
the keyboard and offer a configuration similar to the arrow pad's one.
*/
Camera::Camera(KEYBOARD p_keyboard, float p_X, float p_Y, float p_Z, float p_psi, float p_theta, float p_rotation_speed, float p_translation_speed, int p_window_width, int p_window_height) :
    keyboard(p_keyboard),
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
    for(int i=0 ; i<255 ; i++) { keys[i] = false; }
    switch(keyboard) {
        case AZERTY:
            key_map[FORWARD]  = static_cast<int>('z');
            key_map[BACKWARD] = static_cast<int>('s');
            key_map[LEFT]     = static_cast<int>('q');
            key_map[RIGHT]    = static_cast<int>('d');
            break;
        case QWERTY:
            key_map[FORWARD]  = static_cast<int>('w');
            key_map[BACKWARD] = static_cast<int>('s');
            key_map[LEFT]     = static_cast<int>('a');
            key_map[RIGHT]    = static_cast<int>('d');
            break;
    }
}

/*
Computes the new angle values given the mouse direction. The sight's
only limits are when looking up or down: it is impossible for the user to
look at his feets or straight up in the air (these edge cases would need
a special treatment in the gluLookAt function).
*/
void Camera::rotation(int x, int y) {
    theta -= static_cast<float>(x - mouse_x) * rotation_speed;
    psi   += static_cast<float>(y - mouse_y) * rotation_speed;
    if(psi<=0.1)            psi = 0.1;
    else if(psi>=0.95*M_PI) psi = 0.95*M_PI;
    mouse_x = x;
    mouse_y = y;
}

/*
Computes the new sphere center given the speed and direction of the camera.
The direction depends on the current angles values, the keys being pushed,
and the elapsed time since the last function call.
*/
void Camera::translation() {
    float t = static_cast<float>(glutGet(GLUT_ELAPSED_TIME) - time);
    time    = glutGet(GLUT_ELAPSED_TIME);
    if(keys[key_map[FORWARD]]) {
        X += sin(theta)*sin(psi) * translation_speed * t;
        Y += cos(psi)            * translation_speed * t;
        Z += cos(theta)*sin(psi) * translation_speed * t;
    }
    if(keys[key_map[BACKWARD]]) {
        X -= sin(theta)*sin(psi) * translation_speed * t;
        Y -= cos(psi)            * translation_speed * t;
        Z -= cos(theta)*sin(psi) * translation_speed * t;
    }
    if(keys[key_map[LEFT]]) {
        X -= sin(theta - M_PI/2)*sin(psi) * translation_speed * t;
        Z -= cos(theta - M_PI/2)*sin(psi) * translation_speed * t;
    }
    if(keys[key_map[RIGHT]]) {
        X -= sin(theta + M_PI/2)*sin(psi) * translation_speed * t;
        Z -= cos(theta + M_PI/2)*sin(psi) * translation_speed * t;
    }
}
