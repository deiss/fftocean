# FFTOcean

![Screenshot](media/Screenshot.png)

## PROJECT

FFTOcean is a C++ implementation of researcher J. Tessendorf's paper [*"Simulating Ocean Water"*](http://graphics.ucsd.edu/courses/rendering/2005/jdewall/tessendorf.pdf). It is a real-time simulation of ocean water in a 3D world. The (reverse) FFT is used to compute the 2D wave height field from the Philipps spectrum. It is possible to adjusts parameters such as wind speed, direction and strength, wave choppiness, and sea depth.

See on [Youtube](http://youtu.be/JSNyfPAvYbg).

## LICENSE

This project is licensed under the GPL License. See [COPYING](COPYING) for more information.

***

### Install

Linux/Mac : `make` will create the binary in the *bin* directory.

***

### Use

To launch a default simulation, call `bin/ocean`:

    bin/ocean
    
You can specify more parameters for the simulation. You can get a list of these parameters with the option `--help`.

    bin/ocean --help

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
