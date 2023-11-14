/**
 * @file    main.cpp
 * @author  Richard Kocián (xkocia19)
 *
 * @brief   ISA Project - dhcp-stats
 * @date    2023-10-13
 */

#include "ParamsParser.h"
#include "DHCPStats.h"


int main(int argc, char **argv) {
    auto paramsParser = ParamsParser(argc, argv);
    cout << "IP-Prefix Max-hosts Allocated addresses Utilization" << endl;
    auto dhcpStats = new DHCPStats(&paramsParser);
    dhcpStats->startSniffing();
    return 0;
}
