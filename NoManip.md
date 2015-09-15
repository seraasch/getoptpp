The `GetOpt_pp` class can be additionally queried with two other ways, for people who doesn't like manipulators:
  * using the `getopt()` method
  * using iterators

Please note that the 'spirit' of `GetOpt_pp` is to be used as a stream, therefore to be used with manipulators.


## The `getopt()` method ##

The options can be retrieved by invoking the `getopt()` method. This method receives the same parameters as the `Option` manipulators, except that the result is returned rather than passed as a parameter.
```
     cout << ops.getopt<int>('i');
```
The `getopt()` method can receive a default value, to be returned when the option is not found.

When exceptions are not enabled, the returned value is undefined if an error occurred (i.e. invalid format, option not found, parsing error, etc.).


## Using iterators ##

You can iterate over all the command line options.
There are two iterators:
  * `short_iterator`: iterates over the short format options
  * `long_iterator`: iterates over the long format options

Both iterators implement the following interface:
  * pre-increment operator: moves to the next command line entry
  * the `option()` method: returns current option; a `char` for short\_iterator, a `std::string` for a long\_iterator
  * the `args()` method: returns a `std::vector<std::string>` const reference containing all the options for the current command line entry.

Iterators are used as any STL iterator: you obtain the first using the `GetOpt_pp::begin()` method, increment, and compare against the `GetOpt_pp::end()` method.


The following example iterates over all the long format options, showing each one and the number of arguments per option:

```
int main(int argc, char* argv[])
{
	GetOpt_pp ops(argc, argv);

	for(GetOpt_pp::long_iterator it = ops.begin(); it != ops.end(); ++it)
		std::cout << "\t" << it.option() << " has " << it.args().size() << " arguments." << std::endl;
}
```

//

Next: [Extending the Types](ExtendingTypes.md)

Back to [Table of Contents](Documentation.md)