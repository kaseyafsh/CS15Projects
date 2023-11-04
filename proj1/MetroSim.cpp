/*
 *  MetroSim.cpp
 *  Kasey Afshani 
 *  10/5/23
 *
 *  CS 15 Project 1: MetroSim 
 *
 *  Create the implementation for the MetroSim. Allows clients to add 
    passengers and move the train from station to station. 
 */

#include "MetroSim.h"
#include "Passenger.h"
#include "PassengerQueue.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <sstream>

using namespace std;

/*
 * name:      read_stations 
 * purpose:   read in all the stations from the input file
 * arguments: instream pointer, filename
 * returns:   none
 * effects:   gets all of the station names into the station struct
 */
void MetroSim::read_stations(std::ifstream &input, std::string filename) { 
    // open the file 
    input.open(filename); 

    // check to see if the file opened properly 
    if(not input.is_open()) { 
        cerr << "Error: could not open file " << filename << endl; 
        exit(EXIT_FAILURE); 
    }

    std::string curr_line; 
    int i = 0;
    while(getline(input, curr_line)) { 
        // create an instance of type station and of type PassengerQueuue
        Station curr_station; 
        PassengerQueue queue; 
        
        // update the information in the station struct and make train struct
        // the right size
        curr_station.name = curr_line; 
        curr_station.waiting = queue; 
        curr_station.stop_num = i;
        i++; 
        stations.push_back(curr_station);
        train.push_back(queue);
    }

    // close the file 
    input.close();
}

/*
 * name:      query
 * purpose:   read in commands and call the functions that execute them
 * arguments: istream and ostream pointer objects
 * returns:   none
 * effects:   runs the commands that the user or file inputs
 */
void MetroSim::query(std::istream &input, std::ostream &output) { 
    //initialize variables
    int arr = 0; 
    int dep = 0;
    std::string command = "";
    int pass_tracker = 0; 

    print_everything(cout);
    cout << "Command? "; 
    while(getline(input, command)) { 
        Station s; 
        // convert the command to a string stream if they're adding a passenger
        if(command[0] == 'p') { 
            istringstream info(command); 
             info >> command >> dep >> arr; 
        }
        if(command == "m m") {
            move(output);
        } else if(command == "p") { 
            pass_tracker++; 
            Passenger p(pass_tracker, dep, arr); 
            stations[dep].waiting.enqueue(p);

        } else if (command == "m f") { 
            std::cout << "Thanks for playing MetroSim. Have a nice day!\n"; 
            return;
        }
        print_everything(cout);
        cout << "Command? "; 
    }
}

/*
 * name:      move
 * purpose:   move the train car
 * arguments: none
 * returns:   none
 * effects:   moves the train one stop and moves the passengers accordingly
 */
 void MetroSim::move(std::ostream &output) { 
    
    // move the passenger from the queue to the train
    if(stations[location].waiting.size() != 0) { 
        while((int)stations[location].waiting.size() > 0) { 
            Passenger p = stations[location].waiting.front();
            train[p.to].enqueue(p);
            stations[location].waiting.dequeue();
        }
    }

    // physcially move the train 
    if(location < (int)stations.size() - 1) { 
        location++; 
    } else { 
        location = 0; 
    }

    // remove passengers who've arrived at their station and output their depart
    while(train[location].size() != 0){
        output << "Passenger " << train[location].front().id 
        << " left train at station " 
        << stations[train[location].front().to].name << endl; 
        train[location].dequeue();
    }
 }


/*
 * name:      print_everything
 * purpose:   print all of the program's information to the client 
 * arguments: ostream pointer
 * returns:   none
 * effects:   prints all the program's info  
 */
void MetroSim::print_everything(std::ostream &output) { 
    // print the top part  
    output << "Passengers on the train: {";
    for(int i = 0; i < (int)train.size(); i++) { 
        train[i].print(output);
    }
    output  << "}" << endl; 

    // print all the stations and their queues
    for(int i = 0; i < (int)stations.size(); i++) { 
        if(location == i) { 
            output << "TRAIN: [" << i << "] " << stations.at(i).name 
                   << " {";
                 stations.at(i).waiting.print(output);  
                 output << "}" << endl;
        } else {
        output <<  "       [" << i << "] " << stations.at(i).name 
        << " {";
        stations.at(i).waiting.print(output);
        output <<  "}" << endl; 
        }
    }
}