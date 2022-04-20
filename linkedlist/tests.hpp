#pragma once

#include <memory>

#include "ll.hpp"
#include "test_case.hpp"

std::shared_ptr<LinkedList<int>> create_ll(size_t num_nodes);

testcase_ret_t test_basic(const tester_ptr_t&);
testcase_ret_t test_basic_size_and_get(const tester_ptr_t&);
testcase_ret_t test_pop(const tester_ptr_t&);
testcase_ret_t test_reverse(const tester_ptr_t&);
testcase_ret_t test_find(const tester_ptr_t&);
testcase_ret_t test_map(const tester_ptr_t&);
testcase_ret_t test_first_last(const tester_ptr_t&);
testcase_ret_t test_middle(const tester_ptr_t&);
