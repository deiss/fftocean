# FFT-Ocean

![Screenshot](Screenshot.png)
Youtube: http://youtu.be/JSNyfPAvYbg

## PROJECT

FFT-Ocean is a C++ implementation of researcher J. Tessendorf's paper "Simulating Ocean Water":
http://graphics.ucsd.edu/courses/rendering/2005/jdewall/tessendorf.pdf

The FFT is used to compute the wave height field. In the paper, the Philips spectrum is used for the computation. It has parameters like wind speed, direction and strength, wave choppiness, and sea depth.

## LICENSE

This project is licensed under the GPL License. See COPYING for more information.

***

### Install

Linux/Mac : 'make' will create the binary in the 'bin' directory.

### Use

To launch the simulation, call bin/ocean:

    bin/ocean

To close the application:

   *MacOS: cmd+Q
   *Linux: alt+f4 or escape key

### Contact

##### olivier . deiss [at] gmail . com