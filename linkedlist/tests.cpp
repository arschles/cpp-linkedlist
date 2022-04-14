#include <tuple>
#include <string>
#include <functional>
#include <memory>
// #include <iostream>
#include <sstream>
#include <stdlib.h>
#include <optional>

using namespace std;

#include "ll.hpp"
#include "test_case.hpp"
#include "test_runner.hpp"
#include "check.hpp"

// create_ll creates a new linked list with num_nodes
// nodes in it. the value of each node will correspond
// to its index in the list. it's the caller's 
// responsibility to delete the linked list when
// done with it.
std::shared_ptr<LinkedList<int>> create_ll(size_t num_nodes) {
    auto ll = new LinkedList<int>;
    for (size_t i = 0; i < num_nodes; ++i) {
        ll->append(i);
    }
    std::shared_ptr<LinkedList<int>> ret(ll);
    return ret;
}

const size_t num_elts = 200;

testcase_ret_t test_basic(tester_ptr_t tester) {
    LinkedList<int> l; 
    if(l.len() != 0) {
        tester->error("len() should return 0");
        return;
    }
    if(l.get(0) != nullopt) {
        tester->error("get(0) should return nullopt");
        return;
    }
    if(l.get(123) != nullopt) {
        tester->error("get(123) should return nullopt");
        return;
    }
    if(l.pop() != nullopt) {
        tester->error("pop() should return nullopt");
        return;
    }
}

testcase_ret_t test_basic_size_and_get(tester_ptr_t tester) {
    // create new linked list, then
    // check the size and get function for each
    auto ll = create_ll(num_elts);
    if(num_elts != ll->len()) {
        tester->error("len() should return the number of elements");
        return;
    }
    if(ll->get(ll->len()+1).has_value()) {
        tester->error("get(len()+1) should return nullopt");
        return;
    }
    check_fn_t<int> checker = [](size_t idx, int elt) {
        return elt==idx;
    };
    if(!check_all_elts(ll, checker)) {
        tester->error("the value of each element must be its index");
        return;
    }
}

testcase_ret_t test_pop(tester_ptr_t tester) {
    // next pop all the elements, checking size 
    // after each pop
    auto ll = create_ll(num_elts);
    for (size_t i = 0; i < num_elts; ++i) {
        auto popped = ll->pop();
        if(!check_option(popped, int(i))) {
            std::stringstream str;
            str << "pop() should return " << i << " for index " << i;
            tester->error(str);
            return;
        }
        if(ll->len() != (num_elts-1-i)) {
            std::stringstream str;
            str << "len() should return " << num_elts-1-i << " after " << i << " pops";
            tester->error(str);
            return;
        }
    }

    if(0 != ll->len()) {
        tester->error("len() should return 0 after all pops");
        return;
    }
}

testcase_ret_t test_reverse(tester_ptr_t tester) {
    auto ll = create_ll(num_elts);
    ll->reverse();
    if(ll->len() != num_elts) {
        std::stringstream str;
        str << " len() after reverse should return the same " << num_elts << " value as before. ";
        str << " instead returned " << ll->len();
        tester->error(str);
        return;
    }
    // iterate from beginning to end and check indices
    check_fn_t<int> checker = [](size_t idx, int elt) {
        // the value of element at idx should be the mirror
        // of idx after the reversing action
        auto expected_val = num_elts-idx-1;
        return elt==expected_val;
    };
    if(!check_all_elts(ll, checker)) {
        tester->error(
            "the value of each element must be the mirror of its index"
        );
        return;
    }
}

testcase_ret_t test_find(tester_ptr_t tester) {
    auto ll = create_ll(num_elts);
    // we should be able to find every element
    for(size_t i = 0; i < num_elts; ++i) {
        find_fn_t<int> finder = [i](size_t idx, int elt) {
            return elt == i;
        };
        auto find_res = ll->find(finder);
        if(!check_option(find_res, int(i))) {
            std::stringstream str;
            str << "find() should return a value for index " << i;
            tester->error(str);
            return;
        }
    }
}

testcase_ret_t test_map(tester_ptr_t tester) {
    auto ll = create_ll(num_elts);
    map_fn_t<int, string> mapper = [](size_t idx, int elt) {
        return to_string(elt);
    };
    auto mapped_ll = ll->map(mapper);
    
    // mapped_ll is now a new linked list with elements
    // like "0", "1", "2", ... (note the strings, not
    // ints for each element).
    // iterate to check each element
    for(size_t i = 0; i < num_elts; ++i) {
        auto elt = mapped_ll->get(i);
        auto expected_val = to_string(i);
        if(!check_option(elt, to_string(i))) {
            stringstream str;
            str << "get() should return " << to_string(i) << " for index " << i;
            tester->error(str);
            return;
        }
    }
}

testcase_ret_t test_first_last(tester_ptr_t tester) {
    // check is essentially a "function alias" so that we can
    // easily call check(some_option, "abc") instead of
    // check_option<string>(some_option, "abc") below.
    //
    // we need to force the compiler to interpret "abc" as
    // a std::string rather than a const char*, and the 
    // explicit type parameter does that
    auto check = check_option<string>;

    LinkedList<std::string> ll;
    if(ll.first() != nullopt) {
        return tester->error("first() should return nullopt on empty list");
        return;
    }
    if(ll.last() != nullopt) {
        return tester->error("last() should return nullopt on empty list");
        return;
    }
    ll.append("abc");
    if(!check(ll.first(), "abc")) {
        return tester->error("first() should return something on non-empty list");
        return;
    }
    if(!check(ll.last(), "abc")) {
        return tester->error("last() should return something on non-empty list");
        return;
    }
    ll.append("def");
    if(!check(ll.first(), "abc")) {
        return tester->error("first() should still return 'abc' after second append");
        return;
    }
    if(!check(ll.last(), "def")) {
        return tester->error("last() should now return 'def' after second append");
        return;
    }
    ll.pop();
    ll.pop();
    if(ll.first() != nullopt) {
        return tester->error("first() should return nullopt after popping the last element from the list");
        return;
    }
    if(ll.last() != nullopt) {
        return tester->error("last() should return nullopt after popping the last element from the list");
        return;
    }
}
