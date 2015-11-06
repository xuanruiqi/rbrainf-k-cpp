/*
 * CppBrainfuck.h
 * Copyright 2015 by Xuanrui Q. 
 * Licensed under Mozilla Public License. 
 * Available at
 * 
 *     https://www.mozilla.org/en-US/MPL/2.0/ 
 * 
 * Covered Software is provided under this License 
 * on an “as is” basis, without warranty of any kind, 
 * either expressed, implied, or statutory, including, 
 * without limitation, warranties that the Covered Software 
 * is free of defects, merchantable, fit for a particular 
 * purpose or non-infringing. No liability is assumed unless 
 * required by law or consented by writing. Refer to 
 * license for details. 
 */

#ifndef CPPBRAINFUCK_H_
#define CPPBRAINFUCK_H_

#include <iostream>
#include <cstdio>
#include <vector>
#include <exception>
#include <string>
#include <boost/lexical_cast.hpp>

typedef unsigned char byte;
using boost::lexical_cast;

struct DataPointerOutOfBoundsException: public std::runtime_error
{

	int line, col;
	std::string filename, msg;
	char cmsg[120];

	DataPointerOutOfBoundsException(int line, int col, std::string filename = "Console")
		: std::runtime_error("Data pointer out of bounds on line " + lexical_cast<std::string>(line) +
			", " + lexical_cast<std::string>(col))
	{
		this->line = line;
		this->col = col;
		this->filename = filename;
		msg = filename + ", line " + lexical_cast<std::string>(line) + ": DataPointerOutOfBoundsError" + 
			": data pointer out of bound";
		msg.copy(cmsg, msg.size(), 0);
	}

	const char* what() const noexcept
	{
		return cmsg;
	}
};

class CppBrainfuck
{

public:
	CppBrainfuck(std::vector<char> &prog, int size, bool verb);
	~CppBrainfuck();
	void interpret(); // interpret a program from an istream

private:
	
	byte* data; // the data that the program operates on
	int data_size; // the size of data
	byte* data_ptr; // pointer to current data slot
	std::vector<char> program;
	std::vector<char>::iterator command; // pointer to the current command being executed
	int line; // current line number
	int col; // current column number
	bool verbose; // if engine is in verbose mode
	void execute_command();


};

#endif /* CPPBRAINFUCK_H_ */