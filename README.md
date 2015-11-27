#### Project: FFT-Ocean<br/>
#### Author: DEISS Olivier<br/>

This project is an implementation of J. Tessendorf's paper:
http://graphics.ucsd.edu/courses/rendering/2005/jdewall/tessendorf.pdf

Language: C++<br/>
Libraries: OpenGL, Glut

-----------------------------------------------------------------------------------

Youtube video:

http://youtu.be/JSNyfPAvYbg

Images:

![Screenshot 1](Screenshot%201.png)
![Screenshot 2](Screenshot%202.png)

-----------------------------------------------------------------------------------

The project is only available for MacOS and Linux users.

I wrote the project in french, so you may not understand some directories names or
file names. I'm working on the translation of the whole sourcecode.

-----------------------------------------------------------------------------------

You can find the following directories:
   - Affichage: GUI of the project, creates a window, deals with the keyboard etc
   - FFT: my own implementation of the Cooley-Tuckey algorithm, for scientific 
           purposes. This can be replaced by using CUDA library.
   - Ocean: classes that are specific to the project

You can find both the classes Camera (to move over the water with the Z, Q, S, D
keys) and Affichage (to provide the GUI) in my repositories.

Feel free to leave any comment about the project, or if you want to improve it.

-----------------------------------------------------------------------------------

Compilation:
   - MacOS: add GLUT, OpenGL and ApplicationServices frameworks
   - Linux: $ make && make clean

To close the application:
   - MacOS: cmd+Q
   - Linux: alt+f4 or escape key

-----------------------------------------------------------------------------------

To do:
   - comment files in Affichage and FFT directories
   - add Windows version and information to compile the project (libs etc)
   - use another library instead of GLUT which is deprecated
   - add Perlin noise to compute further waves at a lower cost
   - add textures to the waves
   - keyboard control to switch parameters while running the program



