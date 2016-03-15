/*
Project: Ocean
Author:  DEISS Olivier
License: This software is offered under the GPL license. See COPYING for more information.
*/

#ifndef CAMERAHPP
#define CAMERAHPP

#include <cmath>

class Camera {

	public :
	
		Camera(float, float, float, float, float, float, float, int, int);
        ~Camera() {}
    
		int	  getMouseX() { return mouse_x; }
		int	  getMouseY() { return mouse_y; }
		float getSightX() { return X + sin(theta)*sin(psi); }
		float getSightY() { return Y + cos(psi); }
		float getSightZ() { return Z + cos(theta)*sin(psi); }
		float getX()      { return X; }
		float getY()      { return Y; }
		float getZ()      { return Z; }

		void setKeyboard(int i, bool state) { keyboard[i] = state; }
		void setMouse(int x, int y)		    { mouse_x = x; mouse_y = y; }
		void setX(float X)					{ X = X; }
		void setY(float Y)					{ Y = Y; }
		void setZ(float Z)					{ Z = Z; }
		
        void rotation(int, int);
        void translation();
	
	private :
	
		bool  keyboard[255];      // to know if one specific key is up or down. UP = false
		
		float X;
		float Y;
		float Z;
        int	  mouse_x;
		int	  mouse_y;
		float psi;
		float theta;
		float rotation_speed;
		float translation_speed;
		int   time;
	
};
                                                                                 
#endif
