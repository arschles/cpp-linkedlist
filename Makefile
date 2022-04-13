.PHONY: build-ll
build-ll:
	g++ -c -std=c++17 -o bin/test_types.o linkedlist/test_types.cpp
	g++ -c -std=c++17 -o bin/test_runner.o linkedlist/test_runner.cpp
	g++ -c -std=c++17 -o bin/tests.o linkedlist/tests.cpp
	g++ -c -std=c++17 -o bin/main.o linkedlist/main.cpp
	g++ -o ./bin/linkedlist \
		bin/test_types.o \
		bin/test_runner.o \
		bin/tests.o \
		bin/main.o

.PHONY: run-ll
run-ll: build-ll
	./bin/linkedlist
