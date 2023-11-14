/**
 * @file    ParamsParser.h
 * @author  Richard Kocián (xkocia19)
 *
 * @date    2023-11-14
 */

#ifndef DHCP_STATS_IP_H
#define DHCP_STATS_IP_H

#include <iostream>
#include <vector>
#include <unistd.h>
#include <regex>
#include <math.h>


using namespace std;

class IP {
private:
    string ip_addr_str;
    string ip_mask_str;
    int ip;
    int mask;
    int mask_binary;
    void createIP();
    void createIPPrefix();
    int ip_network_addr;
    int ip_broadcast_addr;
    int max_addresses;
    int allocated_addresses;
public:
    IP(string ip);
    int getIP();
    void is_IP_in_range(int ip);
    string getIP_str();
    int get_max_address();
    int get_allocated_max_addresses();
};


#endif //DHCP_STATS_IP_H
