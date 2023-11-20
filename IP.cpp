/**
 * @file    IP.cpp
 * @author  Richard Kocián (xkocia19)
 *
 * @date    2023-11-14
 */

#include "IP.h"

IP::IP(string ip) {
    is_reported = false;
    int pos = ip.find("/");
    ip_addr_str = ip.substr(0, pos);
    ip_mask_str = ip.substr(pos + 1, ip.length());

    mask = stoi(ip_mask_str);

    createIP();
    createIPPrefix();
}

void IP::createIP() {
    string copy = ip_addr_str;
    string octet1 = copy.substr(0, copy.find('.'));
    copy.erase(0, copy.find('.')+1);
    string octet2 = copy.substr(0, copy.find('.'));
    copy.erase(0, copy.find('.')+1);
    string octet3 = copy.substr(0, copy.find('.'));
    copy.erase(0, copy.find('.')+1);
    string octet4 = copy.substr(0, copy.find('.'));
    copy.erase(0, copy.find('.')+1);

    ip = (stoi(octet1) << 24) + (stoi(octet2) << 16) + (stoi(octet3) << 8) + stoi(octet4);

    allocated_addresses = 0;
}

int IP::getIP() {
    return ip;
}

void IP::createIPPrefix() {

    unsigned int all_ones = 4294967295;

    int ones_at_end = (1 << (32-mask)) -1;

    mask_binary = ones_at_end ^ all_ones;

    ip_network_addr = ip & mask_binary;

    ip_broadcast_addr = ip_network_addr | ones_at_end;

    max_addresses = pow(2, (32-mask)) - 2;
}

void IP::is_IP_in_range(int ip) {
    if (ip < ip_broadcast_addr && ip > ip_network_addr) {
        allocated_addresses++;
    }
}

string IP::getIP_str() {
    return ip_addr_str + "/" + ip_mask_str;
}

int IP::get_max_address() {
    return max_addresses;
}

int IP::get_allocated_max_addresses() {
    return allocated_addresses;
}

bool IP::isReported() {
    return is_reported;
}

void IP::setAsReported() {
    is_reported = true;
}
