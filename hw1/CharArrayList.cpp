/*
 *  CharArrayList.cpp
 *  Kasey Afshani
 *  9/13/23
 *
 *  COMP 15 HW 1 Cheshire ConCATenation
 *
 *  Function Definitions for CharArrayList class 
 *
 */

#include "CharArrayList.h"
#include <sstream> 
#include <iostream>
#include <stdexcept>

using namespace std; 

/*
 * name:      CharArrayList default constructor
 * purpose:   initialize an empty ArrayList
 * arguments: none
 * returns:   none
 * effects:   creates an array list on the heap 
 */
CharArrayList::CharArrayList() {
    numItems = 0; 
    capacity = 2;
    data = new char[capacity];
}

/*
 * name:      CharArrayList constructor
 * purpose:   initialize an empty ArrayList with a given character
 * arguments: character that we want to include in the array 
 * returns:   none
 * effects:   adds character to new array on the heap 
 */
CharArrayList::CharArrayList(char c) {
    capacity = 1; 
    numItems = 0;
    data = new char[capacity];
    data[capacity - 1] = c;  
    numItems++; 
}

/*
 * name:      CharArrayList constructor 3
 * purpose:   create a dynamically allocated array with a given array and size
 * arguments: the array of chars we want to dynamically allocate, num of chars
 * returns:   none
 * effects:   turns a given array into a dynamically allocated array, expands
              capacity and updates numItems
 */
CharArrayList::CharArrayList(char arr[], int size) {
    numItems = size; 
    capacity = numItems * 2; 
    data = new char[capacity];
    for(int i = 0; i < numItems; i++) {
        data[i] = arr[i];
    }
}

/*
 * name:      CharArrayList constructor 4
 * purpose:   create a dynamically allocated array with a given array and size
 * arguments: character that we want to include in the array 
 * returns:   none
 * effects:   adds character to new array 
 */
CharArrayList::CharArrayList(const CharArrayList &other) {
    numItems = other.size();  
    
    // allocate memory on the left hand side 
    data = new char[numItems];

    // copy member variables of other 
    for (int i = 0; i < other.size(); i++) { 
        data[i] = other.elementAt(i); 
    }

    capacity = numItems * 2; 
}

/*
 * name:      assignment operator 
 * purpose:   Define an assignment operator for the class that recycles the 
              storage associated with the instance on the left of the assignment 
              and makes a deep copy of the instance on the right hand side into
              the instance on the left hand side.
 * arguments: character that we want to include in the array 
 * returns:   none
 * effects:   adds character to new array 
 */
CharArrayList &CharArrayList::operator=(const CharArrayList &other) {
    // check to see if the two array lists are equal to each other 
    if (this == &other) { 
		return *this;
    }

    // recycle memory for left hand side
    delete[] data;

    // allocate new memory for the left hand side 
    data = new char[2 * other.size()];

    // create a deep copy of the array list
	for (int i = 0; i < other.size(); i++) { 
        data[i] = other.elementAt(i); 
    }
    // update the left hand's side's capacity and size 
	numItems = other.size();
    capacity = (numItems * 2) + 2; 
        return *this; 
}

/*
 * name:      expand
 * purpose:   increase capacity 
 * arguments: none
 * returns:   none
 * effects:   creates a new array on the heap and deep copies the data from 
              the old array onto this new one that has more capacity 
 */
void CharArrayList::expand() { 

    // dynamically allocate new space on the heap 
    char *new_data = new char[2 * capacity + 2];

    // deep copy the info from the old array onto the new array 
    for(int i = 0; i < numItems; i++) { 
        new_data[i] = data[i];
    }

    // update capacity 
    capacity *=2; 
    capacity +=2; 

    // recycle the old array 
    delete [] data; 

    // repopulate the private member function with the new info 
    data = new_data; 
}

/*
 * name:      CharArrayList first
 * purpose:   find the first element of an array
 * arguments: none
 * returns:   the first element of the array
 * effects:   none
 */
char CharArrayList::first() const { 
    if(numItems == 0) {
        throw std::runtime_error("cannot get first of empty ArrayList"); 
    }
    return data[0];
}

/*
 * name:      last
 * purpose:   find the last element of an array
 * arguments: none
 * returns:   the last element of the array
 * effects:   none
 */
char CharArrayList::last() const { 
    if(numItems == 0) {
        throw std::runtime_error("cannot get last of empty ArrayList"); 
    }
    return data[numItems - 1];
}

/*
 * name:      isEmpty
 * purpose:   check to see if the array is empty 
 * arguments: none
 * returns:   true if array is empty, false if not
 * effects:   none
 */
bool CharArrayList::isEmpty() const { 
    if(numItems == 0) {
        return true; 
    } else { 
        return false; 
    }
}

/*
 * name:      clear
 * purpose:   clear all of the elements in the array  
 * arguments: none
 * returns:   none
 * effects:   clears the array 
 */
void CharArrayList::clear() {
    
    // recycle the array 
    delete [] data; 

    // reset everything 
    capacity = 10; 
    data = new char[capacity];
    numItems = 0; 
}



/*
 * name:      toString 
 * purpose:   go through and find each character in the array 
 * arguments: none
 * returns:   each character in the array
 * effects:   none
 */
std::string CharArrayList::toString() const { 

    // initialize string value 
    string concat = ""; 

    // add each char in the array to our string if the array is populated
    if(numItems > 0) {
        for(int i = 0; i < numItems; i++) {
            concat += data[i]; 
        }
       
        return "[CharArrayList of size " + to_string(numItems) + 
        " <<" + concat + ">>]";

    } else { 
        return "[CharArrayList of size 0 <<>>]"; 
    }
    
}

/*
 * name:      toReverseString 
 * purpose:   go through and find each character in the array backwards
 * arguments: none
 * returns:   each character in the array in reverse order
 * effects:   none
 */
std::string CharArrayList::toReverseString() const{ 

    // initialize an empty string 
    string rev_concat = "";

    // if the array is populated, add each of them to the string and print 
    // from back to front 
    if(numItems > 0) {
        for(int i = numItems - 1; i > -1; i--) {
            rev_concat += data[i];
        }

        return "[CharArrayList of size " + to_string(numItems) + 
        " <<" + rev_concat + ">>]";

    } else { 
        return "[CharArrayList of size 0 <<>>]"; 
    }
}

/*
 * name:      elementAt
 * purpose:   find the character in a specific index in the array
 * arguments: int index
 * returns:   character at the given index
 * effects:   none
 */
 char CharArrayList::elementAt(int index) const { 
    // test for if index is below 0 (for all these types)
    if(index < numItems and index >= 0 and !isEmpty()) { 
        return data[index];
    } else { 
        throw std::range_error("index (" + to_string(index) +
                               ") not in range [0.." + to_string(numItems)
                                + ")");
    }
 }

/*
 * name:      CharArrayList destructor
 * purpose:   recycle all the data on the heap 
 * arguments: none
 * returns:   none
 * effects:   recycles data so we pass valgrind!
 */
CharArrayList::~CharArrayList() { 
    delete [] data; 
}

/*
 * name:      replaceAt
 * purpose:   replace a specific character on the array with a new one 
 * arguments: index of character, new character they want 
 * returns:   none
 * effects:   changes a character on the array 
 */
 void CharArrayList::replaceAt(char c, int index) {
    
    // check to see if index is in range and replace or throw error
    if(index < numItems and index >= 0 and !isEmpty()) {
        data[index] = c; 
    } else {
        throw std::range_error("index (" + to_string(index) +
                               ") not in range [0.." + to_string(numItems)
                               + ")");
    }
    
 }

/*
 * name:      removeAt
 * purpose:   remove a specific character on the array with a new one 
 * arguments: index of character 
 * returns:   none
 * effects:   removes a character on the array and shifts the rest over
 */
 void CharArrayList::removeAt(int index) {

    // check to see if index is in range 
    if(index < numItems and index >= 0 and !isEmpty()) {
        
        // shift over all the chars from the char we're removing till the 
        // end of the list and decrement numItems 
        for(int i = index; i < (numItems - 1); i++) {
            data[i] = data[i + 1];
        }
            numItems--; 
    }else{ 
        throw std::range_error("index (" + to_string(index) +
                               ") not in range [0.." + to_string(numItems)
                                + ")");
    }
 }

/*
 * name:      popFromFront
 * purpose:   remove the first character in the array  
 * arguments: none
 * returns:   none
 * effects:   removes the character on the array and shifts the rest over
 */
void CharArrayList::popFromFront() { 
    if(isEmpty()){
        throw std::runtime_error("cannot pop from empty ArrayList");
    }

    removeAt(0);
}

/*
 * name:      popFromBack
 * purpose:   remove the last character in the array  
 * arguments: none
 * returns:   none
 * effects:   removes the character on the array
 */
void CharArrayList::popFromBack() { 
    if(isEmpty()){
        throw std::runtime_error("cannot pop from empty ArrayList");
    }
    removeAt(numItems - 1);
}

/*
 * name:      pushAtBack
 * purpose:   add a character to the end of the array  
 * arguments: the character you want to insert
 * returns:   none
 * effects:   adds the given character to the array
 */
 void CharArrayList::pushAtBack(char c) {

    // check to see if there's room in the array 
    if(numItems == capacity) {
        expand();
    }

    data[numItems] = c; 
    numItems++; 
 }

/*
 * name:      pushAtFront
 * purpose:   add a character to the front of the array  
 * arguments: the character you want to insert
 * returns:   none
 * effects:   adds the given character to the array and shifts the rest over
 */

 void CharArrayList::pushAtFront(char c) { 

    // check if there's room in the array 
    if(numItems == capacity) {
        expand();
    }

    // shift chars over by one 
    for(int i = numItems; i > 0; i--) { 
        data[i] = data[i - 1]; 
    }

    data[0] = c; 
    numItems++; 
 }

/*
 * name:      insertAt
 * purpose:   add a character to a specific spot in the array 
 * arguments: the character you want to insert and the index you want 
 * returns:   none
 * effects:   adds the given character to the array and shifts the rest over
 */
 void CharArrayList::insertAt(char c, int index) { 

    // check to see if there's capacity, if not, expand 
    if(index <= numItems and index >= 0) { 
        if(numItems == capacity) {
            expand();
        }

        // shift chars over starting from the back till the index we insert at 
        for(int i = numItems; i > index; i--) { 
            data[i] = data[i - 1];
        }

        data[index] = c; 
        numItems++; 

    } else { 
        throw std::range_error("index (" + to_string(index) +
                               ") not in range [0.." + to_string(numItems)
                                + "]");
    }
    
 }

 /*
 * name:      insertInOrder
 * purpose:   add a character to it's correct spot in ascending alphabetical 
              order of the array list
 * arguments: the character you want to insert
 * returns:   none
 * effects:   adds the given character to the array and shifts the rest over
 */
void CharArrayList::insertInOrder(char c) { 

    // check to see if we have to expand 
    if(numItems == capacity) {
        expand();
    }
    
    // if the char's asc-ii value  is less than the char in that index, insert 
    // the char at that index and shift of the chars over with insertAt
    for(int i = 0; i < numItems; i++) { 
        if(c <= data[i]) { 
            insertAt(c, i);
            return; 
        } 
    }

    // if the char comes after everything else in the list in alphabetical 
    // order, then add it to the back of the list 
    if(c > data[numItems - 1]) { 
            pushAtBack(c);
        }

}

/*
* name:      concatenate
* purpose:   concatenate together the characters in two array lists 
* arguments: the array list you want to add to your array list
* returns:   none
* effects:   adds the given array list to the end of your array list
*/
void CharArrayList::concatenate(CharArrayList *other) { 

    // check to see if capacity is enough to support both lists 
    while(capacity < numItems + other->size()) {
        expand(); 
    }

    // starting from the back of the first array, add all of the chars to each 
    // index in the first array. 
    for(int i = numItems; i < (numItems + other->size()); i++) {
        data[i] = other->elementAt(i - numItems);
    }

    // update numItems 
    numItems += other->size(); 
}

/*
 * name:      CharArrayList size
 * purpose:   get the current size of the array list
 * arguments: none
 * returns:   the number of chars in the array 
 * effects:   numItems to 0 (also updates capacity and data array)
 */
int CharArrayList::size() const { 
    if(isEmpty()) {
        return 0;
    }
    return numItems; 
}
