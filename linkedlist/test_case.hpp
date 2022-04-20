#pragma once

#include <string>
#include <tuple>
#include <functional>
#include <sstream>
#include <optional>
#include <vector>
#include "ll.hpp"
#include "str_ptr.hpp"
#include "tester.hpp"

// testcase_ret is the type that tests should return
typedef void testcase_ret_t;
// tester_ptr_t is a shared_ptr to a new tester that each test
// case accepts
typedef std::shared_ptr<tester> tester_ptr_t;
// testcase_fn is the function signature for all test cases
typedef std::function<testcase_ret_t(tester_ptr_t)> testcase_fn_t;
