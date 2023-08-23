CC = gcc
CFLAGS = -Wall -Wextra -O3 -fopenmp -pthread
SRC = pcg/pcg_basic.c simulation.h simulation.c graphs/*.c graphs/graphs.h utils/utils.h utils/*.c

all: distribution process

distribution: $(SRC) distribution.c
	$(CC) $(CFLAGS) $(SRC) distribution.c -o distribution.out -lm

process: $(SRC) unhappy_process.c
	$(CC) $(CFLAGS) $(SRC) unhappy_process.c -o unhappy_process.out -lm

test:
	echo "test"
