#ifndef INCLUDE_POWER_ENUM
#define INCLUDE_POWER_ENUM

#include <sstream>

#include "extend/niceties.h"


namespace jx::types::extend
{
    template<typename Underlying = unsigned, Underlying InvalidValue>
    class power_enum
    {
        Underlying value_;
    public:

        static constexpr Underlying Invalid = InvalidValue;

        power_enum(Underlying value = Invalid)
        :   value_(value)
        {}

        operator Underlying() const
        {   return value_;  }

        static power_enum invalid()
        {   return power_enum{Invalid};   }

    private:
        friend std::string to_string(const power_enum &data);
        friend std::istream & operator>>(std::istream &is, power_enum &et);

    static const constexpr std::string_view encoderStrings_[] = {"H.264", "H.265"};
    static const constexpr Underlying count = count_of(encoderStrings_);
    };

    template<typename Underlying = unsigned, Underlying InvalidValue>
    std::string to_string(const power_enum<Underlying, InvalidValue> &data)
    {
        if (data < power_enum::count)
        {
            return std::string{power_enum::encoderStrings_[data]};
        }

        return "NA";
    }

    template<typename Underlying = unsigned, Underlying InvalidValue>
    std::istream & operator>>(std::istream &is,
                              power_enum<Underlying, InvalidValue> &et)
    {
        std::string s;
        is >> s;

        et = power_enum<Underlying, InvalidValue>::invalid();

        for (size_t i = 0; i < count_of(power_enum::encoderStrings_); ++i)
        {
            auto ets = power_enum::encoderStrings_[i];

            if (s == ets)
            {
                et = {static_cast<Underlying>(i)};
                break;
            }
        }

        return is;
    }

    template<typename Underlying = unsigned, Underlying InvalidValue>
    std::ostream & operator<<(std::ostream &os,
                              const power_enum<Underlying, InvalidValue> &et)
    {
        os << to_string(et);
        return os;
    } 
} // namespace jx::types::extend


#endif  // INCLUDE_POWER_ENUM

