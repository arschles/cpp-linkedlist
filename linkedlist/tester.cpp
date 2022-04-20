#include <memory>
#include <sstream>
#include <string>

#include "str_ptr.hpp"
#include "tester.hpp"

using namespace std;

tester::tester(const string& name) {
    this->test_name = shared_ptr<string>(new string(name));
};

str_ptrs_vec_t tester::get_errors() const noexcept {
    return this->errors;
};

void tester::append_error(const std::string& reason) noexcept {
    this->errors.push_back(shared_ptr<string>(new string(reason)));
};

void tester::error(const char* reason) noexcept {
    this->append_error(string(reason));
};

void tester::error(const std::stringstream& reason) noexcept {
    this->append_error(reason.str());
};

