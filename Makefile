# third party
LIB_LIST     = glut
INCLUDE_LIST = GLUT
LIB_GLUT     = -lGL -lGLU -lGLUT

# project configuration
CC       = g++
LD_FLAGS = $(LIB_GLUT)
CC_FLAGS = -Wall -Wno-deprecated-declarations -std=c++11 -Ofast -funroll-loops
EXEC     = ocean

# project structure
MODULES     = ./ Ocean FFT Affichage
BUILD_DIR   = build
BIN_DIR     = bin
SRC_DIR     = $(addprefix src/, $(MODULES))
LIB_DIR     = lib
INCLUDE_DIR = include

# libs and headers subfolders lookup
LIB     = $(foreach lib, $(LIB_LIST), $(addprefix -L$(LIB_DIR)/, $(lib)))
INCLUDE = $(foreach include, $(INCLUDE_LIST), $(addprefix -I$(INCLUDE_DIR)/, $(include)))
SRC     = $(foreach sdir, $(SRC_DIR), $(wildcard $(sdir)/*.cpp))
OBJ     = $(foreach sdir, $(SRC_DIR), $(patsubst $(sdir)/%.cpp, $(BUILD_DIR)/%.o, $(wildcard $(sdir)/*.cpp)))

# sourcefile subfolders lookup
VPATH = $(SRC_DIR)/

# entry point
all: make_dir $(BIN_DIR)/$(EXEC) clean

# directory 'build'
make_dir:
	@echo $(OBJ)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

# create binary
$(BIN_DIR)/$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIB) $(LD_FLAGS)

# remove *.o and 'build' directory
clean:
	rm $(BUILD_DIR)/*.o
	rm -r $(BUILD_DIR)

# objects
$(BUILD_DIR)/main.o: main.cpp Window.hpp Ocean.hpp
	$(CC) $(INCLUDE) $(CC_FLAGS) -o $@ -c $<

$(BUILD_DIR)/Camera.o: Camera.cpp Camera.hpp Window.hpp
	$(CC) $(INCLUDE) $(CC_FLAGS) -o $@ -c $<

$(BUILD_DIR)/Window.o: Window.cpp Window.hpp
	$(CC) $(INCLUDE) $(CC_FLAGS) -o $@ -c $<

$(BUILD_DIR)/FFT.o: FFT.cpp FFT.hpp
	$(CC) $(INCLUDE) $(CC_FLAGS) -o $@ -c $<

$(BUILD_DIR)/Height.o: Height.cpp Height.hpp
	$(CC) $(INCLUDE) $(CC_FLAGS) -o $@ -c $<

$(BUILD_DIR)/Ocean.o: Ocean.cpp Ocean.hpp Height.hpp
	$(CC) $(INCLUDE) $(CC_FLAGS) -o $@ -c $<

$(BUILD_DIR)/Philipps.o: Philipps.cpp Philipps.hpp
	$(CC) $(INCLUDE) $(CC_FLAGS) -o $@ -c $<
