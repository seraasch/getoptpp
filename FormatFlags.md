Format manipulators can be used as with any stream.

They can be used for, for example, changing the input base to 'hex'.

Example:

```
	GetOpt_pp ops(argc, argv);
	
	ops >> std::hex >> Option('i', "number", i);
```

In the example, the '-i' option will receive a number in hexadecimal format (i.e. 0xABC).

The format will be preserved until the next format manipulator is specified.

Therefore, in the example above, if you want to return to 'decimal' input format, you should do the `ops >> std::dec` statement.

//

Next: [Validations](Validations.md)

Back to [Table of Contents](Documentation.md)