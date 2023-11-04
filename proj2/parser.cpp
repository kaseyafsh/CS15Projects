/*
 *  parser.cpp
 *  Kasey Afshani
 *  10/18/23
 *
 *  CS 15 Proj 2 CalcYouLater! 
 *
 *  This file implements a function that will search through a provided RString 
    and return the contents of the RString as long as the opening and closing 
    braces match.
 *
 */

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdexcept> 
#include <cstdio>
using namespace std;


/*
 * name:      parseRString
 * purpose:   find information between opening and closing curly braces
 * arguments: input stream
 * returns:   string of input
 * effects:   none
 */
string parseRString(istream &input) {
    int start_curly = 1; 
    int end_curly = 0;
    std::string direction = "";
    std::string statement = "";

    while(start_curly != end_curly and input >> direction) { 
        // create tracker for the index of our string 
        int tracker = 0; 

        if(direction[tracker] == '{') { 
            start_curly++;
            }
        if(direction[tracker] == '}') { 
            end_curly++;
        }

        tracker++;

        if(start_curly != end_curly) { 
            direction += " ";
        }
        statement += direction;

    }

    return "{ " + statement;

}
