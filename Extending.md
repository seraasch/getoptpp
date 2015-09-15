This example accepts a date (with option 'd' or '--date').

```
struct Date
{
	unsigned int year;
	unsigned int month;
	unsigned int day;
	
	bool valid() const { return (month >= 1 && month <= 12 && day >= 1 && day <= 31); }
	Date(){}
	Date(unsigned int y, unsigned int m, unsigned int d) : year(y), month(m), day(d) {}
		

};

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

int main(int argc, char* argv[])
{
	Date date;
	const Date myBirthday(1977, 7, 31);
	
	GetOpt_pp ops(argc, argv);
	
	if (ops >> Option('d', "date", date, myBirthday))
		std::cout << "Date: " << date.month << "-" << date.day << "-" << date.year << std::endl;
	else
		std::cerr << "Invalid date. Enter mm/dd/yyyy" << std::endl;
	
	return 0;
}
```