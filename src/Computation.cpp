// Author: Ninell Oldenburg
// Matrikelnummer: 792821
// Compiler: GCC g++ --version 4.2.1
// Operating System: MacOS Mojave --version 10.14.6
//
// Computation.cpp
// C-file for managing the user interaction with different function objects
// of the edit-distance-computation

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <math.h>
#include "../include/BKTree.hpp"
#include "../include/Ed_Dis.hpp"

// For Levenshtein-Distance
void compute(BKTree<Lev> bkt,const std::string& filename) {

    // Print statistics of the tree
    std::pair<int,int> stats = bkt.get_stats();
    std::cout << "Burkhard-Keller-Tree with Levenshtein metric created with: " << std::endl;
    std::cout << "Number of nodes: " << stats.first << "," << std::endl;
    std::cout << "Height of: " << stats.second << ".\n" << std::endl;

    // Make a dot file
    bkt.make_dot(filename.substr(0,filename.size()-4)+".dot");

    // Interactive mode
    std::cout << "\n = = = Interactive mode = = = " << "\n";
    std::string word;
    int d;

    while (true) {
        std::cout << "Enter word: " << std::endl;
        std::getline(std::cin, word);

    // Oppurtunity to quit program if input is empty
    if (word.empty()) {
        std::cerr << "Quit program? (y/n)"<< std::endl;
        std::string answer;
        std::getline(std::cin, answer);
        if (answer != "y" && answer != "Y" && answer != "yes") {
            continue;
        }
        return;
    }

    std::cout << "Enter edit distance:" << std::endl;
    std::cin >> d;

    // Don't accept non-integer-values
    if (std::cin.fail()) {
        std::cerr << "Input is not an integer. Try again." << std::endl;
        std::cin.clear();
        std::cin.ignore(__INT_MAX__,'\n');
        continue;
    }

    // If values are negative: make them positive
    if (d < 0) { d = d * -1; }

    // Inform the user that computation can take long when edit distance is high
    if (d > 4) {
        std::cout << "High value will take long time to process.\n"
                         << "Do you want to continue with value " << d << "? (y/n)" << std::endl;
        std::cin.ignore();
        std::string answer;
        std::getline(std::cin, answer);
        if (answer != "y" && answer != "Y" && answer != "yes") {
            continue;
        }
    }

    // Find candidates and print duration for findings
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    start = std::chrono::high_resolution_clock::now();

    std::vector<std::string> result = bkt.find(word,d);
    if (!(result.size() == 0)) {
        std::cout << std::endl << "Words within edit-distance " << d << ": \n";
        for (int i=0; i<=result.size()-1; i++) {
            std::cout << ">>> " << result[i] << std::endl;
        }
        
        std::chrono::time_point<std::chrono::high_resolution_clock> end;
        end = std::chrono::high_resolution_clock::now();

        int elapsed_mill_secs = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();

        std::cout << std::endl << result.size() << " strings found in " << elapsed_mill_secs << " milliseconds.\n" << std::endl;
    }
    // Inform user if no values have been found
    else {
            std::cerr << "No words found for input \"" << word << "\" within edit-distance of " << d << std::endl << std::endl;
    }
    std::cin.ignore();
    }
}

// For Longest-Common-Subsequence
void compute(BKTree<LCS> bkt,const std::string& filename) {

    // Print statistics of the tree
    std::pair<int,int> stats = bkt.get_stats();
    std::cout << "Burkhard-Keller-Tree with Longest Common Subsequence metric created with: " << std::endl;
    std::cout << "Number of nodes: " << stats.first << "," << std::endl;
    std::cout << "Height of: " << stats.second << ".\n" << std::endl;

    // Make a dot file
    bkt.make_dot(filename.substr(0,filename.size()-4)+".dot");

    // Interactive mode
    std::cout << "\n = = = Interactive mode = = = " << "\n";
    std::string word;
    int d;

    while (true) {
        std::cout << "Enter word: " << std::endl;
        std::getline(std::cin, word);

    // Oppurtunity to quit program if input is empty
    if (word.empty()) {
        std::cerr << "Quit program? (y/n)"<< std::endl;
        std::string answer;
        std::getline(std::cin, answer);
        if (answer != "y" && answer != "Y" && answer != "yes") {
            continue;
        }
        return;
    }

    std::cout << "Enter LCS: " << std::endl;
    std::cin >> d;

    // Don't accept non-integer-values
    if (std::cin.fail()) {
        std::cerr << "Input is not an integer. Try again." << std::endl;
        std::cin.clear();
        std::cin.ignore(__INT_MAX__,'\n');
        continue;
    }

    // If values are negative: make them positive
    if (d < 0) { d = d * -1; }

    // Inform the user that computation can take long when edit distance is high
    if (d > 4) {
        std::cout << "High value will take long time to process.\n"
                         << "Do you want to continue with value " << d << "? (y/n)" << std::endl;
        std::cin.ignore();
        std::string answer;
        std::getline(std::cin, answer);
        if (answer != "y" && answer != "Y" && answer != "yes") {
            continue;
        }
    }

    // Find candidates and print duration for findings
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    start = std::chrono::high_resolution_clock::now();

    std::vector<std::string> result = bkt.find(word,d);
    if (!(result.size() == 0)) {
        std::cout << std::endl << "Words within LCS " << d << ": \n";
        for (int i=0; i<=result.size()-1; i++) {
            std::cout << ">>> " << result[i] << std::endl;
        }
        
        std::chrono::time_point<std::chrono::high_resolution_clock> end;
        end = std::chrono::high_resolution_clock::now();

        int elapsed_mill_secs = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();

        std::cout << std::endl << result.size() << " strings found in " << elapsed_mill_secs << " milliseconds.\n" << std::endl;
    }
    // Inform user if no values have been found
    else {
            std::cerr << "No words found for input \"" << word << "\" within LCS of " << d << std::endl << std::endl;
    }
    std::cin.ignore();
    }
}

void compute(BKTree<DLD> bkt,const std::string& filename) {

    // Print statistics of the tree
    std::pair<int,int> stats = bkt.get_stats();
    std::cout << "Burkhard-Keller-Tree with Damerau-Levenshtein metric created with: " << std::endl;
    std::cout << "Number of nodes: " << stats.first << "," << std::endl;
    std::cout << "Height of: " << stats.second << ".\n" << std::endl;

    // Make a dot file
    bkt.make_dot(filename.substr(0,filename.size()-4)+".dot");

    // Interactive mode
    std::cout << "\n = = = Interactive mode = = = " << "\n";
    std::string word;
    int d;

    while (true) {
        std::cout << "Enter word: " << std::endl;
        std::getline(std::cin, word);

    // Oppurtunity to quit program if input is empty
    if (word.empty()) {
        std::cerr << "Quit program? (y/n)"<< std::endl;
        std::string answer;
        std::getline(std::cin, answer);
        if (answer != "y" && answer != "Y" && answer != "yes") {
            continue;
        }
        return;
    }

    std::cout << "Enter edit distance:" << std::endl;
    std::cin >> d;

    // Don't accept non-integer-values
    if (std::cin.fail()) {
        std::cerr << "Input is not an integer. Try again." << std::endl;
        std::cin.clear();
        std::cin.ignore(__INT_MAX__,'\n');
        continue;
    }

    // If values are negative: make them positive
    if (d < 0) { d = d * -1; }

    // Inform the user that computation can take long when edit distance is high
    if (d > 4) {
        std::cout << "High value will take long time to process.\n"
                         << "Do you want to continue with value " << d << "? (y/n)" << std::endl;
        std::cin.ignore();
        std::string answer;
        std::getline(std::cin, answer);
        if (answer != "y" && answer != "Y" && answer != "yes") {
            continue;
        }
    }

    // Find candidates and print duration for findings
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    start = std::chrono::high_resolution_clock::now();

    std::vector<std::string> result = bkt.find(word,d);
    if (!(result.size() == 0)) {
        std::cout << std::endl << "Words within edit-distance " << d << ": \n";
        for (int i=0; i<=result.size()-1; i++) {
            std::cout << ">>> " << result[i] << std::endl;
        }
        
        std::chrono::time_point<std::chrono::high_resolution_clock> end;
        end = std::chrono::high_resolution_clock::now();

        int elapsed_mill_secs = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();

        std::cout << std::endl << result.size() << " strings found in " << elapsed_mill_secs << " milliseconds.\n" << std::endl;
    }
    // Inform user if no values have been found
    else {
            std::cerr << "No words found for input \"" << word << "\" within edit-distance of " << d << std::endl << std::endl;
    }
    std::cin.ignore();
    }
}
