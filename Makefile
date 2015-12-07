CC=g++
INC=-I./Affichage -I./FFT -I./Ocean
LXFLAGS=-lglut -lGL -lGLU
CFLAGS=-O3 -funroll-loops
all: affichage fft ocean main.cpp
	$(CC) $(INC) $(CFLAGS) main.cpp -o FFT-Ocean Camera.o Fenetre.o FFT.o Height.o Ocean.o Philipps.o $(LXFLAGS)

affichage: Affichage/Camera.cpp Affichage/Camera.hpp Affichage/Fenetre.cpp Affichage/Fenetre.hpp
	$(CC) $(INC) $(CFLAGS) -c Affichage/Camera.cpp
	$(CC) $(INC) $(CFLAGS) -c Affichage/Fenetre.cpp

fft: FFT/FFT.cpp FFT/FFT.hpp
	$(CC) $(INC) $(CFLAGS) -c FFT/FFT.cpp

ocean: Ocean/Height.cpp Ocean/Height.hpp Ocean/Ocean.cpp Ocean/Ocean.hpp Ocean/Philipps.cpp Ocean/Philipps.hpp
	$(CC) $(INC) $(CFLAGS) -c Ocean/Height.cpp
	$(CC) $(INC) $(CFLAGS) -c Ocean/Ocean.cpp
	$(CC) $(INC) $(CFLAGS) -c Ocean/Philipps.cpp

clean:
	rm -f *.o

