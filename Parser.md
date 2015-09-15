`GetOpt_pp` parses a sequence of entries.
Each entry has an option, and a list of arguments.
Options can be specified in a short format, or a long format.

  * Short format: each option is represented by a character.
  * Long format: each option is represented by a word (seq. of characters).

Many short options can be specified in the same entry. If the entry contains arguments, they are considered to belong to the last character. For example:
```
  -abc 1 2 3 4
```
is equivalent to
```
  -a -b -c 1 2 3 4
```
which means, option 'a' has no arguments, option 'b' has no arguments neither, and option 'c' has the list 1 2 3 4 as its arguments.


If a list of entries is specified at the beginning without specifying an option, then they are considered to belong to the EMPTY\_OPTION short option. For example:
```
  one two three -a
```
will generate the EMPTY\_OPTION entry, having 'one two three' as its list of arguments, plus the 'a' option. Refer to the [Basic Usage](BasicUsage.md) for further details on this.


You can compile and play with the `example_iterators.cpp` example just to experiment how the parser behaves.

//

Next: [Examples](Examples.md)

Back to [Table of Contents](Documentation.md)