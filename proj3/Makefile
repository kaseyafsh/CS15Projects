#########################################################
#             PROJECT 3: ZAP! Makefile             #
#########################################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 


# executable rule 
zap: main.o phaseOne.o HuffmanTreeNode.o BinaryIO.o HuffmanCoder.o 
	${CXX} ${LDFLAGS} -o zap $^


# This rule builds main.o
main.o: main.cpp HuffmanTreeNode.h HuffmanCoder.h
	$(CXX) $(CXXFLAGS) -c main.cpp


# This rule builds phaseOne.o
phaseOne.o: phaseOne.cpp phaseOne.h HuffmanTreeNode.h BinaryIO.h
	$(CXX) $(CXXFLAGS) -c phaseOne.cpp


# This rule builds HuffmanCoder.o
HuffmanCoder.o: HuffmanCoder.cpp HuffmanCoder.h HuffmanTreeNode.h BinaryIO.h
	$(CXX) $(CXXFLAGS) -c HuffmanCoder.cpp



# The below rule will be used by unit_test. 
unit_test: unit_test_driver.o phaseOne.o HuffmanCoder.o BinaryIO.o ZapUtil.o \
			HuffmanTreeNode.o
	$(CXX) $(CXXFLAGS) $^

# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
clean: 
	rm phaseOne.o HuffmanCoder.o main.o *~ a.out
