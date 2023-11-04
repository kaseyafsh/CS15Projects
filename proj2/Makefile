###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  Kasey Afshani

# this is needed to have make follow symlinks in dependency lists -- please keep
# it! (but remove this comment)
MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

## this rule builds the CalcYouLater executable 
CalcYouLater: main.o RPNCalc.o parser.o DatumStack.o Datum.o
	${CXX} ${LDFLAGS} -o CalcYouLater $^

## this rule builds the main object file
main.o: main.cpp RPNCalc.h parser.h DatumStack.h Datum.h 
	${CXX} ${LDFLAGS} -c main.cpp

## this rule builds the RPNCalc object file
RPNCalc.o: RPNCalc.cpp RPNCalc.h parser.h DatumStack.h Datum.h 
	${CXX} ${LDFLAGS} -c RPNCalc.cpp

## this rule builds the parser object file
parser.o: parser.cpp parser.h 
	${CXX} ${LDFLAGS} -c parser.cpp

## this rule builds the DatumStack object file
DatumStack.o: DatumStack.cpp DatumStack.h Datum.h
	${CXX} ${LDFLAGS} -c DatumStack.cpp

## this rule builds the unit_test object file
unit_test: unit_test_driver.o parser.o DatumStack.o Datum.o
	$(CXX) $(CXXFLAGS) $^


## Rules for building an executable from Datum+vector_example.cpp
## This is useful in seeing the behavior of Datum::toString()
Datum+vector_example.o: Datum+vector_example.cpp Datum.h

Datum+vector_example: Datum+vector_example.o Datum.o
	${CXX} ${LDFLAGS} -o $@ $^

##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^

# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
clean: 
	rm main.o parser.o DatumStack.o RPNCalc.o a.out
