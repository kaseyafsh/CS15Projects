/*
 *  RPNCalc.h
 *  Kasey Afshani
 *  10/18/23
 *
 *  CS 15 Proj 2 CalcYouLater! 
 *
 *  RPNCalc is a class that manipulates elements in a DatumStack. The 
    DatumStack it is called on starts out as empty, but will be altered by 
    RPNCalc's private functions. 
 *
 */

#ifndef RPNCALC_H
#define RPNCALC_H

#include <iostream>
#include <vector>
#include <sstream> 
#include <cstdio>

#include "Datum.h"
#include "DatumStack.h"
#include "parser.h"

class RPNCalc {

public: 

    RPNCalc();
    ~RPNCalc();
    void run();

private: 

    void push_bool(std::string command);
    void print();
    void dup();
    void drop();
    void swap();
    void quit();
    void perform_operation(std::string command);
    void comparison(std::string command);
    void exec();
    void file();
    void if_fcn();
    void query(istream &input);
    bool got_int(std::string s, int *resultp);
    void error_helper();
    void not_fcn();
    bool try_top();
    std::string bye_brackets();

    DatumStack calc; 
    bool finished = false;
}; 
#endif