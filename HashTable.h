/*
 *  Hashtable.h
 *  Hank Sun, Kasey Afshani
 *  12/4/23
 *
 *  CS 15 Proj 4 Gerp
 *   
 *  This is the header file for our HashTable class. It holds a constructor
 *  that initializes the class and our array, a destructor that clears the 
 *  array on the heap, public functions that finds files in a tree and query 
 *  loop. Our KeyValue struct is declared here, as well as our hash table array
 *  the line_info 2D vector and file_paths vector. As well as all functions
 *  that allow the indexing of all files in a directory and functions that
 *  finds the line number of file index of each word, differing depending on if
 *  the search was made to be insensitive or sensitive
 *
 */

#ifndef _HASH_TABLE
#define _HASH_TABLE

#include <string>
#include <vector>
#include <list>
#include <set>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "FSTree.h"
#include "DirNode.h"



class HashTable { 

    public: 
        HashTable();
        ~HashTable(); 
        void query(std::string filename, std::ofstream &output);
        void finding(DirNode *root, std::string passing, int &num_files);
        template <typename streamtype>
        void open_or_exit(streamtype &stream, std::string file_name);

    private:

        struct KeyValue {
            std::string key; 
            std::vector <int> file_index; 
            std::vector <int> line_num; 
        };
         
        int capacity;
        int size;
        void expand();
        std::list<KeyValue> *our_hash;
        std::vector <std::string> file_paths;
        std::vector <std::vector<std::string>> line_info; 

        void hash_it_out(KeyValue element, std::list<KeyValue> *a_hash);
        void chained(KeyValue element, int index, 
                     std::list<KeyValue> *a_hash);
        void build_element(std::string filename, std::string path, 
                            int &num_files);
        std::string make_lowercase(std::string word);
        std::string stripNonAlphaNum(std::string input);
        void find_sensitive(std::string command, std::ofstream &output);
        void find_insensitive(std::string command, std::ofstream &output);
        bool test_duplicate(KeyValue element, int index);
        // void test_output();
       
        
        
};

#endif