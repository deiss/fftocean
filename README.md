# FFTOcean

![Screenshot](media/Screenshot.png)

FFTOcean is a C++ implementation of researcher J. Tessendorf's paper [*"Simulating Ocean Water"*](http://graphics.ucsd.edu/courses/rendering/2005/jdewall/tessendorf.pdf). It is a real-time simulation of ocean water in a 3D world. The (reverse) FFT is used to compute the 2D wave height field from the Philipps spectrum. It is possible to adjust parameters such as wind speed, direction and strength, wave choppiness, and sea depth.

See on [Youtube](http://youtu.be/JSNyfPAvYbg).

***

### Install

##### Linux

You need to have glut installed on your platform. You can install it with:

	apt-get install freeglut3 freeglut3-dev

Then running `make linux` will compile *fftocean* in *bin*. You can run `make clean` to delete the build directory.

##### Mac

You need to have XCode installed on your system. Then running `make mac` will compile *fftocean* in *bin*. You can run `make clean` to delete the build directory.

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

### Improvements

I wanted to focus on the mathematical aspect of the waves, which is why I did not spend much time on the rendering aspect. J. Tessendorf's paper gives ways to obtain a really nice rendering, taking into consideration the reflection of the sun. 

This project is meant to be embedded in a video game or any type of simulation. For this kind of project, you may need an infinite ocean. Fortunately, the reverse FFT produces a periodical signal so you can multiply the patterns of ocean and put them one next to another. The downward of this method is that if the viewpoint is high on the *z* axis, this periodicity will be striking to the user. One solution is to create waves with a second method which does not require a lot of computing power (like using Perlin noise), and to mix it with these waves. The resulting wave *w* will be the sum of the FFT wave *wf* and of the Perlin noise wave *wp*: *w* = a*wf* + b*wp*. *a* and *b* coefficients will be dynamically adjusted so that for a wave that is close to the viewer, the FFT part of the wave is dominant, but for further waves it is the perlin noise part of the wave that takes over.

***

### License

FFTOcean - Copyright (C) 2016 -  Olivier Deiss

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

### Contact

olivier . deiss [at] gmail . com
