SRC_DIR := .

MAIN_SRCS := $(shell find $(SRC_DIR) -name main.c)

BINARIES := $(patsubst %/src/main.c, %/build/main, $(MAIN_SRCS))

INCLUDES := ./lib

CC := gcc
CFLAGS := -Wall -Wextra -pedantic -g
# -Werror

test:
	@echo $(BINARIES)

lib: ./lib/my_utils.o

all: lib $(BINARIES)

%/build/main: %/src/main.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDES) $< -o $@ ./lib/my_utils.o

clean:
	rm -rf $(BINARIES)
	rm -rf ./lib/utils.o

.PHONY: all clean

