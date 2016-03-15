/*
Project: Ocean
Author:  DEISS Olivier
License: This software is offered under the GPL license. See COPYING for more information.
*/

#ifndef CAMERAHPP
#define CAMERAHPP

#include <cmath>
#include <map>

class Camera {

    public :
    
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
    
    private :
    
        enum    DIR {FORWARD, BACKWARD, LEFT, RIGHT};   /* translation direction */
        typedef std::map<DIR, int> k_map;
    
        k_map    key_map;                            /* associations keys - directions */
        KEYBOARD keyboard;                           /* keyboard type */
        bool     keys[255];                          /* keys being pushed (true if pushed) */
        float    X;                                  /* sphere center x axis */
        float    Y;                                  /* sphere center y axis */
        float    Z;                                  /* sphere center z axis */
        int      mouse_x;                            /* mouse x position */
        int      mouse_y;                            /* mouse y position */
        float    psi;                                /* psi angle in spherical coordinates */
        float    theta;                              /* theta angle in spherical coordinates */
        float    rotation_speed;                     /* equivalent to mouse sensibility */
        float    translation_speed;                  /* equivalent to keyboard sensibility */
        int      time;                               /* to keep track of the time between two function calls */
    
};
                                                                                 
#endif
