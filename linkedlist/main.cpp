#include <iostream>
#include "test_runner.hpp"
#include "tests.hpp"
using namespace std;

int main() {
    // basic invariant checks
    {
        const string name("empty list");
        run_testcase(&test_basic, name);
    }
    
    // check basic len() and get() functionality
    {
        const string name("basic size and get functionality");
        run_testcase(&test_basic_size_and_get, name);
    }
    
    // testing the pop function
    {
        const string name("pop");
        run_testcase(&test_pop, name);
    }
    
    {
        const string name("reverse");
        run_testcase(&test_reverse, name);
    }

    {
        const string name("find");
        run_testcase(&test_find, name);
    }

    {
        const string name("map");
        run_testcase(&test_map, name);
    }

    {
        const string name("first and last");
        run_testcase(&test_first_last, name);
    }
    
    {
        const string name("middle");
        run_testcase(&test_middle, name);
    }
    
    cout << "All tests passed" << endl;
    return 0;
}

