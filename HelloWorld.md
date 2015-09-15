The following example shows a Hello World application.
It accepts one parameter, a string, to whom say hello.
This parameter is `-n` for the short option, and `--name` for the long one.
If no option is provided, then the World is greeted.


```
#include <iostream>
#include "getopt_pp.h"

using namespace GetOpt;
using namespace std;

int main(int argc, char* argv[])
{
	string who;
	
	GetOpt_pp ops(argc, argv);
	
	ops >> Option('n', "name", who, "world" );		/* the default name is 'world' */
	
	cout << "Hello " << who << "!" << endl;
	
	return 0;
}
```