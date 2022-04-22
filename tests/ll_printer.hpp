#pragma once

#include <iostream>

#include "ll.hpp"

namespace linkedlist {

// this function is needed to allow BOOST_TEST 
// macros to print out the LinkedList when an
// assertion fails.
//
// as explained in the below link, BOOST_TEST by default
// prints out argument values when an assertion fails.
// there are two options for implementing the logic to
// render a type to a string:
//
// - implementing operator<< on the type
// - implementing this named function
//
// we're choosing the second one to avoid modifying 
// non-test code specifically for testing purposes. 
//
// note that you can also prevent printing out values 
// completely if you want. do this with the 
// BOOST_TEST_DONT_PRINT_LOG_VALUE macro value.
//
// see this link for more details:
// https://www.boost.org/doc/libs/1_64_0/libs/test/doc/html/boost_test/test_output/test_tools_support_for_logging/testing_tool_output_disable.html
template <typename T>
std::ostream& boost_test_print_type(
    std::ostream& ostr,
    linkedlist::LinkedList<T> const& ll
) {
    ostr << "LinkedList with length: " << ll.len();
    return ostr;
}
} // linkedlist
