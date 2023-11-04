/*
 *  Passenger.cpp
 *  Kasey Afshani 
 *  9/26/23
 *
 *  CS 15 Project 1: MetroSim 
 *
 *  Create the implementation for the Passenger class. Should print out the 
    passenger's info 
 *
 */

#include <iostream>
#include <string>
#include "Passenger.h"

/*
 * name:      print 
 * purpose:   print the passenger's number, and arrival and departure stations
 * arguments: pointer to the ostream's output 
 * returns:   none
 * effects:   prints passenger ID, arrival, and departure 
 */
void Passenger::print(std::ostream &output)
{
        // put the passenger's info into the output stream 
        output << "[" << std::to_string(Passenger::id) << ", " 
                << std::to_string(Passenger::from) << "->" 
                << std::to_string(Passenger::to) << "]"; 
}
