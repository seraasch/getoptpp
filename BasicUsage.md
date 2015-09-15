## What `GetOpt_pp` can parse ##

`GetOpt_pp` parses the options passed to the program. Each option can have a list of arguments.
Options can be specified in two ways: with a letter (´short option format´), or with a word (´long option format´). For example:
```
    -h               // the short option format
    --help           // the long option format
```

In terms of `GetOpt_pp`, the long option format is optional, whereas the short option is always required for identifying the option.


You can do the following operations:
  * get the arguments of an option, if specified
  * just test whether an option was specified or not.

You can do such operations by using manipulators (`Option` and `OptionPresent` respectively), iterators, and more (refer to the table of content, or keep reading).

A more complete example:
> ./program **-a** 1 2 3 **-b** 4 5 6 **--word** 7 8 9
means that `program` was invoked with the option '-a' (with arguments 1 2 3), option 'b' (with arguments 4 5 6), and option '--word' (with arguments 7 8 9).
Short options can be any letter, long options can be any word, and arguments can be alphanumeric strings.

Additionally, since version 2.17, `GetOpt_pp` can process files containing options:
> ./program option1 option2 **@optionsfile** option3
By specifying a file name after the `@` character, `GetOpt_pp` opens it and parses options present in that file expanding those options as if they were specified in that place; the options file can also have another `@` file specified so it will be processed recursively.
If the file is not found, an exception of type `OptionsFileNotFoundEx` is thrown; this type contains a string member `targetFile` with the name of the file which wasn't found.
Note that the behavior when the file is not found is different respect to gcc's command line processing, in which the option becomes literal rather than faulty. Look for "@file" in the gcc's [manual](http://gcc.gnu.org/onlinedocs/gcc/Overall-Options.html) for further information.


## How to use `GetOpt_pp` ##

The `GetOpt_pp` class can be queried using the following manipulators:
  * `Option`
  * `OptionPresent`

Usage of manipulators can be done in two ways, just as any regular STL stream:
  * without exceptions
  * with exceptions (explained later)


Additionally, the `GetOpt_pp` class can be queried without using manipulators. See the [Querying without Manipulators](NoManip.md) section for more details.

Finally, the `GetOpt_pp::app_name()` method can be invoked to retrieve the name of the application (that is, the first argument passed to `main()`).


## "`Option`" Manipulator ##
The `Option` manipulator accepts the following arguments:
  1. the short option char (optional)
  1. the long option string (optional)
  1. the reference where it will store the value, on success
  1. the default value (optional)

Either one or the two short/long options can be specified (at least one of them is mandatory). The way to distinguish between short and long options, is that short options are single characters (specified with single quotes, such as `'a'`), whereas long options are strings (specified with double quotes, such as `"hello"`).

Example:
```
    int myvar1, myvar2, myvar3;
    GetOpt_pp ops(argc, argv);

    ops >> Option('t', "test", myvar);  // either -t or --test
    ops >> Option('u', myvar2);         // only -u
    ops >> Option("somthing", myvar3);  // only --something
```

The variable can have a previous value. If the operation does not succeeds (either because the format is invalid, or the option was not provided), the value of the variable is preserved.

You can check if succeeded by casting to bool, as regular streams. The same example as above would look like:
```
    int myvar;
    GetOpt_pp ops(argc, argv);

    if (ops >> Option('t', "test", myvar))
         ...
    else
         cerr << "Error in option 't'" << endl;
```


## "`GlobalOption`" Manipulator ##

_This applies to version 2.15_.
The `GlobalOption` manipulator is used to retrieve arguments which were not preceded by an option. For example, the invocation `./myprogram one two three` does not specify any option. In the example below, the list "`one two three`" would be retrieved in `args` by doing:
```
    std::vector<std::string> args;
    GetOpt_pp ops(argc, argv);
    ops >> GlobalOption(args);
```


## "`OptionPresent`" Manipulator ##

The way to check whether an option (a flag) was set or no, is using the `OptionPresent` manipulator. This manipulator never throws exceptions, and has the same signature as the `Option` manipulator (being the last argument the target bool flag).
Example
```
     bool flag;
     ops >> OptionPresent('x', flag);
```

Another way is not assigning it to a variable, but checking the >> result:
```
     if (ops >> OptionPresent('h', "help"))
         show_help();
```


//

Next: [Using Exceptions](UsingExceptions.md)

Back to [Table of Contents](Documentation.md)