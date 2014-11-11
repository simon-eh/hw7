CC=gcc
CFLAGS=-std=c99 -g -Wall -Wextra -pedantic

all: additup

additup: additup.c
	$(CC) $(CFLAGS) additup.c -o additup

clean:
	rm -f additup