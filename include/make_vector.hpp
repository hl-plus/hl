/***********************/

#ifndef MAKE_VECTOR_HPP_DSLKFJHLGKSDJFHGLKSDJDLKSGJFHKGJRYT_INCLUDED
#define MAKE_VECTOR_HPP_DSLKFJHLGKSDJFHGLKSDJDLKSGJFHKGJRYT_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
# pragma GCC system_header
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/mpl/size.hpp>
#include "make_types.hpp"

namespace hl
{

namespace detail
{
    template <int I>
    struct id2type
    {   };

    typedef id2type<1> true_type;
    typedef id2type<0> false_type;

    template <int I, typename ResultType, typename vector_type, typename... Types>
    inline vector_type&
    make_vector__(vector_type& vc, false_type, Types... v)
    {   return vc;  }

    template <int I, typename ResultType, typename vector_type, typename type, typename... Types>
    inline vector_type&
    make_vector__(vector_type& vc, true_type, type value, Types... vss)
    {
        typedef typename make_types<Types... >::type __rest_type;
        enum {  sizeof__ = boost::mpl::size<__rest_type>::value     };
        vc[I] = ResultType(value);
        return make_vector__<I + 1, ResultType>(vc, detail::id2type<(sizeof__ > 0)>(),  vss...);
    }
}

template <typename ResultType, typename... Types>
inline std::vector <ResultType>
make_vector (Types... vss)
{
   typedef typename make_types<Types... >::type __list_type;
   enum {  sizeof__ = boost::mpl::size<__list_type>::value };

   std::vector<ResultType > vc;
   vc.resize(sizeof__);

   return detail::make_vector__<0, ResultType >(vc, detail::id2type<(sizeof__ > 0)>(), vss...);
}

template <typename... Types>
inline std::vector<std::string>
make_str_vector(Types... vss)
{   return make_vector<std::string>(vss...); }


} //namespace hl

#endif // MAKE_VECTOR_HPP_DSLKFJHLGKSDJFHGLKSDJDLKSGJFHKGJRYT_INCLUDED
