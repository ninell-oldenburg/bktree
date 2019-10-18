# makefile for BKTree program
# Ninell Oldenburg
# Martikelnummer: 792821
# MacOS Majoave --version 10.14.6

CCPP = g++
CCC = clang

all: make-bktree

# Compile program
make-bktree: include/BKTree.hpp include include/Ed_Dis.hpp src/Main.cpp src/Computation.cpp makefile
	$(CCPP) -std=c++11 -o bktree src/Main.cpp
	mv bktree bin/bktree

# Make doxygen-HTML file
docs: docs/BKTree.doxygen
	doxygen docs/BKTree.doxygen

# Test program
tests: include/BKTree.hpp include include/Ed_Dis.hpp src/Main.cpp src/Computation.cpp makefile
	$(CCPP) -std=c++11 -o demo test/Demo.cpp
	mv demo test/demo
	test/demo
	

# Clean up
clean: 
	del /f demo.out
	del /f bin\bktree.out
	del /f /Q docs/html
	del /f data\*.dot

