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
    // -----------------------------------------------------------------

    // ipv4_mask::ipv4_mask(IPv4 addr, IPv4 net_mask)
    // :   address_(addr),
    //     mask_(net_mask)
    // {
    //     apply_mask();
    // }

    // ipv4_mask::ipv4_mask(IPv4 addr, uint32_t bit_mask)
    // // Ugly `reinterpret_cast`. IPv4 should have a constructor.
    // :   ipv4_mask(addr, reinterpret_cast<IPv4>(bit_mask))
    // {}

    // ipv4_mask ipv4_mask::operator+=(IPv4)
    // { return ipv4_mask(); }

    // const IPv4 &ipv4_mask::address() const
    // {   return address_; }

    // const IPv4 &ipv4_mask::mask() const
    // {   return mask_; }

    // void ipv4_mask::apply_mask()
    // {
    //     address_.data.lit_end &= mask_.data.lit_end;
    // }

    // std::string to_string(const ipv4_mask &data)
    // {
    //     return to_string(data.address())
    //         + "/" + to_string(data.mask());
    // }

    // std::ostream &operator<<(std::ostream &os, const ipv4_mask &data)
    // {
    //     os << to_string(data);
    //     return os;
    // }

    // // -----------------------------------------------------------------
    // ipv4_route::ipv4_route(ipv4_mask net_mask, IPv4 gw) {}

    // // -----------------------------------------------------------------
    // ipv4_route operator+(ipv4_mask, IPv4)
    // { return ipv4_route(); }

    // -----------------------------------------------------------------

} // namespace jx::types::network
