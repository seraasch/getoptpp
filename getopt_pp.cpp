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

#include "getopt_pp.h"

GetOpt_pp::GetOpt_pp(int argc, char* argv[])
	: _exc(std::ios_base::goodbit)
{
	OptionArgs currentArgs;
	const char* currentOpt = NULL;
	bool isShort;
	
	// parse arguments by their '-' or '--':
	for(int i=1; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			// save previous option, if any
			if (currentOpt != NULL)
			{
				if (isShort)
					_shortOps[*currentOpt] = currentArgs;
				else
					_longOps[currentOpt] = currentArgs;
				
				currentArgs.clear();
				currentOpt = NULL;
			}
			
			// now see what's next, differentiate whether it's short or long:
			if (argv[i][1] == '-' && argv[i][2] != 0)
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
			currentArgs.push_back(argv[i]);
		}
	}

	// save the last one:
	if (currentOpt != NULL)
	{
		if (isShort)
			_shortOps[*currentOpt] = currentArgs;
		else
			_longOps[currentOpt] = currentArgs;
	}
}

GetOpt_pp& GetOpt_pp::operator >> (const _Option& opt)
{
	_last = opt(_shortOps, _longOps);
	
	if (_last == _Option::OptionNotFound && (_exc & std::ios_base::eofbit ) )
		throw 1;
	else if (_last == _Option::BadType && (_exc & std::ios_base::failbit ) )
		throw 2;
		
	return *this;
}

