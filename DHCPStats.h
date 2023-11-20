/**
 * @file    DHCPStats.cpp
 * @author  Richard Kocián (xkocia19)
 *
 * @brief   ISA Project - dhcp-stats
 * @date    2023-12-14
 */

#ifndef DHCP_STATS_DHCPSTATS_H
#define DHCP_STATS_DHCPSTATS_H

#include "IP.h"
#include "ParamsParser.h"
#include <iomanip>
#include <syslog.h>
#include <pcap.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>


class DHCPStats {
private:
    /**
     * @brief Array of IP ranges (containing IP.cpp objects)
     */
    vector<IP *> ip_ranges;

    ParamsParser* paramsParser;

    /**
     * @brief Erase printed lines in terminal to print updated statistics
     *
     * @param count Number of lines to erase
     */
    void eraseLines(int count);

    /**
     * @brief Print warning to system log with IP that exceeded 50 % of allocation
     *
     * @param ip IP that exceeded 50 % of allocation
     */
    void printToSysLog(string ip);

    /**
     * @brief First print of DHCP statistics of input IP ranges
     */
    void initPrint();

    void setIPRanges();

    /**
     * @brief Print one line of DHCP statistics of particular IP range to terminal
     *
     * @param ip_range IP range
     * @return Occupation of IP
     */
    static double printRow(IP* ip_range);
public:
    /**
     * @brief Initialization
     *
     * @param paramPrs Parsed program parameters
     */
    DHCPStats(ParamsParser* paramPrs);

    /**
     * @brief Print DHCP statistics of input IP ranges
     */
    void printOutput();
    vector<IP *> getIPRanges();

    /**
     * @brief Start sniffing received packets
     */
    void startSniffing();

};


#endif //DHCP_STATS_DHCPSTATS_H
