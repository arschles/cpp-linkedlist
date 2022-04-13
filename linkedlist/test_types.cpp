#ifndef TEST_TYPES
#define TEST_TYPES 1

#include <tuple>
#include <functional>
#include <string>
#include <sstream>
using namespace std;

#include "test_types.hpp"

testcase_ret fail(std::string reason) {
    return tuple<bool, std::string>(false, reason);
}

testcase_ret pass(std::string reason) {
    return tuple<bool, std::string>(true, reason);
}

testcase_ret pass() {
    return pass("");
}

failer::failer(std::string reason) {
    this->out << reason;
}

testcase_ret failer::operator()() {
    return fail(this->out.str());
}



#endif
