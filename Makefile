CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: scheduler_sim

scheduler_sim: scheduler.c main.c scheduler.h
	$(CC) $(CFLAGS) -o scheduler_sim scheduler.c main.c

run: scheduler_sim
	./scheduler_sim

clean:
	rm -f scheduler_sim
