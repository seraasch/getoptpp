Extending types can be useful for two things:
  * putting all the options within a structure (so all the options are together), and
  * receiving a special type (such as a date).

There are several ways to extend support for user-defined types.

The simplest is specializing a conversion template function for your own type.

This function is called `GetOpt::convert`, and is the one that converts a string to the desired type.

By providing this specialization, you automatically enable all the features (including accepting a std::vector

<your\_type>

 of options).

An example of how to specialize this function follows. See the [Using a user-defined type](Extending.md) for the complete code.

```
namespace GetOpt
{
	template <> _Option::Result convert<Date>(const std::string& s, Date& d, std::ios::fmtflags)
	{
		_Option::Result ret = _Option::BadType;
		Date tmp;
		char slash;
		std::stringstream ss(s);
		if (ss >> tmp.month)
		{
			ss >> slash;
			if (ss >> tmp.day)
			{
				ss >> slash;
				if (ss >> tmp.year)
				{
					if (tmp.valid())
					{
						ret = _Option::OK;
						d = tmp;
					}
				}
			}
		}
		
		return ret;
	}
}
```

Please note that the function works on a temporal object (tmp). This is to preserve the design behavior that `GetOpt_pp` won't write anything to a variable if the format is invalid.

You can use the `formatflags` parameter to get the `GetOpt_pp`'s format flags and apply them to your stream, if any. (i.e. `ss.flags(flags);`).

More complex ways of extending types will come soon.

//

Next: [Parser Syntax Details](Parser.md)

Back to [Table of Contents](Documentation.md)