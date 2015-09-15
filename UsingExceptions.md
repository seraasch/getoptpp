The `GetOpt_pp` class provides the `exceptions()` methods (a setter and a getter), same as STL streams.
In order to enable exception throwing, invoke `exceptions(flags)` with the proper flags:
  * `ios::failbit` will throw an exception due to invalid format (i.e. expected int received string).
  * `ios::eofbit` will throw an exception when: the option was not present (and no default value was specified), or there was no argument.

If you want to enable all the options at once, then just call the `exceptions_all()` method instead.

All the exceptions derive from `GetOptEx`, which in turns derives from `std::exception`.
These exceptions are:
  * `ParsingErrorEx`
  * `InvalidFormatEx`
  * `ArgumentNotFoundEx`
  * `TooManyArgumentsEx`
  * `OptionNotFoundEx`
  * `TooManyOptionsEx`  (only thrown by `end_of_options()` method)

//

Next: [Querying the Environment Vars](Envir.md)

Back to [Table of Contents](Documentation.md)