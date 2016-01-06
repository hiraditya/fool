#ifndef UTILS_TEST_HPP
#define UTILS_TEST_HPP


/*
 *  @author Aditya Kumar 
 *
 *  This file is distributed under the MIT License. See 
 *  LICENCE.txt attached with this project or visit
 *  http://www.opensource.org/licenses/mit-license.php 
 *  for terms and conditions.
 */

//
// Basic testing utility inspired from rapidxml/test/test_util.hpp
// sourceforge.net/projects/rapidxml/files/rapidxml/rapidxml%201.13/rapidxml-1.13-with-tests.zip/download
//

#include <iostream>
#include <cstdlib>

class test
{

public:

    static int &pass()
    {
        static int n;
        return n;
    }

    static int &fail()
    {
        static int n;
        return n;
    }

    static int final_results()
    {
        if (fail() + pass() > 0)
        {
            std::cout << "\n" 
                      << (fail() ? "*** Failure (" : "*** Success (")
                      << pass() << "/" << fail() + pass() << " checks pass)\n";
        }
        else
        {
            std::cout << "*** Success\n";
        }
        return (fail() == 0) ? 0 : 1;
    }

};

#define CHECK(c)                                        \
    if (!(c))                                           \
    {                                                   \
        std::cout << "Check " << #c << " fail.\n";    \
        ++test::fail();                               \
    }                                                   \
    else                                                \
        ++test::pass();

#define REQUIRE(c)                                                              \
    if (!(c))                                                                   \
    {                                                                           \
        std::cout << "Requirement " << #c << " fail, aborting test.\n";       \
        ++test::fail();                                                       \
        std::exit(test::final_results());                                       \
    }                                                                           \
    else                                                                        \
        ++test::pass();

#endif // UTILS_TEST_HPP

