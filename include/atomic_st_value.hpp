
/****************/
#ifndef ATOMIC_ST_VALUE_HPP_INCLUDED_SDKGFNBDFKGBNJDFKGJHDFGKHJDKFGJHDKFGJKGJFS
#define ATOMIC_ST_VALUE_HPP_INCLUDED_SDKGFNBDFKGBNJDFKGJHDFGKHJDKFGJHDKFGJKGJFS

#include <atomic>

namespace hl
{
    template <typename Type, typename Branch>
    struct atomic_st_value
    {
        static std::atomic<Type> value_;
    };

    template <typename Type, typename Branch>
    std::atomic<Type> atomic_st_value<Type, Branch>::value_ (false);
}

#endif //ATOMIC_ST_VALUE_HPP_INCLUDED_SDKGFNBDFKGBNJDFKGJHDFGKHJDKFGJHDKFGJKGJFS
