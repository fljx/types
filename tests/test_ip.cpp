#include <iostream>
#include <string_view>
#include <array>
#include <sstream>
#include <numeric>
#include "gtest/gtest.h"

#include "network/ip.h"
#include "extend/niceties.h"

// -----------------------------------------------------------------

using jx::types::network::IPv4;

class test_ip_fixture : public testing::Test
{
protected:
    static constexpr std::string test_strings[] = {
        "10.146.23.12", "255.255.255.0", "10.146.23.254"};

    std::string test_list;

public:
    test_ip_fixture()
    {
        std::string draft;
        std::accumulate(std::begin(test_strings),
                        std::end(test_strings), 0,
                        [&draft](size_t, const std::string_view &s)
                        {
                            if (!draft.empty())
                            {
                                draft.append(", ");
                            }
                            draft.append(s);
                            return 0;
                    });
        test_list = draft;
    }
};

TEST_F(test_ip_fixture, test_IPv4_basic)
{
    // Direct octets constructor.
    IPv4   ip1(192, 168, 0, 10);

    ASSERT_TRUE(   ip1[0] == 192
                && ip1[1] == 168
                && ip1[2] == 0
                && ip1[3] == 10);

    // std::array constructor.
    IPv4   ip2(std::array<uint8_t, 4>{192, 168, 1, 101});

    ASSERT_TRUE(   ip2[0] == 192
                && ip2[1] == 168
                && ip2[2] == 1
                && ip2[3] == 101);

    // std::string constructor.
    IPv4   ip3("10.152.200.26");

    ASSERT_TRUE(   ip3[0] == 10
                && ip3[1] == 152
                && ip3[2] == 200
                && ip3[3] == 26);

    // Comparison operator.
    ASSERT_FALSE( ip1 == ip2 );
    ASSERT_TRUE( ip1 != ip3 );

    // Test modifying it.
    ip1[0] = 10;
    ip1[1] = 132;
    ip1[2] = 0;
    ip1[3] = 66;

    ASSERT_TRUE(ip1 == IPv4(10, 132, 0, 66));

    // Test convert to string.
    ASSERT_FALSE("192.168.0.10" == to_string(ip1));
    ASSERT_TRUE("10.132.0.66" == to_string(ip1));

    // Test compare to implicitly built from string.
    ASSERT_NE(ip1, "192.168.0.10");
    ASSERT_EQ(ip1, "10.132.0.66");
    // auto result = (ip1 == "192.168.0.10");
    // ASSERT_TRUE(result);
    ASSERT_EQ(ip1, std::string{"10.132.0.66"});
    ASSERT_TRUE(ip1 != std::string{"192.168.0.10"});

    // ASSERT_TRUE("192.168.0.10" == ip);

    std::cout << "------------------------------------\n";
}

TEST_F(test_ip_fixture, test_IPv4_stream)
{
    IPv4   ip(192, 168, 0, 10);
    std::ostringstream oss;

    oss << ip;

    ASSERT_TRUE(oss.str() == "192.168.0.10");

    std::istringstream is{test_list};

    for (size_t i = 0; is.good()
        && i < jx::types::count_of(test_strings);
        ++i)
    {
        is >> ip;

std::cout << i << ") to_string(ip): " << to_string(ip)
    << " == test_strings[i]: " << test_strings[i] << std::endl;

        ASSERT_TRUE(to_string(ip) == test_strings[i]);
        //ASSERT_TRUE(ip == test_strings[i]);
    }

    std::cout << "------------------------------------\n";
}

// -----------------------------------------------------------------
/*
https://godbolt.org/z/dTznTeof4
https://godbolt.org/z/sh395c87G
*/