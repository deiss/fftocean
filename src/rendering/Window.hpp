/*
Project: Ocean
Author:  DEISS Olivier
License: This software is offered under the GPL license. See COPYING for more information.
*/

/*
This namespace deals with the rendering of the application. It receives the
events (mouse, keyboard) and prints the ocean, fps to screen.
*/

#ifndef WINDOWHPP
#define WINDOWHPP

#define WIDTH  640
#define HEIGHT 480

#include "ocean/Ocean.hpp"

extern Ocean* ocean;
extern int    mainwindow;

namespace Window {

    void draw();                                                                    /* main drawing function, calls the above ones */
    void draw_fps();                                                                /* draws the FPS (Frames Per Second) in the top right corner */
    void draw_ocean();                                                              /* draws the ocean, don't forget to call that one... */
    
    void setFPS(int);                                                               /* sets the target FPS */
    void fps_action();                                                              /* given the current FPS and the target FPS, computes the needed sleeping time */
    void init(int, int, std::string, int, char**, std::string keyboard, int FPS);   /* creates the window */
    
    void keyboard(unsigned char, int, int);                                         /* keyboard (key is pushed) event function */
    void keyboardUp(unsigned char, int, int);                                       /* keyboard (key is released) event function */
    void mouseMove(int, int);                                                       /* mouse event function */

    void launch();                                                                  /* listen to events, initializes the variables and start the drawing */
    void quit();                                                                    /* clean exit - actually never executed */
    void reshape(int, int);                                                         /* sets the viewport and perspective */

}

#endif
