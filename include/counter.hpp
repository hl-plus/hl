/*******************/

#ifndef COUNTER_HPP_1983F814_5FE5_11E2_9559_12E96188709B_INCLUDED
#define COUNTER_HPP_1983F814_5FE5_11E2_9559_12E96188709B_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
# pragma GCC system_header
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)
// This file contains a functional of compile time counter
//similar MSVC C++ compilation __COUNTER__
//, but we can have more that one branches.
//

namespace hl
{

/**
 *   The struct by which we can convert function call signature to int
 * @parameter II The class sizer counter has size II byte.
 * like this:
 * sizer_counter<2> function(void);
 * enum { sz = sizeof(function()) }; //sz == 2
 */
template<int II>
struct sizer_counter
{
    char bf_[II];
};

#ifndef __MS_HL_COUNTER_DEPTH_INSTANTIATION__
#define __MS_HL_COUNTER_DEPTH_INSTANTIATION__ 127
#endif // #ifndef __MS_HL_COUNTER_DEPTH_INSTANTIATION__
/**  The recursive instantiation to depth __MS_HL_COUNTER_DEPTH_INSTANTIATION__
 * @parameter I. This parameter specify a depth of instantiation
 * that specify counter_jump__((counter_deep<__MS_HL_COUNTER_DEPTH_INSTANTIATION__>*)0 )
 * because counter_deep<__MS_HL_COUNTER_DEPTH_INSTANTIATION__>* can
 * be converted to nearest instantiated base class counter_deep<I>*
 * where I < __MS_HL_COUNTER_DEPTH_INSTANTIATION__.
 */
template<int I = __MS_HL_COUNTER_DEPTH_INSTANTIATION__>
struct counter_deep: counter_deep<I - 1>
{
};

/** Last finalizator
 * This is last instantiation.
 */
template<>
struct counter_deep<0>
{
};

/** We can create counter from some personal branch
 * but default is _root_counter__
 */
struct root_counter__;

/**
 *   First counter position sizeof(counter_jump__()) == 1
 *  This is compile time jump function
 *  @parameter type Is a type by which we can have counter.
 */
template<typename type>
sizer_counter<1> counter_jump__(...);

/** The root type counter instantiation
 * @parameter type is a type by which we have counting
 * we use this to instantiation child type ::is<>.
 */
template<typename type_ = root_counter__> struct counter
{
    /** At every turn we have instance of function which was instantiated by previous instance of ::is<>
     * @parameter id is a calculated parameter.
     * and we instatiate new template function by friend declaration. But size of that
     * will be greater on a one than previous
     */
    template<int id
    = sizeof(counter_jump__<type_>((counter_deep<__MS_HL_COUNTER_DEPTH_INSTANTIATION__>*)0, (type_*)0))>
    struct is
    {
        enum
        {   v = id + 1};

        /** Make new instance of counter engine methods
         * @parameter counter_deep<v>* Is a parameter from which we can call sizeof(counter_jump__(counter_deep<__MS_HL_COUNTER_DEPTH_INSTANTIATION__ ...)
         * which will child of counter_deep<v> in next step.
         * @parameter type* <undefined> is a counter branching.
         */
        template <typename type>
        friend sizer_counter<v> counter_jump__(counter_deep<v>*, type_*);
        static const int value = id - 2;
    };

    /** This is a first value of counter.
     * can be changed by some approach.
     */
    enum
    {   value = is<>::value};
};

} //namespace hl

#endif // COUNTER_HPP_INCLUDED
