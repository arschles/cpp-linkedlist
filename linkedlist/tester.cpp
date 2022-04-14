#include <memory>
#include <string>
#include <sstream>
using namespace std;

#include "tester.hpp"
#include "str_ptr.hpp"

tester::tester(const string& name) {
    this->test_name = shared_ptr<string>(new string(name));
};

str_ptr_t tester::get_name() const noexcept {
    return this->test_name;
};

str_ptrs_vec_t tester::get_errors() const noexcept {
    return this->errors;
};

void tester::append_error(const std::string& err) noexcept {
    this->errors.push_back(shared_ptr<string>(new string(err)));
};

void tester::error(const char* err) noexcept {
    this->append_error(string(err));
};

void tester::error(const std::stringstream& reason) noexcept {
    this->append_error(reason.str());
};

