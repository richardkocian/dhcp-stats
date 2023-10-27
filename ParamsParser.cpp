/**
 * @file    ParamsParser.cpp
 * @author  Richard Kocián (xkocia19)
 *
 * @brief   Class for parsing program parameters - ISA Project - dhcp-stats
 * @date    2023-10-13
 */

#include "ParamsParser.h"

ParamsParser::ParamsParser(int argc, char **argv) {
    int c;
    int t = 0;
    while ( (c = getopt(argc, argv, "r:i:")) != EOF) {
        switch (c) {
            case 'r':
                t+=2;
                fileName = optarg;
                break;
            case 'i':
                t+=2;
                interface = optarg;
                break;
            default:
                fprintf(stderr,"Unknown parameter!\n");
                exit(EXIT_FAILURE);
        }
    }
    for (int i = t+1; i < argc; ++i) {

        /*********************************************************
        *    Validating IPv4 addresses with regexp
        *    Author: Danail Gabenski
        *    Date: Apr 21, 2016 at 5:01
        *    Availability: https://stackoverflow.com/a/36760050
        **********************************************************/
        regex ipRegex(R"(^((25[0-5]|(2[0-4]|1\d|[1-9]|)\d)\.?\b){4}\/([1-2]?[\d]|3[0-2])$)");
        if (regex_match (argv[i], ipRegex)) {
            ipAddresses.push_back(argv[i]);
        } else {
            fprintf(stderr,"Unknown parameter! %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }

    }
}

string ParamsParser::getFile() {
    return fileName;
}

string ParamsParser::getInterface() {
    return interface;
}

vector<string> ParamsParser::getIpAddresses() {
    return ipAddresses;
}
