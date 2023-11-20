# DHCP-STATS

Author: Richard Kocián (xkocia19)

Date: 20.11.2023

## Summary
Application that is able to sniff dhcp packets and generate network prefixes usage statistics.

## Building and running the application
To build the application open terminal in this folder and run:

    $ make
Make command will compile the program through g++ compiler, then
you can run application by running:

    $ ./dhcp-stats [-r filename] [-i interface-name] ip-prefix [ip-prefix [ ... ]]

* `-r filename`: specifies file for analyzing dhcp packets
* `-i interface-name`: specifies interface for analyzing dhcp packets
* `ip-prefix`: IPv4 prefixes from which the program will generate statics (xxx.xxx.xxx.xxx/xx)

Constraints:
There should be passed parameter -r or -i but not both together.

Example run:

    $ ./dhcp-stats -i eth0 192.168.1.0/24 192.168.0.0/22 172.16.32.0/24

Example output:

    $ IP-Prefix Max-hosts Allocated addresses Utilization
    192.168.1.0/24 254 65 25.59%
    192.168.0.0/22 1022 203 19.86%
    172.16.32.0/24 254 30 11.81%

## List of submitted files:

* main.cpp
* DHCPStats.cpp
* DHCPStats.h
* IP.cpp
* IP.h
* ParamsParser.cpp
* ParamsParser.h
* manual.pdf
* dhcp-stats.1
* README.md
