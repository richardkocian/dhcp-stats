CFLAGS = -std=c++2a -Wall -Wextra

.PHONY: clean all

all: main

main: main.o ParamsParser.o
	g++ main.o ParamsParser.o -o dhcp-stats -lpcap

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp -o main.o

ParamsParser.o: ParamsParser.h ParamsParser.cpp
	g++ $(CFLAGS) -c ParamsParser.cpp -o ParamsParser.o

clean:
	rm -f *.o dhcp-stats
