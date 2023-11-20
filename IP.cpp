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

    //cout << "IP is: " << ip_addr << endl;
    //cout << "Prefix is: " << ip_mask << endl;

    mask = stoi(ip_mask_str);
    //cout << "Prefix is: " << mask << endl;
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
/*    cout << "octet1 is: " << octet1 << endl;
    cout << "octet2 is: " << octet2 << endl;
    cout << "octet3 is: " << octet3 << endl;
    cout << "octet4 is: " << octet4 << endl;*/

    ip = (stoi(octet1) << 24) + (stoi(octet2) << 16) + (stoi(octet3) << 8) + stoi(octet4);

    //cout << "IP is: " << ip << endl;

    allocated_addresses = 0;
}

int IP::getIP() {
    return ip;
}

void IP::createIPPrefix() {

    unsigned int all_ones = 4294967295;
    //cout << "Mask is: " << mask << endl;
    int ones_at_end = (1 << (32-mask)) -1;
    // cout << "xoruju: " << endl;
    // std::cout << "Maska binární: " << std::bitset<32>(ones_at_end) << std::endl;
    // std::cout << "All ones: " << std::bitset<32>(all_ones) << std::endl;

    mask_binary = ones_at_end ^ all_ones;
    //std::cout << std::bitset<32>(mask_binary) << " - Maska" << std::endl;

    //std::cout << "IP binární: " << std::bitset<32>(ip) << std::endl;
    //std::cout << "IP string: " << ip_addr_str << std::endl;

    ip_network_addr = ip & mask_binary;

    //cout << "IP_prefix is: " << ip_prefix << endl;

    //std::cout << std::bitset<32>(ip_network_addr) << " IP prefix binární: " << std::endl;

    ip_broadcast_addr = ip_network_addr | ones_at_end;

    //std::cout << std::bitset<32>(ip_broadcast_addr) <<  " IP last addre: " << std::endl;

    max_addresses = pow(2, (32-mask)) - 2;
}

void IP::is_IP_in_range(int ip) {
    if (ip < ip_broadcast_addr && ip > ip_network_addr) {
        allocated_addresses++;
        //cout << "V range " << ip_addr_str << "/" << ip_mask_str << " je IP: " << ip << endl;
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
