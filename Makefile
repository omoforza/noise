CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -Iinclude
LDFLAGS = -lm -lfftw3l
SOURCES = src/test.cpp src/laser.cpp src/mirror.cpp src/cavity.cpp src/electric_field.cpp src/AmpA.cpp src/AmpB.cpp src/AmpC.cpp src/AmpF.cpp src/amplifier.cpp src/hpf.cpp src/pdh.cpp
OBJECTS = $(patsubst src/%.cpp, build/%.o, $(SOURCES))
TARGET = test.x

# Default target
all: $(TARGET)

# Linking the final target
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compile each source file to object files
build/%.o: src/%.cpp
	@mkdir -p build # Only create build directory if it doesn't exist
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and executables
clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -rf build

# Remove object files if sources have changed
.PHONY: all clean