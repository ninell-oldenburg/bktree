// Author: Ninell Oldenburg
// Matrikelnummer: 792821
// Compiler: GCC g++ --version 4.2.1
// Operating System: MacOS Mojave --version 10.14.6
//
// BKTree.hpp
// Header file for creating a Burkhard-Keller-Tree out of a text file
// and finding strings for Approximate String Search


#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <math.h>
#include "../include/Ed_Dis.hpp"

typedef std::bitset<16> ch;
typedef std::vector<ch> Word;

// Class for creating a node
template <typename T>
class Node {

// Member variables: name, edit-distance function, children nodes, number of chlidren
protected:
    Word m_name;
    T m_func;
    std::vector<Node<T>* > m_children;
    unsigned int m_num_children;
    
// Constructors
public:
    Node<T>(){}
    
    Node<T>(const Word &word)  : m_name(word), m_children(std::vector<Node<T>* >()), m_num_children(0) { }
    
    ~Node<T>() {}
    
    // Getter
    Word get_name() const {
        return m_name;
    }
    
    std::vector<Node<T>* > get_children() const {
        return m_children;
    }
    
    Word get_child_at(int index) const {
        return m_children[index]->get_name();
    }
    
    unsigned int get_num_children() const {
        return m_num_children;
    } // Getter
    
    // Function to compute the edit distance with given edit-distance function through template
    int compute_dis(std::vector<char> first, std::vector<char> second, T edit_dist) {
            return edit_dist(first,second);
    }
    
    // Adding child by computing edit distance to the node to be inserted and inserting it
    // in children vector at index of computed edit distance
    unsigned int add_child(const Word& insert_node) {
        int dis = compute_dis(make_char_vec(m_name),make_char_vec(insert_node),m_func);
        
        // only valid for positive edit distances; if (dis == 0) word already exists
        if (dis>0) {
            // make sure that children vector is big enough; if not: resize and insert new node
            // for every node to be inserted: increse number-of-children-counter
            if (m_children.size() > dis) {
                // vector index is still free: insert new node here;
                if (m_children.at(dis)==nullptr) {
                    Node *new_child = new Node<T>(insert_node);
                    m_children.at(dis) = new_child;
                    incr_num_children(1);
                }
                // else: continue searching recursivly for the next free position
                else {
                    incr_num_children(1);
                    return (m_children.at(dis)->add_child(insert_node) + 1);
                }
            }
            else {
                m_children.resize(dis+1);
                Node *new_child = new Node(insert_node);
                m_children.at(dis) = new_child;
                incr_num_children(1);
            }
        }
        // return 1 that add_Node-function of BKTRee<T>() can check the max height of each subtree
        return 1;
    } // add_child()
    
    // Setter
    void incr_num_children(unsigned int number) {
        m_num_children += number;
    }
    
    // Helper-functions due to binary saved strings
    std::string make_string(const Word &word) {
        std::string result;
        for (int i=0; i!=word.size(); i++) {
            result += char (word.at(i).to_ulong());
        }
        return result;
    }
    
    std::vector<char> make_char_vec(const Word &word) {
        std::vector<char> result;
        for (int i=0; i!=word.size(); i++) {
            result.push_back(char (word.at(i).to_ulong()));
        }
        return result;
    } // Helper
    
    
    // Function to find a child recursivly with search string and given threshold
    // (both value are user input)
    std::vector<Word> find_child(const Word &word, int threshold) {
        // compute edit distance and save, in case of within-threshold-finding, in result vector
        int dis = compute_dis(make_char_vec(get_name()),make_char_vec(word), m_func);
        std::vector<Word> results;
        
        // LCS works the other way round: threshold is minimum of which strings in given
        // edit distance should be accepted
        if (typeid(T) == typeid(LCS)) {
            if (dis >= threshold) {
                results.push_back(get_name());
            }
        }
        // In case of within-threshold-finding, append to result vector
        else {
            if (dis <= threshold) {
                results.push_back(get_name());
            }
        }
        
        // Define the range of children to be searched
        int min = (dis-threshold > 0 ? dis-threshold : (dis-threshold) * (-1));
        int max = dis+threshold;
                    
        // Recursivly find children in that range
        for (int i=min; i<=max; i++) {
            if (get_children().size() > i) {
                if (get_children().at(i) != nullptr) {
                    // And merge findings with this result vector
                    std::vector<Word> subtotal = get_children().at(i)->find_child(word, threshold);
                    results.insert(results.end(), subtotal.begin(), subtotal.end());
                }
            }
        }
        // Return result vector
        return results;
    }
};

template <typename T>
class BKTree {
private:
    // Member variables: edit distance function, root node, height of the tree
    T m_func;
    class Node<T> *m_root;
    unsigned int m_height;
    
public:
    // Constructors
    BKTree<T>() {
        m_root = 0;
        m_height = 0;
    }
    
    // If file was given by user: read the file by reading every line and ignoring whitespaces
    BKTree<T>(const std::string &file) {
        std::clog << std::endl << "Reading file \"" << file << "\" ... \n" << std::endl;
        
        m_root = nullptr;
        m_height = 0;
            
        std::string ignore = "\n\r\v\t\f ";
        std::ifstream iffile;
        iffile.open(file);
        std::string in_word;
            
        // Compute the time the file needs to be read by the constructor
        std::chrono::time_point<std::chrono::high_resolution_clock> start;
        start = std::chrono::high_resolution_clock::now();
        
        if (iffile.is_open()) {
            while (iffile.good()) {
                std::getline(iffile,in_word);
                if (!in_word.empty() && ignore.find(in_word) == std::string::npos) {
                    // save all the strings in binary format
                    add_Node(string_to_bit(in_word.c_str()));
                }
            }
        iffile.close();
        // Print time that file needed to be read
        std::chrono::time_point<std::chrono::high_resolution_clock> end;
        end = std::chrono::high_resolution_clock::now();

        int elapsed_mill_secs = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
            
        std::cout << "File read successfully in " << elapsed_mill_secs << " milliseconds.\n" << std::endl;
        }
        // Inform user if program is not able to open the file
        else {
            std::cerr << "Unable to open file \"" << file << "\"" << std::endl;
        }
    }
    
    // Destructor
    ~BKTree<T>() {
    }
    
    // Getter
    unsigned int get_height() const {
        return m_height;
    }
    
    std::pair<int,int> get_stats() {
        std::pair <int,int> stats (m_root->get_num_children(),get_height());
        return stats;
    } // Getter
    
    // Setter
    void set_height(unsigned int new_height) {
        m_height = new_height;
    }
    
    // Helper-functions due to binary format of strings to be saved
    Word string_to_bit(const std::string &str) {
        Word bin_word;
        for (int i=0; i<=str.length()-1; i++) {
            char c = str[i];
            if (!(isspace(c))) {
                ch bin_letter(c);
                bin_word.push_back(bin_letter);
            }
        }
        return bin_word;
    }
    
    std::string make_string(const Word &word) {
        std::string result;
        for (int i=0; i!=word.size(); i++) {
            result += char (word.at(i).to_ulong());
        }
        return result;
    }
    
    std::vector<char> make_char_vec(const std::string &word) {
        std::vector<char> result;
        for (int i=0; i<=word.size(); i++) {
            result.push_back(char (word.at(i)));
        }
        return result;
    } // Helper
    
    
    // Function for adding nodes
    void add_Node(const Word &insert_node) {
        // if there is no root: make word be the root
        if (m_root==nullptr) {
            m_root = new Node<T>(insert_node);
            set_height(1);
        }
        // insert all the other words and save maximum high of tree
        else {
            unsigned int new_height = m_root->add_child(insert_node)+1;
            if (new_height > get_height()) {
                set_height(new_height);
            }
        }
    }
    
    // Function to write dot-file
    void make_dot(std::string dot_name) {
        // Inform user and start writing head of file, write recursily the actual content,
        // and write tail of dot file afterwards.
        std::clog << "Creating dot file... \n" << std::endl;
        std::ofstream offile(dot_name.c_str());
        if (offile) {
            offile << "digraph BKTree { \n";
            offile << write_dot_recursive(m_root);
            offile << "}\n";
            offile.close();
            std::clog << "Dot file created succesfully and saved under \"" << dot_name << "\"" << std::endl;
        }
        // Also inform user if something didn't go well
        else {
            std::cerr << "Unable to write dot file. \n" << std::endl;
            return;
        }
    }
    
    // Iterate recursivly over all the nodes and remeber all the transitions;
    // write everything to a string
    std::string write_dot_recursive(class Node<T> *curr_node) {
        if (curr_node == nullptr) {
            return  "\"""\" [shape=circle]\n";
        }
        std::string dot_out;
        for (int i=0; i!=curr_node->get_children().size(); i++) {
            if (curr_node->get_children().at(i) != nullptr) {
                dot_out += "\"" + make_string(curr_node->get_name()) + "\" -> \"" + make_string(curr_node->get_child_at(i)) + "\" [label= " + std::to_string(i) + "]\n";
                dot_out += write_dot_recursive(curr_node->get_children().at(i));
           }
        }
        
        // Decide if child is final leaf or not
        if (curr_node->get_children().size() != 0) {
            dot_out += "\"" + make_string(curr_node->get_name()) + "\" [shape=circle]\n";
        }
        else {
            dot_out += "\"" + make_string(curr_node->get_name()) + "\"" + " [shape=doublecircle]\n";
        }
        // return the string
        return dot_out;
    } // writing dot file
    
    
    // Function to find children by user given string and thresold
    std::vector<std::string> find(const std::string &str, int threshold) {
        // Save findings in result vector and convert string to the binary version
        std::vector<std::string> result;
        Word word = string_to_bit(str);
        
        // Start at root to find candidates
        std::vector<Word> subtotal = m_root->find_child(word, threshold);
        // And append findings to the string-result vector to be returned
        if (subtotal.size() != 0) {
            for (int i=0; i<subtotal.size(); i++) {
                result.push_back(make_string(subtotal[i]));
            }
        }
        return result;
    } // Find children
};


