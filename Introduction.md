Construct a `GetOpt_pp` object by passing the `argc` and `argv` params to its constructor.

The `GetOpt_pp` object will behave as an `istream`.
The data can be extracted using some manipulators, the simplest being `Option`.

```
int main(int argc, char* argv[])
{
    GetOpt_pp args(argc, argv);
    int ret;

    args >> Option('i', "long_option", ret);

    return ret;
}
```

In the example above, either the option '-i' (short form) or "--long\_option" (long form) is read from the arguments. That means that the program can be invoked in any of the following forms:
  * program -i _number_
  * program --long\_option _number_
and that number will be stored in `ret`.


**Quick Notes:**
  * All the symbols are defined within the `GetOpt` namespace. Add a `using namespace GetOpt;` for making all visible. Examples in this documentation assume that line is present.
  * Include `getopt_pp.h`, and link `getopt_pp.cpp`
> > For example: `g++ example_helloworld.cpp getopt_pp.cpp -o example_helloworld`
  * Some people don't like to link new cpp files or create libraries; if that's you, just include `getopt_pp_standalone.h` without any .cpp from only one of your source files.


//

Next: [Basic Usage](BasicUsage.md)

Back to [Table Of Contents](Documentation.md)