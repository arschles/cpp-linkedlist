#include <cstdlib>
#include <functional>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "ll.hpp"

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


