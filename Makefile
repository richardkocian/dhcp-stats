CFLAGS = -std=c++2a -Wall -Wextra

.PHONY: clean all

all: main

main: main.o
	g++ main.o -o dhcp-stats

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp -o main.o

clean:
	rm -f *.o dhcp-stats
