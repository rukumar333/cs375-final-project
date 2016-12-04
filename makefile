CXX ?= g++
CXXFLAGS := -g -O3 -std=c++11 -Wall -Wextra -pedantic
LDFLAGS :=

all: main.o NearestNeighbor.o
	$(CXX) $(LDFLAGS) main.o NearestNeighbor.o -o main.exe

main.o: main.cpp KDTree.hpp Point.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

NearestNeighbor.o: NearestNeighbor.cpp NearestNeighbor.hpp KDTree.hpp Point.hpp
	$(CXX) $(CXXFLAGS) -c NearestNeighbor.cpp

clean:
	-rm *.o main.exe
