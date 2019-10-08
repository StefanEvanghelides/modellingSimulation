# Metadata: DIR is specified in environment
TARGET = ./run

# Compiler specs
CXX = g++
CXXFLAGS = -Wall -std=c++2a -pthread

# Sources and headers
# USE "dir /s /b *.cpp" to show all *.cpp files recursively
SOURCES := $(shell find $(shell pwd) -name '*.cpp')

# Link objects and create executable
$(TARGET):
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@

clean:
	rm -rf RUN