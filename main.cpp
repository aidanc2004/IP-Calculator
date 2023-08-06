#include <iostream>
#include <cmath>

typedef unsigned int address;

const address FIRST_OCTET  = 0b11111111000000000000000000000000;
const address SECOND_OCTET = 0b00000000111111111000000000000000;
const address THIRD_OCTET  = 0b00000000000000001111111100000000;
const address FOURTH_OCTET = 0b00000000000000000000000011111111;

// counts number of on bits in an address
// http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetNaive
unsigned int countbits(address v) {
    unsigned int c; // c accumulates the total bits set in v

    for (c = 0; v; v >>= 1) {
        c += v & 1;
    }

    return c;
}

// convert address into string
std::string addrstr(address addr) {
    // seperate address into octets
    int octets[4];
    octets[0] = (addr & FIRST_OCTET) >> 24;
    octets[1] = (addr & SECOND_OCTET) >> 16;
    octets[2] = (addr & THIRD_OCTET) >> 8;
    octets[3] = (addr & FOURTH_OCTET);

    // join together octets with '.'
    std::string result = std::to_string(octets[0]) + "." + std::to_string(octets[1])+ "." +
                         std::to_string(octets[2]) + "." + std::to_string(octets[3]);

    return result;
}

// convert string into address 
address straddr(std::string addr) {
    // TODO
    return 123;
}

// get minimum host number
address getHostMin(address networkAddress) {
    return networkAddress + 1;
}

// get maximum host number
address getHostMax(address broadcast) {
    return broadcast - 1;
}

int main() {
    // hardcoded for now
    address addr    = 0b11000000101010000000000010011010; // 192.168.0.154
    address netmask = 0b11111111111111111111111100000000; // 255.255.255.0 (/24)

    // number of hosts that can be on a network
    int numberofhosts = std::pow(2, countbits(~netmask)) - 2;
    // host mask
    address wildcard = ~netmask;
    // reserved for network address and broadcast address
    address networkAddress = addr & netmask;
    address broadcast = addr | wildcard;
    // the minimum and maximum host on a network
    address minHost = getHostMin(networkAddress);
    address maxHost = getHostMax(broadcast);

    std::cout << "Address:           " << addrstr(addr) << '\n';
    std::cout << "Netmask:           " << addrstr(netmask) << "\n\n";

    std::cout << "Network address:   " << addrstr(networkAddress) << '\n';
    std::cout << "Wildcard:          " << addrstr(wildcard) << '\n';
    std::cout << "Broadcast address: " << addrstr(broadcast) << '\n';

    std::cout << "Number of Hosts:   " << numberofhosts << '\n';

    std::cout << "Minimum Host:      " << addrstr(minHost) << '\n';
    std::cout << "Maximum Host:      " << addrstr(maxHost) << '\n';

    return 0;
}