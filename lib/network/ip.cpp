#include <locale>

#include "network/ip.h"

namespace jx::types::network
{

// -----------------------------------------------------------------

template<typename T, unsigned int sz>
inline unsigned int lengthof(T (&)[sz]) { return sz; }

// -----------------------------------------------------------------

std::string to_string(const IPv4  &data)
{
    return std::to_string(data[0]) + "."
           + std::to_string(data[1]) + "."
           + std::to_string(data[2]) + "."
           + std::to_string(data[3]);
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

    auto loc = is.getloc();
    is.imbue(std::locale(is.getloc(), new field_separator));

    for (size_t i = 0; i < sizeof(ip.data.bytes) && is.good(); ++i)
    {
        is >> s;
        ip[i] = static_cast<uint8_t>(std::stoi(s));
    }

    is.imbue(loc);

    return is;
}

// -----------------------------------------------------------------

}   // jx::types::network
