#include <string>
#include <memory>
#include <iostream>
#include <sstream>
using namespace std;

#include "test_case.hpp"

using namespace std;

void run_testcase(testcase_fn_t fn, string name) {
    auto tester_ptr = shared_ptr<tester>(new tester(name));
    fn(tester_ptr);
    auto errs = tester_ptr->get_errors();
    if(errs.size() > 0) {
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
