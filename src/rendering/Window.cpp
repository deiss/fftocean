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

#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <sstream>
#include <vector>

#include "cross_platform/GLUT.hpp"

#include "Camera.hpp"
#include "Window.hpp"

namespace Window {
    
    /* allows to move in the 3D scene */
    Camera* camera;
    
    /* keeps a constant FPS */
    int             frames(-1);
    int             fps;              /* actual FPS */
    int             fps_goal;         /* expected FPS */
    std::string     fps_str;
    time_t          sleep_avant(0);
    int             t;
    struct timespec tim1, tim2;

    /* Ocean vertices and parameters */
    int     nxOcean;
    int     nyOcean;
    double* vertexOceanX;
    double* vertexOceanY;
    int     height = 1;    /* for waves squares dupplication */
    int     width  = 1;    /* for waves squares dupplication */

    void draw() {
        if(glutGet(GLUT_ELAPSED_TIME) - t >= 1000) fps_action();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        camera->translation();
        gluLookAt(camera->getX(), camera->getY(), camera->getZ(), camera->getSightX(), camera->getSightY(), camera->getSightZ(), 0, 1, 0);
        draw_ocean();
        draw_fps();
        glutSwapBuffers();
        glutPostRedisplay();
        nanosleep(&tim1, &tim2);
        frames++;
    }
    
    void draw_fps() {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, 640, 0, 480);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glRasterPos2f(550, 460);
        char        buf[15] = "FPS : ";
        const char* p(buf);
        strcat(buf, fps_str.c_str());
        do glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *p); while(*(++p));
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }
    
    void draw_ocean() {
        ocean->main_computation();
        glColor3ub(82, 184, 255);
        for(int offsetX = 0 ; offsetX <= width ; offsetX++) {
            for(int offsetY = 0 ; offsetY <= height ; offsetY++) {
                for(int x = 0 ; x < nxOcean ; x++) {
                    ocean->gl_vertex_array_y(x, vertexOceanY, offsetX, offsetY);
                    glEnableClientState(GL_VERTEX_ARRAY);
                    glVertexPointer(3, GL_DOUBLE, 0, vertexOceanY);
                    glDrawArrays(GL_LINE_STRIP, 0, nyOcean+1);
                    glDisableClientState(GL_VERTEX_ARRAY);
                }
                for(int y = 0 ; y < nyOcean ; y++) {
                    ocean->gl_vertex_array_x(y, vertexOceanX, offsetX, offsetY);
                    glEnableClientState(GL_VERTEX_ARRAY);
                    glVertexPointer(3, GL_DOUBLE, 0, vertexOceanX);
                    glDrawArrays(GL_LINE_STRIP, 0, nxOcean+1);
                    glDisableClientState(GL_VERTEX_ARRAY);
                }
            }
        }
        glColor3ub(0, 0, 0);
    }
    
    void fps_action() {
        t      = glutGet(GLUT_ELAPSED_TIME);
        fps    = frames;
        frames = 0;
        std::ostringstream oss;
        oss << fps;
        fps_str = oss.str();
        sleep_avant  = tim1.tv_nsec;
        tim1.tv_nsec = (int)(((double)(1.0/fps_goal) - (double)(1.0/fps))*pow(10, 9) + sleep_avant) % 1000000000;
    }
    
    void init(int width, int height, std::string titre, int argc, char** argv, std::string keyboard, int p_fps) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
        glutInitWindowSize(width, height);
        mainwindow = glutCreateWindow(titre.c_str());
        glEnable(GL_MULTISAMPLE);
        Camera::KEYBOARD mode = keyboard=="azerty" ? Camera::AZERTY : Camera::QWERTY;
        camera = new Camera(mode, -100, 100, -100, 4*M_PI/7, M_PI/4, 0.01, 0.2, WIDTH, HEIGHT);
        fps_goal = p_fps;
    }
    
    void keyboard(unsigned char key, int x, int y) {
        camera->setKeyboard(key, true);
    }
    
    void keyboardUp(unsigned char key, int x, int y) {
        camera->setKeyboard(key, false);
    }

    void launch() {
        tim1.tv_sec  = 0;
        tim1.tv_nsec = 0;
        t = glutGet(GLUT_ELAPSED_TIME);
        nxOcean = ocean->get_nx();
        nyOcean = ocean->get_ny();
        vertexOceanX = new double[3*(nxOcean+1)];
        vertexOceanY = new double[3*(nyOcean+1)];
        glClearColor(1, 1, 1, 1);
        glutReshapeFunc(reshape);
        glutDisplayFunc(draw);
        glutPassiveMotionFunc(mouseMove);
        glutKeyboardFunc(keyboard);
        glutKeyboardUpFunc(keyboardUp);
        glutWarpPointer(WIDTH/2, HEIGHT/2+40);   /* +40 for mac bar */
        glutMainLoop();
    }
    
    void mouseMove(int x, int y) {
        camera->rotation(x, y);
        if(x>=WIDTH || x<=0 || y>=HEIGHT || y<=0) {
            glutWarpPointer(WIDTH/2, HEIGHT/2);
            camera->setMouse(WIDTH/2, HEIGHT/2);
        }
    }
    
    void quit() {
        delete[] vertexOceanX;
        delete[] vertexOceanY;
    }

    void reshape(int width, int height) {
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45, float(width)/float(height), 1, 10*sqrt(pow(ocean->get_ly(), 2) + pow(ocean->get_lx(), 2)));
    }
    
}
