#include <tuple>
#include <string>
#include <functional>
#include <memory>
#include <sstream>
#include <cstdlib>
#include <optional>

#include "check.hpp"
#include "ll.hpp"
#include "test_case.hpp"
#include "test_runner.hpp"

using namespace std;

// create_ll creates a new linked list with num_nodes
// nodes in it. the value of each node will correspond
// to its index in the list. it's the caller's 
// responsibility to delete the linked list when
// done with it.
shared_ptr<LinkedList<int>> create_ll(size_t num_nodes) {
    auto ll = make_shared<LinkedList<int>>();
    for (size_t i = 0; i < num_nodes; ++i) {
        ll->append(i);
    }
    return ll;
}

const size_t num_elts = 200;

testcase_ret_t test_basic(const tester_ptr_t& tester) {
    LinkedList<int> l; 
    if(l.len() != 0) {
        return tester->error("len() should return 0");
    }
    if(l.get(0) != nullopt) {
        return tester->error("get(0) should return nullopt");
    }
    if(l.get(num_elts+1) != nullopt) {
        return tester->error("get(123) should return nullopt");
    }
    if(l.pop() != nullopt) {
        return tester->error("pop() should return nullopt");
    }
}

testcase_ret_t test_basic_size_and_get(const tester_ptr_t& tester) {
    // create new linked list, then
    // check the size and get function for each
    auto ll = create_ll(num_elts);
    if(num_elts != ll->len()) {
        return tester->error("len() should return the number of elements");
    }
    if(ll->get(ll->len()+1).has_value()) {
        return tester->error("get(len()+1) should return nullopt");
    }
    if(!check_all_elts<int>(ll, [](size_t idx, int elt) {
        return elt == idx;
    })) {
        return tester->error("the value of each element must be its index");
    }
}

testcase_ret_t test_pop(const tester_ptr_t& tester) {
    // next pop all the elements, checking size 
    // after each pop
    auto ll = create_ll(num_elts);
    for (size_t i = 0; i < num_elts; ++i) {
        auto popped = ll->pop();
        if(!check_option(popped, int(i))) {
            stringstream str;
            str << "pop() should return " << i << " for index " << i;
            return tester->error(str);
        }
        if(ll->len() != (num_elts-1-i)) {
            stringstream str;
            str << "len() should return " << num_elts-1-i << " after " << i << " pops";
            return tester->error(str);
        }
    }

    if(0 != ll->len()) {
        return tester->error("len() should return 0 after all pops");
    }
}

testcase_ret_t test_reverse(const tester_ptr_t& tester) {
    auto ll = create_ll(num_elts);
    ll->reverse();
    if(ll->len() != num_elts) {
        stringstream str;
        str << " len() after reverse should return the same " << num_elts << " value as before. ";
        str << " instead returned " << ll->len();
        return tester->error(str);
    }
    if(!check_all_elts<int>(ll, [](size_t idx, int elt) {
        // the value of element at idx should be the mirror
        // of idx after the reversing action
        auto expected_val = num_elts-idx-1;
        return elt==expected_val;
    })) {
        return tester->error(
            "the value of each element must be the mirror of its index"
        );
    }
}

testcase_ret_t test_find(const tester_ptr_t& tester) {
    auto ll = create_ll(num_elts);
    // we should be able to find every element
    for(size_t i = 0; i < num_elts; ++i) {
        auto find_res = ll->find([i](size_t idx, int elt) {
            return elt == i;
        });
        if(!check_option(find_res, int(i))) {
            stringstream str;
            str << "find() should return a value for index " << i;
            return tester->error(str);
        }
    }
}

testcase_ret_t test_map(const tester_ptr_t& tester) {
    auto ll = create_ll(num_elts);
    auto mapped_ll = ll->map<string>([](size_t idx, int elt) {
        return to_string(elt);
    });
    
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
            return tester->error(str);
        }
    }
}

testcase_ret_t test_first_last(const tester_ptr_t& tester) {
    // check is essentially a "function alias" so that we can
    // easily call check(some_option, "abc") instead of
    // check_option<string>(some_option, "abc") below.
    //
    // we need to force the compiler to interpret "abc" as
    // a string rather than a const char*, and the 
    // explicit type parameter does that
    auto check = check_option<string>;

    LinkedList<string> ll;
    if(ll.first() != nullopt) {
        return tester->error("first() should return nullopt on empty list");
    }
    if(ll.last() != nullopt) {
        return tester->error("last() should return nullopt on empty list");
    }
    ll.append("abc");
    if(!check(ll.first(), "abc")) {
        return tester->error("first() should return something on non-empty list");
    }
    if(!check(ll.last(), "abc")) {
        return tester->error("last() should return something on non-empty list");
    }
    ll.append("def");
    if(!check(ll.first(), "abc")) {
        return tester->error("first() should still return 'abc' after second append");
    }
    if(!check(ll.last(), "def")) {
        return tester->error("last() should now return 'def' after second append");
    }
    ll.pop();
    ll.pop();
    if(ll.first() != nullopt) {
        return tester->error("first() should return nullopt after popping the last element from the list");
    }
    if(ll.last() != nullopt) {
        return tester->error("last() should return nullopt after popping the last element from the list");
    }
}

testcase_ret_t test_middle(const tester_ptr_t& tests) {
    LinkedList<int> ll0;
    if(ll0.middle() != nullopt) {
        tests->error("middle() should return nullopt on empty list");
    }
    auto ll1 = create_ll(1);
    if(!check_option(ll1->middle(), 0)) {
        tests->error("middle() should return the first element on a list of length 1");
    }
    auto ll2 = create_ll(2);
    if(!check_option(ll2->middle(), 1)) {
        tests->error("middle() should return the first element on a list of length 2");
    }
    auto ll3 = create_ll(3);
    if(!check_option(ll3->middle(), 1)) {
        tests->error("middle() should return the middle element on a list of length 3");
    }
}

testcase_ret_t test_operator_equal(const tester_ptr_t& tester) {
    // create to equal linked lists first
    auto ll1 = create_ll(num_elts);
    auto ll2 = create_ll(num_elts);
    if (!(*ll1 == *ll2) || *ll1 != *ll2) {
        return tester->error("identical linked lists should be equal");
    }
    auto ll3 = ll2->map<int>([](size_t idx, int elt) {
        return elt + 1;
    });
    if (*ll1 == *ll3 || !(*ll1 != *ll3)) {
        return tester->error("linked lists with different elements should not be equal");
    }
}

testcase_ret_t test_copy_ctor(const tester_ptr_t& tester) {
    LinkedList<int> ll1;
    ll1.append(1);
    auto ll2 = make_shared<LinkedList<int>>(ll1);
    check_fn<int> checker = [](size_t idx, int elt) {
        return elt==idx+1;
    };

    if ((ll1.len() != ll2->len()) || !check_all_elts(ll2, checker)) {
        return tester->error("const& copy constructor should produce equivalent copies");
    }

    auto ll3 = create_ll(1);
    auto ll4 = make_shared<LinkedList<int>>(ll3);
    if (ll3->len() != ll4->len() || !check_all_elts(ll4, checker)) {
        return tester->error("shared_ptr copy constructor should produce equivalent copies");
    }
}
testcase_ret_t test_swap(const tester_ptr_t& tester) {
    auto ll1 = create_ll(num_elts);
    auto ll2 = create_ll(num_elts*2);
    // after the swap call, ll1, should have 1 element in it
    // and ll2 should have num_elts
    ll2 = ll1->swap(ll2);
    check_fn<int> checker = [](size_t idx, int elt) {
        return elt==idx;
    };
    if (ll1->len() != num_elts*2 || !check_all_elts(ll1, checker)) {
        return tester->error("swap() should return the second list");
    }
    if (ll2->len() != num_elts || !check_all_elts(ll2, checker)) {
        return tester->error("swap() should swap the existing list with the given one");
    }
}
