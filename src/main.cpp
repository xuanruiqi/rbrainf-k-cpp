/*
 * main.cpp
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
#include <fstream>
#include <vector>
#include <string>
#include <boost/program_options.hpp>

namespace options = boost::program_options;


std::vector<char> read_program(std::string filename)
{
	std::ifstream file(filename, std::ios::binary);
	std::vector<char> read_prog;
	char c;
	while(file.get(c))
		read_prog.push_back(c);
	file.close();
	return read_prog;
}

std::vector<char> read_program_cin()
{
	std::vector<char> read_prog;
	char c;
	while(std::cin.get(c))
		read_prog.push_back(c);
	return read_prog;
}

int main(int argc, char* argv[])
{
	// messy command line argument processing stuff
	// ignore if you don't care about command line arguments
	int data_size;
	bool verbose = 0;
	std::string in_file;
	options::options_description desc("Options: ");
	desc.add_options()
		("data-size,s", options::value<int>(&data_size)->default_value(1024), "Set data array size. Default value is 1024 bytes.")
		("help,h", "Display this message")
		("version", "Display version information")
		("verbose,v", "Output more messages");

	options::options_description hidden("Hidden options");
	hidden.add_options()("input-file", 	options::value<std::string>(&in_file)->default_value(""), "input file");

	options::options_description all("All options");
	all.add(desc).add(hidden);

	options::positional_options_description p;
	p.add("input-file", 1);

	options::variables_map vm;
	options::store(options::command_line_parser(argc, argv).options(all) 
			.positional(p).run(), vm);
	options::notify(vm);

	if(vm.count("help"))
	{
		std::cout << desc << std::endl;
		return 0;
	}

	if(vm.count("version"))
	{
		std::cout << "RBrainf**k, an interpreter for Brainfuck, " << 
			"written in C++11" << std::endl;
		std::cout << "Copyright 2015 by xuanruiqi" << std::endl;
		return 0;
	}

	if(vm.count("verbose")) verbose = 1;

	if(in_file == "") std::cout << "RBrainf**k 0.0 Alpha" << std::endl;

	if(verbose) std::cout << "Maximum data size: " << data_size << std::endl;

	std::vector<char> program;
	if(in_file != "") program = read_program(in_file);
	else program = read_program_cin();

	if(verbose && in_file != "")
	{
		std::cout << "Interpreting: " << in_file << std::endl;
	}

	CppBrainfuck interpreter(program, data_size, verbose);
	interpreter.interpret();

	if(verbose) std::cout << "Program terminated with exit status 0" << std::endl;
	return 0;
}