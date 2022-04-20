.PHONY: build
build:
	clang++ -Ilinkedlist -std=c++17 -o ./bin/linkedlist linkedlist/*.cpp

.PHONY: test
test: build
	./bin/linkedlist

.PHONY: lint
lint:
	clang-tidy \
		--warnings-as-errors=* \
		-checks=abseil-,boost-,bugprone-,cert-,clang-analyzer-,concurrency-,cppcoreguidelines-,darwin-,google-,hicpp-,linuxkernel-,llvm-,llvmlibc-,misc-,modernize-,performance-,portability-,readabilty- \
		--extra-arg=-std=c++17 \
		-header-filter=.* \
		linkedlist/*.cpp
	cppcheck --std=c++17 --enable=all linkedlist
