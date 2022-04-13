.PHONY: build-ll
build-ll:
	g++ -std=c++17 -o ./bin/linkedlist linkedlist/*.cpp

.PHONY: test-ll
test-ll: build-ll
	./bin/linkedlist
