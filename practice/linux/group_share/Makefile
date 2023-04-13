Src := $(wildcard *.c)
Obj := $(patsubst %.c,%,$(Src))
CC := gcc
CFLAGS := -Wall -g

Out: $(Obj)

%: %.c
	$(CC) $< -o $@ $(CFLAGS) -pthread

.PHONY: Out
