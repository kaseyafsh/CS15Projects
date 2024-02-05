/*
 *  phaseOne.h
 *  Kasey Afshani
 *  11/3/23
 *
 *  COMP 15 Project 3 ZAP!
 *
 *  This file includes the definitions for some of the fundamental functions
    of ZAP! These functions will allow us to serialize and deserialiez our 
    trees to make it easier to decode them later on. 
 *
 */

#ifndef _PHASE_ONE_H
#define _PHASE_ONE_H

#include <istream>
#include <string>
#include <vector>
#include <fstream>

#include "HuffmanTreeNode.h"


void count_freqs(std::istream &text);
std::string serialize_tree(HuffmanTreeNode *root);
HuffmanTreeNode *deserialize_tree(const std::string &s);
HuffmanTreeNode *deserialize_helper(std::istringstream &ss);

void recycle_memory(HuffmanTreeNode *root);



#endif