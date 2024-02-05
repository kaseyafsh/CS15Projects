/*
 *  main.cpp
 *  Kasey Afshani and Hank Sun
 *  12/4/23
 *
 *  CS 15 Proj 4 Gerp! 
 *
 *  This is the main file of our program. The output files are opened here and
 *  passed into the HashTable class that was also declared here. At the end of
 *  the program, a thank you statement is printed. The open or exit function is
 *  also declared here to ensure each file can be opened properly.
 *
 */
#include <iostream>
#include <stack>
#include <sstream> 
#include <stdexcept> 
#include <cstdio>
#include <fstream>
#include <stdio.h>
#include <string.h>

#include "FSTree.h"
#include "HashTable.h"


using namespace std; 

/*
 * name:      main
 * purpose:   run the program
 * arguments: number of arguments and pointer to what's written on command line
 * returns:   none
 * effects:   Runs gerp
 */
int main(int argc, char *argv[]) { 
    if (argc == 3) {
        HashTable gerp;
        ofstream output; 
        gerp.open_or_exit(output, argv[2]);
        
        gerp.query(argv[1], output);
    } else { 
        cerr << "Usage: ./gerp inputDirectory outputFile\n"; 
        exit(EXIT_FAILURE); 
    }
    cout << "Goodbye! Thank you and have a nice day.\n";
    return 0;
}
