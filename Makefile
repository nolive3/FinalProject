CXX=g++
CPPFLAGS=-I /usr/local/boost_1_53_0 -g -w -O0 -std=c++0x
LDFLAGS=


testo: main.o node.o graphwrappersingleton.o
	$(CXX) $(LDFLAGS) main.o node.o graphwrappersingleton.o -o testo

main.o: pointer.h main.cpp node.h graphwrappersingleton.h
node.o: pointer.h node.h graphwrappersingleton.h node.cpp
graphwrappersingleton.o: graphwrappersingleton.h graphwrappersingleton.cpp
