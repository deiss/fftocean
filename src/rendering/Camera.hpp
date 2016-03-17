/*
FFTOcean

Copyright (C) 2016 -  Olivier Deiss - olivier.deiss@gmail.com

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

/*
This class defines a camera for a 3D scene, to be used with the glut library.
The camera is implemented as a sphere. Its center defines the position of the camera,
and one point on the sphere surface defines the sight. The calculus involves psi and
theta angles, which represent the spherical coordinates system.
To look around, call rotation() from the mouse event function, and to move, call
the setKeyboard() function from the keyboard event function. Then, in the drawing
function, call translation() to update the position, and using the get*() functions,
call the gluLookAt() function with the matching parameters.
*/

#ifndef CAMERAHPP
#define CAMERAHPP

#include <cmath>
#include <map>

class Camera {

    public:
    
        enum KEYBOARD {AZERTY, QWERTY};   /* type of keyboard */
    
        Camera(KEYBOARD, float, float, float, float, float, float, float, int, int);
        ~Camera() {}
    
        int   getMouseX() { return mouse_x; }
        int   getMouseY() { return mouse_y; }
        float getSightX() { return X + sin(theta)*sin(psi); }
        float getSightY() { return Y + cos(psi); }
        float getSightZ() { return Z + cos(theta)*sin(psi); }
        float getX()      { return X; }
        float getY()      { return Y; }
        float getZ()      { return Z; }

        void setKeyboard(int i, bool state) { keys[i] = state; }
        void setMouse(int x, int y)         { mouse_x = x; mouse_y = y; }
        void setX(float p_X)                { X = p_X; }
        void setY(float p_Y)                { Y = p_Y; }
        void setZ(float p_Z)                { Z = p_Z; }
        
        void rotation(int, int);
        void translation();
    
    private:
    
        enum    DIR {FORWARD, BACKWARD, LEFT, RIGHT};   /* translation direction */
        typedef std::map<DIR, int> k_map;
    
        k_map    key_map;                               /* associations keys - directions */
        KEYBOARD keyboard;                              /* keyboard type */
        bool     keys[255];                             /* keys being pushed (true if pushed) */
        float    X;                                     /* sphere center x axis */
        float    Y;                                     /* sphere center y axis */
        float    Z;                                     /* sphere center z axis */
        int      mouse_x;                               /* mouse x position */
        int      mouse_y;                               /* mouse y position */
        float    psi;                                   /* psi angle in spherical coordinates */
        float    theta;                                 /* theta angle in spherical coordinates */
        float    rotation_speed;                        /* equivalent to mouse sensibility */
        float    translation_speed;                     /* equivalent to keyboard sensibility */
        int      time;                                  /* to keep track of the time between two function calls */
    
};
                                                                                 
#endif
