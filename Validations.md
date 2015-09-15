Validations are almost all automatic.
The `GetOpt_pp` class will throw an exception if the `exception()` method was called with the appropriate flags (see previous section), or returned false when casted to bool if the format was invalid.

However, you may want to check that the user didn't specify additional options you did not look for. Those options may got parsed, but you never extracted them with a manipulator, so they are still within the `GetOpt_pp` instance.

Two ways to do this: with and without exceptions.

## Checking Without exceptions ##

The `options_remain()` method comes into scene: after you extracted all the known options, you can call this method in order to see if there are other options you didn't expect.
Example:
```

   ops >> Option('i', myOption);    // OK

   if (ops.options_remain())
      cerr << "Oops! Unexpected options. Refer to help" << endl;
```


## Checking With exceptions ##

You can call the `end_of_options()` method to tell `GetOpt_pp` that you finished extracting all the options, so if there are still more options, then that's an error. This method calls the `options_remain()` method, and if it returns true, throws `TooManyOptionsEx`. Only applicable when `eofbit` was specified.
Example:
```
ops.exceptions_all();
try {
   ops >> Option('i', myOption);    // OK
   ops.end_of_options();            // you say: I'm done!
}
catch(TooManyOptionsEx)
{
   cerr << "You specified more options than those I understand\n";
}
catch(GetOptEx)
{
   cerr << "Invalid options. Try again\n";
}
```
//


Next: [Querying without Manipulators](NoManip.md)

Back to [Table of Contents](Documentation.md)