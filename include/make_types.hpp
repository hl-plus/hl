/*********************/

#ifndef MAKE_TYPES_HPP_SEKRHTGLKDSJFHGLDKJFHBVMXCVBMNDHGFGJFG_INCLUDED
#define MAKE_TYPES_HPP_SEKRHTGLKDSJFHGLDKJFHBVMXCVBMNDHGFGJFG_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
# pragma GCC system_header
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if !defined(__USE_BOOST_MPL_) || defined (__USE_HL_MPL)
#if defined (__HL_INSTALLED)
#    include <hl/if.hpp>
#    include <hl/is_same.hpp>
#    include <hl/t_list_helper.hpp>
#else
#    include "../include/if.hpp"
#    include "../include/is_same.hpp"
#    include "../include/t_list_helper.hpp"
#endif
#endif

namespace hl
{

struct null_type;

#if defined(__USE_BOOST_MPL_)
    typedef boost::mpl::vector0<> null_type_def;
#else
    typedef null_type null_type_def;
#endif


template <typename... Rest>
struct make_types
{
#if defined(__USE_BOOST_MPL_)
    typedef boost::mpl::vector0<> type;
#else
    typedef null_type_def type;
#endif
};

template <typename Type, typename... Rest>
struct make_types<Type, Rest... >
{
#if defined(__USE_BOOST_MPL_)
    typedef typename
        boost::mpl::if_c<
                (boost::is_same<typename make_types<Rest... >::type
                                , null_type_def >::value || 1)
                , boost::mpl::vector<Type>
                , boost::mpl::v_item<Type, typename make_types<Rest... >::type, 1 >
        >::type type;
#else
    typedef typename
        hl::if_c<
                hl::is_same<typename make_types<Rest... >::type
                       , null_type_def >::value
                , hl::end_of_tlist<Type>
                , hl::v_item<Type, typename make_types<Rest... >::type, 1 >
        >::type type;
#endif
};

template <typename Type >
struct is_vi_item
{
    enum { value = 0 };
    typedef null_type base;
    typedef null_type type;
};

#if defined(__USE_BOOST_MPL_)
template < typename Type
        , typename Base
        , int I >
struct is_vi_item <boost::mpl::v_item<Type, Base, I> >
{
    enum { value = 1 };
    typedef Base base;
    typedef Type type;
};

template <typename Type, typename Next, int I = 1>
struct push_front
{
    typedef boost::mpl::v_item<Type, Next, I> type;
};

#else

template <typename Type, typename Base, int I>
struct v_item;

template < typename Type
        , typename Base
        , int I >
struct is_vi_item <hl::v_item<Type, Base, I> >
{
    enum { value = 1 };
    typedef Type type;
    typedef Base base;
};

template <typename Type, typename Next, int I = 1>
struct push_front
{
    typedef hl::v_item<Type, Next, I> type;
};

#endif

} // namespace hl


#endif // MAKE_TYPES_HPP_SEKRHTGLKDSJFHGLDKJFHBVMXCVBMNDHGFGJFG_INCLUDED
