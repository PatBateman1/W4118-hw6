CC = gcc
CFLAGS = -g -Wall -Werror
LDFLAGS = -g -lpthread

TARGETS = myprogram
OBJS = myprogram.o

$(TARGETS):
$(OBJS):

PHONY += clean
clean:
	rm -rf $(TARGETS) a.out *.o *.order

.PHONY: $(PHONY)