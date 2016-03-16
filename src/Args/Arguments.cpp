/*
Project: DigitScanner
Author:  DEISS Olivier
License: This software is offered under the GPL license. See COPYING for more information.
*/

#include <iostream>

#include "Arguments.hpp"

Arguments::Arguments(int p_argc, char** p_argv) :
    lx(130),
    ly(350),
    nx(128),
    ny(256),
    wind_speed(25),
    wind_alignment(1),
    min_wave_size(0),
    A(0.000005),
    argc(p_argc),
    argv(p_argv) {
}

void Arguments::print_help() {
    std::cout << "USE: ocean [options]" << std::endl;
    std::cout << std::endl;
    std::cout << "OPTIONS:" << std::endl;
    std::cout << "   --help                     Displays this help." << std::endl;
    std::cout << "   --lx <value>               Actual width of the ocean. Default: 130" << std::endl;
    std::cout << "   --ly <value>               Actual height of the ocean. Default: 350" << std::endl;
    std::cout << "   --nx <value>               Number of subdivision of the ocean. The higher it is, the mode precise the waves are. This needs to be a power of 2. Default: 128." << std::endl;
    std::cout << "   --nx <value>               Number of subdivision of the ocean. The higher it is, the mode precise the waves are. This needs to be a power of 2. Default: 256." << std::endl;
    std::cout << "   --wind_speed <value>       Speed of the wind. Default: 25." << std::endl;
    std::cout << "   --wind_alignment <value>   Defines how the waves should stay in the wind's direction This parameter is an integer. Default: 1." << std::endl;
    std::cout << "   --min_wave_size <value>    Defines the minimum wave height. Default: 0." << std::endl;
    std::cout << "   --A <value>                Adjustment parameter, to increase or decrease wave depth. Default: 0.000005" << std::endl;
}

int Arguments::parse_arguments() {
    std::string help_msg = "You can use --help to get more help.";
    for(int i=1 ; i<argc ; i++) {
        std::string arg_value(argv[i]);
        /* help */
        if(arg_value=="--help") {
            return -2;
        }
        /* integer */
        else if(arg_value=="--nx") {
            if(++i<argc) {
                std::string nx_str(argv[i]);
                try                            { nx = std::stoi(nx_str); }
                catch(std::exception const& e) { std::cerr << "nx must be a positive integer." << std::endl; return -1; }
                if(nx<=0) { std::cerr << "nx must be a positive integer." << std::endl; return -1; }
                else      { arg_set.insert("nx"); }
            }
            else { std::cerr << "nx is not specified." << std::endl; std::cerr << help_msg << std::endl; return -1; }
        }
        else if(arg_value=="--ny") {
            if(++i<argc) {
                std::string ny_str(argv[i]);
                try                            { ny = std::stoi(ny_str); }
                catch(std::exception const& e) { std::cerr << "ny must be a positive integer." << std::endl; return -1; }
                if(ny<=0) { std::cerr << "ny must be a positive integer." << std::endl; return -1; }
                else      { arg_set.insert("ny"); }
            }
            else { std::cerr << "ny is not specified." << std::endl; std::cerr << help_msg << std::endl; return -1; }
        }
        else if(arg_value=="--wind_alignment") {
            if(++i<argc) {
                std::string wind_alignment_str(argv[i]);
                try                            { wind_alignment = std::stoi(wind_alignment_str); }
                catch(std::exception const& e) { std::cerr << "wind_alignment must be a positive integer." << std::endl; return -1; }
                if(wind_alignment<0) { std::cerr << "wind_alignment must be a positive integer." << std::endl; return -1; }
                else                 { arg_set.insert("wind_alignment"); }
            }
            else { std::cerr << "wind_alignment is not specified." << std::endl; std::cerr << help_msg << std::endl; return -1; }
        }
        /* double */
        else if(arg_value=="--lx") {
            if(++i<argc) {
                std::string lx_str(argv[i]);
                try                            { lx = std::stod(lx_str); }
                catch(std::exception const& e) { std::cerr << "lx must be a positive float." << std::endl; return -1; }
                if(lx<=0) { std::cerr << "lx must be a positive float." << std::endl; return -1; }
                else      { arg_set.insert("lx"); }
            }
            else { std::cerr << "lx is not specified." << std::endl; std::cerr << help_msg << std::endl; return -1; }
        }
        else if(arg_value=="--ly") {
            if(++i<argc) {
                std::string ly_str(argv[i]);
                try                            { ly = std::stod(ly_str); }
                catch(std::exception const& e) { std::cerr << "ly must be a positive float." << std::endl; return -1; }
                if(ly<=0) { std::cerr << "ly must be a positive float." << std::endl; return -1; }
                else      { arg_set.insert("ly"); }
            }
            else { std::cerr << "ly is not specified." << std::endl; std::cerr << help_msg << std::endl; return -1; }
        }
        else if(arg_value=="--wind_speed") {
            if(++i<argc) {
                std::string wind_speed_str(argv[i]);
                try                            { wind_speed = std::stod(wind_speed_str); }
                catch(std::exception const& e) { std::cerr << "wind_speed must be a float." << std::endl; return -1; }
                arg_set.insert("wind_speed");
            }
            else { std::cerr << "wind_speed is not specified." << std::endl; std::cerr << help_msg << std::endl; return -1; }
        }
        else if(arg_value=="--min_wave_size") {
            if(++i<argc) {
                std::string min_wave_size_str(argv[i]);
                try                            { min_wave_size = std::stod(min_wave_size_str); }
                catch(std::exception const& e) { std::cerr << "min_wave_size must be a positive float." << std::endl; return -1; }
                if(min_wave_size<0) { std::cerr << "min_wave_size must be a positive float." << std::endl; return -1; }
                else                { arg_set.insert("min_wave_size"); }
            }
            else { std::cerr << "min_wave_size is not specified." << std::endl; std::cerr << help_msg << std::endl; return -1; }
        }
        else if(arg_value=="--A") {
            if(++i<argc) {
                std::string A_str(argv[i]);
                try                            { A = std::stod(A_str); }
                catch(std::exception const& e) { std::cerr << "A must be a positive float." << std::endl; return -1; }
                if(A<=0) { std::cerr << "A must be a positive float." << std::endl; return -1; }
                else     { arg_set.insert("min_wave_size"); }
            }
            else { std::cerr << "A is not specified." << std::endl; std::cerr << help_msg << std::endl; return -1; }
        }
        else {
            std::cerr << "Unknown \"" << arg_value << "\" parameter." << std::endl;
            std::cerr << help_msg << std::endl; return -1;
        }
    }
    /* errors */
    if(!check_long_args(help_msg)) return -1;
    return 0;
}

bool Arguments::parse_string_arg(std::string arg_value, int* i, std::string* arg_container, std::string error_msg) {
    if(++*i<argc) {
        *arg_container = std::string(argv[*i]);
        arg_set.insert(arg_value.substr(2, arg_value.size()-2));
        return true;
    }
    else {
        std::cerr << error_msg << std::endl;
        return false;
    }
}

bool Arguments::check_long_args(std::string help_msg) {
    return true;
}
