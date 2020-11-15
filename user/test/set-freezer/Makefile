CC = gcc
CFLAGS = -g -Wall -Werror -I../../../linux/include/uapi 
LDFLAGS = -g

SRCS = $(wildcard *.c)
TARGETS = $(patsubst %.c, %, $(SRCS))

all: $(TARGETS)
 
$(TARGETS): %:%.c
	$(CC) $< $(CFLAGS) -o $@

.PHONY: clean all
clean:
	rm -rf $(TARGETS)
