# compilator and liker flags
CC       = g++
LD_FLAGS = -lglut -lGL -lGLU32
CC_FLAGS = -Wall -O3 -funroll-loops
EXEC     = Ocean

# project configuration
MODULES   = Ocean FFT Affichage
BUILD_DIR = build
BIN_DIR   = bin
SRC_DIR   = $(addprefix src/, $(MODULES))

SRC     = $(foreach sdir, $(SRC_DIR), $(wildcard $(sdir)/*.cpp))
OBJ     = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))

VPATH = $(SRC_DIR)/

# entry point
all: make_dir $(BIN_DIR)/$(EXEC) clean

# directory 'build'
make_dir:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

# create binary
$(BIN_DIR)/$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LD_FLAGS)

# remove *.o and 'build' directory
clean:
	rm $(BUILD_DIR)/*.o
	rm -r $(BUILD_DIR)

# objects
$(BUILD_DIR)/main.o: main.cpp Window.hpp Ocean.hpp
	$(CC) $(CC_FLAGS) -o $@ -c $<

$(BUILD_DIR)/Camera.o: Camera.cpp Camera.hpp Window.hpp
	$(CC) $(CC_FLAGS) -o $@ -c $<

$(BUILD_DIR)/Window.o: Window.cpp Window.hpp
	$(CC) $(CC_FLAGS) -o $@ -c $<

$(BUILD_DIR)/FFT.o: FFT.cpp FFT.hpp
	$(CC) $(CC_FLAGS) -o $@ -c $<

$(BUILD_DIR)/Height.o: Height.cpp Height.hpp
	$(CC) $(CC_FLAGS) -o $@ -c $<

$(BUILD_DIR)/Ocean.o: Ocean.cpp Ocean.hpp Height.hpp
	$(CC) $(CC_FLAGS) -o $@ -c $<

$(BUILD_DIR)/Philipps.o: Philipps.cpp Philipps.hpp
	$(CC) $(CC_FLAGS) -o $@ -c $<
