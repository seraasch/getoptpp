As of version 2.0, the way to query environment vars is by appending them to the long options set. More sofisticated ways will arrive in version 3, where the `Environment` streaming object will be defined, with a similar interface as the `GetOpt_pp` class.
The `Environment` class will be used to extract and insert (new) environment variables, as well as iterate over them.

The current implementation idea, is to consider the environment as an additional 'default values' source. In this way, you can transparently extract a command line option, and if it was not provided, `GetOpt_pp` will try to read it from the environment.


## Querying Environment Vars as Long Format Options ##

In order to include the environment variables as a 'default values' source, you have to add the `Include_Environment` flag to the `GetOpt_pp` constructor:

```
int main(int argc, char* argv[])
{
	std::string name;
	
	GetOpt_pp ops(argc, argv, Include_Environment);

	ops >> Option('n', "HELLO_NAME", name, "world" );		/* the default name is 'world' */
	
	std::cout << "Hello " << name << "!" << std::endl;
	
	return 0;
}
```

Then, each time you retrieve an option (either with a manipulator or the `getopt()` method), the following search sequence will take place:
  1. from the command line
  1. from the environment vars
  1. from the default value parameter, if specified

In the example above, the '-n' option is searched. If it is not found, then the "--HELLO\_NAME" option is searched in the command line. If it is neither found, then the "HELLO\_NAME" environment variable is searched. Finally, if it is not found, the "world" default value will be taken.

Note that the environment variable has to be named same as the long option.

//


Next: [Format Flags](FormatFlags.md)

Back to [Table of Contents](Documentation.md)