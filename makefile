CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude

SOURCES = src/main.cpp src/pbwt_algos.cpp src/pbwt_algos_single_sweep.cpp src/utils.cpp
EXEC = build/pbwt

all:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXEC)

clean:
	rm -f $(EXEC)

.PHONY: all clean
