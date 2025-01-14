# Makefile for main.cpp

# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -Ofast -I/usr/include/osmium
LDFLAGS := -lz -lprotobuf-lite

# Target executable
TARGET := main

# Source files
SRC := main.cpp

# Object files
OBJ := $(SRC:.cpp=.o)

# Default target to build the executable
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets (to avoid conflicts with file names)
.PHONY: all clean