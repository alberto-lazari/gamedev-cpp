# Compiler
CXX := g++

# Directories
BUILD_DIR := bin
EXE := $(BUILD_DIR)/sdlproj

# SDL Library Path
SDL := SDL2-2.30.11

# Dynamic libraries path
DYLD_LIBRARY_PATH := $(SDL)/lib/$(shell uname -m)

# Source Files
SRC := Source/Core/*.cpp \
			 Source/Main.cpp

# Compiler Flags
CXXFLAGS := -std=c++11 \
            -Wall \
            -Wextra \
            -I$(SDL)/include

LDFLAGS := -L$(DYLD_LIBRARY_PATH) \
           -lSDL2 \
           -lSDL2_image \
           -lSDL2_mixer \
           -lSDL2_ttf

# Build Rule
build: $(EXE)

$(EXE): $(BUILD_DIR) $(SRC)
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SRC) -o $(EXE)

# Run the executable
run: build
	@# Set dynamic libraries search path
	@DYLD_LIBRARY_PATH=$(DYLD_LIBRARY_PATH) \
		$(EXE)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Clean Rule
clean:
	@rm -rf $(BUILD_DIR)

.PHONY: clean
