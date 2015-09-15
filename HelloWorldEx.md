The following example shows a Hello World application, similar to the previous one, but includes exception handling.
It accepts one parameter, a string, to whom say hello.
This parameter is `-n` for the short option, and `--name` for the long one.
If no option is provided, then the World is greeted.
However, if some error occurs (i.e. the option is specified without an argument), an exception is thrown.


```
#include <iostream>
#include "getopt_pp.h"

using namespace GetOpt;
using namespace std;

int main(int argc, char* argv[])
{
	std::string name;
	int ret;
	
	GetOpt_pp ops(argc, argv);
	
	ops.exceptions(std::ios::failbit | std::ios::eofbit);
	
	try
	{
		ops >> Option('n', "name", name, "world" );		/* the default name is 'world' */
	
		std::cout << "Hello " << name << "!" << std::endl;
		ret = 0;
	}
	catch(GetOpt::GetOptEx ex)
	{
		std::cerr << "Error in arguments" << std::endl;
		ret = -1;
	}
	
	return ret;
}

```