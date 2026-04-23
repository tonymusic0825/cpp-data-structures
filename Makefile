# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -g -Wpedantic -O3

all: main

main: vvMap.cpp
	$(CXX) $(CXXFLAGS) -o main vvMap.cpp

clean:
	rm -f main