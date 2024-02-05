/*
 *  HashTable.cpp
 *  Kasey Afshani and Hank Sun
 *  12/4/23
 *
 *  CS 15 Proj 4 Gerp! 
 *
 *  Defines behavior for gerp based on the input provided by the client. 
 *  This file holds all implementations of the HashTable.h class.  
 */


#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <set>
#include <stdexcept> 
#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "HashTable.h"

using namespace std;
    

/*
 * name:      HashTable
 * purpose:   initialize elements for our HashTable
 * arguments: none
 * returns:   none
 * effects:   initializes hash table 
 */
HashTable::HashTable() { 
    size = 0; 
    capacity = 100000;
    our_hash = new std::list<KeyValue>[capacity];
    for(int i = 0; i < capacity; i++) {
        our_hash[i].resize(0);
    }
}

/*
 * name:      HashTable destructor
 * purpose:   delete elements for our HashTable
 * arguments: none
 * returns:   none
 * effects:   frees memory blocks 
 */
HashTable::~HashTable() { 
    delete [] our_hash; 
}


/*
 * name:      expand
 * purpose:   increase capacity 
 * arguments: none
 * returns:   none
 * effects:   creates a new array on the heap and deep copies the data from 
              the old array onto this new one that has more capacity 
 */
void HashTable::expand() { 

    // dynamically allocate new space on the heap 
    std::list<KeyValue> *new_hash = 
                                new std::list<KeyValue>[2 * capacity + 2];

    capacity *=2; 
    capacity +=2; 
    //  deep copy the info from the old array onto the new array 
    for(int  i = 0; i < capacity; i++) { 
        for(std::list<KeyValue>::iterator it = our_hash[i].begin(); 
            it != our_hash[i].end(); ++it) {
            hash_it_out(*it, new_hash);
        }
    }
    
    // recycle the old array 
    delete [] our_hash; 

    // repopulate the private member function with the new info 
    our_hash = new_hash;
}

/*
 * name:      query
 * purpose:   call correct functions based on commands given by users
 * arguments: command from user
 * returns:   none
 * effects:   calls function to find the path to the given command word
 */
void HashTable::query(std::string filename, std::ofstream &output) { 
    cout << "Query? "; 
    string command = "";
    string word = "";
    FSTree new_tree(filename);
    DirNode *root = new_tree.getRoot();
    int num_files = -1;
    finding(root, filename, num_files);
    while (cin >> command) {
        if(command == "@i" or command == "@insensitive") { 
            cin >> word; 
            find_insensitive(word, output);

        } else if (command == "@q" or command == "@quit") { 
            output.close();
            return; 

        } else if (command == "@f") { 
            cin >> word; 
            output.close();
            open_or_exit(output, word);

        } else { 
            find_sensitive(command, output);
        }
        cout << "Query? "; 
    }
}


/*
 * name:      test_duplicate
 * purpose:   check to see if we've already dealt with a word on the same line
 * arguments: the word we are looking for and its index in the hash table
 * returns:   true if it has already been dealt with, false if not
 * effects:   none
 */
bool HashTable::test_duplicate(KeyValue element, int index) { 

      for(std::list<KeyValue>::iterator it = our_hash[index].begin(); 
        it != our_hash[index].end(); ++it) {
            if((element.file_index[0] == it->file_index.back()) and 
            (element.key == it->key) and 
            (element.line_num[0] == it->line_num.back())) { 
                return true; 
            }
    }
    return false;
}

/*
 * name:      find_sensitive
 * purpose:   find the information for the line associated with the given word,
              exactly how it has been given to us
 * arguments: the word we are looking for
 * returns:   string with the path, line number, and line info from the command
              word's original file 
 * effects:   none
 */
void HashTable::find_sensitive(std::string command, std::ofstream &output) {
    command = stripNonAlphaNum(command);
    string new_command = make_lowercase(command);
    int index = hash<string>{}(new_command) % capacity;
    string result = ""; 

    for(std::list<KeyValue>::iterator it = our_hash[index].begin(); 
             it != our_hash[index].end(); ++it) {
        if(command == it->key) {
            for(int i = 0; i < int(it->file_index.size()); i++) {
                result += file_paths[it->file_index[i]] + ":" + 
                to_string(it->line_num[i]) + ": " + 
                line_info[it->file_index[i]][it->line_num
                [i] - 1] + "\n";
            }
        }
    }
     if(result == "") {
        result = stripNonAlphaNum(command) + 
        " Not Found. Try with @insensitive or @i.\n";    
    }
    output << result; 
}

/*
 * name:      make_lowercase
 * purpose:   convert a word into all lowercase chars
 * arguments: the word we are converting
 * returns:   all-lowercase string
 * effects:   none
 */
std::string HashTable::make_lowercase(string word) { 
    string new_word = "";
    for(int i = 0; i < (int)word.length(); i++) {
        char c = tolower(word[i]);
        new_word += c;
    }
    return new_word; 
}

/*
 * name:      find_insensitive
 * purpose:   find the information for the line associated with the given word
 * arguments: the word we are looking for
 * returns:   string with the path, line number, and line info from the command
              word's original file 
 * effects:   none
 */
void HashTable::find_insensitive(string command, std::ofstream &output) { 
    command = stripNonAlphaNum(command);
    string new_command = make_lowercase(command);

    int index = hash<string>{}(new_command) % capacity;
    string result = "";
    set <string> our_set;

    for(std::list<KeyValue>::iterator it = our_hash[index].begin(); 
        it != our_hash[index].end(); ++it) {
        string new_key = make_lowercase(it->key);
        
        if(new_command == new_key) {
            for(int i = 0; i < int(it->file_index.size()); i++) {
                our_set.insert(file_paths[it->file_index[i]] + ":" + 
                to_string(it->line_num[i]) +  ": "
                + line_info[it->file_index[i]][it->line_num[i] - 1] + "\n");
            }
        }
    }

    if(our_set.empty()) {
        output << stripNonAlphaNum(command) + " Not Found.\n";
    }
    for(set <string> ::iterator it = our_set.begin(); 
        it != our_set.end(); ++it) {
        output << *it;
    }
}

/*
 * name:      chained
 * purpose:   chain together words that map to the same bucket in the hash
 * arguments: line number of word in file, word we are hashing, name of file we
              are in 
 * returns:   none
 * effects:   chains words in our hash bucket in a linked list 
 */
void HashTable::chained(KeyValue element, int index, list<KeyValue> *a_hash) {
    bool found = false;
    for(std::list<KeyValue>::iterator it = our_hash[index].begin(); 
             it != our_hash[index].end(); ++it) {
        if(it->key == element.key) {
            it->file_index.push_back(element.file_index[0]);
            it->line_num.push_back(element.line_num[0]);
            found = true;
        }
    }
    if(not found) { 
        our_hash[index].push_back(element);
    }
}

/*
 * name:      hash_it_out
 * purpose:   map our element to the correct index in the hash 
 * arguments: element we want to hash out 
 * returns:   none
 * effects:   stores element from files in a hash 
 */
void HashTable::hash_it_out(KeyValue element, list<KeyValue> *a_hash) { 
    
     if(size == capacity) {
        expand();
    }
    
    string new_key = make_lowercase(element.key);
    int index = hash<string>{}(new_key) % capacity;
    

    if(our_hash[index].empty()) {
        our_hash[index].push_back(element);
        size++;
    } else  {
        if(test_duplicate(element, index)) {
            return;
        }    
        chained(element, index, our_hash);
    }
}

/*
 * name:      build_element
 * purpose:   build our hash that will store words from our files
 * arguments: root of our file tree 
 * returns:   none
 * effects:   stores words from files in a hash 
 */
void HashTable::build_element(string filename, string path, int &num_files) {
    ifstream infile;
    open_or_exit(infile, path + "/" + filename);
    //store the path in file_paths
    file_paths.push_back(path + "/" + filename);
    std::vector<std::string> new_vector;
    line_info.push_back(new_vector);
    //update file index
    num_files++;
    string line = "";
    int line_num = 0;
    while(getline(infile, line)) {
        line_num++;
        line_info[num_files].push_back(line);
        stringstream ss; 
        ss.str(line);
        //store the line itself at the correct line index
        string word;
        while(ss >> word) {
            string stripped_word = stripNonAlphaNum(word);
            if(stripped_word.length() <= 0) {
                continue;
            }
            KeyValue new_kv;
            new_kv.key = stripped_word;
            new_kv.file_index.push_back(num_files);
            new_kv.line_num.push_back(line_num); 
            // passing in private member variable for modularity       
            hash_it_out(new_kv, our_hash);
        }
    }
    infile.close();
}


/*
 * name:      stripNonAlphaNum
 * purpose:   get rid of non-alpha numerical characters on the ends of string
 * arguments: string
 * returns:   shortened string without the non-alpha numerical chars
 * effects:   none
 */
string HashTable::stripNonAlphaNum(string input) {
    bool found_string = false;
    while (not found_string) { 
        if((input[0] > 64 and input[0] < 91) or 
            (input[0] > 96 and input[0] < 123) or 
            (input[0] > 47 and input[0] < 58)) {
            found_string = true;
        } else if(input.length() == 0) {
            input = "";
            found_string = true; 
        } else { 
            input = input.substr(1, input.length() - 1);
        }
    }
    found_string = false; 
    while  (not found_string and input.length() != 0) { 
        if((input[input.length() - 1] > 64 and input[input.length() - 1] < 91) 
            or (input[input.length() - 1] > 96 and 
            input[input.length() - 1] < 123) or (input[input.length() - 1] > 47 
            and input[input.length() - 1] < 58)) {
                found_string = true;
        } else if(input.length() == 0) {
            input = "";
            found_string = true; 
        } else {
            input = input.substr(0, input.length() - 1);
        }
    }
    return input; 
}

/*
 * name:      finding
 * purpose:   traverse through the file tree and index the files
 * arguments: the root of the FSTree and the string of the path
 * returns:   none
 * effects:   none
 */
void HashTable::finding(DirNode *root, std::string passing, int &num_files) { 
    for(int i = 0; i < root->numSubDirs(); i++) { 
        finding(root->getSubDir(i), passing + "/" + 
                root->getSubDir(i)->getName(), num_files);
    }
    for(int j = 0; j < root->numFiles(); j++) { 
        build_element(root->getFile(j), passing, num_files);
    }
}

/*
 * name:      open_or_exit
 * purpose:   check to see if our files opened properly
 * arguments: filstream and filename 
 * returns:   none
 * effects:   opens our file
 */

template <typename streamtype>
void HashTable::open_or_exit(streamtype &stream, std::string file_name) {
    stream.open(file_name);
    if(not stream.is_open()) {
        std::cerr << "Error: could not open file " << file_name << std::endl;
        exit(EXIT_FAILURE);
    }
}

//This function is called during the testing phase to check that the info from
//every file that is indexed to check that we are indexing properly
// void Ha shTable::test_output() {
//     for(int i = 0; i < capacity; i++) { 
//         //  cerr << "our hash size" << our_hash[i].size() << endl;
//         for(std::list<KeyValue>::iterator it = our_hash[i].begin(); 
//             it != our_hash[i].end(); ++it) {
//             cerr < < "key is " << it->key << endl;
//             // for(int k = 0; k < (int)it->file_index.size(); k++) {
//             //     cerr << "file index is " << it->file_index[k];
//             //     cerr << "line number is " << it->line_num[k];
//             // }
//         }
//     }
 //     for(int i = 0; i < (int)file_paths.size(); i++) {
//         cerr << "file paths is: " << file_paths[i] << endl;
//     }
 //     for(int  n = 0; n < (int)line_info.size(); n++) {
//         for(int u = 0; u < (int)line_info[n].size(); u++) {
//             cerr << "line info is: " << line_info[n][u] << endl;
//         }
//     }
// }