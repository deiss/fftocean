# FFTOcean

![Screenshot](media/Screenshot.png)

## PROJECT

FFTOcean is a C++ implementation of researcher J. Tessendorf's paper [*"Simulating Ocean Water"*](http://graphics.ucsd.edu/courses/rendering/2005/jdewall/tessendorf.pdf). It is a real-time simulation of ocean water in a 3D world. The (reverse) FFT is used to compute the 2D wave height field from the Philipps spectrum. It is possible to adjusts parameters such as wind speed, direction and strength, wave choppiness, and sea depth.

See on [Youtube](http://youtu.be/JSNyfPAvYbg).

## LICENSE

FFTOcean

Copyright (C) 2016 -  Olivier Deiss

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

You should have received [a copy of the GNU General Public License](COPYING)
along with this program. If not, see <http://www.gnu.org/licenses/>.

***

### Install

##### Linux

You need to have glut installed on your platform. You can install it with:

	apt-get install freeglut3 freeglut3-dev

Then running `make linux` will compile *FFTOcean* in *bin*. You can run `make clean` to delete the build directory.

##### Mac

You need to have XCode installed on your system. Then running `make mac` will compile *FFTOcean* in *bin*. You can run `make clean` to delete the build directory.

***

### Use

To launch a default simulation, call `bin/fftocean`:

    bin/fftocean
    
You can specify more parameters for the simulation. You can get a list of these parameters with the option `--help`.

    bin/fftocean --help

To close the application:
* Mac: `cmd+Q`
* Linux: `alt+f4`

Using the mouse, you can look around you. To move, the keys depend on the keyboard, and you can specify the type of keyboard you are using with the option `--keyboard` (default: "azerty").

##### AZERTY

You can move using the `Z`, `Q`, `S`, `D` keys as follow:

* `Z`: go forward
* `Q`: translate to the left
* `S`: go backward
* `D`: translate to the right

##### QWERTY

You can move using the `W`, `A`, `S`, `D` keys as follow:

* `W`: go forward
* `A`: translate to the left
* `S`: go backward
* `D`: translate to the right 

***

### Contact

olivier . deiss [at] gmail . com
