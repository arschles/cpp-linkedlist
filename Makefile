CLANG_TIDY_PREFIX=clang-tidy \
		--warnings-as-errors=* \
		-checks=abseil-,boost-,bugprone-,cert-,clang-analyzer-,concurrency-,cppcoreguidelines-,darwin-,google-,hicpp-,linuxkernel-,llvm-,llvmlibc-,misc-,modernize-,performance-,portability-,readabilty- \
		--extra-arg=-std=c++17 \
		--extra-arg=-Ilinkedlist \
		-header-filter=.*
CPPCHECK_PREFIX=cppcheck --std=c++17 --enable=all --includes-file=linkedlist
BOOST_INCLUDES?=/usr/include/boost

.PHONY: test
test:
	clang++ -Ilinkedlist -I${BOOST_INCLUDES} -std=c++17 -o ./bin/ll-tests tests/*.cpp
	./bin/ll-tests

.PHONY: lint
lint:
	$(CLANG_TIDY_PREFIX) tests/*.cpp tests/*.hpp linkedlist/*.cpp linkedlist/*.hpp
	# $(CPPCHECK_PREFIX) linkedlist tests
		
	
