An example receiving either the `-h` or `--help` options, for showing usage.

```
#include <iostream>
#include "getopt_pp.h"

using namespace GetOpt;

static void show_usage();

int main(int argc, char* argv[])
{
	GetOpt_pp ops(argc, argv);
	
	if (ops >> OptionPresent('h', "help"))
                show_usage();

	return 0;
}


void show_usage()
{
    std::cout << "whatever" << endl;
}

```