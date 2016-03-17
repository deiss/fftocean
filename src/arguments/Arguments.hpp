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

/*
This class treats the command line arguments and sets their default value.
*/

#ifndef Arguments_hpp
#define Arguments_hpp

#include <iostream>
#include <set>
#include <vector>

class Arguments {

    public:
    
        double      lx;               /* width of the scene */
        double      ly;               /* height of the scene */
        int         fps;              /* target FPS of the simulation */
        int         nx;               /* waves detail level */
        int         ny;               /* waves detail level */
        double      wind_speed;       /* wind speed */
        int         wind_alignment;   /* to specify how the waves should align to the wind */
        double      min_wave_size;    /* minimum wave size, to smooth the simulation */
        double      A;                /* amplification factor */
        double      motion_factor;    /* motion factor to slow down or speed up the simulation */
        std::string keyboard;         /* keyboard mode: azerty or qwerty */
    
        Arguments(int, char**);
        ~Arguments() {}

        bool is_set(std::string arg) { return arg_set.count(arg); }
        void print_help();
        int  parse_arguments();

    private:

        bool parse_string_arg(std::string, int*, std::string*, std::string);
        bool check_long_args(std::string);
    
        std::set<std::string> arg_set;   /* if an argument is correct and specified it is added to this set */
        int                   argc;      /* number of arguments */
        char**                argv;      /* value of arguments */

};

#endif
