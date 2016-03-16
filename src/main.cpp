/*
Project: Ocean
Author:  DEISS Olivier
License: This software is offered under the GPL license. See COPYING for more information.
*/

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Args/Arguments.hpp"

#include "Ocean/Ocean.hpp"
#include "Ocean/Height.hpp"
#include "Ocean/Philipps.hpp"

#include "Graphic/Window.hpp"

Ocean*      ocean;
int         mainwindow;

int main (int argc, char** argv) {

    /* random for gaussian numbers */
    srand(time(NULL));
    
    /* command line arguments */
    Arguments args(argc, argv);
    int err = args.parse_arguments();
    if(err<0) {
        if(err==-2) {
            args.print_help();
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
