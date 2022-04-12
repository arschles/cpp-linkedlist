#include <tuple>
#include <string>
#include <functional>
#include <memory>
#include <sstream>
#include <iostream>
#include "ll.cc"
#include <stdlib.h>

using namespace std;

typedef tuple<bool, string> testcase_ret;
typedef function<testcase_ret(string)> testcase_fn;

testcase_ret fail(string reason) {
    return tuple<bool, string>(false, reason);
}

class failer {
    private:
        ostringstream out;
    public:
        failer(string reason) {
            this->out << reason;
        }

        template <class T>
        failer& operator<<(T val) {
            this->out << val;
            return *this;
        }

        testcase_ret operator()() {
            return fail(this->out.str());
        }
};

testcase_ret pass(string reason) {
    return tuple<bool, string>(true, reason);
}

testcase_ret pass() {
    return pass("");
}

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


void run_testcase(testcase_fn fn, string name) {
    auto ret = fn(name);
    auto passed = get<0>(ret);
    auto msg = get<1>(ret);
    if(passed) {
        cout << "PASSED: test case " << endl;
    } else {
        cout << "FAILED: test case " << name << " (" << msg << ")" << endl;
        exit(EXIT_FAILURE);
    }
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
    function<bool(bool, int, int)> checker = [](bool accum, size_t idx, int elt) {
        auto cur_matches = elt==idx;
        return cur_matches && accum;
    };
    if(!ll->reduce<bool>(true, checker)) {
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
    function<bool(bool, int, int)> checker = [](bool accum, size_t idx, int elt) {
        // the value of element at idx should be the mirror
        // of idx
        auto expected_val = num_pushes-idx;
        auto cur_matches = elt==expected_val;
        return cur_matches && accum;
    };
    if(!ll->reduce<bool>(true, checker)) {
        return fail(
            "the value of each element must be the mirror of its index"
        );
    }
    return pass();
}

int main() {
    // basic invariant checks
    run_testcase(test_basic, "empty list");
    
    // check basic len() and get() functionality
    run_testcase(
        test_basic_size_and_get,
        "basic size and get functionality"
    );

    run_testcase(
        test_pop,
        "pop"
    );
    
    run_testcase(
        test_reverse,
        "reverse"
    );
    
    cout << "All tests passed" << endl;
    return 0;
}

