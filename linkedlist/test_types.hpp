#pragma once

#include <string>
#include <tuple>
#include <functional>
#include <sstream>
#include <optional>

#include "ll.hpp"

typedef std::tuple<bool, std::string> testcase_ret;
typedef std::function<testcase_ret(std::string)> testcase_fn;

testcase_ret fail(std::string reason);
testcase_ret pass();
testcase_ret pass(std::string reason);

// check_option returns true if opt.has_value()
// and opt.value() is equal to expected
template <typename T>
bool check_option(std::optional<T> opt, T expected) {
    if(!opt.has_value()) {
        return false;
    }
    return opt.value() == expected;
};

// check_fn_t is the function used to "visit"
// all elements of the linked list. create one
// of these functions to pass into check_all_elts
template <typename T>
using check_fn_t = std::function<bool(size_t, T)>;

// check_all_elts runs fn on every element
// in ll, returning false immediately if fn does.
// if fn returned true for all elements in ll,
// returns true
template <typename T>
bool check_all_elts(
    std::shared_ptr<LinkedList<T>> ll,
    check_fn_t<T> fn
) {
    for (size_t i = 0; i < ll->len(); i++) {
        auto elt = ll->get(i).value();
        if(!fn(i, elt)) {
            return false;
        }
    }
    return true;
}

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
