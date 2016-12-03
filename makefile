CXX := g++
CXXFLAGS := -g -std=c++11 -Wall -Wextra -pedantic
LDFLAGS :=

all: main.o KDTree.o
	$(CXX) $(LDFLAGS) main.o KDTree.o -o main.exe

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

KDTree.o: KDTree.cpp KDTree.hpp
	$(CXX) $(CXXFLAGS) -c KDTree.cpp
