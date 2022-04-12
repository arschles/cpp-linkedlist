.PHONY: build-ll
build-ll:
	g++ -o ./bin/ll.out -std=c++17 linkedlist/*.cc

.PHONY: run-ll
run-ll: build-ll
	./bin/ll.out
