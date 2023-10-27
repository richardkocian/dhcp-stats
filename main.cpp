/**
 * @file    main.cpp
 * @author  Richard Kocián (xkocia19)
 *
 * @brief   ISA Project - dhcp-stats
 * @date    2023-10-13
 */

#include "ParamsParser.h"

int main(int argc, char **argv) {
    auto paramsParser = ParamsParser(argc,argv);

    if (empty(paramsParser.getFile())) {
        cout << "Filename: unknown" << endl;
    } else {
        cout << "Filename: " + paramsParser.getFile() << endl;
    }

    if (empty(paramsParser.getInterface())) {
        cout << "Interface: unknown" << endl;
    } else {
        cout << "Interface: " + paramsParser.getInterface() << endl;
    }
    for (const auto& ip : paramsParser.getIpAddresses()) {
        cout << "IP: " + ip << endl;
    }
    return 0;
}
