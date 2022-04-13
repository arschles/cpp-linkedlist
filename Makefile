.PHONY: build-ll
build-ll:
	g++ -std=c++17 -o ./bin/linkedlist linkedlist/*.cpp

.PHONY: run-ll
run-ll: build-ll
	./bin/linkedlist
