/*
 *  unit_tests.h
 *  Kasey Afshani 
 *  9/20/23
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to linked up in Fur
 *
 *  Use the unit testing framework to make sure everything in the code is 
    running properly, trying to test out edge cases and basics. 
 *
 */


#include "CharLinkedList.h"
#include <cassert>
#include <iostream>
#include <stdexcept>

using namespace std; 

// tests the default constructor on making an empty node for a new linked list
void default_constructor_test() { 
    CharLinkedList new_list; 

    assert(new_list.size() == 0);
    assert(new_list.isEmpty());
    
    // next line commented out because it uses private member variable
    // assert(new_list.front) == nullptr);
}


// tests the constructor for only one node. should create list of one 
void second_constructor_test() { 
    CharLinkedList new_list('a');
    assert(new_list.size() == 1);
    assert(new_list.elementAt(0) == 'a');
}


// tests the constructor for a populated list into a linked list. 
void populated_constructor_test() { 

    // create instance of populated linked list 
    char list[] = {'a', 'b', 'c'};
    CharLinkedList test_list(list, 3);

    // check to see if everything populated correctly
    assert(test_list.size() == 3); 
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
}


// tests the elementAt for a small linked list. 
void elementAt_test_two_elements() { 

    // create instance of populated linked list
    char list[] = {'a', 'b'};
    CharLinkedList test_list(list, 2);

    assert(test_list.elementAt(0) == 'a'); 
    assert(test_list.elementAt(1) == 'b');
}


// tests the elementAt function on an empty linked list. should throw an error
void elementAt_test_empty() { 

    // create instance of empty list 
    CharLinkedList test_list;

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
        assert(error_message == "index (8) not in range [0..0)"); 
        assert(range_error_thrown);  
}


// tests elementAt for an out of range index (too high). should throw an error
void elementAt_error_high() { 
    // create instance of a populated linked list 
    char name[4] = {'a', 'b', 'b','y'};
    CharLinkedList test_list(name, 4);

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


// tests elementAt for an out of range index (negative). should throw an error
void elementAt_error_neg() { 
    // create instance of a populated linked list 
    char name[4] = {'a', 'b', 'b','y'};
    CharLinkedList test_list(name, 4);

    // bool to track if range error is thrown 
    bool range_error_thrown = false; 

    // var to track any error messages raised
    std::string error_message = "";

    // try to access element out of range and catch the error message (expected)
     try {
        test_list.elementAt(-2); 
    }
    catch(const range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
        // check to see if it passed
        assert(error_message == "index (-2) not in range [0..4)"); 
        assert(range_error_thrown);  
}


// tests the pushAtFront function for an empty linked list. also tests the 
// isEmpty function
void pushAtFront_empty() { 
    
    // create instance of empty linked list and make sure it's really empty
    CharLinkedList empty_list; 
    assert(empty_list.isEmpty());

    // push a char to the front 
    empty_list.pushAtFront('a');

    // check to see all was updated properly
    assert(empty_list.size() == 1);
    assert(empty_list.elementAt(0) == 'a'); 
    assert(empty_list.first() == 'a');
    assert(empty_list.last() == 'a');
}


// tests the pushAtFront function on a one-element linked list
void pushAtFront_one() { 

    // create an instance of a one-element linked list
    CharLinkedList test_list('a');

    // push char to front 
    test_list.pushAtFront('z');

    // make sure all updated properly 
    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'z');
    assert(test_list.elementAt(1) == 'a');
}


// tests the pushAtFront function for a populated linked list
void pushAtFront_populated() { 

    // create instance of populated linked list 
    char list[] = {'a', 'b', 'c'};
    CharLinkedList test_list(list, 3);

    // push a char to the front 
    test_list.pushAtFront('z');

    // assert all elements are in the right place and size updated properly
    assert(test_list.size() == 4); 
    assert(test_list.elementAt(0) == 'z');
    assert(test_list.elementAt(1) == 'a');
    assert(test_list.elementAt(2) == 'b');
    assert(test_list.elementAt(3) == 'c');
}


// tests the size function for a populated linked list
void size_populated() { 
    char list[] = {'a', 'b', 'c'};
    CharLinkedList test_list(list, 3);
    assert(test_list.size() == 3); 
}


// tests the isEmpty function. should say the list is empty
void isEmpty_test() { 
    CharLinkedList empty_list; 
    assert(empty_list.isEmpty());
}


// tests the pushAtBack function on an empty linked list 
void pushAtBack_empty() { 

    // create instance of empty linked list 
    CharLinkedList empty_list; 

    // push at back 
    empty_list.pushAtBack('a');

    // make sure all was updated properly 
    assert(empty_list.size() == 1);
    assert(empty_list.elementAt(0) == 'a');
    assert(empty_list.first() == 'a'); 
    assert(empty_list.last() == 'a'); 
}


// tests the pushAtBack function on a one-element linked list 
void pushAtBack_singleton() { 

    // create an instance of a singleton linked list 
    CharLinkedList test_list('a');

    // push a char at back 
    test_list.pushAtBack('b');

    // make sure all indexes were updated properly and size increased
    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
}


// tests the pushAtBack function on a populated linked list 
void pushAtBack_populated() { 

    // create instance of populated linked list
    char list[] = {'a', 'b', 'c'};
    CharLinkedList test_list(list, 3);

    // add a new char to the end of the list 
    test_list.pushAtBack('z');

    // make sure all indicies and size updated properly 
    assert(test_list.size() == 4); 
    assert(test_list.elementAt(3) == 'z');
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
}


//test copy constructor on an empty linked list. should create 2nd empty list
void copy_constructor_empty() { 
    CharLinkedList empty_list; 
    CharLinkedList copy_list(empty_list); 

    assert(copy_list.size() == 0); 

}


//test copy constructor on a one-element linked list
void copy_constructor_singleton() { 

    // create a single-element linked list 
    CharLinkedList test_list('a');

    // create a copy of the first list
    CharLinkedList copy_list(test_list);

    // check to see if the copy list has the same attributes as the o.g. list
    assert(copy_list.size() == 1);
    assert(copy_list.first() == 'a'); 
    assert(copy_list.last() == 'a'); 

}


// test constructor 4 on copying an existing linked list. should create an 
// identical linked list
void copy_constructor_test_populated() { 
    // create an instance of the original linked list 
    char abc[] = {'a', 'b', 'c'}; 
    CharLinkedList test_list(abc, 3);

    // create an instance of the copy list 
    CharLinkedList copy_list(test_list);
    // (check to see if it matches commented out )
    // std::string test = copy_list.toString(); 
    // cerr << test << endl; 

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
    // create an instance of the list we want to change  
    char abc[] = {'a', 'b', 'c'}; 
    CharLinkedList list1(abc, 3);

    // create an instance of the list we want to reassign list1 to be 
    char name[4] = {'a', 'b', 'b','y'};
    CharLinkedList list2(name, 4);
    
    // reassign list 1 to be list 2 
    list1 = list2; 
    
    std::string test = list1.toString(); 

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

    // create an instance of the list we want to reassign 
    char abc[] = {'a', 'b', 'c'}; 
    CharLinkedList list1(abc, 3);
    
    // create an empty linked list we will reassign list 1 to be
    CharLinkedList empty_list; 

    // reassign list 1 to the empty list 
    list1 = empty_list;
    
    // check to see if list 1 is empty 
    assert(list1.isEmpty());
}


// test the reassignment operator function on an empty and populated linked list
// should make the empty list populated
void reassignment_test_empty_populated() { 

    // create a populated linked list for us to reassign the empty list to 
    char abc[] = {'a', 'b', 'c'}; 
    CharLinkedList list1(abc, 3);
    
    // create an instance of an empty linked list for us to copy info into 
    CharLinkedList empty_list;

    // reassign empty list to list 1
    empty_list = list1; 

    // check to see that empty list was populated 
    assert(empty_list.first() == 'a');
    assert(empty_list.elementAt(1) == 'b');
    assert(empty_list.last() == 'c');
    assert(empty_list.size() == 3);
}


// test the first function on an empty list. should throw an error. 
void first_empty() { 

    // create an instance of an empty linked list 
    CharLinkedList empty_list; 
    
    // bool to track if runtime error has been thrown 
    bool runtime_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to access the first index and catch the error message (expected)
    try {
        empty_list.first();
    }
    catch(const runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
        // check to see if it passed
        assert(runtime_error_thrown);
        assert(error_message == "cannot get first of empty LinkedList"); 
}


// test the last function on an empty linked list. should throw an error 
void last_empty() { 
    // create an instance of an empty linked list 
    CharLinkedList empty_list; 
    
    // bool to track if runtime error has been thrown 
    bool runtime_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to access the first index and catch the error message (expected)
    try {
        empty_list.last();
    }
    catch(const runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
        // check to see if it passed
        assert(runtime_error_thrown);
        assert(error_message == "cannot get last of empty LinkedList"); 
}


// test the first and last functions on a one-element list 
void first_last_singleton() { 

    // create instance of single element linked list 
    CharLinkedList test_list('a');

    // check to make sure list info is correct
    assert(test_list.size() == 1);
    assert(test_list.first() == 'a');
    assert(test_list.last() == 'a');
}


// test the first and last functions on a populated linked list 
void first_last_populated() { 

    // create instance of populated linked list 
    char list[] = {'a', 'b', 'c'};
    CharLinkedList test_list(list, 3);

    // make sure list info is correct 
    assert(test_list.size() == 3);
    assert(test_list.first() == 'a');
    assert(test_list.last() == 'c');
}


// test the first and last functions on a populated list that's been modified
void first_last_altered() { 
    
    // create instance of a populated linked lis t
    char list[] = {'a', 'b', 'c'};
    CharLinkedList test_list(list, 3);

    // alter information in the list 
    test_list.pushAtFront('z');
    test_list.pushAtBack('f'); 

    // check to see if first and last updated properly 
    assert(test_list.size() == 5);
    assert(test_list.first() == 'z');
    assert(test_list.last() == 'f');
}


// test the popFromFront on an empty linked list. should throw an error
void popFromFront_empty() { 
    CharLinkedList empty_list; 

    // bool to track if runtime error has been thrown 
    bool runtime_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to access the first index and catch the error message (expected)
    try {
        empty_list.popFromFront();
    }
    catch(const runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
        // check to see if it passed
        assert(runtime_error_thrown);
        assert(error_message == "cannot pop from empty LinkedList"); 
}


// test the popFromFront on a one-element linked list. should empty the list.
void popFromFront_singleton() { 

    // create instance of one-element linked list 
    CharLinkedList test_list('a');

    //call pop from front 
    test_list.popFromFront(); 

    assert(test_list.isEmpty()); 

} 


// test the popFromFront on a populated linked list. should have a new first 
// and decrement the list size 
void popFromFront_populated() { 

    // create instance of populated linked list 
    char list[] = {'a', 'b', 'c'};
    CharLinkedList test_list(list, 3);

    //popoff front 
    test_list.popFromFront(); 

    assert(test_list.size() == 2);
    assert(test_list.first() == 'b');
    assert(test_list.last() == 'c');
}


// test the popFromBack function on an empty linked list
void popFromBack_empty() { 
    // create instance of empty list
    CharLinkedList empty_list; 

    // bool to track if runtime error has been thrown 
    bool runtime_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to access the last index and catch the error message (expected)
    try {
        empty_list.popFromBack();
    }
    catch(const runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
        // check to see if it passed
        assert(runtime_error_thrown);
        assert(error_message == "cannot pop from empty LinkedList"); 
}


// test the popFromBack function on a single-element linked list 
void popFromBack_singleton() { 
    // create instance of one-element linked list 
    CharLinkedList test_list('a');

    //call pop from front 
    test_list.popFromBack(); 

    assert(test_list.isEmpty()); 
}


// test the popFromBack function on a populated linked list
void popFromBack_populated() { 
    // create instance of populated linked list 
    char list[] = {'a', 'b', 'c'};
    CharLinkedList test_list(list, 3);

    //call popFromback 
    test_list.popFromBack(); 

    assert(test_list.size() == 2);
    assert(test_list.first() == 'a');
    assert(test_list.last() == 'b');
}


// test the insertAt function on an empty linked list. should create a list 
// with one element 
void insertAt_empty() { 
    CharLinkedList empty_list; 
    empty_list.insertAt('a', 0);
    assert(empty_list.size() == 1);
    assert(empty_list.elementAt(0) == 'a');
    assert(empty_list.first() == 'a');
    assert(empty_list.last() == 'a');
}


// test the insertAt function at the front of a one element linked list
void insertAt_singleton_front() { 
    CharLinkedList test_list('b');
    test_list.insertAt('a', 0);
    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.first() == 'a');
    assert(test_list.last() == 'b');
}


// test the insertAt function at the back of a one element linked list
void insertAt_singleton_back() { 
    CharLinkedList test_list('a');
    test_list.insertAt('b', 1);
    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.first() == 'a');
    assert(test_list.last() == 'b');
}


// test the insertAt in the middle of a populated list 
void insertAt_populated_middle() { 

    // create instance of populated linked list 
    char list[] = {'a', 'b', 'd'};
    CharLinkedList test_list(list, 3);

    test_list.insertAt('c', 2);
    assert(test_list.size() == 4); 
    assert(test_list.first() == 'a');
    assert(test_list.last() == 'd');
    assert(test_list.elementAt(1) == 'b');
    assert(test_list.elementAt(2) == 'c');
}


// test insertAt for an out of range on a populated list (above size)
void insertAt_populated_tooBig() { 
    
    // create an instance of a populated linked list 
    char list[] = {'a', 'b', 'd'};
    CharLinkedList test_list(list, 3);

    // bool to track if range error has been thrown 
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to insert out of range and catch the error message (expected)
    try {
        test_list.insertAt('c', 5);
    }
    catch(const range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
        // check to see if it passed
        assert(range_error_thrown);
        assert(error_message == "index (5) not in range [0..3]");
}


// test insertAt for an out of range on a populated list (below 0). should 
// throw an error
void insertAt_populated_negative() { 

     // create an instance of a populated linked list 
    char list[] = {'a', 'b', 'd'};
    CharLinkedList test_list(list, 3);

    // bool to track if range error has been thrown 
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to insert out of range and catch the error message (expected)
    try {
        test_list.insertAt('c', -1);
    }
    catch(const range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
        // check to see if it passed
        assert(range_error_thrown);
        assert(error_message == "index (-1) not in range [0..3]");
}


// test insertAt for an out of range on empty list. should throw an error
void insertAt_empty_error() { 
    // create an instance of an empty linked list 
    CharLinkedList test_list; 

    // bool to track if range error has been thrown 
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to insert out of range and catch the error message (expected)
    try {
        test_list.insertAt('c', -1);
    }
    catch(const range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
        // check to see if it passed
        assert(range_error_thrown);
        assert(error_message == "index (-1) not in range [0..0]");
}


// test insertAt for an out of range on a singleton list. should throw an error
void insertAt_singleton_error() { 
    // create an instance of an singleton linked list 
    CharLinkedList test_list('a'); 

    // bool to track if range error has been thrown 
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to insert out of range and catch the error message (expected)
    try {
        test_list.insertAt('c', 2);
    }
    catch(const range_error &e) {
        range_error_thrown = true;
        error_message =  e.what();
    }
        // check to see if it passed
        assert(range_error_thrown);
        assert(error_message == "index (2) not in range [0..1]");
}


// try to insert at the last element on a populated linked list
void insertAt_populated_last() { 

    // create an instance of a populated linked list 
    char list[] = {'a', 'b', 'd'};
    CharLinkedList test_list(list, 3);

    // insert at the last element on the list 
    test_list.insertAt('e', 3);

    // make sure everything updated properly
    assert(test_list.size() == 4);
    assert(test_list.first() == 'a');
    assert(test_list.last() == 'e');
}


// test the toString function on an empty linked list 
void toString_empty() { 
    CharLinkedList empty_list; 
    std::string list = empty_list.toString();
    assert(list == "[CharLinkedList of size 0 <<>>]");
}


// test the toString function on a one-element linked list
void toString_singleton() { 

    // create an instance of a singleton list 
    CharLinkedList test_list('a'); 

    // create a string equal to the string that the function definition prints
    std::string list = test_list.toString();
    assert(list == "[CharLinkedList of size 1 <<a>>]");
}


// test the toString function on a populated linked list 
void toString_populated() { 

    // create an instance of a populated linked list 
    char list[] = {'a', 'b', 'c'};
    CharLinkedList test_list(list, 3);

    // call toString and ensure it returns the proper statement 
    std::string test = test_list.toString();
    assert(test == "[CharLinkedList of size 3 <<abc>>]"); 
}


// test the clear function on an empty linked list. should basically do nothing
 void clear_empty() { 

    // create an instance of an empty linked list 
    CharLinkedList empty_list; 

    empty_list.clear(); 

    // make sure the list was cleared 
    assert(empty_list.isEmpty());
 }


// test the clear function on a one-element linked list. should empty the list
void clear_singleton() { 
    
    // create instance of one element linkedl ist 
    CharLinkedList test_list('a'); 

    // run clear 
    test_list.clear(); 

    // make sure the list is empty and front is null (commented out)
    assert(test_list.size() == 0); 
    // assert(test_list.front == nullptr); 
} 


// test the clear function on a populated linked list. should empty the list
void clear_populated() { 
    // create an instance of a populated linked list 
    char list[] = {'a', 'b', 'c'};
    CharLinkedList test_list(list, 3);

    // run clear and make sure everything updated properly 
    test_list.clear(); 
    assert(test_list.isEmpty());
    // assert(test_list.front == nullptr); 
}


// run the clear function on a populated linked list and then pushAtBack to 
// create a singleton list. 
void clear_populated_pushBack() { 
    // create an instance of a populated linked list 
    char list[] = {'a', 'b', 'c'};
    CharLinkedList test_list(list, 3);

    test_list.clear(); 

    test_list.pushAtBack('n'); 
    assert(test_list.first() == 'n'); 
    assert(test_list.last() == 'n'); 
    assert(test_list.size() == 1);
}


// test the removeAt function on an empty linked list. should throw an error
void removeAt_empty() { 

    // create an instance of an empty linked list
    CharLinkedList empty_list; 

    // bool to track if range error has been thrown 
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to remove out of range and catch the error message (expected)
    try {
        empty_list.removeAt(2);
    }
    catch(const range_error &e) {
        range_error_thrown = true;
        error_message =  e.what();
    }
        // check to see if it passed
        assert(range_error_thrown);
        assert(error_message == "index (2) not in range [0..0)");
}


// test the removeAt function on a one-element list. should clear the list
void removeAt_singleton() { 

    //create an instance of a one-element linked list 
    CharLinkedList test_list('a');

    // remove the element in the list 
    test_list.removeAt(0);

    // check to see if everything's updated properly 
    assert(test_list.isEmpty());
}


// test the removeAt function on a populated list. should shorten list by 1
void removeAt_populated_middle() { 

    // create an instance of a populated linked list 
    char list[] = {'a', 'b', 'd'};
    CharLinkedList test_list(list, 3);

    //remove the middle element of the list 
    test_list.removeAt(1); 

    // check to see if everything updated properly 
    assert(test_list.size() == 2); 
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'd');
} 


// test  removeAt function on a populated list front. should shorten list by 1
// and change the front of the list 
void removeAt_populated_front() { 

    // create an instance of a populated linked list 
    char list[] = {'a', 'b', 'd'};
    CharLinkedList test_list(list, 3);

    //remove the middle element of the list 
    test_list.removeAt(0); 

    // check to see if everything updated properly 
    assert(test_list.size() == 2); 
    assert(test_list.first() == 'b');
    assert(test_list.elementAt(1) == 'd');
} 


// test the removeAt function on a populated list back. should shorten list by 1
void removeAt_populated_back() { 

    // create an instance of a populated linked list 
    char list[] = {'a', 'b', 'd'};
    CharLinkedList test_list(list, 3);

    //remove the middle element of the list 
    test_list.removeAt(2); 

    // check to see if everything updated properly 
    assert(test_list.size() == 2); 
    assert(test_list.first() == 'a');
    assert(test_list.last() == 'b');
} 


// test the removeAt function out of range on populated list. should throw error
void removeAt_populated_too_high() { 

    // create an instance of a populated linked list 
    char list[] = {'a', 'b', 'd'};
    CharLinkedList test_list(list, 3);

    // bool to track if range error has been thrown 
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to remove out of range and catch the error message (expected)
    try {
        test_list.removeAt(3);
    }
    catch(const range_error &e) {
        range_error_thrown = true;
        error_message =  e.what();
    }
        // check to see if it passed
        assert(range_error_thrown);
        assert(error_message == "index (3) not in range [0..3)");
}


// test the removeAt function on a negative index on a populated list. should 
// throw an error
void removeAt_negative() { 

    // create an instance of a populated linked list 
    char list[] = {'a', 'b', 'd'};
    CharLinkedList test_list(list, 3);

    // bool to track if range error has been thrown 
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to remove out of range and catch the error message (expected)
    try {
        test_list.removeAt(-1);
    }
    catch(const range_error &e) {
        range_error_thrown = true;
        error_message =  e.what();
    }
        // check to see if it passed
        assert(range_error_thrown);
        assert(error_message == "index (-1) not in range [0..3)");
}


// test the toReverseString function on an empty linked list
void toReverseString_empty() { 
    
    // create instance of empty linked list 
    CharLinkedList empty_list; 

    // create a string of all of the list chars in reverse order 
    std::string list = empty_list.toReverseString();

    // check to see all went well 
    assert(list == "[CharLinkedList of size 0 <<>>]");
}


// test the toReverseString function on a one-element linked list
void toReverseString_singleton() { 

    // create instance of one-element linked list 
    CharLinkedList test_list('a'); 

    // create a string of all of the list chars in reverse order 
    std::string list = test_list.toReverseString();

    // check to see all went well 
    assert(list == "[CharLinkedList of size 1 <<a>>]");
}


// test the toReverseString function on a populated linked list 
void toReverseString_populated() { 

    // create an instance of a populated linked list 
    char list[] = {'a', 'b', 'c'};
    CharLinkedList test_list(list, 3);

    // call toReverseString 
    std::string test = test_list.toReverseString();

    // check to see if the list printed backwards 
    assert(test == "[CharLinkedList of size 3 <<cba>>]"); 
}


// test the insertInOrder on an empty linked list 
void insertInOrder_empty() { 

    // create instance of empty linked list 
    CharLinkedList empty_list; 

    empty_list.insertInOrder('a');

    assert(empty_list.size() == 1); 
    assert(empty_list.first() == 'a');
    assert(empty_list.last() == 'a'); 
}


// test the insertInOrder on a one element linked list
void insertInOrder_singleton() { 

    //create instance of one-element linked list 
    CharLinkedList test_list('b');

    test_list.insertInOrder('a');

    // look to see if list printed correctly
    // std::string test = test_list.toString(); 
    // cerr << test << endl; 

    // make sure elements are in the right place 
    assert(test_list.size() == 2); 
    assert(test_list.first() == 'a'); 
    assert(test_list.last() == 'b');
} 


// test the insertInOrder on a populated linked list in the middle 
void insertInOrder_populated_middle() { 
    // create an instance of a populated linked list 
    char list[] = {'a', 'b', 'd'};
    CharLinkedList test_list(list, 3);

    test_list.insertInOrder('c'); 

    // look to see if list printed correctly
    // std::string test = test_list.toString(); 
    // cerr << test << endl; 

    // make sure elements are in the right place 
    assert(test_list.size() == 4); 
    assert(test_list.elementAt(2) == 'c'); 
}


// test the insertInOrder on populated linked list for a char equal to 
// a char already in the list 
void insertInOrder_populated_same() { 
    // create an instance of a populated linked list 
    char list[] = {'a', 'b', 'd'};
    CharLinkedList test_list(list, 3);

    test_list.insertInOrder('b'); 

    // look to see if list printed correctly
    // std::string test = test_list.toString(); 
    // cerr << test << endl; 

    // make sure elements are in the right place 
    assert(test_list.size() == 4); 
    assert(test_list.elementAt(2) == 'b'); 
}


// test the insertInOrder on a populated linked list that'll add at the end 
void insertInOrder_populated_last() { 
    // create an instance of a populated linked list 
    char list[] = {'a', 'b', 'd'};
    CharLinkedList test_list(list, 3);

    test_list.insertInOrder('z'); 

    // look to see if list printed correctly
    // std::string test = test_list.toString(); 
    // cerr << test << endl; 

    // make sure elements are in the right place 
    assert(test_list.size() == 4); 
    assert(test_list.last() == 'z'); 
}


//test the replaceAt function on a one-element linked list 
void replaceAt_singleton() { 

    // create an instance of a one-element linked list 
    CharLinkedList test_list('a');

    test_list.replaceAt('b', 0);

    assert(test_list.size() == 1);
    assert(test_list.first() == 'b');
    assert(test_list.last() == 'b');
}


// test the replaceAt function on a populated linked list (middle)
void replaceAt_populated_middle() { 
     // create an instance of a populated linked list 
    char list[] = {'a', 'b', 'd'};
    CharLinkedList test_list(list, 3);

    // replace the middle element of the list 
    test_list.replaceAt('e', 1);

    // make sure all went well 
    assert(test_list.size() == 3);
    assert(test_list.first() == 'a');
    assert(test_list.last() == 'd');
    assert(test_list.elementAt(1) == 'e');
    
}



// test the replaceAt function on a populated linked list (start)
void replaceAt_populated_start() { 
     // create an instance of a populated linked list 
    char list[] = {'a', 'b', 'd'};
    CharLinkedList test_list(list, 3);

    // replace the middle element of the list 
    test_list.replaceAt('c', 2);

    // make sure all went well 
    assert(test_list.size() == 3);
    assert(test_list.first() == 'a');
    assert(test_list.last() == 'c');
    assert(test_list.elementAt(1) == 'b');
}


// test the replaceAt function on a populated linked list (last)
void replaceAt_populated_last() { 
     // create an instance of a populated linked list 
    char list[] = {'a', 'b', 'd'};
    CharLinkedList test_list(list, 3);

    // replace the middle element of the list 
    test_list.replaceAt('e', 0);

    // make sure all went well 
    assert(test_list.size() == 3);
    assert(test_list.first() == 'e');
    assert(test_list.last() == 'd');
    assert(test_list.elementAt(1) == 'b');
}


// test the replace at function on a populated linked list. should throw error
void replaceAt_populated_toohigh() { 
    // create an instance of a populated linked list 
    char list[] = {'a', 'b', 'd'};
    CharLinkedList test_list(list, 3);

    // bool to track if range error has been thrown 
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to replace out of range and catch the error message (expected)
    try {
        test_list.replaceAt('a', -1);
    }
    catch(const range_error &e) {
        range_error_thrown = true;
        error_message =  e.what();
    }
        // check to see if it passed
        assert(range_error_thrown);
        assert(error_message == "index (-1) not in range [0..3)");
}


// test the replaceAt function on an empty linked list. should throw an error
void replaceAt_empty() { 
    // create an instance of an empty linked list 
    CharLinkedList empty_list; 

     // bool to track if range error has been thrown 
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    // try to replace out of range and catch the error message (expected)
    try {
        empty_list.replaceAt('a', 0);
    }
    catch(const range_error &e) {
        range_error_thrown = true;
        error_message =  e.what();
    }
        // check to see if it passed
        assert(range_error_thrown);
        assert(error_message == "index (0) not in range [0..0)");
}


// test concatenate on an empty linked list with an empty linked
void concatenate_two_empty() { 
    // create two empty linked lists 
    CharLinkedList list1; 
    CharLinkedList list2; 

    list1.concatenate(&list2); 

    // make sure everything stayed empty 
    assert(list1.isEmpty()); 
}


// test concatenate on two populated lists 
void concatenate_two_populated() { 
    // create two instances of populated linked lists
    char list[] = {'a', 'b', 'd'};
    char abc[] = {'a', 'b', 'c'};
    CharLinkedList list1(list, 3);
    CharLinkedList list2(abc, 3); 

    // concatenate them
    list1.concatenate(&list2); 

    // check to see if list 2 was concatenated onto list 1 and list 1's elements
    // were properly updated 
    assert(list1.size() == 6);
    assert(list1.first() == 'a');
    assert(list1.last() == 'c'); 
    assert(list1.elementAt(3) == 'a');
}


// test concatenate for an empty list onto a populated list
void concatenate_empty_populated() { 
    // create instance of empty and populated linked lists 
    CharLinkedList empty_list; 
    char list[] = {'a', 'b', 'd'};
    CharLinkedList test_list(list, 3);

    test_list.concatenate(&empty_list); 

    // make sure that test_list's info didn't change 
    assert(test_list.size() == 3);
    assert(test_list.first() == 'a'); 
    assert(test_list.last() == 'd');

}


// test concatenate for a populated list onto an empty list 
void concatenate_populated_empty() { 
    // create instance of empty and populated linked lists 
    CharLinkedList empty_list; 
    char list[] = {'a', 'b', 'd'};
    CharLinkedList test_list(list, 3);

    empty_list.concatenate(&test_list); 

    // make sure that the empty list now has test_list's info
    assert(empty_list.size() == 3);
    assert(empty_list.first() == 'a'); 
    assert(empty_list.last() == 'd');

}


// test concatenate on a populated list onto itself. should copy the contents 
void concatenate_populated_itself() { 
    // create instance of populated linked list. 
    char list[] = {'a', 'b', 'd'};
    CharLinkedList test_list(list, 3);

    test_list.concatenate(&test_list); 

    // make sure that the list's info was concatenated onto it's back 
    assert(test_list.size() == 6);
    assert(test_list.first() == 'a'); 
    assert(test_list.elementAt(3) == 'a');
    assert(test_list.last() == 'd');
}