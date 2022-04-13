#pragma once

#include <string>
#include <tuple>
#include <functional>
#include <sstream>

typedef std::tuple<bool, std::string> testcase_ret;
typedef std::function<testcase_ret(std::string)> testcase_fn;

testcase_ret fail(std::string reason);
testcase_ret pass();
testcase_ret pass(std::string reason);

class failer {
    private:
        std::ostringstream out;
    public:
        failer(std::string reason);

        template <typename T>
        failer& operator<<(T val) {
            this->out << val;
            return *this;
        }

        testcase_ret operator()();
};
