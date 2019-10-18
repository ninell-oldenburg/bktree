// Author: Ninell Oldenburg
// Matrikelnummer: 792821
// Compiler: GCC g++ --version 4.2.1
// Operating System: MacOS Mojave --version 10.14.6
//
// Ed_Dis.hpp
// Header file with function objects for computation of different string matrices

#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
#include <iterator>
#include <sstream>
#include <vector>
#include <math.h>

typedef std::bitset<16> ch;
typedef std::vector<ch> Word;

// Every algorithm has as input to strings and returns an int number according
// to algorithm which represents the edit distance between strings

// Levenshtein distance according to:
// https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C++
class Lev {
public:
    int operator()(std::vector<char> first, std::vector<char> second)
    {
        // If strings are equal: edit distance is 0
        if (first == second) { return 0; }
            
        std::size_t first_len = first.size();
        std::size_t second_len = second.size();
        
        // Create matrix accroding to length of strings plus 1 index to initialize
        // beginning of matrix with number of index of different strings
        std::vector<std::vector<unsigned int> > matrix(first_len+1, std::vector<unsigned int>(second_len+1));
        
        matrix[0][0] = 0;
        for (int i=1; i<=first_len; i++) matrix[i][0] = i;
        for (int i=1; i<=second_len; i++) matrix[0][i] = i;
        
        // Fill matrix with edit distances
        // Valid operations: delete, insert, substitute
        for (int i=1; i<=first_len; i++) {
            for (int j=1; j<=second_len; j++) {
                matrix[i][j] = std::min(std::min(matrix[i-1][j]+1, matrix[i][j-1]+1), matrix[i-1][j-1]+ (first[i-1] == second[j-1] ? 0 : 1));
            }
        }
        // Bottom right most value of matrix is edit distance of both strings
        // if we imagine to have started in the top left corner
        return matrix[first_len][second_len];
    }
};

// Longest Common Subsequence
// According to: https://en.wikipedia.org/wiki/Longest_common_subsequence_problem
class LCS {
public:
        int operator()(std::vector<char> first, std::vector<char> second) {
        std::size_t first_len = first.size();
        std::size_t second_len = second.size();
                
        // Create matrix accroding to length of strings plus 1 index to initialize
        // beginning of matrix with 0's
        std::vector<std::vector<unsigned int> > matrix(first_len+1, std::vector<unsigned int>(second_len+1));
        
        matrix[0][0] = 0;
        for (int i=1; i<=first_len; i++) matrix[i][0] = 0;
        for (int i=1; i<=second_len; i++) matrix[0][i] = 0;
            
        // Iterate over both strings
        for (int i=1; i<=first_len; i++) {
            for (int j=1; j<=second_len; j++) {
                // If strings are equal: increse preceding value by one
                if (first[i-1] == second[j-1]) {
                    matrix[i][j] = matrix[i-1][j-1]+1;
                }
                // If not: keep preceding value
                else {
                    matrix[i][j] = std::max(matrix[i][j-1], matrix[i-1][j]);
                }
            }
        }
        // Bottom right most value of matrix is number of LCS
        // if we imagine to have started in the top left corner
        return matrix[first_len][second_len];
    }
};

// Damerau-Levenshtein-Distance
// According to: https://en.wikipedia.org/wiki/Damerau-Levenshtein_distance
class DLD {
public:
    int operator()(std::vector<char> first, std::vector<char> second)
    {
        // Works equally to Levenshtein-Distance (above)
        // Only difference: see next comment
        if (first == second) { return 0; }
            
        std::size_t first_len = first.size();
        std::size_t second_len = second.size();
            
        std::vector<std::vector<unsigned int> > matrix(first_len+1, std::vector<unsigned int>(second_len+1));
            
        matrix[0][0] = 0;
        for (int i=1; i<=first_len; i++) matrix[i][0] = i;
        for (int i=1; i<=second_len; i++) matrix[0][i] = i;
            
        // Valid operations: delete, insert, substitute & transition
        for (int i=1; i<=first_len; i++) {
            for (int j=1; j<=second_len; j++) {
                matrix[i][j] = std::min(std::min(matrix[i-1][j]+1, matrix[i][j-1]+1), matrix[i-1][j-1]+ (first[i-1] == second[j-1] ? 0 : 1));
                // If transition was detected: save it as valid operation
                if (i > 1 && j > 1 && first[i-1] == second[j-2] && first[i-2] == second[j-1]) {
                    matrix[i][j] = std::min(matrix[i][j], matrix[i-2][j-2]+(first[i-1] == second[j-1] ? 0 : 1));
                }
            }
        }
        return matrix[first_len][second_len];
    }
};
