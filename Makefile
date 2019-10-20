.PHONY: test
test: build/test
	./build/test

build/test: test.cc uint_mersenne.h | build/.
	$(COMPILE_CXX) $< -o $@ -std=c++11 -isystem test -Wall -Werror $(CXXWFLAGS)

.PHONY: format
format:
	clang-format -i test.cc uint_mersenne.h

.PHONY: tidy
tidy: build/compile_commands.json
	clang-tidy -p build test.cc $(TIDYFLAGS)

%/.:
	mkdir -p $@

.PHONY: always-build
always-build:

build/compile_commands.json: always-build | build/.
	@$(MAKE) -n -B BUILD_COMPILE_DATABASE=1 | { \
	  echo '['; comma=; \
	  while read -r line; do \
	    if [ "$$line" = COMPILE ]; then \
	      read -r directory; read -r file; read -r command; \
	      command=$${command//\\/\\\\}; \
	      echo "$$comma{\"directory\":\"$$directory\""; \
	      echo ",\"command\":\"$${command//\"/\\\"}\""; \
	      echo ",\"file\":\"$$file\"}"; \
	    fi; \
	  done; \
	  echo ']'; \
	} > $@

ifeq ($(WARNINGS),everything)
CXXWFLAGS := -Weverything -Wno-c++98-compat
else
CXXWFLAGS :=
endif

ifeq ($(BUILD_COMPILE_DATABASE),1)
ifeq ($(NIX_PATH),)
COMPILE_CXX := +f(){ echo COMPILE; pwd; echo "$$1"; echo "$(CXX) $$(printf '%q ' "$$@")" 2>&1 | grep -- -cc1; }; f
else
COMPILE_CXX := +f(){ echo COMPILE; pwd; echo "$$1"; echo "$(CXX) $$(NIX_DEBUG=1 $(CXX) --version "$$@" 2>&1 1>/dev/null | grep -v -- --version | grep '^  ' | cut -b 3- | xargs -d '\n' printf '"%s" ')"; }; f
endif
else
COMPILE_CXX := $(CXX)
endif
