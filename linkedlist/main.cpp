#include <iostream>

#include "test_runner.hpp"
#include "tests.hpp"

using namespace std;

int main() {
    run_testcase(&test_basic, "empty list");
    run_testcase(&test_basic_size_and_get, "basic size and get functionality");
    run_testcase(&test_pop, "pop");
    run_testcase(&test_reverse, "reverse");
    run_testcase(&test_find, "find");
    run_testcase(&test_map, "map");
    run_testcase(&test_first_last, "first and last");
    run_testcase(&test_middle, "middle");
    run_testcase(&test_operator_equal, "operator==");
    run_testcase(&test_swap, "swap");
    run_testcase(&test_copy_ctor, "copy constructor");
    
    cout << "All tests passed" << endl;
    return 0;
}

