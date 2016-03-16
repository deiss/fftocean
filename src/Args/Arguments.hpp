/*
Project: DigitScanner
Author:  DEISS Olivier
License: This software is offered under the GPL license. See COPYING for more information.
*/

#ifndef Arguments_hpp
#define Arguments_hpp

#include <iostream>
#include <set>
#include <vector>

class Arguments {

    public:
    
        double lx;
        double ly;
        int    nx;
        int    ny;
        double wind_speed;
        int    wind_alignment;
        double min_wave_size;
        double A;
        double motion_factor;
    
        Arguments(int, char**);
        ~Arguments() {}

        bool is_set(std::string arg) { return arg_set.count(arg); }
        void print_help();
        int  parse_arguments();

    private:

        bool parse_string_arg(std::string, int*, std::string*, std::string);
        bool check_long_args(std::string);
    
        std::set<std::string> arg_set;
        int                   argc;
        char**                argv;

};

#endif
