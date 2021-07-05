CC = gcc
CFLAGS  = -g -Wall -std=gnu99

exe_file = cache_sim
$(exe_file): cache.o simulator.o
	$(CC) cache.o simulator.o -o $(exe_file)
cache.o: cache.c
	$(CC) $(CFLAGS) -c cache.c
simulator.o: simulator.c
	$(CC) $(CFLAGS) -c simulator.c

clean:
	rm -f *.out *.o $(exe_file)
