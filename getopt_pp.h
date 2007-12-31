/*
GetOpt_pp:	Yet another C++ version of getopt.
    Copyright (C) 2007  Daniel Gutson, FuDePAN

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GETOPT_PP_H
#define GETOPT_PP_H

#include <string>
#include <vector>
#include <map>
#include <sstream>

/*
	DESIGN GOALS:
		- EASY to use
		- EASY to learn
		- mimc STL's streams
		- EASY to extend
*/

typedef std::vector<std::string> OptionArgs;
typedef std::map<std::string, OptionArgs> LongOptions;
typedef std::map<char, OptionArgs> ShortOptions;


struct _Option
{
	enum Result
	{
		OK,
		OptionNotFound,
		BadType,
		NoArgs
	};

	virtual Result operator() (const ShortOptions& short_ops, const LongOptions& long_ops) const = 0;
	virtual ~_Option(){}
};

template <class T> class _OptionTBase : public _Option
{
	const char short_opt;
	const std::string long_opt;
protected:
	T& target;
	virtual Result _assign(const OptionArgs& args) const = 0;
	
public:
	_OptionTBase(const _OptionTBase<T>& other)
		: short_opt(other.short_opt), long_opt(other.long_opt), target(other.target)
	{}
	
	_OptionTBase(char short_opt, const std::string& long_opt, T& target)
		: short_opt(short_opt), long_opt(long_opt), target(target)
	{}
	
	virtual Result operator() (const ShortOptions& short_ops, const LongOptions& long_ops) const
	{
		Result ret = OptionNotFound;
		ShortOptions::const_iterator it = short_ops.find(short_opt);
		
		if (it != short_ops.end())
			ret = _assign(it->second);
		else if (!long_opt.empty())
		{
			LongOptions::const_iterator it = long_ops.find(long_opt);
			if (it != long_ops.end())
				ret = _assign(it->second);
		}

		return ret;
	}
};

template <class T> class _OptionT : public _OptionTBase<T>
{
protected:
	virtual _Option::Result _assign(const OptionArgs& args) const
	{
		if (!args.empty())
		{
			std::stringstream ss;
			ss.clear();
			ss << args[0];
			ss >> this->target;
			//if (ss.str().empty())
				return ss.fail() ? _Option::BadType : _Option::OK;
			//else
			//	return BadType;
		}
		else
			return _Option::NoArgs;
	}
public:	
	_OptionT(const _OptionT<T>& other)
		: _OptionTBase<T>(other)
	{}
	
	_OptionT(char short_opt, const std::string& long_opt, T& target)
		: _OptionTBase<T>(short_opt, long_opt, target)
	{}

};

template <> class _OptionT<std::string> : public _OptionTBase<std::string>
{
protected:
	virtual _Option::Result _assign(const OptionArgs& args) const
	{
		if (!args.empty())
		{
			target = args[0];
			return _Option::OK;
		}
		else
			return _Option::NoArgs;
	}
	
public:	
	_OptionT(const _OptionT<std::string>& other)
		: _OptionTBase<std::string>(other)
	{}

	_OptionT(char short_opt, const std::string& long_opt, std::string& target)
		: _OptionTBase<std::string>(short_opt, long_opt, target)
	{}
};

template <class T, class BaseOption>
class _DefValOption : public BaseOption
{
	const T default_value;
public:
	
	_DefValOption(const _DefValOption<T, BaseOption>& other)
		: BaseOption(other), default_value(other.default_value)
	{}

	_DefValOption(char short_opt, const std::string& long_opt, T& target, const T& default_value)
		: BaseOption(short_opt, long_opt, target), default_value(default_value)
	{}

	virtual _Option::Result operator() (const ShortOptions& short_ops, const LongOptions& long_ops) const
	{
		_Option::Result ret = BaseOption::operator()(short_ops, long_ops);
		
		if (ret == _Option::OptionNotFound)
		{
			this->target = default_value;
			ret = _Option::OK;
		}

		return ret;
	}
};


template <class T>
inline _OptionT<T> Option(char short_opt, const std::string& long_opt, T& target)
{
	return _OptionT<T>(short_opt, long_opt, target);
}

template <class T>
inline _OptionT<T> Option(char short_opt, T& target)
{
	return _OptionT<T>(short_opt, std::string(), target);
}

// Defaulted version
template <class T>
inline _DefValOption<T, _OptionT<T> > 
Option(char short_opt, const std::string& long_opt, T& target, const T& def)
{
	return _DefValOption<T, _OptionT<T> >(short_opt, long_opt, target, def);
}

template <class T>
inline _DefValOption<T, _OptionT<T> > Option(char short_opt, T& target, const T& def)
{
	return _DefValOption<T, _OptionT<T> >(short_opt, std::string(), target, def);
}

// Defaults for strings:
inline _DefValOption<std::string, _OptionT<std::string> > 
Option(char short_opt, const std::string& long_opt, std::string& target, const char* def)
{
	return _DefValOption<std::string, _OptionT<std::string> >(short_opt, long_opt, target, def);
}

inline _OptionT<std::string> Option(char short_opt, std::string& target, const char* def)
{
	return _DefValOption<std::string, _OptionT<std::string> >(short_opt, std::string(), target, def);
}


struct OptionPresent : _Option
{
	const char short_opt;
	const std::string& long_opt;
	bool& present;
	
	OptionPresent(char short_opt, const std::string& long_opt, bool& present)
		: short_opt(short_opt), long_opt(long_opt), present(present)
	{}
	
	virtual Result operator() (const ShortOptions& short_ops, const LongOptions& long_ops) const
	{
		ShortOptions::const_iterator it = short_ops.find(short_opt);
		
		present = (it != short_ops.end());
		if (!present)
		{
			present = (long_ops.find(long_opt) != long_ops.end());
		}
		
		return OK;
	}
};

class GetOpt_pp
{
	ShortOptions _shortOps;
	LongOptions _longOps;
	std::ios_base::iostate _exc;
	_Option::Result _last;
public:
	GetOpt_pp(int argc, char* argv[]);
	
	std::ios_base::iostate exceptions ( ) const			{ return _exc; }
	void exceptions ( std::ios_base::iostate except )	{ _exc = except; }
	
	operator bool() const							{ return _last == _Option::OK;	}
	
	GetOpt_pp& operator >> (const _Option& opt);
};



#endif
