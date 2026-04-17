# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -g -Wpedantic -O3

all: main

main: customMap.cpp
	$(CXX) $(CXXFLAGS) -o main customMap.cpp

clean:
	rm -f main