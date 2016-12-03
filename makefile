FLAGS = -std=c++11 -g

all: main.o KDTree.o
	g++ $(FLAGS) main.o KDTree.o -o main.exe

main.o: main.cpp
	g++ $(FLAGS) -c main.cpp

KDTree.o: KDTree.cpp KDTree.hpp
	g++ $(FLAGS) -c KDTree.cpp
