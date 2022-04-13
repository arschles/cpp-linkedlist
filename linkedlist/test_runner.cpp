#include <string>
#include <iostream>
#include "test_types.hpp"

using namespace std;

void run_testcase(testcase_fn fn, string name) {
    auto ret = fn(name);
    auto passed = get<0>(ret);
    auto msg = get<1>(ret);
    if(passed) {
        cout << "PASSED [" << name << "]" << endl;
    } else {
        cout << "FAILED [" << name << "]: " << msg << endl;
        exit(EXIT_FAILURE);
    }
}
