/**
 * @file    ParamsParser.h
 * @author  Richard Kocián (xkocia19)
 *
 * @brief   Class for parsing program parameters - ISA Project - dhcp-stats
 * @date    2023-10-13
 */

#ifndef DHCP_STATS_PARAMSPARSER_H
#define DHCP_STATS_PARAMSPARSER_H

#include <iostream>
#include <vector>
#include <unistd.h>
#include <regex>


using namespace std;

class ParamsParser {
private:
    string fileName;
    string interface;
    vector<string> ipAddresses;
public:
    ParamsParser(int argc, char **argv);
    string getFile();
    string getInterface();
    vector<string> getIpAddresses();
};


#endif //DHCP_STATS_PARAMSPARSER_H
