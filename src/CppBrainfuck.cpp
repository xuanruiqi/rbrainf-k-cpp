/*
 * CppBrainfuck.cpp
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

#include "CppBrainfuck.h"
#include <iostream>
#include <exception>
#include <stack>

CppBrainfuck::CppBrainfuck(std::vector<char> &prog, int size, bool verb = 0)
{
	data_size = size;

	data = new byte[data_size];
	for(int i = 0; i < data_size; ++i) 
		data[i] = 0;

	data_ptr = data;

	program = prog;
	command = program.begin();

	line = 1;
	col = 0;

	verbose = verb;
}

// constructor
CppBrainfuck::~CppBrainfuck()
{
	delete [] data;
	data = nullptr;
	data_ptr = nullptr;
}

void CppBrainfuck::interpret()
{
	while(command < program.end()) execute_command();
}

void CppBrainfuck::execute_command()
{
	col++;
	switch(*command)
	{
		case '>' :
			try
			{
				if(data_ptr - data >= data_size) 
					throw DataPointerOutOfBoundsException(line, col);
			}
			catch(DataPointerOutOfBoundsException &e)
			{
				std::cerr << e.what() << std::endl;
				if(verbose)
				{
					std::cerr << "Program terminated with exit status 1: error"
						<< std::endl;
				}
				exit(1);
			}
			data_ptr++;
			break;
		case '<' :
			try
			{
				if(data_ptr - data <= 0) 
					throw DataPointerOutOfBoundsException(line, col);
			}
			catch(DataPointerOutOfBoundsException &e)
			{
				std::cerr << e.what() << std::endl;
				if(verbose)
				{
					std::cerr << "Program terminated with exit status 1: error"
						<< std::endl;
				}
				exit(1);
			}
			data_ptr--;
			break;
		case '+' :
			(*data_ptr)++;
			break;
		case '-' :
			(*data_ptr)--;
			break;
		case '.' :
			std::cout << *data_ptr;
			break;
		case ',' :
			{
				std::cin.clear();
				char tmp = 0;
				std::cin >> reinterpret_cast<byte&>(tmp);
				*data_ptr = tmp;
				break;
			}
		case '[' :
			if (*data_ptr == 0)
			{   // find pairing ]
				std::stack<char> brackets;
				brackets.push(*command);
				while (!brackets.empty())
				{
					command++;
					if (*command == '[') brackets.push(*command);
					else if (*command == ']') brackets.pop();
				}
			}
			break;
		case ']' :
			{
				// find pairing [
				std::stack<char> brackets;
				brackets.push(*command);
				while (!brackets.empty())
				{
					command--;
					if (*command == ']') brackets.push(*command);
					else if (*command == '[') brackets.pop();
				}
				command--;
				break;
			}
		case '\n':
			line++;
			col = 1;
			break;
		default:
			break;
	}
	command++;
}