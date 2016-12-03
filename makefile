CXX ?= g++
CXXFLAGS := -g -std=c++11 -Wall -Wextra -pedantic
LDFLAGS :=

all: main.o
	$(CXX) $(LDFLAGS) main.o -o main.exe

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp
