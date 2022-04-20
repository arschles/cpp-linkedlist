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
		-checks=clang-analyzer-*,-clang-analyzer-cplusplus*,readability-*,bugprone-*,cppcoreguidelines-,boost-,abseil-,cert-,modernize- \
		--extra-arg=-std=c++17 \
		-header-filter=.* \
		linkedlist/*.cpp
	cppcheck --std=c++17 --enable=all linkedlist
