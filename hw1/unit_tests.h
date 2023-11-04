/*
 * unit_tests.h
 *
 * CS 15 homework 1
 * by Tyler Calabrese, January 2021
 *
 * edited by: Milod Kazerounian, January 2022
 *
 * Uses Matt Russell's unit_test framework to test the CharArrayList class.
 *
 * Instructions for using testing framework can be found at in CS 15's lab
 * 1 -- both in the spec and in the provided ArrayList_tests.h and Makefile.
 * More in-depth information for those who are curious as to how it works can
 * be found at http://www.github.com/mattrussell2/unit_test.
 */
#include "CharArrayList.h"
#include <cassert>
#include <iostream>
#include <stdexcept>

using namespace std; 

/********************************************************************\
*                       CHAR ARRAY LIST TESTS                        *
\********************************************************************/

/* To give an example of thorough testing, we are providing
 * the unit tests below which test the insertAt function. Notice: we have
 * tried to consider all of the different cases insertAt may be
 * called in, and we test insertAt in conjunction with other functions!
 *
 * You should emulate this approach for all functions you define.
 */

//tests the construction of an empty array list 
// afterwards, size and capacity should be 0. also checks the isEmpty function
void default_constructor_test() {
    // create an instance of the array 
    CharArrayList test_list;

    // check to see everything's been initialized correctly 
    assert(test_list.size() == 0);
    assert(test_list.isEmpty());
}

//tests the constructor of an array list with one character
// afterwards, capacity and size should be 1 and data should point to the char
// given as an argument 
void one_element_constructor_test() {
    // create an instance of the array the char at  
    CharArrayList tester_list('a'); 

    // check to see everything's been initialized correctly 
    assert(tester_list.size() == 1);
    assert(tester_list.first() == 'a');
    assert(tester_list.last() == 'a');
}


// tests the constructor when given an array list and size to dynamically 
// allocate. should create a dynamically allocated array list on the heap
void populated_array_constructor_test() { 
    // create an instance of the array list 
    char testing[3] = {'a', 'b', 'c'};
    CharArrayList test_list(testing, 3);

    // check to see everything's been initialized correctly 
    assert(test_list.size() == 3);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.last() == 'c');
}


// test constructor 4 on copying an already dynamically allocated array list. 
// should dynamically allocate another array and copy the contents from the 
// first list over. 
void copy_constructor_test() { 
    // create an instance of the original array list 
    char abc[] = {'a', 'b', 'c'}; 
    CharArrayList test_list(abc, 3);

    // create an instance of the copy list 
    CharArrayList copy_list(test_list);

    // test to see if the copy list has the same information as the original 
    assert(copy_list.size() == 3);
    assert(copy_list.elementAt(0) == 'a');
    assert(copy_list.elementAt(1) == 'b');
    assert(copy_list.elementAt(2) == 'c');
    assert(copy_list.last() == 'c');
}


// test the reassignment operator function. should create a deep copy of the 
// instance on the right 
void reassignment_test_two_populated() {
    // create an instance of the array we want to change  
    char abc[] = {'a', 'b', 'c'}; 
    CharArrayList list1(abc, 3);

    // create an instance of the array we want to reassign list1 to be 
    char name[4] = {'a', 'b', 'b','y'};
    CharArrayList list2(name, 4);
    
    // reassign list 1 to be list 2 
    list1 = list2; 
    
    // check to see if list 1 has the properties of list 2
    assert(list1.size() == 4);
    assert(list1.elementAt(0) == 'a');
    assert(list1.elementAt(1) == 'b');
    assert(list1.elementAt(2) == 'b');
    assert(list1.elementAt(3) == 'y');

}


// test the reassignment operator function on an empty and populated list. 
// should turn the populated list empty 
void reassignment_test_populated_empty() { 

    // create an instance of the array we want to reassign 
    char abc[] = {'a', 'b', 'c'}; 
    CharArrayList list1(abc, 3);
    
    // create an empty array list we will reassign list 1 to be
    CharArrayList empty_list; 

    // reassign list 1 to the empty list 
    list1 = empty_list;
    
    // check to see if list 1 is empty 
    assert(list1.isEmpty());
}


// test the reassignment operator function on an empty and populated array list. 
// should make the empty list populated
void reassignment_test_empty_populated() { 

    // create a populated array instance for us to reassign the empty list to 
    char abc[] = {'a', 'b', 'c'}; 
    CharArrayList list1(abc, 3);
    
    // create an instance of an empty array list for us to copy info into 
    CharArrayList empty_list;

    // reassign empty list to list 1
    empty_list = list1; 

    // check to see that empty list was populated 
    assert(empty_list.first() == 'a');
    assert(empty_list.elementAt(1) == 'b');
    assert(empty_list.last() == 'c');
    assert(empty_list.size() == 3);
}


// tests the toString function. afterwards, should print out the array of l
// letters and the size of the array 
void toString_test_populated() {
    // create an instance of a populated array for us to test 
    char name[4] = {'a', 'b', 'b','y'};
    CharArrayList test_list(name, 4);
    
    // create a string to find what's being printed and check 
    std::string info = test_list.toString(); 
    assert(info == "[CharArrayList of size 4 <<abby>>]");
}


// testing tostring on an empty array list. should print that size is 0
void toString_test_empty() { 
    // create instance of array list 
    CharArrayList test_list; 
    
    // create a string to find what's being printed and check 
    std::string test = test_list.toString();
    assert(test == "[CharArrayList of size 0 <<>>]"); 
}


// test toString on an array list with only one char. should print that one char
void toString_test_one() { 

    // create instance of an array list with only one element 
    CharArrayList test_list('a');
    assert(test_list.toString() == "[CharArrayList of size 1 <<a>>]");
}


// test the reverseToString on a populated array. 
// should print out the array backwards 
void toReverseString_test_populated() { 

    // create instance of populated array 
    char name[4] = {'a', 'b', 'b','y'};
    CharArrayList test_list(name, 4);

    // create a string to find what's being printed and check
    std::string info = test_list.toReverseString(); 
    assert(info == "[CharArrayList of size 4 <<ybba>>]");
}


// test the reverse string on an empty array. should return that size is 0
void toReverseString_test_empty() { 
    // create an instance of an empty array list 
    CharArrayList empty_list;

    // create a string to find what's being printed and check
    std::string test = empty_list.toReverseString(); 
    assert(test == "[CharArrayList of size 0 <<>>]");
}

void toReverseString_test_one() { 

    // create instance of an array list with only one element 
    CharArrayList test_list('a');
    assert(test_list.toReverseString() == "[CharArrayList of size 1 <<a>>]");
}

// test the replaceAt function. should swap the characters in the array. 
// size should remain constant. 
void replaceAt_test_populated_middle() {

    // create an instance of a populated array list 
    char abc[] = {'a', 'b', 'c'};
    CharArrayList test_list(abc, 3);

    // try to replace char at the end of the function 
    test_list.replaceAt('z', 2); 
    assert(test_list.elementAt(2) == 'z');
    assert(test_list.size() == 3); 
}


// test the replaceAt function for an out of range index. should run an error
// statement 
void replaceAt_test_error() { 

    // create an instance of a populated array list 
    char abc[] = {'a', 'b', 'c'};
    CharArrayList test_list(abc, 3);

    // bool to track if range error has been thrown 
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to run the function and catch the error (expected)
    try {
        test_list.replaceAt('z', 7); 
    }
    catch(const range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
        // check to see if it passed 
        assert(error_message == "index (7) not in range [0..3)"); 
        assert(range_error_thrown);
}

// test for replaceAt in the "middle of" an empty array list. 
// should give us a range error  
void replaceAt_test_empty_middle() { 

    // create instance of empty array list 
    CharArrayList empty_list; 

    // bool to track if range error has been thrown 
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to run the function and catch the error (expected)
    try {
        empty_list.replaceAt('z', 8); 
    }
    catch(const range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
        // check to see if it passed
        assert(error_message == "index (8) not in range [0..0)"); 
        assert(range_error_thrown);
}

// test for replaceAt in the "start of" an empty array list. 
// should give us a range error  
void replaceAt_test_empty_start() { 

    // create instance of empty array list 
    CharArrayList empty_list; 

    // bool to track if range error has been thrown 
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to run the function and catch the error (expected)
    try {
        empty_list.replaceAt('z', 0); 
    }

    catch(const range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
        // check to see if it passed
        assert(error_message == "index (0) not in range [0..0)"); 
        assert(range_error_thrown);
}

// test the removeAt function. should remove the char at the given index and 
// shift the rest over by one to fill the space. size should decrease by 1.  
void removeAt_test_populated_middle() {

    // create an instance of a populated array 
    char abc[] = {'a', 'b', 'c'};
    CharArrayList test_list(abc, 3);
    
    // remove an element in the middle of the array 
    test_list.removeAt(1); 

    // make sure everything's been updated properly 
    assert(test_list.elementAt(1) == 'c');
    assert(test_list.size() == 2);
}


// test to see what happens if we want to remove something out of range. should 
// print out an error message and size should remain constant
void removeAt_test_error() {

    // create an instance of a populated array 
    char abc[] = {'a', 'b', 'c'};
    CharArrayList test_list(abc, 3);

    // bool to track if range error has been thrown 
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to run the function and catch the error (expected)
    try {
        test_list.removeAt(4);
    }
    catch(const range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
        // check to see if it passed
        assert(error_message == "index (4) not in range [0..3)"); 
        assert(test_list.size() == 3);
        assert(range_error_thrown);
}


// try to call the removeAt function in the middle of an empty array list. 
// should return with an error message
void removeAt_test_empty() { 

    // create an instance of an empty array list 
    CharArrayList test_list; 

    // bool to track if range error has been thrown 
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to run removeAt in the "middle" of an empty function 
    // and catch the error 
    try { 
        test_list.removeAt(2);
    }
    catch(const range_error &e) { 
        range_error_thrown = true;
        error_message = e.what();
    }
        // check to see if it passed
        assert(error_message == "index (2) not in range [0..0)");
        assert(test_list.size() == 0);
        assert(range_error_thrown);
}


// try to call the removeAt function at the "start" of an empty array list
// should return with an error message 
void removeAt_test_empty_start() { 

    // create an instance of an empty array list 
    CharArrayList test_list; 

    // bool to track if range error has been thrown 
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to run removeAt at the "start" of an empty function 
    // and catch the error 
    try { 
        test_list.removeAt(0);
    }
    catch(const range_error &e) { 
        range_error_thrown = true;
        error_message = e.what();
    }
        // check to see if it passed 
        assert(error_message == "index (0) not in range [0..0)");
        assert(test_list.size() == 0);
        assert(range_error_thrown);
}


// Call the removeAt function on a one-element array list. should empty the list
void removeAt_test_one() { 
    // create an instance of an array list with population of 1 
    CharArrayList test_list('g'); 

    // remove the only element 
    test_list.removeAt(0);

    // check to see if the array list is empty 
    assert(test_list.isEmpty());
}


// test to make sure that size is updating correctly on a populated array list
void size_test() {
    // create an instance of a populated array list 
    char abc[] = {'a', 'b', 'c'};
    CharArrayList test_list(abc, 3);

    //make sure size is what we want it to be 
    assert(test_list.size() == 3); 

}


// test the popFromFront function. should remove first element and shift the  
// rest of the array over
void popFromFront_test_populated() {

    // create an instance of a populated array list 
    char abc[] = {'a', 'b', 'c'};
    CharArrayList test_list(abc, 3);

    // remove the first element 
    test_list.popFromFront();

    // check to see if everything shifted correctly + updated properly 
    assert(test_list.elementAt(0) == 'b');
    assert(test_list.elementAt(1) == 'c');
    assert(test_list.size() == 2);
}


// test the popFromFront function on an empty array. should print out an error 
void popFromFront_test_empty() {

    // create an instance of an empty array list 
    CharArrayList test_list; 

    // bool to track if runtime error has been thrown 
    bool runtime_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to remove the first element and catch the error (expected)
    try { 
        test_list.popFromFront();
    }
    catch(const runtime_error &e) { 
        runtime_error_thrown = true;
        error_message = e.what();
    }
        // check to see if it passed
	    assert(error_message == "cannot pop from empty ArrayList"); 
        assert(test_list.size() == 0);
        assert(runtime_error_thrown);
}


// test the popFromFront function on a one-element array list.
void popFromFront_test_one() {

    // create an instance of an array list with one element
    CharArrayList test_list('b'); 

    //remove the first element
    test_list.popFromFront();

    //check to see if the list is now empty 
    assert(test_list.isEmpty());
}


// test the popFromBack function. should remove the last element of the array 
void popFromBack_test_populated() {

    // create an instance of a populated array list 
    char abc[] = {'a', 'b', 'c'};
    CharArrayList test_list(abc, 3);

    // remove the last element of the list 
    test_list.popFromBack();

    // make sure everything updated properly 
    assert(test_list.last() == 'b');
    assert(test_list.size() == 2);
}


// test the popFromBack on an empty array list. should return with an error 
void popFromBack_test_empty() { 
    
    // create an instance of an empty array list 
    CharArrayList test_list; 

    // bool to track if runtime error has been thrown 
    bool runtime_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to remove the last element and catch the error message (expected)
    try { 
        test_list.popFromBack();
    }
    catch(const runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
        // check to see if it passed
	    assert(error_message == "cannot pop from empty ArrayList"); 
        assert(test_list.size() == 0);
        assert(runtime_error_thrown);
}


// test the popFromBack function on a one-element array list.
void popFromBack_test_one() {

    // create an instance of an array list with one element
    CharArrayList test_list('b'); 

    //remove the first element
    test_list.popFromBack();

    //check to see if the list is now empty 
    assert(test_list.isEmpty());
}


// test the pushAtBack function. should add a character to the end of the 
// array list
void pushAtBack_test_populated() { 
    // create an instance of a populated array list 
    char abc[] = {'a', 'b', 'c'};
    CharArrayList test_list(abc, 3);

    // add an element to the back of the list 
    test_list.pushAtBack('d');

    // test to see if everything updated properly 
    assert(test_list.last() == 'd');
    assert(test_list.size() == 4); 
}


// try to push at back on an empty array. should create a 1 element array list 
void pushAtBack_test_empty() { 

    // create an instance of an empty array list 
    CharArrayList empty_list; 

    // add a char to the end of an array list 
    empty_list.pushAtBack('a');

    // make sure everything was updated properly 
    assert(empty_list.size() == 1);
    assert(empty_list.first() == 'a');
    assert(empty_list.last() == 'a');
}


// test pushAtBack on a single element array list. size should update to 2
void pushAtBack_test_one() { 

    // create an instance of an array list with one element 
    CharArrayList test_list('a');

    // add an element to the end of the array 
    test_list.pushAtBack('b');

    // check to see if everything was updated properly 
    assert(test_list.size() == 2);
    assert(test_list.first() == 'a');
    assert(test_list.last() == 'b');
}


// test the pushAtFront fcn. should add a character to the start of the array 
// list and shift the rest over 
void pushAtFront_test_populated() { 

    // create an instance of a populated array list 
    char abc[] = {'a', 'b', 'c'};
    CharArrayList test_list(abc, 3);

    //add an element to the front of the array 
    test_list.pushAtFront('z'); 

    // check to make sure everything shifted + updated properly 
    assert(test_list.first() == 'z');
    assert(test_list.size() == 4);
    assert(test_list.elementAt(1) == 'a');
    assert(test_list.elementAt(3) == 'c');
}


// test the pushAtFront on an empty array. should create a 1 element array list 
void pushAtFront_test_empty() { 

    // create an instance of an empty array list 
    CharArrayList empty_list; 

    // add a char to the end of an array list 
    empty_list.pushAtFront('a');

    // make sure everything was updated properly 
    assert(empty_list.size() == 1);
    assert(empty_list.first() == 'a');
    assert(empty_list.last() == 'a');
}


// test pushAtFront on a single element array list. size should update to 2
void pushAtFront_test_one() { 

    // create an instance of an array list with one element 
    CharArrayList test_list('a');

    // add an element to the end of the array 
    test_list.pushAtFront('b');

    // check to see if everything was updated properly 
    assert(test_list.size() == 2);
    assert(test_list.first() == 'b');
    assert(test_list.last() == 'a');
}


// test the clear section. should come back with an empty array list. 
void clear_test_populated() { 

    // create an instance of a populated array list
    char name[4] = {'a', 'b', 'b','y'};
    CharArrayList test_list(name, 4);

    // clear the array list 
    test_list.clear(); 

    // make sure the array list was cleared properly 
    assert(test_list.isEmpty()); 
}


// try to clear an already empty array list. 
void clear_test_empty() { 

    // create an instance of an empty array list 
    CharArrayList test_list; 

    // clear the array list 
    test_list.clear();

    // make sure there are no double frees, the list doesn't change 
    assert(test_list.size() == 0);
    assert(test_list.isEmpty());

}


// test the "last" function on a populated array (and also first)
void last_test_populated() {

    // create an instance of a popualted array list 
    char abc[3] = {'a', 'b', 'c'};
    CharArrayList test_list(abc, 3);

    // make sure the correct indices are being accessed 
    assert(test_list.last() == 'c');
    assert(test_list.first() == 'a');
}


// test the "last" function on an empty array list 
void last_test_empty() { 

    // create an instance of an empty array list 
    CharArrayList test_list;

    // bool to track if runtime error has been thrown 
    bool runtime_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to access the last index and catch an error message (expected)
    try {
        test_list.last();
    }
    catch(const runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
        // check to see if it passed
        assert(runtime_error_thrown);
	    assert(error_message == "cannot get last of empty ArrayList"); 
}


// test the "last" function on an array list with only one element 
void last_test_one() { 

    // create an instance of an array list with one element 
    CharArrayList test_list('a');

    // check to see if last works 
    assert(test_list.last() == 'a');
}


// test the "first" test on an empty array. should return an error message
void first_test_empty() { 

    // create an instance of an empty array list 
    CharArrayList test_list; 

    // bool to track if runtime error has been thrown 
    bool runtime_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to access the first index and catch the error message (expected)
    try {
        test_list.first();
    }
    catch(const runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
        // check to see if it passed
        assert(runtime_error_thrown);
        assert(error_message == "cannot get first of empty ArrayList"); 
}


// test the elementAt function. should return character at desired index 
void elementAt_test_populated() {

    // create instance of a populated array list 
    char name[4] = {'a', 'b', 'b','y'};
    CharArrayList test_list(name, 4);

    // make sure the correct char is being accessed for each index 
    assert(test_list.elementAt(3) == 'y');
    assert(test_list.elementAt(2) == 'b');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(0) == 'a');
}


// test elementAt function for out of range
void elementAt_test_error() { 

    // create instance of a populated array list 
    char name[4] = {'a', 'b', 'b','y'};
    CharArrayList test_list(name, 4);

    // bool to track if range error is thrown 
    bool range_error_thrown = false; 

    // var to track any error messages raised
    std::string error_message = "";

    // try to access element out of range and catch the error message (expected)
     try {
        test_list.elementAt(8); 
    }
    catch(const range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
        // check to see if it passed
        assert(error_message == "index (8) not in range [0..4)"); 
        assert(range_error_thrown);        
}


// test the insertAt function. should // create an instance of a populated array list 
    char list[] = {'a', 'b', 'd'};
    CharLinkedList test_list(list, 3);

    // bool to track if runtime error has been thrown 
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to insert out of range and catch the error message (expected)
    try {
        test_list.insertAt(-1, 'c');
    }
    catch(const range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
        // check to see if it passed
        assert(range_error_thrown);
        assert(error_message == "cannot pop from empty LinkedList");
        //the given character at the desired 
// index and shift the rest over
void insertAt_test_populated_middle() { 
    
    // create an instance of a populated array list 
    char name[4] = {'a', 'b', 'b','y'};
    CharArrayList test_list(name, 4);

    // insert a char in the middle of the list 
    test_list.insertAt('r', 1); 

    // make sure everything shifted/was updated properly 
    assert(test_list.size() == 5); 
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'r');
    assert(test_list.elementAt(2) == 'b');
    assert(test_list.elementAt(3) == 'b');
    assert(test_list.elementAt(4) == 'y');
}


// test the insertAt function for a range error. 
void insertAt_test_error() { 
    
    // create an instance of a populated array list 
    char name[4] = {'a', 'b', 'b','y'};
    CharArrayList test_list(name, 4);

    // bool to track whether or not range error is thrown 
    bool range_error_thrown = false; 

    // var to track any error messages raised
    std::string error_message = "";

    // try to insert a character in out of range and catch the error (expected)
    try { 
        test_list.insertAt('r', 5); 
    }

    catch(const range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
        // check to see if it passed 
        assert(error_message == "index (5) not in range [0..4]"); 
        assert(range_error_thrown);
}


// test the insert at for the last index in the function
void insertAt_test_populated_end() { 

    // create an instance of a populated array list 
    char name[4] = {'a', 'b', 'b','y'};
    CharArrayList test_list(name, 4);

    // insert a char at the end of the list 
    test_list.insertAt('r', 4); 

    // check to make sure all is well 
    assert(test_list.elementAt(4) == 'r');
    assert(test_list.size() == 5);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'b');
    assert(test_list.elementAt(3) == 'y');
}


// test the insertAtfunction for a range below 0 
void insertAt_test_below0() { 
    
    // create an instance of a populated array list 
    char name[4] = {'a', 'b', 'b','y'};
    CharArrayList test_list(name, 4);

    // bool to track whether or not range error is thrown 
    bool range_error_thrown = false; 

    // var to track any error messages raised
    std::string error_message = "";

    // try to insert a character in out of range and catch the error (expected)
    try { 
        test_list.insertAt('r', -1); 
    }

    catch(const range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
        cerr << e.what() << endl; 
    }
        // check to see if it passed 
        assert(error_message == "index (-1) not in range [0..4]"); 
        assert(range_error_thrown);
}

// test the concatonate function. should add all of the elements of the 
// given array into our array. 
void concatenate_test_both_populated() { 
    // create the first instance of a populated array list 
    char abc[] = {'a', 'b', 'c'}; 
    CharArrayList list1(abc, 3);

    // create the second instance of a populated array list 
    char name[4] = {'a', 'b', 'b','y'};
    CharArrayList list2(name, 4);

    // add list 2 to the back of list 1 
    list1.concatenate(&list2);

    // check to see if list 1 was updated properly 
    assert(list1.size() == 7);
    assert(list1.first() == 'a');
    assert(list1.elementAt(5) == 'b'); 
    assert(list1.last() == 'y');
}


// test the concatenate function with a populated list on itself 
void concatenate_test_on_itself() { 

    // create instance of a populated array list 
    char abc[] = {'a', 'b', 'c'}; 
    CharArrayList list1(abc, 3);

    // try to concatenate the list onto itself 
    list1.concatenate(&list1);

    // make sure everything was updated properly 
    assert(list1.size() == 6);
    assert(list1.first() == 'a');
    assert(list1.elementAt(3) == 'a'); 
    assert(list1.last() == 'c');
}


// test the concatenate function with an empty list onto a populated list 
void concatenate_test_populated_empty() { 

    // create instance of a populated array list 
    char abc[] = {'a', 'b', 'c'}; 
    CharArrayList list1(abc, 3);

    // create an instance of an empty array list 
    CharArrayList empty_list; 

    // concatenate the empty list onto list1
    list1.concatenate(&empty_list);

    // check to make sure everything remained constant 
    assert(list1.size() == 3);
    assert(list1.first() == 'a');
    assert(list1.elementAt(1) == 'b'); 
    assert(list1.last() == 'c');
}


// test the concatenate function with a populated list onto an empty array list 
void concatenate_test_empty_populated() { 
    // create instance of a populated array list 
    char abc[] = {'a', 'b', 'c'}; 
    CharArrayList list1(abc, 3);

    // create an instance of an empty array list 
    CharArrayList empty_list; 

    // concatenate list1 onto the empty list 
    empty_list.concatenate(&list1);

    // check to make sure everything remained constant 
    assert(empty_list.size() == 3);
    assert(empty_list.first() == 'a');
    assert(empty_list.elementAt(1) == 'b'); 
    assert(empty_list.last() == 'c');
}
 

// test the insertInOrder function. should insert the given character in correct
// alphabetical order into the list. 
void insertInOrder_test_front() { 

    // create an instance of a populated array list 
    char bce[3] = {'b', 'c', 'e'};
    CharArrayList test_list(bce, 3);

    // try to insert something that'll go at the front of the list 
    test_list.insertInOrder('a');

    // make sure everything was updated/shifted properly 
    assert(test_list.first() == 'a');
    assert(test_list.size() == 4);
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'e');
}

// test the insertInOrder function for a character not a-z
void insertInOrder_test_weird_character() { 
    // create an instance of a populated array list 
    char bce[3] = {'b', 'c', 'e'};
    CharArrayList test_list(bce, 3);

    // try to insert something that'll go at the front of the list 
    test_list.insertInOrder('<');

    // make sure everything was updated/shifted properly 
    assert(test_list.first() == '<');
    assert(test_list.size() == 4);
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
    assert(test_list.elementAt(3) == 'e');
}


// test the insertInOrder function for a char in the middle of the array list
void insertInOrder_test_middle() { 
    
    // create an instance of a populated array list 
    char bce[3] = {'b', 'c', 'e'};
    CharArrayList test_list(bce, 3);

    // insert a char that'll go in the middle of the list 
    test_list.insertInOrder('d');

    // make sure everything was updated/shifted properly 
    assert(test_list.first() == 'b');
    assert(test_list.size() == 4);
    assert(test_list.elementAt(1) == 'c');
    assert(test_list.elementAt(2) == 'd');
    assert(test_list.elementAt(3) == 'e');
}


// test the insertInOrder function for a char that's already on the array list
void insertInOrder_test_same_letter() {

    // create an instance of a populated array list 
    char bce[3] = {'b', 'c', 'e'};
    CharArrayList test_list(bce, 3);

    // try to insert a char that's the same as a char already in the list 
    test_list.insertInOrder('e'); 

    // make sure everything was updated/shifted properly 
    assert(test_list.size() == 4);
    assert(test_list.first() == 'b');
    assert(test_list.elementAt(1) == 'c');
    assert(test_list.elementAt(2) == 'e');
    assert(test_list.elementAt(3) == 'e');
}
    

// test the insertInOrder function for a char going to the end of the array 
void insertInOrder_test_end() {

    // create an instance of a populated array list 
    char bce[3] = {'b', 'c', 'e'};
    CharArrayList test_list(bce, 3);

    // insert a char that'll go at the end of the list 
    test_list.insertInOrder('z'); 

    // make sure everything was updated/shifted properly 
    assert(test_list.size() == 4);
    assert(test_list.first() == 'b');
    assert(test_list.elementAt(1) == 'c');
    assert(test_list.elementAt(2) == 'e');
    assert(test_list.elementAt(3) == 'z');
}


// Tests correct insertion into an empty AL.
// Afterwards, size should be 1 and element at index 0
// should be the element we inserted.
void insertAt_empty_correct() { 

    CharArrayList test_list;
    test_list.insertAt('a', 0);
    assert(test_list.size() == 1);
    assert(test_list.elementAt(0) == 'a');

}


// Tests incorrect insertion into an empty AL.
// Attempts to call insertAt for index larger than 0.
// This should result in an std::range_error being raised.
void insertAt_empty_incorrect() {

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharArrayList test_list;
    try {
    // insertAt for out-of-range index
    test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
    // if insertAt is correctly implemented, a range_error will be thrown,
    // and we will end up here
    range_error_thrown = true;
    error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..0]");
}


// Tests correct insertAt for front of 1-element list.
void insertAt_front_singleton_list() {
    
    // initialize 1-element list
    CharArrayList test_list('a');

    // insert at front
    test_list.insertAt('b', 0);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'b');
    assert(test_list.elementAt(1) == 'a');
}


// Tests correct insertAt for back of 1-element list.
void insertAt_back_singleton_list() {
    
    // initialize 1-element list
    CharArrayList test_list('a');

    // insert at back
    test_list.insertAt('b', 1);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
}


// Tests calling insertAt for a large number of elements.
// Not only does this test insertAt, it also checks that
// array expansion works correctly.
void insertAt_many_elements() {
    
    CharArrayList test_list;

    // insert 1000 elements
    for (int i = 0; i < 1000; i++) {
        // always insert at the back of the list
        test_list.insertAt('a', i);
    }

    assert(test_list.size() == 1000);

    for (int i = 0; i < 1000; i++) {
        assert(test_list.elementAt(i) == 'a');
    }
}


// Tests insertion into front of a larger list
void insertAt_front_large_list() {
    char test_arr[9] = { 'a', 'b', 'c', 'z', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 9);

    test_list.insertAt('y', 0);

    assert(test_list.size() == 10);
    assert(test_list.elementAt(0) == 'y');
    assert(test_list.toString() == "[CharArrayList of size 10 <<yabczdefgh>>]");
}

// Tests insertion into the back of a larger list
void insertAt_back_large_list() {

    char test_arr[10] = { 'y', 'a', 'b', 'c', 'z', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 10);  

    test_list.insertAt('x', 10);

    assert(test_list.size() == 11);
    assert(test_list.elementAt(10) == 'x');
    assert(test_list.toString() == 
    "[CharArrayList of size 11 <<yabczdefghx>>]"); 
}


// Tests insertion into the middle of a larger list
void insertAt_middle_large_list() {
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);

    test_list.insertAt('z', 3);

    assert(test_list.size() == 9);
    assert(test_list.elementAt(3) == 'z');
    assert(test_list.toString() == "[CharArrayList of size 9 <<abczdefgh>>]");
}


// Tests out-of-range insertion for a non-empty list.
void insertAt_nonempty_incorrect() {
   
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    try {
        test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..8]");
}
