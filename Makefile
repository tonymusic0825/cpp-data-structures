# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -g -Wpedantic

all: main

main: dynamicArray.cpp
	$(CXX) $(CXXFLAGS) -o main dynamicArray.cpp

clean:
	rm -f main