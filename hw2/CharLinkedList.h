/*
 *  CharLinkedList.h
 *  YOUR NAME HERE
 *  DATE CREATED
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 *  This file defines public and private members of the CharLinkedList class. 
    Each new list can either start empty, with one char, or multiple, and 
    clients can use the functions below to manipulate these lists. 
 *
 */

#ifndef CHAR_LINKED_LIST_H
#define CHAR_LINKED_LIST_H

#include <string>

class CharLinkedList {

public: 
    // constructors
    CharLinkedList(); 
    CharLinkedList(char c); 
    CharLinkedList(char arr[], int size); 
    CharLinkedList(const CharLinkedList &other); 

    // destructor
    ~CharLinkedList();

    //other functions 
    CharLinkedList &operator=(const CharLinkedList &other);
    bool isEmpty() const; 
    void clear(); 
    int size() const; 
    char first() const; 
    char last() const; 
    char elementAt(int index) const; 
    std::string toString() const;  
    std::string toReverseString() const; 
    void pushAtBack(char c); 
    void pushAtFront(char c); 
    void insertAt(char c, int index); 
    void insertInOrder(char c);  
    void popFromFront(); 
    void popFromBack();  
    void removeAt(int index); 
    void replaceAt(char c, int index);   
    void concatenate(CharLinkedList *other); 

private: 

    // create the Node struct 
    struct Node { 
        char data; 
        Node *next; 
        Node *prev; 
    };

    // private member variables 
    Node *front; 
    Node *back; 
    int numItems; 

    // recursive helper functions 
    void destructor_helper(Node *next_node);
    char elementAt_helper(Node *next_node, int index) const;
    Node* replaceAt_helper(Node *next_node, int index);

};

#endif
