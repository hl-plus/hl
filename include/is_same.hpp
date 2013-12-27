/*********************/

#ifndef IS_SDFKIHWESRERLBGPBODVBJCXKVB_SAME_HPP
#define IS_SDFKIHWESRERLBGPBODVBJCXKVB_SAME_HPP

#if defined (__HL_INSTALLED)
#   include <hl/bool_types.hpp>
#else
#   include "../include/bool_types.hpp"
#endif

namespace hl
{
template<typename Type0, typename Type1>
struct is_same: false_type
{
};

template<typename Type>
struct is_same<Type, Type> : true_type
{
};
}

#endif // IS_SDFKIHWESRERLBGPBODVBJCXKVB_SAME_HPP
