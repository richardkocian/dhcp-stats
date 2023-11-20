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
#include <cmath>

using namespace std;

class IP {
private:
    /**
     * @brief String with IPv4 address
     */
    string ip_addr_str;

    /**
     * @brief String with IPv4 mask
     */
    string ip_mask_str;

    /**
     * @brief IPv4 address stored in integer
     */
    int ip;

    /**
     * @brief Mask of IPV4 address stored in integer
     */
    int mask;

    bool is_reported;

    /**
     * @brief Binary (integer) number used to correctly mask first IPv4 address of IPv4 range
     */
    int mask_binary;

    /**
     * @brief Calculate IPv4 address to store it binary in int
     */
    void createIP();

    /**
     * @brief Calculate IPv4 range
     */
    void createIPPrefix();

    /**
     * @brief IPv4 network address of IPv4 range
     */
    int ip_network_addr;

    /**
     * @brief IPv4 broadcast address of IPv4 range
     */
    int ip_broadcast_addr;

    /**
     * @brief Max addresses that can be allocated in this range
     */
    int max_addresses;

    /**
     * @brief Current count of allocated IPv4 addresses in this range
     */
    int allocated_addresses;

public:
    /**
     * @brief Initialization
     *
     * @param ip IPv4 address with mask (xxx.xxx.xxx.xxx/xx)
     */
    IP(string ip);

    int getIP();
    void is_IP_in_range(int ip);
    string getIP_str();
    int get_max_address();
    int get_allocated_max_addresses();
    bool isReported();
    void setAsReported();
};


#endif //DHCP_STATS_IP_H
