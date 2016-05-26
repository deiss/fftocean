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

#include "parameters/Parameters.hpp"

#include "ocean/Ocean.hpp"
#include "ocean/Height.hpp"
#include "ocean/Philipps.hpp"

#include "rendering/Window.hpp"

Ocean* ocean;
int    mainwindow;

void       build_menu(Parameters* const);
const bool check_errors(Parameters* const);

int main(int argc, char** argv) {

    /* random for gaussian numbers */
    srand(time(NULL));
    
    /* args parser */
    Parameters::config p_c {40, 90, 3, 1, 17, 5, 3, 2, Parameters::lang_us};
    Parameters p(argc, argv, p_c);
    build_menu(&p);
    try {
        p.parse_params();
    }
    /* catch errors on parameters */
    catch(const std::exception& e) {
        std::cerr << "error :" << std::endl << "   " << e.what() << std::endl;
        std::cerr << "You can use \"--help\" to get more help." << std::endl;
        return 0;
    }
    /* stops if no arg or help requested */
    if(p.is_spec("help") || argc==1) {
        p.print_help();
        return 0;
    }
    /* or if license is needed */
    else if(p.is_spec("license")) {
        p.print_license();
        return 0;
    }
    /* checks incompatibility among parameters */
    if(!check_errors(&p)) {
        std::cerr << "You can use \"--help\" to get more help." << std::endl;
        return 0;
    }
    
    /* ocean parameters */
    const double lx             = p.num_val<double>("lx");
    const double ly             = p.num_val<double>("ly");
    const int    nx             = p.num_val<int>("nx");
    const int    ny             = p.num_val<int>("ny");
    const double wind_speed     = p.num_val<double>("wind_speed");
    const int    wind_alignment = p.num_val<int>("wind_alignment");
    const double min_wave_size  = p.num_val<double>("min_wave_size");
    const double A              = p.num_val<double>("A");
    const double motion_factor  = p.num_val<double>("motion_factor");
    
    Philipps philipps(lx, ly, nx, ny, wind_speed, wind_alignment, min_wave_size, A);
    Height   height(nx, ny);
    ocean = new Ocean(lx, ly, nx, ny, motion_factor);
    
    height.generate_philipps(&philipps); /* Philipps spectrum */
    ocean->generate_height(&height);     /* initial ocean wave height field */
    
    /* rendering */
    Window::init(WIDTH, HEIGHT, "FFTOcean", argc, argv, p.cho_val("keyboard"), p.num_val<int>("fps"), p.num_val<float>("camera_speed"));
    Window::launch();
    
    /* free */
    Window::quit();
    delete ocean;
    
    return 0;
    
}

void build_menu(Parameters* const p) {
    p->set_program_description("FFTOcean is a C++ implementation of researcher J. Tessendorf's paper \"Simulating Ocean Water\". It is a real-time simulation of ocean water in a 3D world. The reverse FFT is used to compute the 2D wave height field from the Philipps spectrum. It is possible to adjust parameters such as wind speed, direction and strength, wave choppiness, and sea depth.\n\nGithub: https://github.com/CSWest/FFTOcean.git\n\nFFTOcean Copyright (C) 2016 Olivier Deiss - olivier.deiss@gmail.com\n\nThis program comes with ABSOLUTELY NO WARRANTY. This is free software, and you are welcome to redistribute it under certain conditions. Type 'fftocean --license' for details.");
    
    p->set_usage("fftocean [--run] [parameters]");

    p->insert_subsection("GENERAL");
    p->define_param                   ("help", "Displays this help.");
    p->define_param                   ("license", "Displays the GPL license.");
    p->define_param                   ("run", "Runs the simulation");
                                       
    p->insert_subsection("ENVIRONMENT DIMENSIONS AND FACTORS");
    p->define_num_str_param<double>   ("lx", {"value"}, {350}, "Actual width of the ocean.", true);
    p->define_num_str_param<double>   ("ly", {"value"}, {350}, "Actual height of the ocean.", true);
    p->define_num_str_param<int>      ("nx", {"value"}, {128}, "Number of subdivision of the ocean. The higher it is, the mode precise the waves are. This needs to be a power of 2.", true);
    p->define_num_str_param<int>      ("ny", {"value"}, {256}, "Number of subdivision of the ocean. The higher it is, the mode precise the waves are. This needs to be a power of 2.", true);
    p->define_num_str_param<double>   ("wind_speed", {"value"}, {50}, "Speed of the wind.", true);
    p->define_num_str_param<int>      ("wind_alignment", {"value"}, {2}, "Defines how the waves should stay in the wind's direction. This parameter is an integer.", true);
    p->define_num_str_param<double>   ("min_wave_size", {"value"}, {0.1}, "Defines the minimum wave height and makes the simulation smoother.", true);
    p->define_num_str_param<double>   ("A", {"value"}, {0.0000038}, "Adjustment parameter, to increase or decrease wave depth.", true);
    
    p->insert_subsection("CAMERA SETTINGS");
    p->define_num_str_param<int>      ("fps", {"value"}, {35}, "Target FPS.", true);
    p->define_num_str_param<double>   ("motion_factor", {"value"}, {0.6}, "Allows to slow down or speed up the simulation.", true);
    p->define_num_str_param<float>    ("camera_speed", {"value"}, {0.2}, "Translation speed of the camera.", true);
    p->define_choice_param            ("keyboard", "mode", "azerty", {{"azerty", "Z, Q, S, D: forward, left, backward, right."},
                                                                      {"qwerty", "W, A, S, D: forward, left, backward, right."}},
                                       "Specifies the type of keyboard.");
}

const bool check_errors(Parameters* const p) {
    if(p->num_val<double>("lx")<=0)
        std::cerr << "Ocean width must be positive." << std::endl;
    else if(p->num_val<double>("ly")<=0)
        std::cerr << "Ocean height must be positive." << std::endl;
    else if(p->num_val<int>("nx")<4)
        std::cerr << "Width subdivision is too small." << std::endl;
    else if(p->num_val<int>("ny")<4)
        std::cerr << "Height subdivision is too small." << std::endl;
    else if(p->num_val<double>("wind_speed")<0)
        std::cerr << "Wind speed cannot be negative." << std::endl;
    else if(p->num_val<double>("min_wave_size")<0)
        std::cerr << "Minimum wave size cannot be negative." << std::endl;
    else if(p->num_val<double>("A")<0)
        std::cerr << "A cannot be zero." << std::endl;
    else if(p->num_val<int>("fps")<=0)
        std::cerr << "FPS must be positive." << std::endl;
    else if(p->num_val<double>("motion_factor")<=0)
        std::cerr << "Motion factor must be positive." << std::endl;
    else if(p->num_val<float>("camera_speed")<=0)
        std::cerr << "Camera speed must be positive." << std::endl;
    else
        return true;
    return false;
}

























