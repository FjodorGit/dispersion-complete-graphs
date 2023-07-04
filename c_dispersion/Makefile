CC = gcc
CFLAGS = -Wall -Wextra -O3 -fopenmp -pthread
SRC = pcg/pcg_basic.c simulation.h simulation.c graphs/*.c graphs/graphs.h

all: distribution process

distribution:
	$(CC) $(CFLAGS) $(SRC) distribution.c -o distribution -lm

process:
	echo "Hello process"

test:
	echo "test"
