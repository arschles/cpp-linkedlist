#define BOOST_TEST_MODULE LinkedList_Tests

#include <iostream>
#include <optional>
#include <string>

#include <boost/test/included/unit_test.hpp>

#include "ll.hpp"
#include "ll_util.hpp"

using namespace std;

const size_t num_elts = 201;

// this function is needed to allow BOOST_TEST to print
// out the LinkedList when the assertion failed.
// we implement this function instead of implementing operator<<
// directly on the LinkedList. see the following link for more 
// detail:
// https://www.boost.org/doc/libs/1_64_0/libs/test/doc/html/boost_test/test_output/test_tools_support_for_logging/testing_tool_output_disable.html
template <typename T>
ostream& boost_test_print_type(ostream& ostr, LinkedList<T> const& ll) {
    ostr << "LinkedList with length: " << ll.len();
    return ostr;
}


BOOST_AUTO_TEST_CASE(empty_list) {
    LinkedList<string> l;
    BOOST_TEST(l.len() == 0);
    BOOST_TEST(!l.get(0).has_value());
    BOOST_TEST(!l.get(num_elts+1).has_value());
    BOOST_TEST(!l.pop().has_value());
}

BOOST_AUTO_TEST_CASE(basic_size_and_get) {
    // create new linked list, then
    // check the size and get function for each
    auto ll = create_ll(num_elts);
    BOOST_TEST(ll->len() == num_elts);
    BOOST_TEST(!ll->get(ll->len()+1).has_value());
    ll->for_each([](size_t idx, int elt) {
        BOOST_TEST(elt == idx);
    });
}

BOOST_AUTO_TEST_CASE(pop_function) {
    // next pop all the elements, checking size 
    // after each pop
    auto ll = create_ll(num_elts);
    for (size_t i = 0; i < num_elts; ++i) {
        auto popped = ll->pop();
        BOOST_TEST(popped.has_value());
        BOOST_TEST(popped.value() == int(i));
        const size_t expected_new_len = num_elts-1-i;
        BOOST_TEST(ll->len() == expected_new_len);
    }
    BOOST_TEST(ll->len() == 0);
}

BOOST_AUTO_TEST_CASE(reverse_function) {
    auto ll = create_ll(num_elts);
    ll->reverse();
    BOOST_TEST(ll->len() == num_elts);
    ll->for_each([&](size_t idx, int elt) {
        auto expected_val = num_elts - idx-1;
        BOOST_TEST(elt == expected_val);
    });
}

BOOST_AUTO_TEST_CASE(find_function) {
    auto ll = create_ll(num_elts);
    // we should be able to find every element
    for(size_t i = 0; i < num_elts; ++i) {
        auto find_res = ll->find([i](size_t idx, int elt) {
            return elt == i;
        });
        BOOST_TEST(find_res.has_value());
        BOOST_TEST(find_res.value() == int(i));
    }
}

BOOST_AUTO_TEST_CASE(map_function) {
    auto ll = create_ll(num_elts);
    auto mapped_ll = ll->map<string>([](size_t idx, int elt) {
        return to_string(elt);
    });
    
    // mapped_ll is now a new linked list with elements
    // like "0", "1", "2", ... (note the strings, not
    // ints for each element).
    // iterate to check each element
    mapped_ll->for_each([](size_t idx, string elt) {
        string expected = to_string(idx);
        BOOST_TEST(elt == to_string(idx));
    });
}

BOOST_AUTO_TEST_CASE(first_and_last_functions) {
    LinkedList<string> ll;
    BOOST_TEST(!ll.first().has_value());
    BOOST_TEST(!ll.last().has_value());
    
    ll.append("abc");
    BOOST_TEST(ll.first().has_value());
    BOOST_TEST(ll.first().value() == "abc");
    BOOST_TEST(ll.last().has_value());
    BOOST_TEST(ll.last().value() == "abc");
    
    ll.append("def");
    BOOST_TEST(ll.first().has_value());
    BOOST_TEST(ll.first().value() == "abc");
    BOOST_TEST(ll.last().has_value());
    BOOST_TEST(ll.last().value() == "def");
    
    ll.pop();
    ll.pop();
    BOOST_TEST(!ll.first().has_value());
    BOOST_TEST(!ll.last().has_value());
}

BOOST_AUTO_TEST_CASE(middle_function) {
    LinkedList<int> ll0;
    BOOST_TEST(ll0.len() == 0);
    BOOST_TEST(!ll0.middle().has_value());
    
    auto ll1 = create_ll(1);
    BOOST_TEST(ll1->middle().has_value());
    BOOST_TEST(ll1->middle().value() == 0);
    
    auto ll2 = create_ll(2);
    BOOST_TEST(ll2->middle().has_value());
    BOOST_TEST(ll2->middle().value() == 1);
    
    auto ll3 = create_ll(3);
    BOOST_TEST(ll3->middle().has_value());
    BOOST_TEST(ll3->middle().value() == 1);
}

BOOST_AUTO_TEST_CASE(operator_equal) {
    // create two equal linked lists and check
    // that the == and != operators work
    auto ll1 = create_ll(num_elts);
    auto ll2 = create_ll(num_elts);
    BOOST_TEST((*ll1 == *ll2) == true);
    BOOST_TEST((*ll1 != *ll2) == false);
    
    // transform ll2 into a linked list not equal
    // to ll1, then check that the == and != operators
    // work between ll1 and the new one
    auto ll3 = ll2->map<int>([](size_t idx, int elt) {
        return elt + 1;
    });

    BOOST_TEST(!(*ll1 == *ll3));
    BOOST_TEST(*ll1 != *ll3);
}

BOOST_AUTO_TEST_CASE(copy_constructor) {
    LinkedList<int> ll1;
    ll1.append(1);
    ll1.append(4);
    auto ll2 = make_shared<LinkedList<int>>(ll1);

    auto expected_elts = {1, 4};
    auto expected = make_shared<vector<int>>(expected_elts);

    BOOST_TEST(ll1.len() == ll2->len());
    BOOST_TEST(ll2->len() == expected->size());
    ll2->for_each([&expected](size_t idx, int elt) {
        BOOST_TEST(elt == expected->at(idx));
    });
}

BOOST_AUTO_TEST_CASE(swap_function) {
    auto ll1 = create_ll(num_elts);
    auto ll2 = create_ll(num_elts*2);
    // after the swap call, ll1, should have 1 element in it
    // and ll2 should have num_elts
    ll2 = ll1->swap(ll2);
    
    // ll1 now should have the elements of ll2
    BOOST_TEST(ll1->len() == num_elts*2);
    ll1->for_each([](size_t idx, int elt) {
        BOOST_TEST(elt == idx);
    });

    // ll2 now should have the elements of ll1
    BOOST_TEST(ll2->len() == num_elts);
    ll2->for_each([](size_t idx, int elt) {
        BOOST_TEST(elt == idx);
    });
}
