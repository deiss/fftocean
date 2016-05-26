/*
FFTOcean - Copyright (C) 2016 - Olivier Deiss - olivier.deiss@gmail.com

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
    void init(int, int, std::string, int, char**, std::string keyboard,
                  int FPS, float translation_speed);                                /* creates the window */
    
    void keyboard(unsigned char, int, int);                                         /* keyboard (key is pushed) event function */
    void keyboardUp(unsigned char, int, int);                                       /* keyboard (key is released) event function */
    void mouseMove(int, int);                                                       /* mouse event function */

    void launch();                                                                  /* listen to events, initializes the variables and start the drawing */
    void quit();                                                                    /* clean exit - actually never executed */
    void reshape(int, int);                                                         /* sets the viewport and perspective */

}

#endif
