/*
 *  main.cpp
 *  Kasey Afshani
 *  11/5/23
 *
 *  CS 15 Proj 3 ZAP! 
 *
 *  Call the HuffmanCoder class to execute ZAP! Users can choose to either zap
    or unzap, and they will provide a file to perform the operations on and an
    output file to store the result in! 
 *
 */
#include <iostream>
#include <vector>
#include <sstream> 
#include <stdexcept> 
#include <cstdio>
#include <fstream>
#include <stdio.h>
#include <string.h>

#include "HuffmanCoder.h"


using namespace std; 

/*
 * name:      main
 * purpose:   run the program
 * arguments: number of arguments and pointer to what's written on command line
 * returns:   none
 * effects:   Runs ZAP!
 */
int main(int argc, char *argv[]) { 

    if(argc != 4) { 
        cerr << "Usage: ./zap [zap | unzap] inputFile outputFile\n";
        exit(EXIT_FAILURE); 
    }

    ifstream input;  
    ofstream output; 


    HuffmanCoder testing; 
    if (strcmp(argv[1], "zap") == 0) {
        testing.encoder(argv[2], argv[3]);
    } else if (strcmp(argv[1], "unzap") == 0) { 
        testing.decoder(argv[2], argv[3]);
    } else { 
        cerr << "Usage: ./zap [zap | unzap] inputFile outputFile\n";
        exit(EXIT_FAILURE); 
    }
}