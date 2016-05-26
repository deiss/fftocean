/*

    This class is part of another project Help80 also available on Github.
    
************************************************************************************************
 
LICENSE

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
 
************************************************************************************************

FILE


    The classes defined in this file can be used for parameters parsing and display, while
    making sure the help menu looks nice on terminals.

    This file defines classes Parameters, ParamHolder and Param. Param is a template function
    that inherits from ParamHolder. Parameters owns a std::vector of ParamHolder, and has access
    to the derived object Param through dynamic_cast.
    
    To store parameters of multiple types, the std::string version of types is available with
    typeid(T).name(). This type is stored in ParamHolder. When arguments are parsed, each type is
    tried, and the right function is called for the right type (among stoi, stod, stold, and
    nothing for std::string parameters).
    
    
                          ---------------                 ----------------
                          | ParamHolder |---------------<>|  Parameters  |
                          ---------------                 ----------------
                                 ^
                                 |
                                 |    ------------
                         -------------| Template |
                         |     Param  --+---------
                         ----------------
 
                         
    ParamHolder and Param are private nested classes inside class Parameters. Also, Parameters
    defines the following exception classes:
        - ValueOutOfRangeException: thrown if the value given is not in the range of the built-in
                                    type
        - NotEnoughValuesException: when cmd line doesn't have as many args as required
        - DecimalExpectedException: when a decimal value is expected but not given
        - IntegerExpectedException: when an integer value is expected but not given
        - UndefinedValueException: when trying to access n-th value of a parameter that doesn't
                                   exist
        - UnsupportedParameterTypeException: when the developer tries to create a parameter of
                                             unsupported type
        - DuplicateParameterException: when the developer tries to create a parameter with an
                                       existing name
        - UnknownParameterException: when there is an unknown parameter in the command line
        - UndefinedParameterException: when the developer tries to retrieve value for a parameter
                                       that doesn't exist
        - DynamicCastFailedException: when a dynamic_cast returns a null pointer. This happens in
                                      a call to num_val with wrong template type for instance
    
 
    How to build the menu:
        
        First you can specify a description of your program, and how to use it with functions
        set_program_description and set_usage.
 
        To build the menu, use the functions:
            - define_param :        to define a parameter with no value
            - define_num_str_param: to define a numeric or std::string parameter
            - define_choice_param:  to define a multiple choice parameter
 
        You can add structure by adding subsections with function insert_subsection.
        When the menu is ready, you can print it with print_help().
        
 
    How to use the parameters:
 
        First, call parse_params to analyse the command line arguments. Then,
        use the functions:
            - is_spec : to know if a simple parameter is specified
            - num_val : to get a numeric value
            - str_val : to get a std::string value
            - cho_val : to get a multiple choice value
 
************************************************************************************************

*/

#ifndef Parameters_hpp
#define Parameters_hpp

#define PLATFORM_WINDOWS  1
#define PLATFORM_MAC      2
#define PLATFORM_UNIX     3

#define INVALID_SOCKET -1
#define SOCKET_ERROR   -1

/* platform detection */
#if defined(_WIN32)
    #define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
    #define PLATFORM PLATFORM_MAC
#else
    #define PLATFORM PLATFORM_UNIX
#endif

/* headers for terminal width */
#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
    #include <sys/ioctl.h>
    #include <stdio.h>
    #include <unistd.h>
#elif PLATFORM == PLATFORM_WINDOWS
    #include <windows.h>
#endif

/* other headers */
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <sstream>
#include <typeinfo>
#include <vector>

class Parameters {

    class ParamHolder;

    public:
    
        typedef std::vector<std::pair<std::string, std::string>> vec_choices;
    
        enum LANG {lang_fr, lang_us};
    
        struct config {
            const int min_terminal_width;                                                  // min width of terminal
            const int max_terminal_width;                                                  // max width of terminal
            const int params_indent_len;                                                   // nb of characters from the left to print param+values
            const int param_to_desc_len;                                                   // nb of spaces between longest param list and descripton
            const int desc_indent_len;                                                     // nb of characters from the left to print description
            const int choice_indent_len;                                                   // indentation for choices descriptions
            const int choice_desc_indent_len;                                              // indentation for choice description
            const int right_margin_len;                                                    // nb of chars from the right of the terminal
            LANG      lang;                                                                // language to print the menu in
        };
    
        Parameters(const int, char const* const* const, config);
        Parameters(const int, char const* const* const, config, const int);
        ~Parameters();
    
        /* use of parameters */
        template<typename T>
        const T                   num_val(const std::string&, const int=1) const;          // return n-th value for parameter. nb starts at 1
        const std::string         str_val(const std::string&, const int=1) const;          // return n-th value for parameter. nb starts at 1
        const std::string         cho_val(const std::string&)              const;          // returns choice value
        const bool                is_spec(const std::string&)              const;          // tells if parameters is defined
        void                      parse_params();                                          // reads cmd line and store args
    
        /* help menu */
        void                      insert_subsection(const std::string&);                   // prints subsection when printing help menu
        void                      print_help(const bool=true, const bool=true) const;      // print help menu
        void                      set_program_description(const std::string&);             // sets program description
        void                      set_usage(const std::string&);                           // sets usage
        void                      print_license();                                         // prints GPL license
    
        template<typename T>  // in the order: add a parameter with values, with choices, with no values
        void define_num_str_param(const std::string&, const std::vector<std::string>&, const std::vector<T>&, const std::string&, const bool=false);
        void define_choice_param(const std::string&, const std::string&, const std::string&, vec_choices, const std::string&, const bool=false);
        void define_param(const std::string&, const std::string&);
    
    
    private:
    
        typedef std::map<std::string, ParamHolder* const> map_params;
        typedef std::map<std::string, vec_choices>        map_choices;
        typedef std::map<size_t, std::string>             map_order;
    
        Parameters(const Parameters&);
        Parameters& operator=(const Parameters&);
    
        /* display funcs */
        static const int          get_terminal_width();                                    // returns current's terminal width
        static const std::string  bold(const std::string&);                                // returns the bold version of str
        static const std::string  underline(const std::string&);                           // returns the underlined version of str
        template<typename T> void pr_def(ParamHolder* const, const bool=false) const;      // prints default value
        void                      print_description()                          const;      // print program description
        void                      print_usage()                                const;      // print usage
        void                      print_parameters()                           const;      // print list of parameters
    
        /* cmd line */
        const int                 argc;                                                    // command line args number
        char const* const* const  argv;                                                    // command line args values
    
        /* display parameters */
        const int                 min_terminal_width;                                      // max width of the terminal
        const int                 max_terminal_width;                                      // max width of the terminal
        const int                 terminal_width;                                          // the width of the terminal
        const int                 param_to_desc_len;                                       // nb of spaces between longest param list and descripton
        const int                 desc_indent_len;                                         // nb of characters form the left to print desccription
        const int                 params_indent_len;                                       // nb of characters from the left to print param+values
        const int                 choice_indent_len;                                       // indentation for choices
        const int                 choice_desc_indent_len;                                  // indentation for choices descriptions
        const int                 right_margin_len;                                        // nb of chars from the right of the terminal
        std::string               desc_indent;                                             // spaces for indentation of big description
        std::string               choice_indent;                                           // indentation for choices descriptions
        std::string               params_indent;                                           // string of 'params_indent_len' spaces
        std::string               choice_desc_indent;                                           // string of 'params_indent_len' spaces
    
        /* internal vars */
        const LANG                lang;                                                    // language to print the menu in
        std::string               description;                                             // description of the program
        bool                      description_is_set;                                      // true if set_description() is called
        std::string               usage;                                                   // usage of the program
        bool                      usage_is_set;                                            // true if set_usage() is called
        std::vector<std::string>  subsections;                                             // sub sections titles in the help menu
        std::vector<std::size_t>  subs_indexes;                                            // indexes of the subsections (where to print them)
        map_params                params;                                                  // data structure that stores all the parameters
        map_order                 order;                                                   // data structure to store order of parameters
        map_choices               choices;                                                 // stores choices associated to choice-parameters
        std::set<std::string>     choices_params;                                          // stores all the params that are multiple choice
    
    
    private:
    
        class ParamHolder {

            public:
            
                ParamHolder(const std::string& p_name, const std::string& p_description, const std::string& p_type_name, const std::vector<std::string>& p_values_names={}, const bool p_display_default_value=false):
                    name(p_name),
                    description(p_description + " "),
                    nb_values(static_cast<int>(p_values_names.size())),
                    values_names(p_values_names),
                    type_name(p_type_name),
                    display_default_value(p_display_default_value),
                    is_defined(false) {}
                virtual ~ParamHolder() {}
            
                const std::string              name;                                       // param name with added suffix '--'
                const std::string              description;                                // long description paragraph, can't start or end with ' '
                const int                      nb_values;                                  // nb of values expected for the parameters
                const std::vector<std::string> values_names;                               // name of these values, without '<' and '>'
                const std::string              type_name;                                  // to distinguish the type of the values
                const bool                     display_default_value;                      // if default value has to be displayed in help menu
                bool                           is_defined;                                 // if the arg was specified by the user
            
            
            private:
            
                ParamHolder(const ParamHolder&);
                ParamHolder& operator=(const ParamHolder&);

        };

        template<typename T>
        class Param: public ParamHolder {

            public:
            
                Param(const std::string& p_name, const std::string& p_description, const std::vector<std::string>& p_values_names, const std::vector<T>& p_default_values, const bool p_display_default_value):
                    ParamHolder(p_name, p_description, typeid(T).name(), p_values_names, p_display_default_value),
                    values(p_default_values),
                    def_values(p_default_values) {}
                Param(const std::string& p_name, const std::string& p_description):
                    ParamHolder(p_name, p_description, typeid(T).name()) {}
                virtual ~Param() {}
                
                std::vector<T>       values;                                               // parameter values
                const std::vector<T> def_values;                                           // parameter default values

        };


    public:

        class UndefinedParameterException: public std::exception {
            public:
                UndefinedParameterException(const std::string& p_param_name, const std::string& p_function, LANG p_lang) throw():
                    description(p_lang==lang_fr
                        ? "dans " + p_function + " : paramètre \"--" + p_param_name + "\" non défini"
                        : "in function " + p_function + ": undefined parameter \"--" + p_param_name + "\"") {}
                virtual ~UndefinedParameterException() throw() {}
                virtual const char* what()       const throw() { return description.c_str(); }
            private:
                const std::string description;   
        };

        class UnknownParameterException: public std::exception {
            public:
                UnknownParameterException(const std::string& p_param_name, const std::string& p_function, LANG p_lang) throw():
                    description(p_lang==lang_fr
                        ? "dans " + p_function + " : paramètre \"" + p_param_name + "\" inconnu"
                        : "in function " + p_function + ": unknown parameter \"" + p_param_name + "\"") {}
                virtual ~UnknownParameterException() throw() {}
                virtual const char* what()       const throw() { return description.c_str(); }
            private:
                const std::string description;
        };

        class DuplicateParameterException: public std::exception {
            public:
                DuplicateParameterException(const std::string& p_param_name, const std::string& p_function, LANG p_lang) throw():
                    description(p_lang==lang_fr
                        ? "dans " + p_function + " : définition du paramètre \"" + p_param_name + "\" : un paramètre de même nom existe déjà"
                        : "in function " + p_function + ": definition of parameter \"" + p_param_name + "\": a parameter with the same name already exists") {}
                virtual ~DuplicateParameterException() throw() {}
                virtual const char* what()       const throw() { return description.c_str(); }
            private:
                const std::string description;
        };

        class UnsupportedParameterTypeException: public std::exception {
            public:
                UnsupportedParameterTypeException(const std::string& p_type, const std::string& p_function, LANG p_lang) throw():
                    description(p_lang==lang_fr
                        ? "dans " + p_function + " : type de paramètre \"" + p_type + "\" pas encore supporté"
                        : "in function " + p_function + ": type \"" + p_type + "\" not supported yet") {}
                virtual ~UnsupportedParameterTypeException() throw() {}
                virtual const char* what()             const throw() { return description.c_str(); }
            private:
                const std::string description;
        };

        class UndefinedValueException: public std::exception {
            public:
                UndefinedValueException(std::string const& p_param_name, const int nb_values, const int req_value, const std::string& p_function, LANG p_lang) throw():
                    description(p_lang==lang_fr
                        ? "dans " + p_function + " : paramètre \"" + p_param_name + "\" : " + std::to_string(nb_values) + " valeurs, tentative d'accès à " + std::to_string(req_value)
                        : "in function " + p_function + ": parameter \"" + p_param_name + "\": " + std::to_string(nb_values) + " values, tried to access " + std::to_string(req_value)) {}
                virtual ~UndefinedValueException() throw() {}
                virtual const char* what()    const throw() { return description.c_str(); }
            private:
                const std::string description;
        };

        class IntegerExpectedException: public std::exception {
            public:
                IntegerExpectedException(std::string const& p_param_name, const std::string& arg_value, const std::string& p_function, LANG p_lang) throw():
                    description(p_lang==lang_fr
                        ? "dans " + p_function + " : le paramètre \"" + p_param_name + "\" attend une valeur entière, et a reçu \"" + arg_value + "\""
                        : "in function " + p_function + ": parameter \"" + p_param_name + "\" expects an integer value, but received \"" + arg_value + "\"") {}
                virtual ~IntegerExpectedException() throw() {}
                virtual const char* what()    const throw() { return description.c_str(); }
            private:
                const std::string description;
        };

        class DecimalExpectedException: public std::exception {
            public:
                DecimalExpectedException(std::string const& p_param_name, const std::string& arg_value, const std::string& p_function, LANG p_lang) throw():
                    description(p_lang==lang_fr
                        ? "dans " + p_function + " : le paramètre \"" + p_param_name + "\" attend une valeur décimale, et a reçu \"" + arg_value + "\""
                        : "in function " + p_function + ": parameter \"" + p_param_name + "\" expects a decimal value, but received \"" + arg_value + "\"") {}
                virtual ~DecimalExpectedException() throw() {}
                virtual const char* what()    const throw() { return description.c_str(); }
            private:
                const std::string description;
        };

        class NotEnoughValuesException: public std::exception {
            public:
                NotEnoughValuesException(std::string const& p_param_name, const int nb_values, const int rec_values, const std::string& p_function, LANG p_lang) throw():
                    description(p_lang==lang_fr
                        ? "dans " + p_function + " : le paramètre \"" + p_param_name + "\" attend " + std::to_string(nb_values) + " valeurs, et en a reçu " + std::to_string(rec_values)
                        : "in function " + p_function + ": parameter \"" + p_param_name + "\" expects " + std::to_string(nb_values) + " values, but received " + std::to_string(rec_values)) {}
                virtual ~NotEnoughValuesException() throw() {}
                virtual const char* what()    const throw() { return description.c_str(); }
            private:
                const std::string description;
        };

        template<typename T>
        class ValueOutOfRangeException: public std::exception {
            public:
                ValueOutOfRangeException(std::string const& p_param_name, const std::string& arg_value, const std::string& p_function, LANG p_lang) throw():
                    min(nb_to_string(std::numeric_limits<T>::min())),
                    max(nb_to_string(std::numeric_limits<T>::max())),
                    description(p_lang==lang_fr
                        ? "dans " + p_function + " : le paramètre \"" + p_param_name + "\" doit être compris entre " + min + " et " + max + " mais a reçu " + arg_value
                        : "in function " + p_function + ": parameter \"" + p_param_name + "\" must be between " + min + " and " + max + " but received " + arg_value) {}
                virtual ~ValueOutOfRangeException() throw() {}
                virtual const char* what()    const throw() { return description.c_str(); }
            private:
                const std::string nb_to_string(T nb) { std::ostringstream oss; oss << nb; return oss.str(); }
                const std::string min;
                const std::string max;
                const std::string description;
        };

        class UnknownChoiceException: public std::exception {
            public:
                UnknownChoiceException(std::string const& p_param_name, const std::string& arg_value, const std::string& p_function, LANG p_lang) throw():
                    description(p_lang==lang_fr
                        ? "dans " + p_function + " : le choix \"" + arg_value + "\" pour le paramètre \"" + p_param_name + "\" n'est pas disponible"
                        : "in function " + p_function + ": choice \"" + arg_value + "\" for parameter \"" + p_param_name + "\" is not available") {}
                virtual ~UnknownChoiceException() throw() {}
                virtual const char* what()    const throw() { return description.c_str(); }
            private:
                const std::string description;
        };

};


/*** template functions definition ***/

template<typename T>
void Parameters::define_num_str_param(const std::string& param_name, const std::vector<std::string>& values_names, const std::vector<T>& default_param_values, const std::string& param_desc, const bool display_default_value) {
    /* check if already exist */
    if(params.count("--" + param_name)) {
        throw DuplicateParameterException(param_name, "Parameters::define_param", lang);
    }
    /* get type name */
    const std::string type_name = typeid(T).name();
    /* create param */
    Param<T>* const p = new Param<T>("--" + param_name, param_desc, values_names, default_param_values, display_default_value);
    /* store param */
    order.insert(std::make_pair(params.size(), "--" + param_name));
    params.insert(std::make_pair("--" + param_name, p));
}

template<typename T>
void Parameters::pr_def(ParamHolder* const p, const bool add_quotes) const {
    if(typeid(T).name()!=typeid(short int    ).name() && typeid(T).name()!=typeid(unsigned short int    ).name()
    && typeid(T).name()!=typeid(int          ).name() && typeid(T).name()!=typeid(unsigned int          ).name()
    && typeid(T).name()!=typeid(long int     ).name() && typeid(T).name()!=typeid(unsigned long int     ).name()
    && typeid(T).name()!=typeid(long long int).name() && typeid(T).name()!=typeid(unsigned long long int).name()
    && typeid(T).name()!=typeid(float        ).name() && typeid(T).name()!=typeid(std::string           ).name()
    && typeid(T).name()!=typeid(double       ).name() && typeid(T).name()!=typeid(long double           ).name()) {
        throw UnsupportedParameterTypeException(typeid(T).name(), "Parameters::num_val", lang);
    }
    else {
        const Param<T>* const p_reint = dynamic_cast<Param<T>* const>(p);
        if(lang==lang_fr) std::cout << desc_indent << bold("Défaut :");
        else              std::cout << desc_indent << bold("Default:");
        for(int j=0 ; j<p->nb_values ; j++) {
            if(!add_quotes) { std::cout << " "   << p_reint->def_values[static_cast<std::size_t>(j)];         if(j<p->nb_values-1) std::cout << ","; }
            else            { std::cout << " \"" << p_reint->def_values[static_cast<std::size_t>(j)] << "\""; if(j<p->nb_values-1) std::cout << ","; }
        }
        std::cout << std::endl;
    }
}

template<typename T>
const T Parameters::num_val(const std::string& param_name, const int value_number) const {
    if(params.count("--" + param_name)) {
        Parameters::ParamHolder* const p = params.at("--" + param_name);
        if(value_number>p->nb_values) {
            throw UndefinedValueException(param_name, p->nb_values, value_number, "Parameters::str_val", lang);
        }
        else {
            if(typeid(T).name()!=typeid(short int    ).name() && typeid(T).name()!=typeid(unsigned short int    ).name()
            && typeid(T).name()!=typeid(int          ).name() && typeid(T).name()!=typeid(unsigned int          ).name()
            && typeid(T).name()!=typeid(long int     ).name() && typeid(T).name()!=typeid(unsigned long int     ).name()
            && typeid(T).name()!=typeid(long long int).name() && typeid(T).name()!=typeid(unsigned long long int).name()
            && typeid(T).name()!=typeid(float        ).name()
            && typeid(T).name()!=typeid(double       ).name() && typeid(T).name()!=typeid(long double           ).name()) {
                throw UnsupportedParameterTypeException(typeid(T).name(), "Parameters::num_val", lang);
            }
            else {
                /* reinterpret with the good type */
                Param<T>* const p_reint = dynamic_cast<Param<T>* const>(p);
                /* return value */
                return p_reint->values[static_cast<std::size_t>(value_number-1)];
            }
        }
    }
    else {
        throw UndefinedParameterException(param_name, "Parameters::define_param", lang);
    }
}

#endif
