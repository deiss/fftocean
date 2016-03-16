/*
Project: Ocean
Author:  DEISS Olivier
License: This software is offered under the GPL license. See COPYING for more information.
*/

#include <algorithm>
#include <cmath>
#include <iostream>

#include "GLUT/glut.h"

#include "Height.hpp"
#include "Ocean.hpp"

/* Ocean constructor */
Ocean::Ocean(const double p_lx, const double p_ly, const int p_nx, const int p_ny, const double p_wind_speed, const int p_wind_alignment, const double p_min_wave_size, const double p_A) :
    lx(p_lx),
    ly(p_ly),
    nx(p_nx),
    ny(p_ny),
    philipps(new Philipps(p_wind_speed, p_wind_alignment, p_min_wave_size, p_A, p_lx, p_ly, p_nx, p_ny)),
    height(nx, ny) {
    height0I.resize(nx+1);
    height0R.resize(nx+1);
    HR.resize(nx+1);
    HI.resize(nx+1);
    hr.resize(ny+1);
    hi.resize(ny+1);
    for(vec_vec_d_it it=HR.begin() ; it!=HR.end() ; it++) it->resize(ny+1);
    for(vec_vec_d_it it=HI.begin() ; it!=HI.end() ; it++) it->resize(ny+1);
    for(vec_vec_d_it it=hr.begin() ; it!=hr.end() ; it++) it->resize(nx+1);
    for(vec_vec_d_it it=hi.begin() ; it!=hi.end() ; it++) it->resize(nx+1);
}

Ocean::~Ocean() {
    delete philipps;
}

/* Initial random height field */
void Ocean::generate_height_0() {
    height.generate_philipps(philipps);
    /* real part */
    for(vec_vec_d_it itx=height0R.begin() ; itx!=height0R.end() ; itx++) {
        itx->resize(ny+1);
        height.init_fonctor(std::distance(height0R.begin(), itx));
        std::generate(itx->begin(), itx->end(), height);
    }
    /* imaginary part */
    for(vec_vec_d_it itx=height0I.begin() ; itx!=height0I.end() ; itx++) {
        itx->resize(ny+1);
        height.init_fonctor(std::distance(height0I.begin(), itx));
        std::generate(itx->begin(), itx->end(), height);
    }
}

/* Computes the height field at a given time */
void Ocean::get_sine_amp(int x, double time, std::vector<double> *p_HR, std::vector<double> *p_HI) {
    double   A;
    double   L = 0.1;
    int      y;
    vec_d_it itR;
    vec_d_it itI;
    for(itR=p_HR->begin(), itI=p_HI->begin(), y=0 ; itR!=p_HR->end() ; itR++, itI++, y++) {
        A = time*sqrt(9.81 * sqrt(pow((2*M_PI*x)/lx, 2)+pow((2*M_PI*y)/ly, 2)) * (1+(pow((2*M_PI*x)/lx, 2)+pow((2*M_PI*y)/ly, 2))*pow(L, 2)));
        *itR = height0R[x][y]*cos(A) - height0I[x][y]*sin(A) + height0R[nx-x][ny-y]*cos(-A) + height0I[nx-x][ny-y]*sin(-A);
        *itI = height0I[x][y]*cos(A) + height0R[x][y]*sin(A) - height0I[nx-x][ny-y]*cos(-A) + height0R[nx-x][ny-y]*sin(-A);
    }
}

/* Creates an array that OpenGL can directly use - X */
void Ocean::gl_vertex_array_x(int y, double *vertices, int offset_x, int offset_y) {
    for(int x=0 ; x<nx ; x++) {
        vertices[3*x]   = (lx/nx)*x + offset_x*lx;
        vertices[3*x+1] = pow(-1, x+y)*hr[y][x];
        vertices[3*x+2] = (ly/ny)*y + offset_y*ly;
    }
    vertices[3*nx]   = (1 + offset_x)*lx;
    vertices[3*nx+1] = pow(-1, nx+y)*hr[y][0];
    vertices[3*nx+2] = (ly/ny)*y + offset_y*ly;
}

/* Creates an array that OpenGL can directly use - Y */
void Ocean::gl_vertex_array_y(int x, double *vertices, int offset_x, int offset_y) {
    for(int y=0 ; y<ny ; y++) {
        vertices[3*y]   = (lx/nx)*x + offset_x*lx;
        vertices[3*y+1] = pow(-1, x+y)*hr[y][x];
        vertices[3*y+2] = (ly/ny)*y + offset_y*ly;
    }
    vertices[3*ny]   = (lx/nx)*x + offset_x*lx;
    vertices[3*ny+1] = pow(-1, x+ny)*hr[0][x];
    vertices[3*ny+2] = (1 + offset_y)*ly;
}

/*
Does all the calculus needed for the ocean. This basically means
updating the spectrum and computing the 2D reverse FFT to get the wave shape.
*/
void Ocean::main_computation() {
    for(int x=0 ; x<nx ; x++) {
        get_sine_amp(x, (double)glutGet(GLUT_ELAPSED_TIME)/1000, &HR[x], &HI[x]);
        fft = FFT(ny, HR[x], HI[x]);
        fft.reverse();
        fft.get_result(&HR[x], &HI[x]);
    }
    for(int y=0 ; y<ny ; y++) {
        int      x;
        vec_d_it it;
        for(it=hr[y].begin(), x=0 ; it!=hr[y].end() ; it++, x++) *it = HR[x][y];
        for(it=hi[y].begin(), x=0 ; it!=hi[y].end() ; it++, x++) *it = HI[x][y];
        fft = FFT(nx, hr[y], hi[y]);
        fft.reverse();
        fft.get_result(&hr[y], &hi[y]);
    }
}
