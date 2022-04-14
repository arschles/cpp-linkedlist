#pragma once

#include <memory>

#include "ll.hpp"
#include "test_case.hpp"

std::shared_ptr<LinkedList<int>> create_ll(size_t num_nodes);

testcase_ret_t test_basic(tester_ptr_t);
testcase_ret_t test_basic_size_and_get(tester_ptr_t);
testcase_ret_t test_pop(tester_ptr_t);
testcase_ret_t test_reverse(tester_ptr_t);
testcase_ret_t test_find(tester_ptr_t);
testcase_ret_t test_map(tester_ptr_t);
testcase_ret_t test_first_last(tester_ptr_t);
