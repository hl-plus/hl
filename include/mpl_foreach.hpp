/*********************/

#ifndef MPL_FOREACH_HPP_123BEFC2_60B6_11E2_B4ED_E20E6288709B_INCLUDED
#define MPL_FOREACH_HPP_123BEFC2_60B6_11E2_B4ED_E20E6288709B_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
# pragma GCC system_header
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if defined (__HL_INSTALLED)
#    include <hl/include/vi_item.hpp>
#    include <hl/include/is_same.hpp>
#    include <hl/include/t_list_helper.hpp>
#else
#    include "../include/vi_item.hpp"
#    include "../include/is_same.hpp"
#    include "../include/t_list_helper.hpp"
#endif


namespace hl
{
    namespace detail
    {
        template <typename type>
        struct is_mpl_vector : hl::false_type
        {    };
#if defined (__BOOST_INSTALLED)
        template<
              typename T0, typename T1, typename T2, typename T3, typename T4
            , typename T5, typename T6, typename T7, typename T8, typename T9
            , typename T10, typename T11, typename T12, typename T13, typename T14
            , typename T15, typename T16, typename T17, typename T18, typename T19
            >
        struct is_mpl_vector<
                    boost::mpl::vector
                    <
                          T0, T1, T2, T3, T4
                        , T5, T6, T7, T8, T9
                        , T10, T11, T12, T13, T14
                        , T15, T16, T17, T18, T19
                    >
                > : hl::true_type
        {    };
#endif
    } //detail
} //namespace hl

namespace hl
{
    struct null_type;

#if !defined(__USE_BASIC_HL)
    template <typename Type, typename Base, int I>
    struct vi_extract<boost::mpl::v_item<Type, Base, I> >
    {
        enum { value = 1, V = I };

        typedef Type type;
        typedef Base base;
        typedef Base next;
    };
#endif

    namespace detail
    {
        template <typename type, typename functor_type>
        inline bool
        for_each_impl_(functor_type fn, hl::true_type)
        {   return true; }

        template <typename type, typename functor_type>
        inline bool
        for_each_impl_(functor_type fn, hl::false_type)
        {
          if (!fn.template operator()<typename vi_extract<type>::type >())
              return detail::for_each_impl_<typename vi_extract<type>::base>(fn
                        , hl::is_same<typename vi_extract<type>::next, null_type >());
          return true;
        }

          //Iterator by v_item || boost::mpl::v_item
        template <typename type, typename functor_type>
        inline bool
        for_each_impl(functor_type fn, hl::false_type)
        {
        return detail::for_each_impl_<type>(fn
                   , hl::is_same<typename vi_extract<type>::type, null_type >());

        }

        template <int I, int Sz, typename type, typename functor_type>
        inline bool
        for_each_vc_impl_(functor_type fn, hl::false_type)
        {  return true;  }

        template <int I, int Sz, typename type, typename functor_type>
        inline bool
        for_each_vc_impl_(functor_type fn, hl::true_type)
        {
#        if defined(__USE_BOOST_MPL_)
        typedef typename
            boost::mpl::at_c<type, I>::type cur_type;
#        else
        typedef typename
            hl::at_c<type, I>::type cur_type;
#        endif

            if (!fn.template operator()<cur_type >())
                return detail::for_each_vc_impl_<(I + 1), Sz, type>(fn, hl::id2type<((I + 1) < Sz)>());

            return true;
        }

        //vector iteration
        template <typename type, typename functor_type>
        inline bool
        for_each_impl(functor_type fn, hl::true_type)
        {
            enum
            {
#            if defined(__USE_BOOST_MPL_)
                size_ = boost::mpl::size<type>::type::value
#            else
                size_ = hl::size<type>::value
#            endif
            };

            return detail::for_each_vc_impl_<0, size_, type>(fn, hl::id2type<(size_ > 0)>());
        }
    }

    template <typename type
         , typename functor_type>
    inline bool
    for_each(functor_type fn)
    {
        // if returned will true we stop iteration
        return detail::for_each_impl<type>(fn, hl::detail::is_mpl_vector<type>());
    }

} // namespace hl

#endif
