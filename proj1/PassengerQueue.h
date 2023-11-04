/*
 *  PassengerQueue.h
 *  Kasey Afshani 
 *  9/26/23
 *
 *  CS 15 Project 1: MetroSim 
 *
 *  Create function definitions for the PassengerQueue class. Will allow client
    to manipulate the list using vectors.
 *
 */

#ifndef __PASSENGERQUEUE_H__
#define __PASSENGERQUEUE_H__

#include <iostream>
#include "Passenger.h"
#include <vector>
#include <stdexcept>

class PassengerQueue {
    
public: 
    Passenger front();
    void dequeue(); 
    void enqueue(const Passenger &passenger);
    int size();
    void print(std::ostream &output);


private: 
    // initialize vector 
    std::vector<Passenger> queue; 
};
#endif
