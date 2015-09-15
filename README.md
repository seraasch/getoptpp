This is yet another C++ version of the `getopt` function, that is, for parsing command line options and environment variables.
However, unlike other versions, the design goals of this one are:

  * EASY to use
  * EASY to learn
  * mimic STL's streams
  * minimum code to type
  * smooth integration with STL types
  * Platform independant (ANSI C++)
  * EASY to extend for your own types

That is, you just construct a `GetOpt_pp` object with argc and argv, and then extract the options with the **>>** operator as an **istream** :)

Example:
We want to receive two options, one for an int (say, named `-i` and `--test1`), and another for a float (named `-f` and without long option). Results in `test1` and `test2` vars.

```
int main(int argc, char* argv[])
{
        using namespace GetOpt;
	int test1 = 10;
	float test2 = 3.14f;
		
	GetOpt_pp ops(argc, argv);
	
	ops >> Option('i', "test1", test1) >> Option('f', test2); 
	
	std::cout << test1 << "\n" << test2 << "\n";
	return 0;
}
```

See the project's [Wiki](Documentation.md) for documentation.

**Current version: 2.18**


## NEWS ##
GetOpt\_pp is now distributed with Boost 1.0 license, turning it suitable for some commercial projects and still remaining free software.


# Donations #
GetOpt\_pp is maintained at FuDePAN, an NGO/NPO for bioinformatics research. If you find GetOpt\_pp useful, please consider to donate so we can keep up the research and maintenance.

[![](https://www.paypal.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=BKPL5FYMLGXFQ&lc=AR&item_name=FuDePAN&item_number=getoptpp&currency_code=USD&bn=PP%2dDonationsBF%3abtn_donateCC_LG%2egif%3aNonHosted)

Coming in GetOpt\_pp 3.0: environment stream for inserting and extracting env vars!

_Don't miss GetOpt\_pp Episode 3!_

This project belongs to [FuDePAN](http://www.fudepan.org.ar).


---

&lt;wiki:gadget url="http://www.revolvermaps.com/gadget/rm2\_gadget.xml" height="180" width="180" &gt;