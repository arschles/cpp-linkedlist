#ifndef TESTS
#define TESTS 1

#include <tuple>
#include <string>
#include <functional>
#include <memory>
#include <iostream>
#include <stdlib.h>
#include <optional>

using namespace std;

#include "ll.hpp"
#include "test_types.hpp"
#include "test_runner.hpp"

// create_ll creates a new linked list with num_nodes
// nodes in it. the value of each node will correspond
// to its index in the list. it's the caller's 
// responsibility to delete the linked list when
// done with it.
std::shared_ptr<LinkedList<int>> create_ll(size_t num_nodes) {
    auto ll = new LinkedList<int>;
    for (size_t i = 0; i < num_nodes; i++) {
        ll->append(i);
    }
    std::shared_ptr<LinkedList<int>> ret(ll);
    return ret;
}

testcase_ret test_basic(string name) {
    LinkedList<int> l; 
    if(l.len() != 0) {
        return fail("len() should return 0");
    }
    if(l.get(0) != nullopt) {
        return fail("get(0) should return nullopt");
    }
    if(l.get(123) != nullopt) {
        return fail("get(123) should return nullopt");
    }
    if(l.pop() != nullopt) {
        return fail("pop() should return nullopt");
    }

    return pass();
}

testcase_ret test_basic_size_and_get(string name) {
    const size_t num_pushes = 200;
    // create new linked list, then
    // check the size and get function for each
    auto ll = create_ll(num_pushes);
    if(num_pushes != ll->len()) {
        return fail("len() should return the number of elements");
    }
    if(ll->get(ll->len()+1).has_value()) {
        return fail("get(len()+1) should return nullopt");
    }
    reduce_fn_t<int, bool> checker = [](bool accum, size_t idx, int elt) {
        auto cur_matches = elt==idx;
        return cur_matches && accum;
    };
    if(!ll->reduce(true, checker)) {
        return fail("the value of each element must be its index");
    }
    return pass();
}

testcase_ret test_pop(string name) {
    const size_t num_pushes = 200;
    // next pop all the elements, checking size 
    // after each pop
    auto ll = create_ll(num_pushes);
    for (size_t i = 0; i < num_pushes; i++) {
        auto popped = ll->pop();
        if(!popped.has_value()) {
            auto f = failer(
                "pop() should return a value for index "
            );
            f << i;
            return f();
        }
        if(popped.value() != i) {
            auto f = failer("value of index ");
            f << i << " should be " << i;
            f << " (it was " << popped.value() << ")";
            return f();
        }
        if(ll->len() != (num_pushes-1-i)) {
            auto f = failer("len() should return ");
            f << num_pushes-1-i << " after " << i << " pops";
            return f();
        }
    }

    if(0 != ll->len()) {
        return fail("len() should return 0 after all pops");
    }
    return pass();
}

testcase_ret test_reverse(string name) {
    const size_t num_pushes = 200;
    auto ll = create_ll(num_pushes);
    ll->reverse();
    if(ll->len() != num_pushes) {
        auto f = failer("len*() after reverse should be ");
        f << num_pushes<< ", same as before";
        return f();
    }
    // iterate from beginning to end and check indices
    reduce_fn_t<int, bool> checker = [](bool accum, size_t idx, int elt) {
        // the value of element at idx should be the mirror
        // of idx after the reversing action
        auto expected_val = num_pushes-idx-1;
        auto cur_matches = elt==expected_val;
        return cur_matches && accum;
    };
    if(!ll->reduce(true, checker)) {
        return fail(
            "the value of each element must be the mirror of its index"
        );
    }
    return pass();
}

#endif
