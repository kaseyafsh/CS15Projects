/*
 *  HuffmanCoder.h
 *  Kasey Afshani
 *  11/13/23
 *
 *  CS 15 Proj 3 ZAP! 
 *
 *  HuffmanCoder is a class that manipulates HuffmanTreeNodes. It will call on
    the HuffmanTreeNode class to build Huffman trees, encode, and decode given
    files. 
 *
 */
#ifndef _HUFFMAN_CODER
#define _HUFFMAN_CODER

#include <string>
#include <istream>
#include <vector>
#include <fstream>
#include <queue> 
#include <utility>

#include "HuffmanTreeNode.h"

class HuffmanCoder {

   public:

    void encoder(const std::string &inputFile, const std::string &outputFile);
    void decoder(const std::string &inputFile, const std::string &outputFile);


    private: 

    template <typename streamtype>
    void open_or_die(streamtype &input, std::string filename);

    std::string serialize_tree(HuffmanTreeNode *root);
    HuffmanTreeNode *deserialize_tree(const std::string &s);
    HuffmanTreeNode *deserialize_helper(std::istringstream &ss);


    void count_freqs(std::istream &text);
    int freqs[256] = {0}; 
    std::string codes[256] = {""};

    void build_queue();
    HuffmanTreeNode *build_tree();

    void make_codes(HuffmanTreeNode *root, std::string s);

    void recycle_memory(HuffmanTreeNode *root);

    std::string encode_text(std::istream &input);
    std::string find_message(std::string binary, HuffmanTreeNode *root);
    bool same_char(std::string binary, HuffmanTreeNode *root);
    void conversion(const std::string &outputFile, std::string binary, 
                    std::string serialized);

    bool checker(const std::string &inputFile); 
    
    std::string returning = ""; 

    std::priority_queue<HuffmanTreeNode*, std::vector <HuffmanTreeNode*>, 
                        NodeComparator> my_pq;

};

#endif