# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -g -Wpedantic -O3

all: main

main: doublyLinkedList.cpp
	$(CXX) $(CXXFLAGS) -o main doublyLinkedList.cpp

clean:
	rm -f main