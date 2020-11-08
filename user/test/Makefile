CC = gcc
CFLAGS = -g -Wall -Werror
LDFLAGS = -g -lpthread

SRCS = $(wildcard *.c)
TARGETS = $(patsubst %.c, %, $(SRCS))

all: $(TARGETS)
 
$(TARGETS): %:%.c
	$(CC) $< $(CFLAGS) -o $@

.PHONY: clean all
clean:
	rm -rf $(TARGETS)

