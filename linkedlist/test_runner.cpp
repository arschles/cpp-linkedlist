#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "test_case.hpp"

using namespace std;

void run_testcase(const testcase_fn_t& fn, const string& name) {
    auto tester_ptr = make_shared<tester>(name);
    fn(tester_ptr);
    auto errs = tester_ptr->get_errors();
    if(!errs.empty()) {
        stringstream str;
        for(size_t i = 0; i < errs.size(); ++i) {
            str << "\t" << i+1 << ". " << *errs[i];
            if(i != errs.size() - 1) {
                str << "\n";
            }
        }
        cerr << "FAILED [" << name << "]:\n" << str.str() << endl;
        exit(EXIT_FAILURE);
    } else {
        cout << "PASSED [" << name << "]" << endl;
    }
}
