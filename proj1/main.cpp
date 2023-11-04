/*
 *  main.cpp
 *  Kasey Afshani 
 *  10/5/23
 *
 *  CS 15 Project 1: MetroSim 
 *
 *  Reads in the files for MetroSim and passes them to MetroSim implementation. 
 */

#include <iostream>
#include <fstream>
#include <string>

#include "MetroSim.h"

using namespace std;

// function declaration
template <typename streamtype>
void open_files(streamtype &input, std::string filename);

int main(int argc, char *argv[])
{
    ifstream instream; 
    ofstream outstream; 
    fstream output;
    MetroSim sim; 
        if(argc < 3){ 
            cerr << "Usage: ./MetroSim stationsFile outputFile [commandsFile]";
            cerr << endl; 
            exit(EXIT_FAILURE); 
        }
        
        sim.read_stations(instream, argv[1]);
        open_files(outstream, argv[2]);
        if(argc > 3) {
            open_files(instream, argv[3]);
            sim.query(instream, outstream);
            instream.close();
        } else { 
            sim.query(cin, outstream);
        }
                
        outstream.close();
        return 0;
}

template <typename streamtype>
void open_files(streamtype &input, std::string filename) { 
    input.open(filename); 

    // make sure the file was created properly 
    if(not input.is_open()) { 
        cerr << "Error: could not open file " << filename << endl; 
        exit(EXIT_FAILURE); 
    }
}

