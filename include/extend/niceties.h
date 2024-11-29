#ifndef INCLUDE_NICETIES
#define INCLUDE_NICETIES

namespace jx::types
{
    template<typename T, unsigned int sz>
    inline unsigned int count_of(T (&)[sz]) { return sz; }
} // namespace jx::types


#endif  // INCLUDE_NICETIES
