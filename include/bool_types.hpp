/******************/

#ifndef BOOL_TYPES_ESWRHTGKSNDFGASNDVGKASDHNGKASDGLJA_HPP
#define BOOL_TYPES_ESWRHTGKSNDFGASNDVGKASDHNGKASDGLJA_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
# define C_PLUS_PLUS_0x11
# pragma GCC system_header
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

namespace hl
{
template<int V>
struct id2type
{
    typedef id2type type;
    enum
    {
        value = V
    };
};

typedef id2type<1> true_type;
typedef id2type<0> false_type;

}

#endif
