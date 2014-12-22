#include <cmath>

class Camera {

	public :
	
		Camera(float, float, float, float, float, float, float, int, int);
		int	  getMouseX()					{ return _mouseX; }
		float getSightX()					{ return _X + sin(_theta)*sin(_psi); }
		float getSightY()					{ return _Y + cos(_psi); }
		float getSightZ()					{ return _Z + cos(_theta)*sin(_psi); }
		float getX()						{ return _X; }
		float getY()						{ return _Y; }
		float getZ()						{ return _Z; }
		void  rotation(int, int);
		void  setKeyboard(int i, bool etat) { _keyboard[i] = etat; }
		void  setMouse(int x, int y)		{ _mouseX = x; _mouseY = y; }
		void  setX(float X)					{ _X = X; }
		void  setY(float Y)					{ _Y = Y; }
		void  setZ(float Z)					{ _Z = Z; }
		void  translation();	
	
	private :
	
		bool  _keyboard[255];
		int	  _mouseX;
		int	  _mouseY;
		float _psi;
		float _rotationSpeed;
		int   _time;
		float _theta;
		float _translationSpeed;
		float _X;
		float _Y;
		float _Z;
	
};

/*  La caméra est un repère sphérique qui peut translater. 
	La cible d'observation se trouve sur la sphère de centre l'origine du repère sphérique */


/*	Utilisation (GLUT/OpenGL) :
 
		Fonction draw() :
 			camera.translation();
 			gluLookAt(camera.getX(), camera.getY(), camera.getZ(), camera.getSightX(), camera.getSightY(), camera.getSightZ(), 0, 1, 0);
 
 		Fonction keyboard() :
			camera.setKeyboard(key, true);
		
 		Fonction keyboardUp() :
			camera.setKeyboard(key, false);
 
		Fonction mouseMove() :
			camera.rotation(x, y); */