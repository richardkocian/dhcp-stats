//
// Created by Richard Kocián on 14.11.2023.
//

#include "DHCPStats.h"

DHCPStats::DHCPStats(ParamsParser *paramPrs) {
    this->paramsParser = paramPrs;
    setIPRanges();
    initPrint();
}

void DHCPStats::setIPRanges() {
    for (const auto &ip: paramsParser->getIpAddresses()) {
        ip_ranges.push_back(new IP(ip));
    }
}

void DHCPStats::initPrint() {
    for (const auto &ip_range: ip_ranges) {
        printRow(ip_range);
    }
}

double DHCPStats::printRow(IP* ip_range) {
    double stats = ((double) ip_range->get_allocated_max_addresses() / (double) ip_range->get_max_address()) * 100;
    cout << ip_range->getIP_str() << " " << (int) ip_range->get_max_address() << " "
         << (int) ip_range->get_allocated_max_addresses() << " " << setprecision(4) << (double) stats << "%"
         << endl;
    return stats;
}

/*********************************************************
*    Title: C++ How do I erase a line from the console?
*    Author: Kein
*    Date: May 20, 2020 at 19:17
*    Availability: https://stackoverflow.com/a/61921163
**********************************************************/
void DHCPStats::eraseLines(int count) {
    if (count > 0) {
        std::cout << "\x1b[2K"; // Delete current line
        // i=1 because we included the first line
        for (int i = 1; i < count; i++) {
            std::cout
                    << "\x1b[1A" // Move cursor up one
                    << "\x1b[2K"; // Delete the entire line
        }
        std::cout << "\r"; // Resume the cursor at beginning of line
    }
}

void DHCPStats::printOutput() {
    eraseLines(ip_ranges.size() + 1);
    for (const auto &ip_range: ip_ranges) {
        double stats = printRow(ip_range);
        if (stats > 50) {
            printToSysLog(ip_range->getIP_str());
        }
    }
}

void DHCPStats::printToSysLog(string ip) {
    // viz https://www.gnu.org/software/libc/manual/html_node/Syslog-Example.html
    setlogmask(LOG_UPTO (LOG_ALERT));

    openlog("dhcp-stats", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

    syslog(LOG_ALERT, "prefix %s exceeded 50%% of allocations", ip.c_str());

    closelog();
}

vector<IP *> DHCPStats::getIPRanges() {
    return ip_ranges;
}

struct dhcp_packet {
    // struktura dhcp packetu, viz https://datatracker.ietf.org/doc/html/rfc2131
    uint8_t op;
    uint8_t htype;
    uint8_t hlen;
    uint8_t hops;
    uint32_t xid;
    uint16_t secs;
    uint16_t flags;
    struct in_addr ciaddr;
    uint8_t yiaddr[4];
    struct in_addr siaddr;
    struct in_addr giaddr;
    uint8_t chaddr[16];
    char sname[64];
    char file[128];
    uint32_t magic_cookie;
    uint8_t options[];
};

void DHCPStats::startSniffing() {
    // https://www.rhyous.com/2011/11/13/how-to-read-a-pcap-file-from-wireshark-with-c/
    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_t *pcap;
    if (empty(paramsParser->getInterface())) {
        pcap = pcap_open_offline(paramsParser->getFile().c_str(), errbuf);
    } else {
        pcap = pcap_open_live(paramsParser->getInterface().c_str(), BUFSIZ, 1, 1000, errbuf);
    }
    if (pcap == nullptr) {
        fprintf(stderr, "%s\n", errbuf);
        exit(2);
    }

    struct pcap_pkthdr *header;
    const u_char *packet;

    while (int returnValue = pcap_next_ex(pcap, &header, &packet) >= 0) {
        if (header->len < 236) {
            // Nemůže se jednat o dhcp packet, minimální velikost je 236 bytů, viz https://datatracker.ietf.org/doc/html/rfc2131
            continue;
        }

        auto dhcp_data = (struct dhcp_packet *) (packet + sizeof(struct ether_header) + sizeof(struct ip) +
                                                 sizeof(struct udphdr));

        long long i = 0;
        while (dhcp_data->options[i] != 255) {
            if (dhcp_data->options[i] == 5) {
                int ip = (dhcp_data->yiaddr[0] << 24) + (dhcp_data->yiaddr[1] << 16) + (dhcp_data->yiaddr[2] << 8) + (dhcp_data->yiaddr[3]);

                for (const auto &ip_range: getIPRanges()) {
                    ip_range->is_IP_in_range(ip);
                    printOutput();
                }
            }
        }
    }
}
