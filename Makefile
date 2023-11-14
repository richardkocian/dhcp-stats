CFLAGS = -std=c++2a -Wall -Wextra

.PHONY: clean all

all: main

main: main.o ParamsParser.o IP.o DHCPStats.o
	g++ main.o ParamsParser.o IP.o DHCPStats.o -o dhcp-stats -lpcap

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp -o main.o

ParamsParser.o: ParamsParser.h ParamsParser.cpp
	g++ $(CFLAGS) -c ParamsParser.cpp -o ParamsParser.o

IP.o: IP.h IP.cpp
	g++ $(CFLAGS) -c IP.cpp -o IP.o

DHCPStats.o: DHCPStats.h DHCPStats.cpp
	g++ $(CFLAGS) -c DHCPStats.cpp -o DHCPStats.o

clean:
	rm -f *.o dhcp-stats
