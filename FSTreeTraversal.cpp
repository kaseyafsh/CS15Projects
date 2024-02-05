/*
 *  FSTreeTraversal.cpp
 *  Kasey Afshani
 *  11/28/23
 *
 *  CS 15 Proj 4 Gerp! 
 *
 *  ADD DESCRIPTION
 *
 */

#include <string>
#include "FSTree.h"
#include <stack> 
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

using namespace std;

// function declarations 
void in_order(DirNode *root);
DirNode *finding(DirNode *root, std::string passing);


int main(int argc, char *argv[]) { 
    if (argc == 2) {

        FSTree our_tree(argv[1]);        
        DirNode *root = our_tree.getRoot();
        in_order(root);
    }

    return 0;
}

void in_order(DirNode *root) { 
    finding(root, "");
    return; 

}

DirNode *finding(DirNode *root, std::string passing) { 
    string sub_name = root->getName();

    if (root->isEmpty()) { 
        return root; 
    }

    for (int i = 0; i < root->numSubDirs(); i++) { 
        if (passing == "") {
            passing += sub_name;
        } else {
            passing += "/" + sub_name;
        }
        finding(root->getSubDir(i), passing);
    }

    for (int j = 0; j < root->numFiles(); j++) { 
        if (passing == "") {
            passing += sub_name + "/" + root->getFile(j);
        } else {
            passing += "/" + sub_name + "/" + root->getFile(j);
        }
        cout << passing << endl;
    }
    return root;
}