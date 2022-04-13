#pragma once

#include <string>
#include <tuple>
#include <functional>
#include <sstream>
#include <optional>

typedef std::tuple<bool, std::string> testcase_ret;
typedef std::function<testcase_ret(std::string)> testcase_fn;

testcase_ret fail(std::string reason);
testcase_ret pass();
testcase_ret pass(std::string reason);

template <typename T>
bool check_option(std::optional<T> opt, T expected) {
    if(!opt.has_value()) {
        return false;
    }
    return opt.value() == expected;
};

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
