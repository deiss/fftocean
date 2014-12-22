#define WIDTH 640
#define HEIGHT 480

#include "Ocean.hpp"

extern Ocean *ocean;

namespace Fenetre {

	void draw();
	void draw_fps();
	void draw_ocean();
	void fps_action();
	void init(int, int, std::string, int, char**);
	void keyboard(unsigned char, int, int);
	void keyboardUp(unsigned char, int, int);
	void launch();
	void mouseMove(int, int);
	void quit();
	void reshape(int, int);
	void setFPS(int);

}