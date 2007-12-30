/*
GetOpt_pp:	Yet another C++ version of getopt.
    Copyright (C) 2007  Daniel Gutson, FuDePAN

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    
	This file is a sample usage (and test case).
	TODO:
		* Support for arrays (of any type):
			opt >> vector<T>
		* More validations
		* Pick good exceptions types
		* Support the 'empty option' arguments
		* fill a structure at once
    
*/

#include <iostream>
#include "getopt_pp.h"

int main(int argc, char* argv[])
{
	int test1 = 10;
	float test2 = 3.14f;
	std::string test3 = "hello";
	
	try
	{	
		GetOpt_pp ops(argc, argv);
		
		ops.exceptions(std::ios::failbit | std::ios::eofbit);
		
		ops 
			>> Option('i', "test1", test1)
			>> Option('f', test2)
			>> Option('s', "string", test3);
		
		std::cout << test1 << "\n" << test2 << "\n" << test3 << "\n";
		return 0;
	}
	catch(int x)
	{
		std::cerr << "Exc: " << x << "\n";
	}
}

