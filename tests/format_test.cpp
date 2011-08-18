/*
    Copyright (C) 2011  Hugo Arregui, FuDePAN

    This file is part of GetOpt_pp.

    GetOpt_pp is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GetOpt_pp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <string>
#include <vector>
#include <iostream>
#include <mili/mili.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "getoptpp/getopt_pp.h"

using namespace GetOpt;
using namespace std;
using namespace mili;

TEST(GetOptPPFormatTest, hexa)
{
    const char* argv[] = {"test", "-i", "15"}; //15 hex
    GetOpt_pp ops(3, argv);
    int i;
    ops >> hex >> Option('i', "number", i);
    ASSERT_EQ(21, i);
}

struct Date
{
    unsigned int year;
    unsigned int month;
    unsigned int day;

    bool valid() const
    {
        return (month >= 1 && month <= 12 && day >= 1 && day <= 31);
    }
    Date() {}
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

TEST(GetOptPPFormatTest, date)
{
    const char* argv[] = {"test", "-d", "12/01/1990"}; // mm/dd/yyyy

    GetOpt_pp ops(3, argv);

    Date date;
    ops >> Option('d', "date", date);

    ASSERT_EQ(12, date.month);
    ASSERT_EQ(1, date.day);
    ASSERT_EQ(1990, date.year);
}
