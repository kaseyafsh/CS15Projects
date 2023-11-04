/*
 *  DatumStack.cpp
 *  Kasey Afshani
 *  10/18/23
 *
 *  CS 15 Proj 2 CalcYouLater! 
 *
 *  This file includes the implementation of the DatumStack class.  
 *
 */

#include <iostream>
#include <vector>
#include <sstream> 
#include <stdexcept> 
#include <cstdio>

#include "Datum.h"
#include "DatumStack.h"

using namespace std; 


/*
 * name:      DatumStack
 * purpose:   create an empty DatumStack
 * arguments: none
 * returns:   none
 * effects:   creates an empty datum stack
 */
DatumStack::DatumStack() { 
    return; 
}


/*
 * name:      DatumStack
 * purpose:   create a populated DatumStack
 * arguments: array of Datum elements, length of stack
 * returns:   none
 * effects:   creates a populated datum stack
 */
 DatumStack::DatumStack(Datum arr[], int length) { 
    
    for(int i = 0; i < length; i++) { 
        stack.push_back(arr[i]);
    }
 }

/*
 * name:      isEmpty
 * purpose:   check to see if the DatumStack has elements in it
 * arguments: none
 * returns:   bool
 * effects:   none
 */
bool DatumStack::isEmpty() { 
    return stack.empty();
}


/*
 * name:      clear
 * purpose:   clear a DatumStack
 * arguments: none
 * returns:   none
 * effects:   empties the datum stack
 */
void DatumStack::clear() { 
    stack.clear();
}


/*
 * name:      size
 * purpose:   find the size of a DatumStack
 * arguments: none
 * returns:   int 
 * effects:   none
 */
 int DatumStack::size() { 
    return stack.size();
 }


/*
 * name:      top
 * purpose:   return the top element of the stack
 * arguments: none
 * returns:   top element of the stack 
 * effects:   none
 */
 Datum DatumStack::top() { 
    if(stack.empty()) { 
        throw std::runtime_error("empty_stack");
    } else {
        return stack.at(stack.size() - 1);
    }
 }

 /*
 * name:      pop
 * purpose:   get rid of the top element of the stack
 * arguments: none
 * returns:   none
 * effects:   pops off the top element of the stack
 */
 void DatumStack::pop() { 
    if(stack.empty()) { 
        throw std::runtime_error("empty_stack");
    } else {
        stack.pop_back();
    }
 }

 /*
 * name:      push
 * purpose:   add an element to the stack
 * arguments: the Datum element we want to add
 * returns:   none
 * effects:   adds an element to the top of the stack 
 */
 void DatumStack::push(Datum element) { 
    stack.push_back(element);
 }