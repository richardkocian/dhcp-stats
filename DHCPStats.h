//
// Created by Richard Kocián on 14.11.2023.
//

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
    vector<IP *> ip_ranges;
    ParamsParser* paramsParser;
    void eraseLines(int count);
    void printToSysLog(string ip);
    void initPrint();
    void setIPRanges();
    static double printRow(IP* ip_range);
public:
    DHCPStats(ParamsParser* paramPrs);
    void printOutput();
    vector<IP *> getIPRanges();
    void startSniffing();

};


#endif //DHCP_STATS_DHCPSTATS_H
