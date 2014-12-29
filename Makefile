CC=g++
INC=-I./Affichage -I./FFT -I./Ocean
LXFLAGS=-lglut -lGL -lGLU
all: affichage fft ocean main.cpp
	$(CC) $(INC) main.cpp -o FFT-Ocean Camera.o Fenetre.o FFT.o Height.o Ocean.o Philipps.o $(LXFLAGS)

affichage: Affichage/Camera.cpp Affichage/Camera.hpp Affichage/Fenetre.cpp Affichage/Fenetre.hpp
	$(CC) $(INC) -c Affichage/Camera.cpp
	$(CC) $(INC) -c Affichage/Fenetre.cpp

fft: FFT/FFT.cpp FFT/FFT.hpp
	$(CC) $(INC) -c FFT/FFT.cpp

ocean: Ocean/Height.cpp Ocean/Height.hpp Ocean/Ocean.cpp Ocean/Ocean.hpp Ocean/Philipps.cpp Ocean/Philipps.hpp
	$(CC) $(INC) -c Ocean/Height.cpp
	$(CC) $(INC) -c Ocean/Ocean.cpp
	$(CC) $(INC) -c Ocean/Philipps.cpp

clean:
	rm -f *.o FFT-Ocean

