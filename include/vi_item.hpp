/*******************/

#ifndef VI_ITEMSDKJHFGKJSHDFKGJHSDFKJHGSDKHFJGKJSHDFGKDSFG_INCLUDED
#define VI_ITEMSDKJHFGKJSHDFKGJHSDFKJHGSDKHFJGKJSHDFGKDSFG_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#   pragma once
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
#   pragma GCC system_header
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

namespace hl
{
    template <typename Type, typename Base, int I>
    struct v_item
    {
        typedef Type type;
        typedef Base base;
    };
}

#if defined(__USE_BOOST_MPL_) && defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
    #include <boost/mpl/vector.hpp>
    #include <boost/mpl/int.hpp>
namespace hl
{
    template <typename Type, typename Base, int I>
    struct vi_type
    {    typedef boost::mpl::v_item<Type, Base, I> type; };
}

#else

#define __USE_BASIC_HL

namespace hl
{
    template <typename Type, typename Base, int I>
    struct vi_type
    {    typedef hl::v_item<Type, Base, I> type; };
}

#if /*!defined(__USE_BOOST_MPL_) && !defined(__USE_HL_MPL) &&*/ defined(__USE_HL_INT)
namespace boost {
    namespace mpl {
        template <int I>
            struct int_ {    enum {value = I };};
    }
}
#else
    #include <boost/mpl/int.hpp>
#endif

#endif

#endif
