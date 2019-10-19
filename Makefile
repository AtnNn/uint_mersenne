.PHONY: test
test: build/test
	./build/test

build/test: test.cc uint_mersenne.h | build/.
	$(CXX) -o $@ $< -std=c++11 -Wall

.PHONY: format
format:
	clang-format -i test.cc uint_mersenne.h

%/.:
	mkdir -p $@
