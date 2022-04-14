#pragma once

#include <string>

#include "str_ptr.hpp"

// tester is the object that is passed to test case functions.
// 
// it contains common functions to be used in all test cases
class tester {
    private:
        str_ptr_t test_name;
        str_ptrs_vec_t errors;

        void append_error(const std::string& str) noexcept;

    public:
        tester(const std::string& name);
        
        // get_name gets the name of the test to which this
        // tester is associated
        str_ptr_t get_name() const noexcept;
        
        // get_errors returns the vector of errors that have
        // been added to this tester
        str_ptrs_vec_t get_errors() const noexcept;
        
        // error marks the test as failed. it does not abort the
        // test, however. you should `return` from your test
        // if you want to do that.
        void error(const char* reason) noexcept;
        void error(const std::stringstream& reason) noexcept;
};
