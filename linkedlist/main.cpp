#include <iostream>
using namespace std;

#include "test_runner.hpp"
#include "tests.hpp"

int main() {
    // basic invariant checks
    run_testcase(test_basic, "empty list");
    
    // check basic len() and get() functionality
    run_testcase(
        test_basic_size_and_get,
        "basic size and get functionality"
    );

    run_testcase(
        test_pop,
        "pop"
    );
    
    run_testcase(
        test_reverse,
        "reverse"
    );

    run_testcase(
        test_find,
        "find"
    );

    run_testcase(
        test_map,
        "map"
    );

    run_testcase(
        test_first_last,
        "first and last"
    );

    run_testcase(
        test_middle,
        "middle"
    );
    
    cout << "All tests passed" << endl;
    return 0;
}

