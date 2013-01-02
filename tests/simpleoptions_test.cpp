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

#define ARGC    (sizeof(argv)/sizeof(const char*))

TEST(GetOptPPTest, just_long_option)
{
    const char* argv[] = {"test", "--name", "Hugo"};
    GetOpt_pp ops(ARGC, argv);
    string name;
    ops >> Option("name", name);
    ASSERT_EQ("Hugo", name);
}

TEST(GetOptPPTest, just_long_option_default)
{
    const char* argv[] = {"test"};
    GetOpt_pp ops(ARGC, argv);
    string name;
    ops >> Option("name", name, "world");
    ASSERT_EQ("world", name);
}

TEST(GetOptPPTest, both_options_long)
{
    const char* argv[] = {"test", "--name", "Hugo"};
    GetOpt_pp ops(ARGC, argv);
    string name;
    ops >> Option('n', "name", name);
    ASSERT_EQ("Hugo", name);
}

TEST(GetOptPPTest, both_options_short)
{
    const char* argv[] = {"test", "-n", "Hugo"};
    GetOpt_pp ops(ARGC, argv);
    string name;
    ops >> Option('n', "name", name);
    ASSERT_EQ("Hugo", name);
}

TEST(GetOptPPTest, option_not_found)
{
    const char* argv[] = {"test"};
    GetOpt_pp ops(ARGC, argv);
    ops.exceptions(ios::eofbit);
    string name;

    ASSERT_THROW(ops >> Option('n', "name", name), OptionNotFoundEx);
}

TEST(GetOptPPTest, no_manipulators)
{
    const char* argv[] = {"test", "-n", "Hugo"};
    GetOpt_pp ops(ARGC, argv);
    string name;

    ASSERT_EQ("Hugo", ops.getopt<std::string>('n', "name"));
}

TEST(GetOptPPTest, no_manipulators_option_not_found)
{
    const char* argv[] = {"test"};
    GetOpt_pp ops(ARGC, argv);
    ops.exceptions(ios::eofbit);

    ASSERT_THROW(ops.getopt<std::string>('n', "name"), OptionNotFoundEx);
}


TEST(GetOptPPTest, global_options)
{
    const char* argv[] = {"test", "arg1", "arg2"};

    GetOpt_pp ops(ARGC, argv);

    std::vector<std::string> args;
    ops >> GlobalOption(args);

    ASSERT_EQ("test", ops.app_name());

    for (std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it)
    {
        const unsigned int index = it - args.begin() + 1;
        ASSERT_EQ(argv[index], *it);
    }

}

TEST(GetOptPPTest, negative_integer)
{
    const char* argv[] = {"app", "--test", "-1", "-12"};

    GetOpt_pp ops(ARGC, argv);

    int value = 0;
    ops >> Option("test", value);

    ASSERT_EQ(-1, value);
    ASSERT_FALSE(ops >> OptionPresent('1'));
    ASSERT_FALSE(ops >> OptionPresent('2'));
}

TEST(GetOptPPTest, negative_float)
{
    const char* argv[] = {"app", "--test", "-.23"};

    GetOpt_pp ops(ARGC, argv);

    float value = 0;
    ops >> Option("test", value);

    ASSERT_EQ(float(-.23), value);
    ASSERT_FALSE(ops >> OptionPresent('2'));
    ASSERT_FALSE(ops >> OptionPresent('3'));
}

TEST(GetOptPPTest, negative_integer_as_string_token)
{
    const char* argv[] = {"app", "--test", "-1"};

    GetOpt_pp ops(ARGC, argv);

    ASSERT_TRUE(ops >> OptionPresent('1'));
}

TEST(GetOptPPTest, negative_integers_vector)
{
    const char* argv[] = {"app", "--test", "1", "-32", "4"};

    GetOpt_pp ops(ARGC, argv);

    std::vector<int> args;
    ops >> Option("test", args);

    ASSERT_EQ(3, args.size());
}

TEST(GetOptPPTest, negative_integers_as_string_tokens)
{
    const char* argv[] = {"app", "--test", "-3","-32", "4", "-1a"};

    GetOpt_pp ops(ARGC, argv);

    std::vector<string> test_args;
    ops >> Option('t', "test", test_args);
    ASSERT_EQ(3, test_args.size());
    ASSERT_TRUE(ops >> OptionPresent('1'));
    ASSERT_TRUE(ops >> OptionPresent('a'));

    ASSERT_FALSE(ops >> OptionPresent('2'));
    ASSERT_FALSE(ops >> OptionPresent('3'));
    ASSERT_FALSE(ops >> OptionPresent('4'));
}

TEST(GetOptPPTest, suboptions_good)
{
    const char* argv[] = {"app", "-x", "@ref/options_file.opt", "-y"};

    GetOpt_pp ops(ARGC, argv);

    EXPECT_TRUE(ops >> OptionPresent('x'));
    EXPECT_TRUE(ops >> OptionPresent('y'));

    int arg;
    EXPECT_TRUE(ops >> Option("first", arg));
    EXPECT_EQ(1, arg);

    EXPECT_TRUE(ops >> Option("second", arg));
    EXPECT_EQ(2, arg);

    EXPECT_TRUE(ops >> Option("third", arg));
    EXPECT_EQ(3, arg);

    EXPECT_TRUE(ops >> Option("fourth", arg));
    EXPECT_EQ(4, arg);

    EXPECT_TRUE(ops >> Option("fifth", arg));
    EXPECT_EQ(5, arg);

    EXPECT_TRUE(ops >> Option("sixth", arg));
    EXPECT_EQ(6, arg);

}

TEST(GetOptPPTest, suboptions_bad)
{
    const char* argv[] = {"app", "-x", "@inexistent.opt", "-y"};
    bool exception_thrown = false;

    try
    {
        GetOpt_pp ops(ARGC, argv);
    }
    catch (const OptionsFileNotFoundEx& e)
    {
        EXPECT_EQ("inexistent.opt", e.targetFile);
        exception_thrown = true;
    }

    EXPECT_TRUE(exception_thrown);
}

