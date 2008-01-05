/*
GetOpt_pp:	Yet another C++ version of getopt.
    Copyright (C) 2007  Daniel Gutson, FuDePAN

    This file is part of GetOpt_pp.
    
    GetOpt_pp is free software: you can redistribute it and/or modify
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

#include "getopt_pp.h"

namespace GetOpt {

GetOpt_pp::GetOpt_pp(int argc, char* argv[])
	: _exc(std::ios_base::goodbit)
{
	OptionData currentData;
	const char* currentOpt = NULL;
	bool isShort;
	
	// parse arguments by their '-' or '--':
	for(int i=1; i < argc; i++)
	{
		const char current = argv[i][0];
		const char next = argv[i][1];
		
		if (current == '-' && (isalpha(next) || next == '-' ) )
		{
			// save previous option, if any
			if (currentOpt != NULL)
			{
				if (isShort)
					_shortOps[*currentOpt] = currentData;
				else
					_longOps[currentOpt] = currentData;
				
				currentData.clear();
				currentOpt = NULL;
			}
			
			// now see what's next, differentiate whether it's short or long:
			if (next == '-' && argv[i][2] != 0)
			{
				currentOpt = &argv[i][2];
				isShort = false;
			}
			else
			{
				currentOpt = &argv[i][1];
				isShort = true;
			}
		}
		else
		{
			// save value!
			currentData.args.push_back(argv[i]);
		}
	}

	// save the last one:
	if (currentOpt != NULL)
	{
		if (isShort)
			_shortOps[*currentOpt] = currentData;
		else
			_longOps[currentOpt] = currentData;
	}
	
	_last = _Option::OK;	// TODO: IMPROVE!!
}

GetOpt_pp& GetOpt_pp::operator >> (const _Option& opt) throw (GetOptEx)
{
	if (_last != _Option::ParsingError)
	{
		_last = opt(_shortOps, _longOps);
		
		switch(_last)
		{
			case _Option::OK: 
				break;
				
			case _Option::OptionNotFound:
				if (_exc & std::ios_base::eofbit )
					throw OptionNotFoundEx();
				break;
				
			case _Option::BadType:
				if (_exc & std::ios_base::failbit )
					throw InvalidFormatEx();
				break;
				
			case _Option::NoArgs:
				if (_exc & std::ios_base::eofbit )
					throw ArgumentNotFoundEx();
				break;
				
			case _Option::TooManyArgs:
				if (_exc & std::ios_base::failbit )
					throw TooManyArgumentsEx();
				break;
				
			case _Option::ParsingError: break;	// just to disable warning
		}
	}
	else if (_exc & std::ios_base::failbit )
		throw ParsingErrorEx();
		
	return *this;
}

bool GetOpt_pp::options_remain() const
{
	bool remain = false;
	ShortOptions::const_iterator it = _shortOps.begin();
	while (it != _shortOps.end() && !remain)
	{
		remain = (it->second.extracted == false);
		++it;
	}
	
	if (!remain)
	{
		LongOptions::const_iterator it = _longOps.begin();
		while (it != _longOps.end() && !remain)
		{
			remain = (it->second.extracted == false);
			++it;
		}
	}
	
	return remain;
}

}
