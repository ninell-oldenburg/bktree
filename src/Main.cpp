// Author: Ninell Oldenburg
// Matrikelnummer: 792821
// Compiler: GCC g++ --version 4.2.1
// Operating System: MacOS Mojave --version 10.14.6
//
// Main.cpp
// C-file for Starting program and informing the user


#include <iostream>
#include <sstream>
#include "Computation.cpp"

int main(int argc, char **argv) {
    
    // Inform about correct usage
    if (argc != 2) {
        std::cerr << "Usage: PROGRAMNAME FILENAME" << std::endl;
        exit(1);
    }
    
    std::cout << std::endl << "Welcome to the Burkhard-Keller-Tree Approximate String Matching Program!\n" << std::endl;
    std::cout << "FUNCTIONS:" << std::endl;
    std::cout << "1. Building a Burkhard-Keller-Search-Tree out of a text file in user-chosen string metric:" << std::endl;
    std::cout << "\t For Longest Common Subsequence type \"lcs\"" << std::endl;
    std::cout << "\t For Damerau-Levenshtein-Distance type \"dlev\"" << std::endl;
    std::cout << "\t Default case: the Levenshtein-Distance." << std::endl;
    std::cout << "For more information consider: https://en.wikipedia.org/wiki/String_metric" << std::endl;
    std::cout << "2. Creating a GraphViz .dot file out of the BK-Tree." << std::endl;
    std::cout << "3. Interactive mode for Approximate String Search." << std::endl;
    std::cout << "4. To quit program press enter-key.\n" << std::endl;

    std::string filename = std::string(argv[1]);
    std::string metric;
    
    std::cout << "Which string metric do you want to use?" << std::endl;
    std::getline(std::cin, metric);
        
    // Create BK-Trees depending on user-chosen string metric
    // Execute user input afterwards
    if (metric == "lcs") {
        BKTree<LCS>tree (filename);
        compute(tree,filename);
        std::cout << "Quiting program..." << std::endl;
        return 0;
    }
    else if (metric == "dlev" ) {
        BKTree<DLD>tree (filename);
        compute(tree,filename);
        std::cout << "Quiting program..." << std::endl;
        return 0;
    }
    else {
        BKTree<Lev> tree(filename);
        compute(tree,filename);
        std::cout << "Quiting program..." << std::endl;
        return 0;
    }
    
    return 0;
    getchar();
}
    

