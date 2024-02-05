/*
 *  unit_tests.h
 *  Kasey Afshani 
 *  11/5/23
 *
 *  CS 15 Project 3: ZAP! 
 *
 *  Use the unit testing framework to make sure everything in the code is 
    running properly, trying to test out edge cases and basics. 
 *
 */


#include "phaseOne.h"
#include "HuffmanCoder.h"
#include "ZapUtil.h"
#include <vector>
#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std; 

/*
 * name:      testing_serial
 * purpose:   test the serialization function
 * arguments: none
 * returns:   none
 * effects:   asserts serialize function works
 */
void testing_serial() { 
   char value = '\0';
   HuffmanTreeNode *anotherFig1Tree = makeFigure1Tree(value);

   std::string result = serialize_tree(anotherFig1Tree); 

   assert(result == "IIILaLbILeLfILcLd"); 
   recycle_memory(anotherFig1Tree);
}

/*
 * name:      testing_deserial
 * purpose:   test the deserialize function
 * arguments: none
 * returns:   none
 * effects:   asserts the deserialize function works
 */
 void testing_deserial() { 
   std::string testing = "IIILaLbILeLfILcLd";

   HuffmanTreeNode *node = deserialize_tree(testing);

   assert(node->get_val() == '\0');
   recycle_memory(node);
   
 }

/*
 * name:      testing_deserial_one
 * purpose:   test the deserialize function one a single node
 * arguments: none
 * returns:   none
 * effects:   asserts the deserialize function works on one node
 */
 void testing_deserial_one() { 
   std::string testing = "La"; 
   HuffmanTreeNode *node = deserialize_tree(testing);
   assert(node->get_val() == 'a');
   recycle_memory(node);

 }

 /*
 * name:      testing_serialize_deserial
 * purpose:   test the deserialize function on serialized figure 1 tree
 * arguments: none
 * returns:   none
 * effects:   asserts the deserialize function works with serialize
 */
void testing_serialize_deserialize() { 
   char value = '\0';
   HuffmanTreeNode *anotherFig1Tree = makeFigure1Tree(value);

   std::string testing = serialize_tree(anotherFig1Tree); 
   HuffmanTreeNode *node = deserialize_tree(testing);
   assert(node->get_val() == '\0');
   // printTree(node, '\0');
   assert(treeEquals(node, anotherFig1Tree, false, false));
   recycle_memory(node);
   recycle_memory(anotherFig1Tree);
}


 /*
 * name:      testing_deserialize_serialize
 * purpose:   test the deserialize function on my idea
 * arguments: none
 * returns:   none
 * effects:   asserts the deserialize function works
 */
void testing_deserialize_serialize() { 
   std::string testing = "IILbLnLa"; 
   HuffmanTreeNode *node = deserialize_tree(testing);

   std::string result = serialize_tree(node); 
   //printTree(node, '\0');

   assert(result == "IILbLnLa"); 
   recycle_memory(node);
}


/*
 * name:      testing_spaces
 * purpose:   test the deserialize function on my idea
 * arguments: none
 * returns:   none
 * effects:   asserts the deserialize function works
 */
void testing_spaces() { 
   std::string testing = "IIL LnLa"; 
   HuffmanTreeNode *node = deserialize_tree(testing);

   std::string result = serialize_tree(node); 
  // printTree(node, '\0');
   assert(result == "IIL LnLa"); 
   recycle_memory(node);
}

/*
 * name:      build_one
 * purpose:   test the build_tree function with one node
 * arguments: none
 * returns:   none
 * effects:   builds a tree with one node
 */
 void build_one() { 
   
 }

 /*
 * name:      build_null
 * purpose:   test the build_tree function with a nullptr
 * arguments: none
 * returns:   none
 * effects:   builds an empty tree 
 */


/*
 * name:      build_many
 * purpose:   test the build_tree function with a real PQ
 * arguments: none
 * returns:   none
 * effects:   builds a HuffmanCodingTree
 */