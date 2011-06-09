#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <exception>

#include <getopt.h>
#include <stdlib.h>

#include "Prefixer.hpp"

void help(){
	std::cout << "Usage: prefixer [OPTION]... FILE" << std::endl ;
	std::cout << "Convert infix expression to prefix format" << std::endl << std::endl ;
	std::cout << "\t\t-r, --reduce\tReduce the expression" << std::endl ;
	std::cout << "\t\t-h, --help\tShow this dialog" << std::endl ;
}

int
main( int argc, char* argv[] )
{
	bool reduce = false ;
	//
	std::string short_options = "rh" ;
	static const struct option long_options[] =
	{
		/* These options set a flag. */
		{ "reduce", no_argument, NULL, 'r' },
		{ "help",   no_argument, NULL, 'h' },
		{ NULL,			no_argument, NULL,  0  }
	};
	//
	int opt = getopt_long( argc, argv, short_options.c_str(), long_options, NULL ) ;
	while( -1 != opt ) {
		//
		switch( opt ) {
			case 'r':
				reduce = true ;
				break ;

			case 'h':
				help() ;
				return EXIT_SUCCESS ;

			default:
				help() ;
				return EXIT_FAILURE ;
		}
		//
		opt = getopt_long( argc, argv, short_options.c_str(), long_options, NULL ) ;
	}
	//
	if( !argv[optind] ) {
		std::cerr << "ERROR: Missing file name" << std::endl ;
		help() ;
		return EXIT_FAILURE ;
	}
	//
	std::string file_name = argv[optind] ;
	std::ifstream fin( file_name.c_str() ) ;
	if( !fin.is_open() ) {
		std::cout << "Could not open " << file_name << std::endl ;
		return EXIT_FAILURE ;
	}
	//
	std::vector<std::string> infix ;
	std::string curr_var ;
	while( fin >> curr_var ) {
		infix.push_back( curr_var ) ;
	}
	//
	fin.close() ;
	if( infix.empty() ) {
		std::cout << file_name << " is empty" << std::endl ;
		return EXIT_FAILURE ;
	}
	//
	std::string prefix_exp ;
	prefixer::Prefixer my_prefixer( infix ) ;
	try {
		my_prefixer.ConvertInfixToPrefix( reduce ) ;
		prefix_exp = my_prefixer.PrintPrefixExpression() ;
	}
	catch( std::exception& e ) {
		std::cout << "ERROR converting to prefix: " << e.what() << std::endl ;
	}
	std::cout << prefix_exp << std::endl ;
	//
	return EXIT_SUCCESS ;
}

