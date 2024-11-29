#ifndef INCLUDE_NETWORK_IP
#define INCLUDE_NETWORK_IP

#include <array>
#include <inttypes.h>
#include <sstream>

// -----------------------------------------------------------------

namespace jx::types::network
{

    class IPv4
    {
    public:
        IPv4(uint8_t o1, uint8_t o2, uint8_t o3, uint8_t o4)
        :   data({o1, o2, o3, o4})
        {}

        IPv4(const std::array<uint8_t, 4> &o)
        :   IPv4(o[0], o[1], o[2], o[3])
        {}

        IPv4(const std::string &from);

        IPv4(const char *from)
        :   IPv4(std::string{from})
        {}

        union
        {
            uint8_t bytes[4];
            struct
            {
                uint8_t o0;
                uint8_t o1;
                uint8_t o2;
                uint8_t o3;
            } octets;
            // Caveat: this number must be in Network Order, not native!
            uint32_t lit_end;
        }
            data;

        const uint8_t &operator[](int i) const
        {   return const_cast<IPv4&>(*this)[i];   }
        uint8_t &operator[](int i)
        {   return data.bytes[i]; }

        friend std::istream & operator>>(std::istream &is, IPv4 &ip);
        friend bool operator==(const IPv4 &ip1, const IPv4 &ip2);
    };

    bool operator==(const IPv4 &ip1, const IPv4 &ip2);
    bool operator!=(const IPv4 &ip1, const IPv4 &ip2);

    std::string to_string(const IPv4 &data);

    std::ostream & operator<<(std::ostream &os, const IPv4 &ip);

    std::istream & operator>>(std::istream &is, IPv4 &ip);

// -----------------------------------------------------------------
/**/
//     class ipv4_mask
//     {
//     public:
//         ipv4_mask(IPv4 addr, IPv4 net_mask);
//         ipv4_mask(IPv4 addr, uint32_t bit_mask);

//         ipv4_mask operator+=(IPv4);

//         const IPv4 & address() const;
//         const IPv4 & mask() const;

//     private:
//         IPv4    address_;
//         IPv4    mask_;

//         void apply_mask();
//     };

//     ipv4_mask operator+(IPv4, IPv4);

//     std::string to_string(const ipv4_mask &data);

//     std::ostream & operator<<(std::ostream &os, const ipv4_mask &data);

// // -----------------------------------------------------------------

//     class ipv4_route
//     {
//     public:
//         ipv4_route(ipv4_mask net_mask, IPv4 gw);

//     private:
//         ipv4_mask   masked;
//         IPv4        gateway;
//     };

//     ipv4_route operator+(ipv4_mask, IPv4);

// -----------------------------------------------------------------

}   // jx::types::network

#endif /* INCLUDE_NETWORK_IP */
