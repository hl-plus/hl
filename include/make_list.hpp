/********************/

#ifndef MAKE_LIST_HPP_INCLUDED_IDSUGDJGFDSJFHGKSJROIQIWTEEWOJFLASDJNVDSAV
#define MAKE_LIST_HPP_INCLUDED_IDSUGDJGFDSJFHGKSJROIQIWTEEWOJFLASDJNVDSAV

#if defined (__BOOST_INSTALLED)
#    include <boost/type_traits/is_same.hpp>
#    include <boost/mpl/vector.hpp>
#    include <boost/mpl/if.hpp>
#endif

#include "sfinae.hpp"
namespace hl
{

namespace detail {

template <typename type_, typename tail_> struct tl_item
{   };
}
struct null_type;

template <typename... Rest>
struct make_list
{
    typedef boost::mpl::vector<hl::null_type > types;
};

template <typename type, typename... Rest>
struct make_list<type, Rest... >
{
    typedef hl::detail::tl_item<type, typename make_list<Rest... >::types > types;
};

template <typename... Rest>
struct make_mpl
{
    typedef hl::null_type types;
};

template <typename type, typename... Rest>
struct make_types<type, Rest... >
{
    typedef typename
        boost::mpl::if_c<
                boost::is_same<typename make_types<Rest... >::types
                                , hl::null_type>::value
                , boost::mpl::vector<type>
                , boost::mpl::v_item<type, typename make_types<Rest... >::types, 1 >
        >::type types;
};

template <typename type_ >
struct is_vi_item
{ enum { value = 0 };   };

template < typename type_
        , typename base_
        , int I >
struct is_vi_item <boost::mpl::v_item<type_, base_, I> >
{
    enum { value = 1 };
    typedef base_ next;
};

template <typename type_
            , typename base_
            , int I>
struct is_vi_item<hl::detail::tl_item<type_, base_, I> >
{
    enum {  value = 1 };
    typedef base_ next;
};

template <typename tll
    , int ix_ = 0
    , int is_ = is_vi_item<tll >::value>
struct size
{
    enum { value
        = size<typename is_vi_item<tll>::next, ix_ + 1 >::value };
};

template <typename tll
        , int ix_>
struct size<tll, ix_, 0>
{
    enum { value = boost::is_same<tll
           , hl::null_type>::value ? ix_ : ix_ + 1 };
};

} //namespace hl 


#endif // MAKE_LIST_HPP_INCLUDED_IDSUGDJGFDSJFHGKSJROIQIWTEEWOJFLASDJNVDSAV
