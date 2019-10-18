# Burkhard-Keller-Tree

This is a program for Approximate String Search using a Burkhard-Keller-Tree for storing. It uses three different string 
metrics for the edit distance calculation.

## Description

The function can be invoked by typing the name of the file (bktree) and the name of the wordlist in the command line. You can 
choose between the string metric to use. I've implemented the Damerau-Levenshtein-Distance as well as the Longest-Common-
Subsequence. In default mode the program is going to use the Levenshtein distance. The program is going to build a Burkhard-
Keller-Search-Tree (see http://blog.notdot.net/2007/4/Damn-Cool-Algorithms-Part-1-BK-Trees for more infos) out of the list, 
prints is height and number of nodes, before displaying the interactive mode. Here, the user can type a word and the an edit 
distance depending on the string metric used and the program will search the tree for strings with that given edit distance.

It was developed under MacOS Mojave version 10.14.6 and g++ compiler version 4.2.1 

## Use

Type make in the command line to compile the program. See below for detailed functions of the included makefile. Feel free to 
also compile the program by yourself. Start the program by typing its name and the name of the wordlist, choose the string 
metric (see https://en.wikipedia.org/wiki/String_metric for more infos) and type string to be searched on with a given edit 
distance.

* make -- > compiles the program and stores .out file in /bin
* make docs -- > writes doxygen-HTML-file for documentation
* make demo -- > compiles demo-program
* make clean -- > removes everything

## Architectur

The strings are stored binary in vectors of 16-bit, one bit representing one ASCII letter, including German ASCIIs ä, ö, ü as 
well as capital Umlaute. The edit distance calculation for the three string metrics is implemented as a function object. The 
BK-Tree class uses the function objects as templates, so every string metric will be instantiated while compile time.


