/*
 *  RPNCalc.cpp
 *  Kasey Afshani
 *  10/18/23
 *
 *  CS 15 Proj 2 CalcYouLater! 
 *
 *  Define behavior for the RPNCalculator based on the input provided by the 
    client. This file includes the implementation of the RPNCalc class. 
 *
 */

#include <iostream>
#include <vector>
#include <sstream> 
#include <stdexcept> 
#include <cstdio>
#include <fstream>
#include <string>

#include "Datum.h"
#include "DatumStack.h"
#include "parser.h"
#include "RPNCalc.h"

using namespace std; 

/*
 * name:      RPNCalc
 * purpose:   initialize empty RPN Calc 
 * arguments: none
 * returns:   none
 * effects:   none 
 */
RPNCalc::RPNCalc() { 
    
}

 /*
 * name:      RPNCalc Destructor
 * purpose:   recycle any memory that RPN calc uses
 * arguments: none
 * returns:   none
 * effects:   none 
 */
RPNCalc::~RPNCalc() { 

}

/*
 * name:      query
 * purpose:   call the correct function for the command inputed by the user
 * arguments: input stream of commands that the user gives
 * returns:   none
 * effects:   runs commands
 */
void RPNCalc::query(istream &input) { 
    //initialize variables
    std::string command = "";
    int ptr; 
    int c_int = 0;

    while(input >> command) { 
        if((command == "#t") or (command == "#f")) {
            push_bool(command);
        } else if(command == "not") {
            not_fcn();
        } else if(command == "print") { 
            print();
        } else if(command == "clear") { 
            calc.clear();
        } else if(command == "drop") { 
            drop();
        } else if(command == "dup") { 
            dup();
        } else if(command == "swap") { 
            swap();
        } else if(command == "quit") { 
            cerr << "Thank you for using CalcYouLater.\n"; 
            finished = true;
        } else if (got_int(command, &ptr)) { 
            Datum i(ptr);
            calc.push(i);
        } else if(command == "{") { 
                    std::string dir = parseRString(input);
                    Datum d(dir);
                    calc.push(d);
        } else if(command == "+" or command == "-" or command == "*"
                  or command == "/" or command == "mod") { 
                    perform_operation(command);
        } else if(command == "<" or command == ">" or command == ">="
                  or command == "<=" or command == "==") { 
                    comparison(command);
        } else if(command == "exec") { 
            exec();
        } else if(command == "file") { 
            file();
        } else if(command == "if") { 
            if_fcn();
        } else { 
            cerr << command << ": unimplemented\n";
        }

        if(finished) {
            return;
        }
    }
}

 /*
 * name:      not_fcn
 * purpose:   push the opposite bool than what's on the top of the stack, and 
              pop off the old bool. 
 * arguments: none
 * returns:   none
 * effects:   pushes the opposite bool on top of stack. size remains constant.
 */
void RPNCalc::not_fcn() {
    std::string error_statement = "";
    Datum f(false);
    Datum t(true);

    try {
        Datum d(calc.top());
        calc.pop();
        if(not d.getBool()) {
            calc.push(t);
        } else { 
            calc.push(f);
        }
    } catch(const runtime_error &e) { 
        error_statement = "Error: " + std::string(e.what()) + "\n"; 
        cerr << error_statement; 
        return; 
    }
}


/*
 * name:      if_fcn
 * purpose:   evaluate the third element in the stack, and based on that execute
              either the top or second RString 
 * arguments: none
 * returns:   none
 * effects:   execute either the top (false case) or second (true case) in stack
 */
void RPNCalc::if_fcn() { 
    std::string error_statement = "";
    try { 
        Datum f(calc.top());
        calc.pop();
        Datum t(calc.top());
        calc.pop();
        Datum testing(calc.top());
        calc.pop();

        if(testing.isBool()) {
            if(f.isRString() and t.isRString()) {
                if(testing.getBool()) {
                    calc.push(t);
                    exec();
                } else { 
                    calc.push(f);
                    exec();
                }
            } else { 
                cerr << "Error: expected rstring in if branch\n";
            }
        } else { 
            cerr << "Error: expected boolean in if test\n";
        }
    } catch(const runtime_error &e) { 
        error_statement = "Error: " + std::string(e.what()) + "\n";
        cerr << error_statement; 
        return; 
    }
}


/*
 * name:      bye_brackets
 * purpose:   get the contents of the top of the stack if it's an RString
 * arguments: none
 * returns:   shortened RString
 * effects:   gets rid of the opening and closing brackets of top
 */
std::string RPNCalc::bye_brackets() { 
    std::string result = calc.top().getRString();
    calc.pop();

    if(result.length() < 4) { 
        return ""; 
    }

    std::string shortened = result.substr(2, (result.length() - 4));
    return shortened; 
}

/*
 * name:      try_top
 * purpose:   see if the stack has a top
 * arguments: none
 * returns:   bool about if the top was accessed
 * effects:   throws appropriate error if the top of the stack doesn't exist
 */
bool RPNCalc::try_top() {
    std::string error_statement = "";
    try { 
        calc.top();
    } catch(const runtime_error &e) { 
        error_statement = "Error: " + std::string(e.what()) + "\n";
        cerr << error_statement; 
        return false;
    }

    return true; 
}

 /*
 * name:      file
 * purpose:   read in contents of a file (passed in as an RString) and perform
              the commands given in the file
 * arguments: none
 * returns:   none
 * effects:   pops a file name off the stack and passes that input stream into
              the query loop
 */
void RPNCalc::file() { 
    // check to see if top of stack is an rString. 
    std::string error_statement = "";

    if(not try_top()) { 
        return;
    }

    try { 
        calc.top().getRString();
    } catch(const runtime_error &e) { 
        error_statement = "Error: file operand not rstring\n";
        calc.pop();
        cerr << error_statement; 
        return; 
    }

    std::string shortened = bye_brackets();
    ifstream file;
    file.open(shortened);

    // check to see if the file opened properly
    if(not file.is_open()) { 
        cerr << "Unable to read " << shortened << endl; 
    }

    // feed file into query
    query(file);

    file.close();
}

/*
 * name:      exec
 * purpose:   perform operations listed in RString on top of the stack 
 * arguments: none
 * returns:   none
 * effects:   operates on the RString on top of the stack, pops it off, and 
              pushes the result onto the stack 
 */
void RPNCalc::exec() { 
    std::string error_statement = "";

    if(not try_top()) {
        return; 
    }

    try { 
        calc.top().getRString();
    } catch(const runtime_error &e) { 
        error_statement = "Error: cannot execute non rstring\n";
        calc.pop();
        cerr << error_statement; 
        return; 
    }

    std::string shortened = bye_brackets();
    istringstream passing(shortened);
    query(passing);
}



/*
 * name:      comparison
 * purpose:   perform comparisons on the top two elements in the stack 
 * arguments: the comparison they want to do between the top two elements
 * returns:   none
 * effects:   operates on the top two elements on the stack, pops them off, and 
              pushes bool result of the comparison on
 */
void RPNCalc::comparison(std::string command) { 
    bool result = false; 
    std::string error_statement = "";

    try { 
        Datum d(calc.top());
        calc.pop();
        Datum og(calc.top());
        calc.pop();
        int top = og.getInt();
        int bottom = d.getInt();

        if(command == ">" and top > bottom) { 
            result = true;
        } else if(command == "<" and top < bottom) { 
            result = true;
        } else if(command == "<=" and top <= bottom) {
            result = true;
        } else if(command == ">=" and top >= bottom) { 
            result = true;
        } else if(command == "==" and top == bottom) {
            result = true;
        }

        Datum r(result);
        calc.push(r);
    } catch(const runtime_error &e) { 
        error_statement = "Error: " + std::string(e.what()) + "\n";
        cerr << error_statement; 
        return; 
    }
}



/*
 * name:      perform_operation
 * purpose:   perform arithmetic operations on the top two elements in the stack
 * arguments: the operation they want to do
 * returns:   none
 * effects:   operates on the top two elements on the stack, pops them off, and 
              pushes the result of the operation on
 */
void RPNCalc::perform_operation(std::string command) { 
    int result = 0; 
    std::string error_statement = "";

    try { 
        Datum og(calc.top());
        calc.pop();
        Datum d(calc.top());
        calc.pop();
        int top = og.getInt();
        int bottom = d.getInt();

        if(command == "+") { 
            result = (top + bottom); 
        } else if(command == "-") { 
            result = (bottom - top);
        } else if(command == "*") {
            result = (top * bottom); 
        } else if(top == 0 and (command == "/" or command == "mod")) { 
            cerr << "Error: division by 0.\n";
            return; 
        } else if(command == "/") {
            result = (bottom / top);
        } else {
            result = (bottom % top);
        }
        Datum r(result);
        calc.push(r);
    } catch(const runtime_error &e) { 
        error_statement = "Error: " + std::string(e.what()) + "\n";
        cerr << error_statement; 
        return; 
    }
}



/*
 * name:      swap
 * purpose:   swap the top two elements of the stack 
 * arguments: none
 * returns:   none
 * effects:   swaps the top of the stack with the next element in the stack.
 */
void RPNCalc::swap() { 
    std::string error_statement = "";

    try { 
        Datum og(calc.top());
        calc.pop();
        Datum two(calc.top());
        calc.pop();
        calc.push(og);
        calc.push(two);
    } catch(const runtime_error &e) { 
            error_statement = "Error: " + std::string(e.what()) + "\n";
            cerr << error_statement; 
    }
}

 /*
 * name:      drop
 * purpose:   pop off the top element of the stack 
 * arguments: none
 * returns:   none
 * effects:   removes the top of the stack. size decreases by 1
 */
void RPNCalc::drop() { 
    if(try_top()) {
        calc.pop();
    }
}


 /*
 * name:      dup
 * purpose:   copy the top of the stack and push it onto the stack
 * arguments: none
 * returns:   none
 * effects:   pushes a copy of the top of the stack onto the stack. size 
              increases by 1. 
 */
void RPNCalc::dup() { 
    std::string error_statement = "";
    try { 
        Datum d(calc.top());
        calc.push(d);
    } catch(const runtime_error &e) { 
        error_statement = "Error: " + std::string(e.what()) + "\n";
        cerr << error_statement; 
        return; 
    }
}

 /*
 * name:      got_int
 * purpose:   check to see if we are looking at an int
 * arguments: string and pointer to result 
 * returns:   bool about if its an int or not
 * effects:   none
 */
bool RPNCalc::got_int(string s, int *resultp) {
        /* Holds the first non-whitespace character after the integer */
        char extra;

        return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

 /*
 * name:      run
 * purpose:   wrapper function to run the program
 * arguments: none
 * returns:   none
 * effects:   runs the program 
 */
void RPNCalc::run() { 
    query(cin);
}

 /*
 * name:      push bool
 * purpose:   push a boolean onto the stack 
 * arguments: the command given by the user 
 * returns:   none
 * effects:   pushes the bool that the user wants onto the stack 
 */
void RPNCalc::push_bool(std::string command) { 
    std::string error_statement = "";
    Datum f(false);
    Datum t(true);

    if(command == "#t") { 
        calc.push(t);
    } else if(command == "#f") { 
        calc.push(f);
    } 
}

  /*
 * name:      print
 * purpose:   print the top element of the stack as a string so the user can
              understand it
 * arguments: none
 * returns:   none
 * effects:   prints the top element of the stack. throws an error if the stack
              is empty
 */
void RPNCalc::print() { 
    std::string error_statement = "";
    try { 
        cout << calc.top().toString() << endl;
    } catch(const runtime_error &e) { 
        error_statement = "Error: " + std::string(e.what()) + "\n";
        cerr << error_statement; 
        return; 
    }
}