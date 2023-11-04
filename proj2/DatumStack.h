/*
 *  DatumStack.h
 *  Kasey Afshani
 *  10/18/23
 *
 *  CS 15 Proj 2 CalcYouLater! 
 *
 *  DatumStack is a class of Datum elements that are stored in a vector to 
    simulate a stack. Every DatumStack starts as empty, and users can add or 
    remove datum elements from the DatumStack. 
 *
 */

#ifndef DATUMSTACK_H
#define DATUMSTACK_H

#include <iostream>
#include <vector>
#include <sstream> 
#include <cstdio>

#include "Datum.h"

class DatumStack {

public: 
    // constructors
    DatumStack();
    DatumStack(Datum arr[], int length);

    // other functions
    bool isEmpty();
    void clear();
    int size();
    Datum top();
    void pop();
    void push(Datum element);



private: 
    std::vector <Datum> stack; 

}; 
#endif



