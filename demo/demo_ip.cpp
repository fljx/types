#include <iostream>
#include <string_view>
#include <array>
#include <sstream>

#include "network/ip.h"

// -----------------------------------------------------------------

using jx::types::network::IPv4;
using dest_addr = jx::types::network::IPv4;

void test_IPv4()
{
    std::cout << __PRETTY_FUNCTION__ << "\n";

    dest_addr   ip(192, 168, 0, 10);
    std::cout << "[dest_addr] " << ip << "\n";  // No need to `to_string(ip)`.

    IPv4   ipv4{192, 168, 0, 10};
    std::cout << "[to_string(ipv4)] " << ipv4 << "\n";

    std::string test_string{"10.146.23.12 255.255.255.0 10.146.23.254"};
    std::istringstream is{test_string};

    std::cout << "=> IPv4 test string: \"" << test_string << "\".\n";

    while (is.good())
    {
        is >> ip;
        std::cout << "Extracted " << ip
            << ", '" << ip << "'\n";
    }

    std::cout << "------------------------------------\n";
}

// -----------------------------------------------------------------

int main()
{
    test_IPv4();
}

// -----------------------------------------------------------------
/*
https://godbolt.org/z/ja1a7oqjh
 */