CC = gcc
CFLAGS = -g -Wall
SOURCE = src/sicmp.c src/icmp.c
DEPS = src/icmp.h

all: $(SOURCE) $(DEPS)
	$(CC) $(CFLAGS) $(SOURCE) $(DEPS) -o sicmp

clean:
	rm -f sicmp
