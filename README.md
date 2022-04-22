# C++ Linked List Implementation

This repository contains C++ linked list implementation, simple test harness, and a suite of unit tests. All linked list sources are header-only and located in [`./linkedlist`](./linkedlist), and the test harness and tests are located in [`./tests`](./tests).

All sources in [`./linkedlist`](./linkedlist) have dependencies only on non-container libraries from the C++17 standard library. Tests have the following dependencies:

- All code in [`./linkedlist`](./linkedlist).
- The C++17 standard library, including containers.
- The [Boost.Test library](https://www.boost.org/doc/libs/1_79_0/libs/test/doc/html/index.html):
  - If on Ubuntu, install with this command: `sudo apt-get install libboost-all-dev`.
  - It's expected that the Boost.Test headers will be installed into `/usr/include/boost`. Override this with the `BOOST_INCLUDES` environment variable when running tests (see below).

## Running Tests

To run the tests, you need the following installed:

- The `clang++` compiler capable of compiling to the C++17 standard (e.g. `-std=c++17`)
- `make`
- The [Boost.Test library](https://www.boost.org/doc/libs/1_79_0/libs/test/doc/html/index.html)

Once you have these tools installed, run `make test` to execute the tests.

>If the `Boost.Test` library headers are installed to somewhere other than `/usr/include/boost`, run `BOOST_INCLUDES=/path/to/boost make test`.
