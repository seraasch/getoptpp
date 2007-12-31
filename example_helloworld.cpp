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


    Example of a Hello World.    
    
*/

#include <iostream>
#include "getopt_pp.h"

int main(int argc, char* argv[])
{
	std::string name;
	
	GetOpt_pp ops(argc, argv);
	
	ops >> Option('n', "name", name, "world" );
	
	std::cout << "Hello " << name << "!" << std::endl;
	
	return 0;
}

