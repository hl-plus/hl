/**********************/

#ifndef EXTRACTOR_HPP_123BEFC2_60B6_11E2_B4ED_E20E6288709B_INCLUDED
#define EXTRACTOR_HPP_123BEFC2_60B6_11E2_B4ED_E20E6288709B_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
# pragma GCC system_header
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)
///
// This file contains functionality of extractor to reflection inside a namespace scope
//

#ifdef __HL_INSTALLED
    #include <hl/register_type.hpp>
#else
    #include "register_type.hpp"
#endif

namespace hl
{

/**
 *   The struct by which we can convert function call signature to int
 * @parameter II The class sizer counter has size of II byte.
 * extract_sizer<2> function(void);
 * enum { sz = sizeof(function()) };
 */
template<int II>
struct extract_sizer
{
    char bf_[II];
};

#ifndef __MS_HL_EXTRACTOR_DEPTH_INSTANTIATION__
#define __MS_HL_EXTRACTOR_DEPTH_INSTANTIATION__ 127
#endif //__MS_HL_EXTRACTOR_DEPTH_INSTANTIATION__

/**  The recursive instantiation to depth __MS_HL_COUNTER_DEPTH_INSTANTIATION__
 * @parameter I. This parameter describe depth of instantiation
 * this resolve __counter_jump((counter_deep<__MS_HL_COUNTER_DEPTH_INSTANTIATION__>*)0 )
 * because (counter_deep<__MS_HL_COUNTER_DEPTH_INSTANTIATION__>*)0 can be converted to nearest instantiated
 * function <1,2,... , __MS_HL_COUNTER_DEPTH_INSTANTIATION__>
 */
template<int I = __MS_HL_EXTRACTOR_DEPTH_INSTANTIATION__>
struct extractor_deep: extractor_deep<I - 1>
{
};

template<>
struct extractor_deep<0>
{
};

/**
 *    This a engine to compile time jump function.
 *  First counter position sizeof(__counter_jump()) == 1
 *  @parameter type Is a type by which we can call extractor.
 */
template<typename type>
extract_sizer<1> extractor_jump__(...);

/**
 *  This is a struct which used as converter template class to type.
 * @parameter is a template which we wish to convert to type.
 */
template<template<int> class type>
struct shell__;

/**
 *  This is a extractor by which we can extract namespace metadata.
 * @parameter iterator_type is a iterator by which extracting possible.
 *
 */
template<template<int> class iterator_type>
struct extract
{
    /**
     *   This is extract implementation. This extractor based on manual_extractor
     *  @parameter id Is a calculated id to instantiate extractor each step.
     */
    template<int id = sizeof(extractor_jump__<shell__<iterator_type> > (
            (extractor_deep<__MS_HL_EXTRACTOR_DEPTH_INSTANTIATION__>*) 0,
            (shell__<iterator_type>*) 0))>
    struct get: manual_extract<iterator_type, boost::mpl::int_<id> >
    {
        /**
         * Increase current ID
         */
        enum
        {
            v = id + 1
        };

        /** Make new instance of counter engine methods
         * @parameter counter_deep<v>* Is a parameter from which we can call sizeof(__counter_jump(counter_deep<__MS_HL_COUNTER_DEPTH_INSTANTIATION__ ...)
         * which will child of counter_deep<v> in next step.
         * @parameter type* <undefined> is a counter branching.
         */
        template<typename type>
        friend extract_sizer<v>
        extractor_jump__(extractor_deep<v>*, shell__<iterator_type>*);
    };
};

} //namespace hl

#endif // EXTRACTOR_HPP_123BEFC2_60B6_11E2_B4ED_E20E6288709B_INCLUDED
