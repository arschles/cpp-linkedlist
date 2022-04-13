#pragma once

#include <memory>

#include "ll.hpp"

std::shared_ptr<LinkedList<int>> create_ll(size_t num_nodes);

testcase_ret test_basic(string name);
testcase_ret test_basic_size_and_get(string name);
testcase_ret test_pop(string name);
testcase_ret test_reverse(string name);
testcase_ret test_find(string name);
testcase_ret test_map(string name);
testcase_ret test_first_last(string name);
