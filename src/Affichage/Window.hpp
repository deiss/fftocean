#define WIDTH 640
#define HEIGHT 480

#include "../Ocean/Ocean.hpp"

extern Ocean *ocean;
extern int    mainwindow;

namespace Window {

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