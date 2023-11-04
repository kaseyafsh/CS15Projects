/*
 *  CharLinkedList.cpp
 *  Kasey Afshani
 *  9/20/23
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 *  Define functions for the CharLinkedList class, which will allow the clinet 
    to manipulate a list. They can add, delete, swap, and perform other 
    operations on their list.  
 *
 */

#include "CharLinkedList.h"
#include <sstream> 
#include <iostream>
#include <stdexcept>

using namespace std; 

/*
 * name:      CharLinkedList default constructor
 * purpose:   initialize an empty linked list
 * arguments: none
 * returns:   none
 * effects:   creates an empty node  
 */
CharLinkedList::CharLinkedList() {
    Node *new_node = nullptr; 
    numItems = 0; 
    front = nullptr; 
    back = nullptr; 
}

/*
 * name:      CharLinkedList constructor 2
 * purpose:   initialize a linked list with one char 
 * arguments: the character we want to use in our linked list 
 * returns:   none
 * effects:   creates a single node  
 */
CharLinkedList::CharLinkedList(char c) {
    
    // create a new node 
    Node *new_node = new Node; 
    new_node->data = c; 
    new_node->next = nullptr; 
    new_node->prev = nullptr; 

    // update private member variables 
    front = new_node; 
    back = new_node;
    numItems = 1; 
}


/*
 * name:      CharLinkedList constructor 3
 * purpose:   create a linked list from a given array 
 * arguments: the array of characters we want to put into our linked list
 * returns:   none
 * effects:   creates a populated linked list 
 */
CharLinkedList::CharLinkedList(char arr[], int size) {

    numItems = size; 

    // create a new node and set its data to the first element in the list 
    Node *prev_node = nullptr;


    // iterate through the array and set nodes in the linked list to array chars
    for(int i = 0; i < size; i++) {
        Node *curr_node = new Node; 
        curr_node->data = arr[i];
        curr_node->prev = prev_node; 
        curr_node->next = nullptr; 
        if(prev_node != nullptr) {
             prev_node->next = curr_node; 
        }
        back = curr_node; 
        prev_node = curr_node;

        // set the front of the list 
        if(i == 0) { 
            front = curr_node; 
        }
        
    }
}

/*
 * name:      CharLinkedList copy constructor 
 * purpose:   create a linked list by copying an existing linked list 
 * arguments: the list of characters we want to put into our linked list
 * returns:   none
 * effects:   creates a populated linked list identical to our argument
 */
CharLinkedList::CharLinkedList(const CharLinkedList &other) {

    // initialize everything 
        front = nullptr; 
        back = nullptr; 
        numItems = 0; 
 
    // create a node with the char at each index of the other list and use it 
    // to create a new linked list
    for(int i = 0; i < other.size(); i++) {
        char l = other.elementAt(i);
        pushAtBack(l);
    }
} 


/*
 * ~CharLinkedList
 *    Purpose: delete all the nodes in the tree 
 * Parameters: None 
 *    Returns: None
 */
 CharLinkedList::~CharLinkedList() { 

    // check to see if the list is empty 
    if(numItems == 0) { 
        return; 
    } else { 
        // delete the nodes and reset numItems 
        destructor_helper(front);
        numItems = 0; 
    }

    
 }


/*
 * destructor_helper
 *    Purpose: help the destructor delete all the nodes in the linked list 
 * Parameters: The front node 
 *    Returns: None
 */
 void CharLinkedList::destructor_helper(Node *curr_node) { 

    // base case: front of list is nullptr 
    if(curr_node == nullptr) { 
        return;
    }
    else { 
        // set the current node to the next node 
        Node *next_node = curr_node->next; 

        // repeat 
        destructor_helper(next_node);

        // delete the current node 
        delete curr_node; 
    }

 }

 /*
 * name:      reassignment operator 
 * purpose:   Define an assignment operator for the class that recycles the 
              storage associated with the instance on the left of the assignment
              and makes a deep copy of the instance on the right hand side into
              the instance on the left hand side.
 * arguments: the address of the other list we want to manipulate 
 * returns:   pointer to the linked list 
 * effects:   reassigns the = operator 
 */
CharLinkedList &CharLinkedList::operator=(const CharLinkedList &other) {        
    // check to see if the two linked lists are equal to each other 
    if (this == &other) { 
        return *this;
    }

    // recycle memory for left hand side
    destructor_helper(this->front);
    front = nullptr; 
    numItems = 0; 

    int tracker = other.size();
    // create a node with the char at each index of the other list and use it 
    // to create a new linked list
    for(int i = 0; i < tracker; i++ ) {
        char l = other.elementAt(i);
        this->pushAtBack(l);
    }
    return *this; 
} 

/*
 * pushAtFront
 *    Purpose: Adds a node to the front of the list
 * Parameters: The data of the node we want to add to the list
 *    Returns: None
 */
void CharLinkedList::pushAtFront(char c) {

    // create a new node 
    Node *new_node = new Node; 
    new_node->data = c; 
    new_node->prev = nullptr; 


    // check to see if there is anything already in the list 
    if(front == nullptr) { 
        front = new_node; 
        back = new_node; 
        new_node->next = nullptr; 

    } else { 

        // set the new node's previous to the current front 
        new_node->prev = front; 

        // set the current front to the new node's next
        new_node->next = front; 

        // reassign front to be the new node 
        front = new_node; 
    } 

    // increase size of list 
    numItems ++; 
}


/*
 * pushAtBack
 *    Purpose: Adds a node to the end of the list
 * Parameters: The data of the node we want to add to the list
 *    Returns: None
 */
 void CharLinkedList::pushAtBack(char c) { 
    // create a new node 
    Node *new_node = new Node; 
    new_node->data = c; 


    // check to see if there is anything already in the list 
    if(front == nullptr) { 
        // create a one-element linked list 
        front = new_node; 
        back = new_node; 
        new_node->next = nullptr; 
        new_node->prev = nullptr; 

    } else {
        // point back to the current end and vice versa to add node to the end
        new_node->prev = back; 
        back->next = new_node; 
        new_node->next = nullptr; 
        back = new_node; 
    }
    // increment numItems
    numItems++; 
 }



/*
 * name:      first
 * purpose:   find the first element of a linked list 
 * arguments: none
 * returns:   the char of the first node in the linked list 
 * effects:   none 
 */
char CharLinkedList::first() const { 
    if(numItems == 0) {
        throw std::runtime_error("cannot get first of empty LinkedList"); 
    }
    return front->data; 
}

// /*
//  * name:      last
//  * purpose:   find the last element of a linked list 
//  * arguments: none
//  * returns:   the char of the last node in the linked list 
//  * effects:   none 
//  */
char CharLinkedList::last() const { 
    if(numItems == 0) {
        throw std::runtime_error("cannot get last of empty LinkedList"); 
    }
    return back->data; 
}

/*
 * name:      size
 * purpose:   find the number of nodes in a linked list 
 * arguments: none
 * returns:   the number of nodes in the linked list 
 * effects:   none 
 */
int CharLinkedList::size() const { 
    return numItems; 
}

/*
 * name:      isEmpty
 * purpose:   check to see if the linked list is empty 
 * arguments: none
 * returns:   bool about whether or not the list is is empty
 * effects:   none 
 */
 bool CharLinkedList::isEmpty() const { 
    if(numItems == 0) { 
        return true; 
    } else{ 
        return false; 
    }
 }

/*
 * name:      elementAt
 * purpose:   find the character at the indicated index
 * arguments: index 
 * returns:   character at that index 
 * effects:   none 
 */
char CharLinkedList::elementAt(int index) const { 

    // check to see if index is in range 
    if(index >= 0 and index < numItems) { 
        char letter = elementAt_helper(front, index);
        return letter; 
    } else { 
    throw std::range_error("index (" + to_string(index) +
                            ") not in range [0.." + to_string(numItems)
                            + ")");

    }
}

/*
 * name:      elementAt_helper 
 * purpose:   run through the list to find the char at the index
 * arguments: pointer to the node we're starting at 
 * returns:   char at the index we want  
 * effects:   none 
 */
 char CharLinkedList::elementAt_helper(Node *next_node, int index) const { 

    Node *curr_node = next_node; 

    if(index == 0) { 
        // base case
        return curr_node->data; 
    } else { 
        // set the current node to the next node 
        curr_node = curr_node->next; 
        // decrement tracker 
        index --; 

        // rerun the function until we reach the base case 
        char info = elementAt_helper(curr_node, index);
        return info; 
    }
 }

/*
 * name:      popFromFront 
 * purpose:   remove the first element from the linked list 
 * arguments: none 
 * returns:   none 
 * effects:   reassigns front to a new node and deletes the original front  
 */
void CharLinkedList::popFromFront() { 
    if(numItems != 0 and numItems != 1) { 

        Node *curr_node = front; 

        // set curr node to the next node in the list 
        curr_node = curr_node->next; 

        // set the next node to front 
        front = curr_node; 

        // delete the old front 
        delete curr_node->prev; 

        // set the new front's prev equal to nullptr
        curr_node->prev = nullptr; 
    
        // decrement numItems 
        numItems--; 

    } else if(numItems == 1) {
        // delete node and update pointers 
        Node *curr_node = front; 
        front = nullptr; 
        back = nullptr; 
        delete curr_node; 
        numItems--;
    } else { 
        throw std::runtime_error("cannot pop from empty LinkedList");
    } 
}


/*
 * name:      popFromBack
 * purpose:   remove the last element from the linked list 
 * arguments: none 
 * returns:   none 
 * effects:   reassigns last to a new node and deletes the original back  
 */
void CharLinkedList::popFromBack() { 
    if(numItems != 0 and numItems != 1) { 

        Node *curr_node = back; 

        // set curr node to the prev node in the list 
        curr_node = curr_node->prev; 

        // set the next node to back 
        back = curr_node; 

        // delete the old back 
        delete curr_node->next; 

        // set the new front's next equal to nullptr
        curr_node->next = nullptr; 
    
        // decrement numItems 
        numItems--; 

    } else if(numItems == 1) {
        // delete node and update pointers 
        Node *curr_node = front; 
        front = nullptr; 
        back = nullptr; 
        delete curr_node; 
        numItems--;
    } else { 
        throw std::runtime_error("cannot pop from empty LinkedList");
    } 
}

/*
 * name:      toString
 * purpose:   print all the elements of the list as a string 
 * arguments: none 
 * returns:   a string of all the elements  
 * effects:   none
 */
std::string CharLinkedList::toString() const { 
    std::string concat = "";
    std::string statement = "";
    if(not isEmpty()) { 
        Node *curr_node = front; 
        while(curr_node != nullptr) { 
            concat += curr_node->data;
            curr_node = curr_node->next; 
        }
        statement = "[CharLinkedList of size " + to_string(numItems) + 
        " <<" + concat + ">>]";
        delete curr_node; 
        return statement; 
    } else { 
        return "[CharLinkedList of size 0 <<>>]"; 
    }
}


/*
 * name:      toReverseString
 * purpose:   print all the elements of the list as a string in reverse
 * arguments: none 
 * returns:   a string of all the elements in reverse 
 * effects:   none
 */
std::string CharLinkedList::toReverseString() const { 
    std::string rev_concat = "";
    std::string statement = "";
    if(not isEmpty()) { 
        // start from the back of the list and iterate through to get all chars
        Node *curr_node = back; 
        while(curr_node != nullptr) { 
            rev_concat += curr_node->data;
            curr_node = curr_node->prev; 
        }
        statement = "[CharLinkedList of size " + to_string(numItems) + 
        " <<" + rev_concat + ">>]";
        delete curr_node; 
        return statement; 
    } else { 
        return "[CharLinkedList of size 0 <<>>]"; 
    }
}


/*
 * name:      insertAt
 * purpose:   insert a char at the desired index in the list
 * arguments: the char we want to insert, index we want to insert at 
 * returns:   none 
 * effects:   adds a char to the list 
 */
void CharLinkedList::insertAt(char c, int index) { 
    if(index == 0) { 
        pushAtFront(c);
    } else if(index == numItems) { 
        pushAtBack(c);
    } else if(index > 0 and index < numItems) {
        // make a new node 
        Node *new_node = new Node; 
        new_node->data = c; 

        // iterate through the list to find the node we want to insert at 
        Node *curr_node = front; 
        for(int i = 0; i < index; i++) { 
            curr_node = curr_node->next; 
            i++; 
        }
        // set node to the next node in the list to keep track 
        Node *second_node = curr_node->next; 
        // set the next node of the new node to the old node's next
        new_node->next = second_node; 
        // set the prev node of the new node to the curr node
        new_node->prev = curr_node;  
        // set the curr node's next to the new node 
        curr_node->next = new_node; 
        // increment numItems 
        numItems++; 
    } else { 
        throw std::range_error("index (" + to_string(index) +
                               ") not in range [0.." + to_string(numItems)
                                + "]");
    }
}


 /*
 * name:      insertInOrder 
 * purpose:   insert a char into the correct alphabetical order in list 
 * arguments: char we want to insert 
 * returns:   none
 * effects:   adds char to linked list  
 */
 void CharLinkedList::insertInOrder(char c) {
    if(isEmpty()) { 
        pushAtFront(c);
        return; 
    }
    if(front->data >= c) { 
        pushAtFront(c);
    } else if (back->data <= c) { 
        pushAtBack(c);
    } else {
        // iterate through the list to find the index we want to insert at
        Node *curr_node = front; 
        int tracker = 0; 
        while(c >= curr_node->data) {
            curr_node = curr_node->next;
            tracker++; 
        }
        // insert the char at the right index 
        insertAt(c, tracker);  
    } 
 }



/*
 * name:      clear
 * purpose:   clear the linked list 
 * arguments: none
 * returns:   none 
 * effects:   clears the list 
 */
void CharLinkedList::clear() { 
    if(not isEmpty()) {
        // delete the list 
        destructor_helper(front);
    }
    // reset private member variables 
    front = nullptr; 
    back = nullptr; 
    numItems = 0; 
}

/*
 * name:      removeAt
 * purpose:   remove a specific char in the linked list 
 * arguments: index of char we want to remove 
 * returns:   none 
 * effects:   shortens the list by one after removing one node 
 */
 void CharLinkedList::removeAt(int index) { 
    if(index == 0 and not isEmpty()) { 
        popFromFront();
    } else if(index == numItems - 1 and not isEmpty()) { 
        popFromBack();
    } else if(index > 0 and index < (numItems - 1) and not isEmpty()) { 
        // find the node we want to delete 
        Node *next_node = replaceAt_helper(front, index);
        // set a node to be that node's next
        Node *curr_node = next_node->next; 
        // set curr node to the removing node's prev's next 
        next_node->prev->next = curr_node; 
        // set curr node's prev to the removing node's prev
        curr_node->prev = next_node->prev; 
        delete next_node; 
        numItems --; 

    } else { 
         throw std::range_error("index (" + to_string(index) +
                               ") not in range [0.." + to_string(numItems)
                                + ")");
    }
 }


/*
 * name:      concatenate
 * purpose:   add a copy of a second linked list to the back of the first
              linked list 
 * arguments: the pointer to the other linked list  
 * returns:   none
 * effects:   adds the chars from the second linked list to back of the first
 */
void CharLinkedList::concatenate(CharLinkedList *other) { 
    // create variable for size 
    int counter = other->size();
  
    // add a new node with the other's char to the back of our list 
    for(int i = 0; i < counter; i++) { 
        pushAtBack(other->elementAt(i));
    }

}



 /*
 * name:      replaceAt
 * purpose:   replace a specific char in the linked list with a new char
 * arguments: index of char we want to replace and the char we want to insert 
 * returns:   none 
 * effects:   changes one char in the linked list 
 */
 void CharLinkedList::replaceAt(char c, int index) { 
    
    //check to see if index is in range 
    if(index >= 0 and index < numItems) { 
        Node *replacing = replaceAt_helper(front, index);
        replacing->data = c; 
        
    } else { 
    throw std::range_error("index (" + to_string(index) +
                            ") not in range [0.." + to_string(numItems)
                            + ")");

    }
 }

/*
 * name:      replaceAt_helper
 * purpose:   find the node at the index we want to change a char at 
 * arguments: index of char we want to replace and the front of the list 
 * returns:   the node at the index who's letter we want to replace 
 * effects:   none
 */
 CharLinkedList::Node* CharLinkedList::replaceAt_helper(Node *next_node, 
                                                       int index) {
    Node *curr_node = next_node; 

    if(index == 0) { 
        // base case
        return curr_node; 
    } else { 
        // set the current node to the next node 
        curr_node = curr_node->next; 
        // decrement tracker 
        index --; 

        // rerun the function until we reach the base case 
        Node *found = replaceAt_helper(curr_node, index);
        return found; 
    }
 }


