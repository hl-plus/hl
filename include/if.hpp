/********************/

#ifndef IF_SDJFGDSHFGJDSFJGDSFJHGDSF_HPP
#define IF_SDJFGDSHFGJDSFJGDSFJHGDSF_HPP

#if defined (HL_INSTALLED)
#   include <hl/bool_types.hpp>
#else
#   include "../include/bool_types.hpp"
#endif

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
# define C_PLUS_PLUS_0x11
# pragma GCC system_header
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)
namespace hl
{
template<int I>
struct int_
{
    enum
    {
        value = I
    };
};

template<int Value, typename Type0, typename Type1>
struct if_c
{
    typedef Type0 type;
};

template<typename Type0, typename Type1>
struct if_c<0, Type0, Type1>
{
    typedef Type1 type;
};

template<typename IsShouldBeId2Type>
struct is_id2type_type
{
    enum
    {
        value = 0, id2type_value = 0
    };
};

template<int I>
struct is_id2type_type<hl::id2type<I> >
{
    enum
    {
        value = 1, id2type_value = I
    };
};

template<typename Quest, typename TypeIfTrue, typename TypeIfFalse>
struct if_
#if defined(C_PLUS_PLUS_0x11)
{
static_assert(
        (is_id2type_type<Quest>::value &&
                (is_id2type_type<Quest>::id2type_value == 1 || is_id2type_type<Quest>::id2type_value == 0))
        , "This isn't correct type to check");
};
#else
;
#endif

template <typename TypeIfTrue
, typename TypeIfFalse>
struct if_<hl::true_type, TypeIfTrue, TypeIfFalse>
{
typedef TypeIfTrue type;
};

template <typename TypeIfTrue
, typename TypeIfFalse>
struct if_<hl::false_type, TypeIfTrue, TypeIfFalse>
{
typedef TypeIfTrue type;
};

}

#endif // IF_SDJFGDSHFGJDSFJGDSFJHGDSF_HPP
