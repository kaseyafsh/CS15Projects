/*
 *  unit_tests.h
 *  Kasey Afshani 
 *  12/1/23
 *
 *  CS 15 Proj 4: Gerp! 
 *  Use the unit testing framework to test the necessary functions for Phase 1
 *
 */


#include "stringProcessing.h"
#include <cassert>
#include <iostream>
#include <stdexcept>

using namespace std; 

// tests the stripNonAlphaNum function on a perfectly good string of lowercase 
// letters
void test_string_good_letters() { 
    std::string result = stripNonAlphaNum("hello");
    assert(result == "hello");
}


// tests the stripNonAlphaNum function on a perfectly good string of numbers
void test_string_good_nums() { 
    std::string result = stripNonAlphaNum("12345");
    assert(result == "12345");
}


// tests the stripNonAlphaNum function on a perfectly good string of uppercase 
// letters
void test_string_good_uppers() { 
    std::string result = stripNonAlphaNum("HELLO");
    assert(result == "HELLO");
}

// tests the stripNonAlphaNum function on a string of lowercase letters with non
// alpha numerical characters at the front and back
void test_string_bad_lower() { 
    std::string result = stripNonAlphaNum("<#&hello#%@*");
    assert(result == "hello");
}

// tests the stripNonAlphaNum function on a string of uppercase letters with non
// alpha numerical characters at the front and back
void test_string_bad_upper() { 
    std::string result = stripNonAlphaNum("<#&HELLO#%@*");
    assert(result == "HELLO");
}

// tests the stripNonAlphaNum function on a string of numbers with non
// alpha numerical characters at the front and back
void test_string_bad_nums() { 
    std::string result = stripNonAlphaNum("<#&12345#%@*");
    assert(result == "12345");
}

// tests the stripNonAlphaNum function on a string of uppercase letters with non
// alpha numerical characters in the middle of the good chars
void test_string_middle_upper() { 
    std::string result = stripNonAlphaNum("HEL+*3LO");
    assert(result == "HEL+*3LO");
}

// tests the stripNonAlphaNum function on a string of LOWERCASE letters with non
// alpha numerical characters in the middle of the good chars
void test_string_middle_lower() { 
    std::string result = stripNonAlphaNum("hel+*3lo");
    assert(result == "hel+*3lo");
}

// tests the stripNonAlphaNum function on a string of numbers with non
// alpha numerical characters in the middle of the good chars
void test_string_middle_nums() { 
    std::string result = stripNonAlphaNum("123+*345");
    assert(result == "123+*345");
}

// tests the stripNonAlphaNum function on a string of uppercase, lowecase, and
// nums with non alpha nums in the front, back, and middle
void test_string_all_mixed() { 
    std::string result = stripNonAlphaNum("&#^1Hp4%$#LSB&$*#");
    assert(result == "1Hp4%$#LSB");
}

// tests the stripNonAlphaNum function on a string of all non-alpha num chars
void test_string_all_bad() { 
    std::string result = stripNonAlphaNum("&#^%$#&$*#");
    assert(result == "");
}