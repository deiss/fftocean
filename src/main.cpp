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

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "arguments/Arguments.hpp"

#include "ocean/Ocean.hpp"
#include "ocean/Height.hpp"
#include "ocean/Philipps.hpp"

#include "rendering/Window.hpp"

Ocean* ocean;
int    mainwindow;

int main(int argc, char** argv) {

    /* random for gaussian numbers */
    srand(time(NULL));
    
    /* command line arguments */
    Arguments args(argc, argv);
    int err = args.parse_arguments();
    if(err<0) {
        if(err==-2) {
            args.print_help();
        }
        if(err==-4) {
            args.print_license();
        }
        return 0;
    }
    
    /* ocean parameters */
    const double lx             = args.lx;
    const double ly             = args.ly;
    const int    nx             = args.nx;
    const int    ny             = args.ny;
    const double wind_speed     = args.wind_speed;
    const int    wind_alignment = args.wind_alignment;
    const double min_wave_size  = args.min_wave_size;
    const double A              = args.A;
    const double motion_factor  = args.motion_factor;
    
    Philipps philipps(lx, ly, nx, ny, wind_speed, wind_alignment, min_wave_size, A);
    Height   height(nx, ny);
    ocean = new Ocean(lx, ly, nx, ny, motion_factor);
    
    height.generate_philipps(&philipps); /* Philipps spectrum */
    ocean->generate_height(&height);     /* initial ocean wave height field */
    
    /* rendering */
    Window::init(WIDTH, HEIGHT, "FFTOcean", argc, argv, args.keyboard, args.fps);
    Window::launch();
    
    /* free */
    Window::quit();
    delete ocean;
    
    return 0;
    
}
