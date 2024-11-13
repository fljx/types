#ifndef INCLUDE_NETWORK_IP
#define INCLUDE_NETWORK_IP

#include <array>
#include <inttypes.h>
#include <sstream>

// -----------------------------------------------------------------

template<typename T, unsigned int sz>
inline unsigned int lengthof(T (&)[sz]) { return sz; }

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
            uint32_t lit_end;
        }
            data;

        const uint8_t &operator[](int i) const
        {   return const_cast<IPv4&>(*this)[i];   }
        uint8_t &operator[](int i)
        {   return data.bytes[i]; }

        friend std::istream & operator>>(std::istream &is, IPv4 &ip);
    };

    std::string to_string(const IPv4  &data);

    std::ostream & operator<<(std::ostream &os, const IPv4 &ip);

    std::istream & operator>>(std::istream &is, IPv4 &ip);

// -----------------------------------------------------------------

}   // jx::types::network

#endif /* INCLUDE_NETWORK_IP */
