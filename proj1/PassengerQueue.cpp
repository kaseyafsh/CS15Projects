/*
 *  PassengerQueue.cpp
 *  Kasey Afshani 
 *  9/26/23
 *
 *  CS 15 Project 1: MetroSim 
 *
 *  Create the implementation for the PassengerQueue class. Should allow clients
    to manipulate the queue by adding and removing passengers using vectors.
 *
 */

#include <iostream>
#include <string>
#include "Passenger.h"
#include "PassengerQueue.h"
#include <vector>


using namespace std;


/*
 * name:      front 
 * purpose:   get the first passenger in the queue's info 
 * arguments: none 
 * returns:   the passenger at the front of the queue 
 * effects:   none
 */
Passenger PassengerQueue::front() {
    if(not queue.empty()) { 
        return queue.front();
    } else { 
         throw std::runtime_error("cannot find front of empty queue"); 
    } 
}

/*
 * name:      dequeue 
 * purpose:   remove the element at the front of the queue
 * arguments: none
 * returns:   none
 * effects:   removes first passenger and shifts the rest over
 */
void PassengerQueue::dequeue(){ 
    if(not queue.empty()) { 
        queue.erase(queue.begin());
    } else { 
        throw std::runtime_error("cannot remove passenger from empty queue");
    }
    
}


/*
 * name:      enqueue 
 * purpose:   add a new passenger to the end of the queue
 * arguments: pointer to the ostream's output 
 * returns:   none
 * effects:   prints passenger ID, arrival, and departure 
 */
void PassengerQueue::enqueue(const Passenger &passenger){ 
    queue.push_back(passenger);

}


/*
 * name:      size 
 * purpose:   find the number of passengers in the queue
 * arguments: none
 * returns:   number of passengers in the queue
 * effects:   none
 */
int PassengerQueue::size(){ 
    return queue.size(); 
}


/*
 * name:      print 
 * purpose:   print the ID, arrival and departure stations for all passengers
              on the queue 
 * arguments: pointer to the ostream's output 
 * returns:   none
 * effects:   prints all passengers' ID, arrival, and departure 
 */
void PassengerQueue::print(std::ostream &output){ 
    for(int i = 0; i < (int)queue.size(); i++) { 
        Passenger p = queue.at(i);
        p.print(output);
    }
}

