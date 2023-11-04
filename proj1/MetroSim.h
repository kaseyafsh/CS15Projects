/*
 *  MetroSim.h
 *  Kasey Afshani 
 *  10/5/23
 *
 *  CS 15 Project 1: MetroSim 
 *
 *  Create the declarations for MetroSim. Defines functions that will allow 
    cleints to add passengers and move the train from station to station. 
 */

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include "Passenger.h"
#include <iostream>
#include "PassengerQueue.h"
#include <vector>
#include <stdexcept>
#include <fstream>


class MetroSim {
public:
    void query(std::istream &input, std::ostream &output);
    void read_stations(std::ifstream &input, std::string filename);


private:
    void move(std::ostream &output);
    void print_everything(std::ostream &output);

    struct Station { 
        std::string name; 
        PassengerQueue waiting; 
        int stop_num; 
    };
    
    std::vector <Station> stations; 
    std::vector <PassengerQueue> train;

    int location = 0; 
};

#endif
