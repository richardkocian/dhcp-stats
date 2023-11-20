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
    // Program parameters parsing
    auto paramsParser = ParamsParser(argc, argv);

    cout << "IP-Prefix Max-hosts Allocated addresses Utilization" << endl;

    // Initialization
    auto dhcpStats = new DHCPStats(&paramsParser);

    // Start sniffing received packets and printing DHCP statistics
    dhcpStats->startSniffing();
    return 0;
}
