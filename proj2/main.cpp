/*
 *  main.cpp
 *  Kasey Afshani
 *  10/18/23
 *
 *  CS 15 Proj 2 CalcYouLater! 
 *
 *  Call the RPNCalc class to execute the Calculator! Users can input numbers, 
    RStrings, or booleans into the calculator and call different commands to 
    manipulate these inputs. 
 *
 */
#include <iostream>
#include <vector>
#include <sstream> 
#include <stdexcept> 
#include <cstdio>

#include "Datum.h"
#include "DatumStack.h"
#include "parser.h"
#include "RPNCalc.h"

using namespace std; 

/*
 * name:      main
 * purpose:   run the program
 * arguments: number of arguments on the command line
 * returns:   none
 * effects:   Runs CalcYouLater
 */
int main(int argc, char *argv[]) { 
    RPNCalc calculator; 
    calculator.run();
    return 0; 
}
