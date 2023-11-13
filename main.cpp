/**
 * @file    main.cpp
 * @author  Richard Kocián (xkocia19)
 *
 * @brief   ISA Project - dhcp-stats
 * @date    2023-10-13
 */

#include "ParamsParser.h"
#include <pcap.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

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
    struct in_addr yiaddr;
    struct in_addr siaddr;
    struct in_addr giaddr;
    uint8_t chaddr[16];
    char sname[64];
    char file[128];
    uint32_t magic_cookie;
    uint8_t options[];
};

int main(int argc, char **argv) {
    printf("sizeof ether header: %lu\n", sizeof(struct ether_header));
    printf("sizeof ip header: %lu\n", sizeof(struct ip));
    printf("sizeof tcp header: %lu\n", sizeof(struct tcphdr));
    printf("sizeof udp header: %lu\n", sizeof(struct udphdr));
    auto test = "DHCPACK";
    printf("test: %d", test[0]);
    auto size_dhcp_data = sizeof(struct udphdr) + sizeof(struct ether_header) + sizeof(struct ip);
    printf("sizeof dhcp header: %lu\n", size_dhcp_data);

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

    // https://www.rhyous.com/2011/11/13/how-to-read-a-pcap-file-from-wireshark-with-c/

    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_t * pcap = pcap_open_offline(paramsParser.getFile().c_str(), errbuf);

    struct pcap_pkthdr *header;

    const u_char *packet;

    int packetCount = 0;

    while (int returnValue = pcap_next_ex(pcap, &header, &packet) >= 0)
    {
        printf("Packet # %i\n", ++packetCount);
        printf("Packet size: %d bytes\n", header->len);

        if (header->len < 236) {
            // Nemůže se jednat o dhcp packet, minimální velikost je 236 bytů, viz https://datatracker.ietf.org/doc/html/rfc2131
            continue;
        }

        auto dhcp_data = (struct dhcp_packet *) (packet + sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct udphdr));

        long long i = 0;
        while (dhcp_data->options[i] != 255) {
            //printf("Option value: %d\n", dhcp_data->options[i]);
            if (dhcp_data->options[i] == 5) {
                printf("DHCPACK detected\n");
                std::cout << "Přiřazená IP adresa: " << inet_ntoa(dhcp_data->yiaddr) << std::endl;
            }
            i++;
        }
    }


    return 0;
}
