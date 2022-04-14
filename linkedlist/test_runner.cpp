#include <string>
#include <memory>
#include <iostream>
#include "test_case.hpp"

using namespace std;

void run_testcase(testcase_fn_t fn, string name) {
    auto tester_ptr = shared_ptr<tester>(new tester(name));
    fn(tester_ptr);
    auto errs = tester_ptr->get_errors();
    if(errs.size() > 0) {
        // TODO: make string of errors
        cerr << "FAILED [" << name << "]" << endl;
        exit(EXIT_FAILURE);
    } else {
        cout << "PASSED [" << name << "]" << endl;
    }
}
