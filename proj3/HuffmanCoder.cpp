/*
 *  main.cpp
 *  Kasey Afshani
 *  11/5/23
 *
 *  CS 15 Proj 3 ZAP! 
 *
 *  Defines the behavior for the HuffmanCoder class based on if the user wants
    to "zap" or "unzap". This file includes the implementation of the 
    HuffmanCoder class. 
 *
 */
#include <iostream>
#include <vector>
#include <sstream> 
#include <stdexcept> 
#include <cstdio>
#include <fstream>
#include <utility>
#include <stdio.h>
#include <string.h>

#include "HuffmanCoder.h"
#include "HuffmanTreeNode.h"
#include "BinaryIO.h"

using namespace std;

/*
 * name:      encoder
 * purpose:   call functions to encode a given input file and save the encoding
              to an output file
 * arguments: input and output files
 * returns:   none
 * effects:   encodes a text and directs encoding to an output file
 */
void HuffmanCoder::encoder(const std::string &inputFile, 
                           const std::string &outputFile) {

    ifstream input; 
    ofstream output; 

    open_or_die(input, inputFile);
    open_or_die(output, outputFile);

    HuffmanTreeNode *node = nullptr; 
    
    count_freqs(input);
    if (not checker(inputFile)) { 
        output << inputFile << " is empty and cannot be compressed.\n";
        input.close();
        output.close();
        return; 
    }

    input.close();
    open_or_die(input, inputFile);
    node = build_tree();
    std::string binary = encode_text(input);
    std::string serialized = serialize_tree(node);
    conversion(outputFile, binary, serialized);

    input.close();
    output.close();
    recycle_memory(node);
}


//  /*
//  * name:      decoder
//  * purpose:   decode a binary text into english letters
//  * arguments: input and output files
//  * returns:   none
//  * effects:   decodes a binary text and stores result in output file
//  */
void HuffmanCoder::decoder(const std::string &inputFile, 
                           const std::string &outputFile) { 

    ifstream input; 
    ofstream output; 

    open_or_die(input, inputFile);
    open_or_die(output, outputFile);

    BinaryIO reading;
    HuffmanTreeNode *node;

    std::pair <std::string, std::string> info;
    info = reading.readFile(inputFile);
    node = deserialize_tree(info.first); 

    if (not same_char(info.second, node)) { 
        std::string message = find_message(info.second, node);
        output << message; 
    } else { 
        output << returning; 
    }

    input.close();
    output.close();
    recycle_memory(node);
}

/*
 * name:      open_or_die
 * purpose:   open the provided input file 
 * arguments: instream pointer and the filename 
 * returns:   none
 * effects:   opens a file or exits if the file cannot be opened
 */
template <typename streamtype>
void HuffmanCoder::open_or_die(streamtype &input, std::string filename) { 
    input.open(filename); 

    // make sure the file was created properly 
    if (not input.is_open()) { 
        cerr << "Unable to open file " << filename << endl; 
        exit(EXIT_FAILURE); 
    }
}


 /*
 * name:      same_char
 * purpose:   check to see if file contains only one char (can be multiple
              instances)
 * arguments: binary code of our file and the root of our tree
 * returns:   bool about whether or not the chars in the file are all the same
 * effects:   updates a string with the root's value as many times as the length
              of the binary code 
 */
bool HuffmanCoder::same_char(std::string binary, HuffmanTreeNode *root) { 

    for (int i = 0; i < (int)binary.length(); i++) { 
        if (binary[i] == '0') { 
            returning += root->get_val();
        } else { 
            return false; 
        }
    }
    return true; 
}


 /*
 * name:      find_message
 * purpose:   decode the binary code and get the chars corresponding to each 
              section of the binary
 * arguments: string of binary code, root of our Huffman tree
 * returns:   string of decoded message. throws an error if the binary code 
              doesn't match our tree. 
 * effects:   none. can throw an error (described above)
 */
std::string HuffmanCoder::find_message(std::string binary, 
                                       HuffmanTreeNode *root) { 

    std::string result; 
    HuffmanTreeNode *curr = root; 

    for (int i = 0; i < (int)binary.length(); i++) { 
        if (binary[i] == '1') { 
            curr = curr->get_right();
        } else if (binary[i] == '0') { 
            curr = curr->get_left();
        } 
        
        if (curr->isLeaf()) {
            result += curr->get_val(); 
            curr = root; 
        } 
        
        if (i == ((int)binary.length() - 1) and curr != root) { 
            throw runtime_error("Encoding did not match Huffman tree.");
        }
    }
    return result; 
}



 /*
 * name:      conversion
 * purpose:   convert our encoding into binary
 * arguments: our output file, string of binary, and string of the serialization
              of our tree
 * returns:   none
 * effects:   prints to terminal the length of the encoding. 
 */
void HuffmanCoder::conversion(const std::string &outputFile, std::string binary,
                            std::string serialized) { 

    BinaryIO convert;

    convert.writeFile(outputFile, serialized, binary);

    cout << "Success! Encoded given text using " << binary.length() << " bits." 
    << endl;
}

 /*
 * name:      checker
 * purpose:   check to see if we have been given an empty file to compress
 * arguments: our input file
 * returns:   false if the file is empty, true if it isn't
 * effects:   will print to cout if the file is empty
 */
bool HuffmanCoder::checker(const std::string &inputFile) { 

    int counter = 0; 
    for (int i = 0; i < 256; i++) { 
        if (freqs[i] == 0) { 
            counter++; 
        }
    }

    if (counter == 256) { 
        cout << inputFile << " is empty and cannot be compressed.\n";
        return false; 
    }
    return true; 
}


/*
 * name:      encode_text
 * purpose:   create the binary string for our encoded text
 * arguments: input stream
 * returns:   string of our binary code
 * effects:   none
 */
std::string HuffmanCoder::encode_text(std::istream &input) { 
    make_codes(my_pq.top(), "");
    std::string binary = ""; 
    char c; 

    while(input.get(c)) { 
         binary += codes[(int)c];
    }    
    return binary; 
}

/*
 * name:      count_freqs
 * purpose:   count the frequencies of each character in an input file
 * arguments: instream pointer
 * returns:   none
 * effects:   updates an array list with the frequencies of each char
*/
void HuffmanCoder::count_freqs(std::istream &text) { 
    char c; 

    while(text.get(c)) { 
        freqs[int(c)]++; 
    }
 }

/*
 * name:      build_tree
 * purpose:   build a Huffman Tree of the chars in our text
 * arguments: none
 * returns:   root of the Huffman Tree
 * effects:   creates a Huffman Tree and shrinks my_pq to a size of 1
*/
HuffmanTreeNode* HuffmanCoder::build_tree() { 
    build_queue();

    while(my_pq.size() > 1) { 
        HuffmanTreeNode *temp = my_pq.top();
        my_pq.pop();
        HuffmanTreeNode *second = my_pq.top();
        my_pq.pop();

        HuffmanTreeNode *together = new HuffmanTreeNode('\0', (temp->get_freq() 
                                             + second->get_freq()));
        together->set_left(temp);
        together->set_right(second);
        my_pq.push(together);
    }

    return my_pq.top();
}


/*
 * name:      build_queue
 * purpose:   build a priority queue based on frequencies of characters
 * arguments: none
 * returns:   none
 * effects:   creates a priority queue
*/
void HuffmanCoder::build_queue() { 
    for (int i = 0; i < 256; i++) { 
        if (freqs[i] != 0) { 
            HuffmanTreeNode *node = new HuffmanTreeNode(char(i), freqs[i]);
            my_pq.push(node); 
        }
    }
}

/*
 * name:      make_codes
 * purpose:   create binary codes for chars in Huffman Tree
 * arguments: the root of our tree and a string for the character's code
 * returns:   none
 * effects:   populates array with codes for chars in Huffman Tree
*/
void HuffmanCoder::make_codes(HuffmanTreeNode *root, string s) {

    //check to see if there's just one node in the tree 
    int tracker = 0; 
    for (int i = 0; i < 256; i++) { 
        if (freqs[i] != 0) { 
            tracker++;
        }
    }

    if (tracker == 1) {
        s = "0";
    }

    // otherwise recurse
    if (root->isLeaf()) { 
        codes[(int)root->get_val()] = s; 
        return;
    } else {
        make_codes(root->get_left(), (s + "0"));
        make_codes(root->get_right(), (s + "1"));
    }
    
}

/*
 * name:      serialize_tree
 * purpose:   find the proper code for each let
 * arguments: pointer to the root of the tree
 * returns:   serialization of the tree, including internal nodes
 * effects:   none
*/
std::string HuffmanCoder::serialize_tree(HuffmanTreeNode *root) { 
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
HuffmanTreeNode* HuffmanCoder::deserialize_tree(const std::string &s) { 
    istringstream ss(s);
    HuffmanTreeNode *node = deserialize_helper(ss);
    return node;
}

/*
 * name:      deserialize_helper
 * purpose:   help convert serialized string format into a tree
 * arguments: string of serialized tree, place in string 
 * returns:   root of the tree
 * effects:   builds a huffman tree 
*/
HuffmanTreeNode* HuffmanCoder::deserialize_helper(std::istringstream &ss) { 
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
 * effects:   recycles all the tree memory using post-order recursion
*/
void HuffmanCoder::recycle_memory(HuffmanTreeNode *root) { 
    if (root == nullptr) { 
        return;
    }
        recycle_memory(root->get_left());
        recycle_memory(root->get_right());
        delete root;
}