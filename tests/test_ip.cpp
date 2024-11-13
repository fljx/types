#include <iostream>
#include <string_view>
#include <array>
#include <sstream>
#include <numeric>
#include "gtest/gtest.h"

#include "network/ip.h"

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

TEST_F(test_ip_fixture, test_IPv4)
{
    std::cout << __PRETTY_FUNCTION__ << "\n";

    IPv4   ip(192, 168, 0, 10);
    std::ostringstream oss;

    oss << ip;

    ASSERT_TRUE(oss.str() == "192.168.0.10");

    std::istringstream is{test_list};

    for (size_t i = 0; is.good()
        && i < sizeof(test_strings)/sizeof(test_strings[0]);
        ++i)
    {
        is >> ip;
        ASSERT_TRUE(to_string(ip) == test_strings[i]);
    }

    std::cout << "------------------------------------\n";
}

// -----------------------------------------------------------------
/*
https://godbolt.org/z/dTznTeof4
*/