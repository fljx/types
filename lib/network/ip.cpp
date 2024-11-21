#include <locale>

#include "network/ip.h"

namespace jx::types::network
{
// -----------------------------------------------------------------

    IPv4::IPv4(const std::string &from)
    {
        std::istringstream is{from};
        is >> *this;
    }

// -----------------------------------------------------------------

    std::string to_string(const IPv4 &data)
    {
        return std::to_string(data[0]) + "."
            + std::to_string(data[1]) + "."
            + std::to_string(data[2]) + "."
            + std::to_string(data[3]);
    }

    bool operator==(const IPv4 &ip1, const IPv4 &ip2)
    {
        return ip1.data.lit_end == ip2.data.lit_end;
    }

    bool operator!=(const IPv4 &ip1, const IPv4 &ip2)
    {
        return !(ip1 == ip2);
    }

    std::ostream & operator<<(std::ostream &os, const IPv4 &ip)
    {
        os << to_string(ip);
        return os;
    }

    // https://stackoverflow.com/a/7304184/466339
    struct field_separator : std::ctype<char>
    {
        field_separator()
        : std::ctype<char>(get_table())
        {}
        
        static mask const* get_table()
        {
            static mask rc[table_size];
            rc['.'] = std::ctype_base::space;
            rc[' '] = std::ctype_base::space;
            rc['\n'] = std::ctype_base::space;
            return &rc[0];
        }
    };

    std::istream & operator>>(std::istream &is, IPv4 &ip)
    {
        std::string s;
        //uint8_t n;
        // unsigned n;

        auto loc = is.getloc();
        is.imbue(std::locale(is.getloc(), new field_separator));

        for (size_t i = 0; i < sizeof(ip.data.bytes) && is.good(); ++i)
        {
            is >> s;
            ip[i] = static_cast<uint8_t>(std::stoi(s));

            // std::istream & operator>>(std::istream &is, uint8_t &);
            //  AKA unsigned char.
            // std::istream & operator>>(std::istream &is, unsigned &);
            // std::istream & operator>>(std::istream &is, int &);

            // is >> n;
            // ip[i] = static_cast<uint8_t>(n);
        }

        is.imbue(loc);

        return is;
    }

// -----------------------------------------------------------------

}   // jx::types::network
