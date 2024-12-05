.PHONY: build test clean

CFLAGS := -Wall -Wextra -ggdb -I../../include/

build:
	@if [ ! -d build ]; then mkdir -p build; fi
	gcc $(CFLAGS) src/main.c -o build/main

test: build
	./build/main ./input/full_input.txt
