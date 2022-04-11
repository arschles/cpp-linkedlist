.PHONY: build
build:
	g++ -o ./bin/lists.out -std=c++17 linkedlist.cpp

.PHONY: run
run: build
	./bin/lists.out
