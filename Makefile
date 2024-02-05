#########################################################
#              PROJECT 4: Gerp! Makefile                #
#########################################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3


# executable rule 

gerp: main.o HashTable.o FSTree.o DirNode.o
	${CXX} ${LDFLAGS} -O2 -o gerp $^

# # This rule builds main.o
main.o: main.cpp DirNode.h FSTree.h HashTable.h
	$(CXX) $(CXXFLAGS) -c main.cpp

HashTable.o: HashTable.cpp HashTable.h DirNode.h FSTree.h
	$(CXX) $(CXXFLAGS) -c HashTable.cpp

# This rule builds FSTreeTraversal.o for phase one
# FSTreeTraversal.o: FSTreeTraversal.cpp DirNode.h FSTree.h
# 	$(CXX) $(CXXFLAGS) -c FSTreeTraversal.cpp

# This rule builds stringProcessing.o for phase 1
# stringProcessing.o: stringProcessing.cpp stringProcessing.h 
# 	$(CXX) $(CXXFLAGS) -c stringProcessing.cpp

# The below rule will be used by unit_test. 
# unit_test: unit_test_driver.o  stringProcessing.o FSTree.o \
# 		   DirNode.o
# 	$(CXX) $(CXXFLAGS) $^

# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
clean:
	rm stringProcessing.o FSTreeTraversal.o HashTable.o *~ a.out
