/*
 *  phaseOne.cpp
 *  Kasey Afshani
 *  11/3/23
 *
 *  COMP 15 Project 3 ZAP!
 *
 *  This file includes the implementation for some of the fundamental functions
    of ZAP! These functions will later help with building Huffman Coding Trees,
    as they serialize, deserialize, and count the frequencies of characters
    for the tree. 
 *
 */

#include "phaseOne.h"
#include "HuffmanTreeNode.h"
#include <sstream> 
#include <iostream>
#include <stdexcept>
#include <fstream>

using namespace std; 

/*
 * name:      count_freqs
 * purpose:   count the frequencies of each character in an input file
 * arguments: instream pointer
 * returns:   none
 * effects:   creates an array list on the heap 
*/
void count_freqs(std::istream &text) { 

    int freqs[256] = {0}; 
    char c; 

    while(text.get(c)) { 
        freqs[int(c)]++; 
    }

    // check to see if counter is working 
    for(int i = 0; i < 256; i++) { 
        if(freqs[i] != 0) {
            cout << char(i) << ": " << freqs[i] << '\n'; 
        }
   }
 }

/*
 * name:      serialize_tree
 * purpose:   find the proper code for each let
 * arguments: pointer to the root of the tree
 * returns:   serialization of the tree, including internal nodes
 * effects:   none
*/
std::string serialize_tree(HuffmanTreeNode *root) { 
    if (root == nullptr) { 
        return ""; 
    } 
    if (root->isLeaf()) { 
         return "L" + string(1, root->get_val()); 
    } else { 
        return "I" +  serialize_tree(root->get_left())
                + serialize_tree(root->get_right());
    }
}

/*
 * name:      deserialize_tree
 * purpose:   wrapper function for deserialize_helper
 * arguments: string of serialized tree
 * returns:   root of the tree
 * effects:   none
*/
HuffmanTreeNode *deserialize_tree(const std::string &s) { 
    istringstream ss(s);
    return deserialize_helper(ss);
}

/*
 * name:      deserialize_helper
 * purpose:   help convert serialized string format into a tree
 * arguments: string of serialized tree, place in string 
 * returns:   root of the tree
 * effects:   builds a huffman tree 
*/
HuffmanTreeNode *deserialize_helper(std::istringstream &ss) { 
    HuffmanTreeNode *node = nullptr;
    char character;
    ss.get(character);

    if (character == 'L') { 
        ss.get(character);
        node = new HuffmanTreeNode(character, -1);
        return node; 
    }
    if (character == 'I') { 
        node = new HuffmanTreeNode('\0', -1);
        node->set_left(deserialize_helper(ss));
        node->set_right(deserialize_helper(ss));

    } 
    
    return node; 
}

/*
 * name:      recycle_memory
 * purpose:   recycle the tree memory
 * arguments: root of the tree
 * returns:   none
 * effects:   recycles all the tree memory
*/
void recycle_memory(HuffmanTreeNode *root) { 
    if (root == nullptr) { 
        return;
    }
        recycle_memory(root->get_left());
        recycle_memory(root->get_right());
        delete root;
}