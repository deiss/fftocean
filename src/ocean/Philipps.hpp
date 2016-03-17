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
This class implements the Philipps spectrum, a spectrum representative of the spectrum
of ocean waves. The spectrum can be obtained with the operator (). This choice makes it
available for use with std::generate algorithm. This spectrum contains the scene parameters,
as they have an impact of the waves shape, so on their spectrum too. Such parameters are
wind speed, wind force (how the waves align with the wind direction) and the minimum wave size.
*/

#ifndef PHILIPPSHPP
#define PHILIPPSHPP

class Philipps {
    
    public:
    
        Philipps(const double, const double, const int, const int, const double, const int, const double, const double);
        ~Philipps() {}
    
        double operator()();
    
        void init_fonctor(int);
    
    private:
  
        const double lx;         /* actual width of the scene */
        const double ly;         /* actual height of the scene */
        const int    nx;         /* nb of x points - must be a power of 2 */
        const int    ny;         /* nb of y points - must be a power of 2 */
    
  const double wind_speed;       /* wind speed */
  const int    wind_alignment;   /* the greater it is, the better waves are in the wind's direction */
  const double min_wave_size;    /* waves are deleted if below this size */
  const double A;                /* numeric constant to adjust the waves height */
        
        int x;                   /* equals i-nx/2 in a series of calls to the functor  */
        int y;                   /* goes in the range [-ny/2 ; ny/2] in a series of calls to the functor */
    
};

#endif
