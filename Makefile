CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference -g3 -O0

SRCDIR=./

SRC=$(wildcard $(SRCDIR)*.c)

OBJ=$(SRC:.c=.o)

EXECUTABLE=outDebug.exe

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)