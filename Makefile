#
# Makefile for C++ RBrainfuck
#
PREFIX  ?= /usr/local
BIN      = brainfuck

CXX      = g++
CXXFLAGS = -g -Wall -Wextra -std=c++11
LIBS     = -lboost_program_options
# LIBPATHS = -L/path/to/boost/program_options
SRCS     = src/main.cpp src/CppBrainfuck.cpp src/CppBrainfuck.h
OBJS     = main.o CppBrainfuck.o

.PHONY: install
brainfuck: ${BIN}

${BIN}: ${SRCS}
	${CXX} ${CXXFLAGS} -o $@ ${SRCS} ${LIBS}
clean: 
	rm -rf brainfuck *.o *~ *.dSYM

install:
	cp ${SRCS} ${DESTDIR} ${PREFIX}/lib
	install -pm 755 ${BIN} ${DESTDIR} ${PREFIX}/bin