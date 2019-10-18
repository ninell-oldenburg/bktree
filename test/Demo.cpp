// Author: Ninell Oldenburg
// Matrikelnummer: 792821
// Compiler: GCC g++ --version 4.2.1
// Operating System: MacOS Mojave --version 10.14.6
//
// Demo.cpp
// C-file for demonstrating program's functions


#include <iostream>
#include <sstream>
#include "../src/Computation.cpp"
#include <stdio.h>


int main() {
    
  std::cout << "This is a short demonstration of BKTree.hpp "
            << "using a small input file (\"testwordlist.txt\"). \n"
            << "This file contains empty lines as well as duplicates of the same word." << "\n";

  std::cout << "Creating an instance of BKTree with Levenshtein-Distance ..." << "\n";
  BKTree<Lev> bkt("../data/testwordlist.txt");

  // Print stats
  std::cout << "Printing statistics for the created tree to std::cerr ..." << "\n";
    std::pair<int,int> stats_lev = bkt.get_stats();
    std::cout << "Number of nodes: " << stats_lev.first << "," << std::endl;
    std::cout << "Height of: " << stats_lev.second << ".\n" << std::endl;

  // Create dot file
  std::cout << "Creating a dot file \"testwordlist_lev.dot\" (make_dot(\"../data/testwordlist_lev.dot\")) ..." << "\n";
  bkt.make_dot("../data/testwordlist_lev.dot");

  // Search tree
  std::cout << "\nThe BK tree will now be searched for various input words "
            << "and tolerance values d (find()). " << "\n";
  std::cout << "1) A word that is already in the tree and thus can be matched: kork" << "\n";
  std::cout << "(returns kork for all d)" << "\n";
    std::cout << ">>> " << bkt.find("kork",0)[0] << std::endl << std::endl;

    std::cout << "2) A word that is not in the tree: krok" << "\n";
  std::cout << "d = 1 returns kook" << "\n";
    std::cout << ">>> " << bkt.find("krok",1)[0] << std::endl << std::endl;
    
    
    
    // Same for LCS
    std::cout << std::endl << "We're doing the same now with the LCS" << std::endl;
    std::cout << "Creating an instance of BKTree with LCS-Distance ..." << "\n";
    BKTree<LCS> lcs("../data/testwordlist.txt");
    std::cout << "BKTree object created successfully." << "\n\n";

    // Print stats
    std::cout << "Printing statistics for the created tree to std::cerr ..." << "\n";
      std::pair<int,int> stats_lcs = lcs.get_stats();
      std::cout << "Number of nodes: " << stats_lcs.first << "," << std::endl;
      std::cout << "Height of: " << stats_lcs.second << ".\n" << std::endl;

    // Create dot file
    std::cout << "Creating a dot file \"testwordlist_lcs.dot\" (make_dot(\"../data/testwordlist_lcs.dot\")) ..." << "\n";
    lcs.make_dot("../data/testwordlist_lcs.dot");

    // Search tree
    std::cout << "\nThe BK tree will now be searched for various input words "
              << "and tolerance values d (find()). " << "\n";
    std::cout << "1) A word that is already in the tree and thus can be matched: kork" << "\n";
    std::cout << "(returns kork for all d=4)" << "\n";
      std::cout << ">>> " << lcs.find("kork",4)[0] << std::endl;

    std::cout << "2) A word that is not in the tree: krok" << "\n";
    std::cout << "d = 3 returns kork and kook" << "\n";
      std::cout << ">>> " << lcs.find("krok",3)[0] << ", " << lcs.find("krok",3)[1] << ", " << std::endl;
    
    
    // Same for Damerau-Levenshtein-Distance
    std::cout << std::endl << "We're doing the same now with the Damerau-Levenshtein-Distance" << std::endl;
    std::cout << "Creating an instance of BKTree with DLev-Distance ..." << "\n";
    BKTree<DLD> dld("../data/testwordlist.txt");
    std::cout << "BKTree object created successfully." << "\n\n";

    // Print stats
    std::cout << "Printing statistics for the created tree to std::cerr ..." << "\n";
      std::pair<int,int> stats_dld = dld.get_stats();
      std::cout << "Number of nodes: " << stats_dld.first << "," << std::endl;
      std::cout << "Height of: " << stats_dld.second << ".\n" << std::endl;

    // Create dot file
    std::cout << "Creating a dot file \"testwordlist_dld.dot\" (make_dot(\"../data/testwordlist_dld.dot\")) ..." << "\n";
    dld.make_dot("../data/testwordlist_dld.dot");

    // Search tree
    std::cout << "\nThe BK tree will now be searched for various input words "
              << "and tolerance values d (find()). " << "\n";
    std::cout << "1) A word that is already in the tree and thus can be matched: kork" << "\n";
    std::cout << "(returns kork for all d=0)" << "\n";
      std::cout << ">>> " << dld.find("kork",0)[0] << std::endl;

    std::cout << "2) A word that is not in the tree: krok" << "\n";
    std::cout << "d = 1 returns kork and kook" << "\n";
      std::cout << ">>> " << dld.find("krok",1)[0] << ", " << dld.find("krok",1)[1] << std::endl << std::endl;
    
  // End
  std::cout << "This is the end of the demonstration." << "\n";
  std::cout << "The BKTree object will now be destroyed. See ../doc for further documentation.\n" << std::endl;
}
