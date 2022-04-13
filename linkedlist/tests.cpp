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
const size_t num_elts = 200;

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
    // create new linked list, then
    // check the size and get function for each
    auto ll = create_ll(num_elts);
    if(num_elts != ll->len()) {
        return fail("len() should return the number of elements");
    }
    if(ll->get(ll->len()+1).has_value()) {
        return fail("get(len()+1) should return nullopt");
    }
    check_fn_t<int> checker = [](size_t idx, int elt) {
        return elt==idx;
    };
    if(!check_all_elts(ll, checker)) {
        return fail("the value of each element must be its index");
    }
    return pass();
}

testcase_ret test_pop(string name) {
    // next pop all the elements, checking size 
    // after each pop
    auto ll = create_ll(num_elts);
    for (size_t i = 0; i < num_elts; i++) {
        auto popped = ll->pop();
        if(!check_option(popped, int(i))) {
            auto f = failer("pop() should return ");
            f << i << " for index " << i;
            return f();
        }
        if(ll->len() != (num_elts-1-i)) {
            auto f = failer("len() should return ");
            f << num_elts-1-i << " after " << i << " pops";
            return f();
        }
    }

    if(0 != ll->len()) {
        return fail("len() should return 0 after all pops");
    }
    return pass();
}

testcase_ret test_reverse(string name) {
    auto ll = create_ll(num_elts);
    ll->reverse();
    if(ll->len() != num_elts) {
        auto f = failer("len*() after reverse should be ");
        f << num_elts<< ", same as before";
        return f();
    }
    // iterate from beginning to end and check indices
    check_fn_t<int> checker = [](size_t idx, int elt) {
        // the value of element at idx should be the mirror
        // of idx after the reversing action
        auto expected_val = num_elts-idx-1;
        return elt==expected_val;
    };
    if(!check_all_elts(ll, checker)) {
        return fail(
            "the value of each element must be the mirror of its index"
        );
    }
    return pass();
}

testcase_ret test_find(string name) {
    auto ll = create_ll(num_elts);
    // we should be able to find every element
    for(size_t i = 0; i < num_elts; i++) {
        find_fn_t<int> finder = [i](size_t idx, int elt) {
            return elt == i;
        };
        auto find_res = ll->find(finder);
        if(!check_option(find_res, int(i))) {
            auto f = failer("find() should return a value for index ");
            f << i;
            return f();
        }
    }
    return pass();
}

testcase_ret test_map(string name) {
    auto ll = create_ll(num_elts);
    map_fn_t<int, string> mapper = [](size_t idx, int elt) {
        return to_string(elt);
    };
    auto mapped_ll = ll->map(mapper);
    
    // mapped_ll is now a new linked list with elements
    // like "0", "1", "2", ... (note the strings, not
    // ints for each element).
    // iterate to check each element
    for(size_t i = 0; i < num_elts; i++) {
        auto elt = mapped_ll->get(i);
        auto expected_val = to_string(i);
        if(!check_option(elt, to_string(i))) {
            auto f = failer("");
            f << "get() should return " << to_string(i);
            f << " for index " << i;
            return f();
        }
    }
    return pass();
}
