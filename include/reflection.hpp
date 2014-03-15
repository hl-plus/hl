/********************/

////
// This file contains compile reflection functionality
//

#ifndef REFLECTION_HPP_8E517050_63A9_11E2_B014_D29A6188709B_INCLUDED
#define REFLECTION_HPP_8E517050_63A9_11E2_B014_D29A6188709B_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
# pragma GCC system_header
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if defined (__BOOST_INSTALLED)
  #include <boost/mpl/if.hpp>
  #include <boost/mpl/int.hpp>
  #include <boost/type_traits/is_same.hpp>
#else
  #define __USE_BASIC_HL
#endif

#if defined (__HL_INSTALLED)
  #include <hl/register_type.hpp>
  #include <hl/sizer.hpp>
#else
  #include "register_type.hpp"
  #include "sizer.hpp"
#endif



namespace hl
{

  /**
   * This is root branch to extract istantiation
   */
  struct refl_branch;

  /**
   * This class allows iteration by metadata storage
   */
  template <int I>
  struct ftbl_iterator ;

  /**
   *   This class allows iteration by some class metadata storage
   * @parameter ftbl Is a storage by which iteration.
   * @parameter Branch is a branch to iterator instantiation
   * @parameter II is a calculated parameter in which we have depth of iteration step
   * @parameter is_ is a calculated parameter to take end of iteration.
   */
  template <template <typename > class ftbl
    , typename Branch = refl_branch
    , int II = 0
    , int is_ = hl::reg_sfinae<ftbl<boost::mpl::int_<II> >, Branch >::value
    >
  struct refl_iterator
  {
    enum { value = II };
  };

  /**
   * Iteration final step.
   */
  template <template <typename > class ftbl
    , int II
    , typename Branch  >
  struct refl_iterator <ftbl, Branch, II, 1>
  {
    /**
     *  This is iteration run
     */
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
    static const int __if_ = hl::reg_sfinae<ftbl<boost::mpl::int_<II + 1> >, Branch >::value;
    enum { value = refl_iterator<ftbl, Branch, II + 1 >::value };
#else
    enum { value = refl_iterator<ftbl, Branch, II + 1 >::value };
#endif

  };

  /**
   *   This class allows take a class metadata
   * @parameter ftbl Is a storage by which iteration.
   * @parameter Branch is a branch to iterator instantiation
   * @parameter base is a template structure base of compile time list
   * @parameter II is a calculated parameter in which we have depth of iteration step
   * @parameter is_ is a calculated parameter to take end of iteration.
   */
  template<
      template <class > class ftbl
    , typename Branch = refl_branch
    , template <typename, typename, int > class base = hl::vi_type
    , int II = 0
    , int is_ = ::hl::reg_sfinae<ftbl< boost::mpl::int_<II> >, Branch >::value
    >
  struct refl_extract
  {
    /**
     * This is instantiate current step describer
     */
    typedef typename
      ftbl< boost::mpl::int_<II> >::type type_;

    /**
     * This is a recursive call to make tail of list
     */
    typedef typename
      refl_extract<ftbl, Branch, base, II + 1>::type next_type;

    /**
     * Make list
     */
#if defined(__USE_BASIC_HL)
   typedef typename
       base<type_, next_type, 1 >::type next_;

    /*typedef typename
        boost::mpl::if_<
            boost::is_same<next_type, boost::mpl::na>
        , hl::null_type
        , typename base<type_, next_type, 1 >::type
    >::type next_;*/
#else
    typedef typename
        boost::mpl::if_<
            boost::is_same<next_type, boost::mpl::na>
        , boost::mpl::vector1<type_>
        , typename base<type_, next_type, 1 >::type
    >::type next_;
#endif

    /**
     * Calculate next type
     */
    typedef next_ type;
  };

  /**
   * Last extraction step
   */
  template <
      template <class > class ftbl
    , typename Branch
    , template <class, class, int > class base
    , int II>
  struct refl_extract<ftbl, Branch, base, II, 0 >
  {

#if defined(__USE_BASIC_HL)
    typedef hl::null_type type;
#else
    typedef typename boost::mpl::na type;
#endif

  };

} // namespace hl

namespace hl {

#ifndef __MS_HL_REFL_EXTRACTOR_MAX_DEPTH__
    #define __MS_HL_REFL_EXTRACTOR_MAX_DEPTH__ 400
#endif

template <int Depth = __MS_HL_REFL_EXTRACTOR_MAX_DEPTH__>
struct refl_extract_deep
            : refl_extract_deep <Depth - 1>
{   };

template <>
struct refl_extract_deep<0> {   };

/**
 *  This is a struct which used as converter template class to type.
 * @parameter is a template which we wish to convert to type.
 */
template <template <typename > class iterator_type >
struct reflection_shell__;


template <typename type>
inline hl::sizer<1>
__refl_extractor_jump(...);

template <template <typename > class ftbl >
struct meta_extract
{
    template <int id = sizeof(
              __refl_extractor_jump<reflection_shell__<ftbl> >((refl_extract_deep<__MS_HL_REFL_EXTRACTOR_MAX_DEPTH__>*)0
                    , (reflection_shell__<ftbl>*)0 ))
              > struct get  : refl_extract<ftbl, boost::mpl::int_<id> >
    {
        /**
         * Increase current ID
         */
        enum { v = id + 1 };

        /** Make new instance of counter engine methods
         * @parameter counter_deep<v>* Is a parameter from which we can call
         *      sizeof(__counter_jump(counter_deep<__MS_HL_COUNTER_DEPTH_INSTANTIATION__ ...)
         * which will child of counter_deep<v> in next step.
         * @parameter type* <undefined> is a counter branching.
         */
        template <typename type>
        friend hl::sizer<v>
          __refl_extractor_jump(refl_extract_deep<v>*, reflection_shell__<ftbl>*);
    };
};

} //namespace hl

/**
 *    defines meta storage
 *  @parameter type_ name of meta storage
 */
#define HL_DEFINE_META_STORAGE(ftbl)                                             \
    template <typename >                                                         \
    struct ftbl

/**
 *    This is a define to make metadata
 * @parameter ftbl name of meta storage
 * @parameter type_ is a type which we would like to save in storage
 */
#define HL_REGISTRATE_REFLACTION_TYPE_IMPL(ftbl, type_)                          \
    template <template <int > class Arg__ >                                      \
    struct ftbl<Arg__<hl::refl_iterator<ftbl, type_>::value > >                  \
    {                                                                            \
      struct _Reg_tag;                                                           \
      typedef type_ type;                                                        \
    }

#define HL_REGISTRATE_REFLACTION_TYPE(ftbl, type_)                               \
    HL_DEFINE_META_STORAGE(ftbl);                                                \
    HL_REGISTRATE_REFLACTION_TYPE_IMPL(ftbl, type_)                              \

/**
 *    This is a define to make metadata
 * @parameter ftbl name of meta storage
 * @parameter type_ is a type which we would like to save in storage
 */
#define HL_REGISTRATE_REFLACTION_TYPE_2ID_IMPL(ftbl, type_, ID)                 \
    template <template <int > class Arg__ >                                     \
    struct ftbl<Arg__<(int)ID > >                                               \
    {                                                                           \
      struct _Reg_tag;                                                          \
      typedef type_ type;                                                       \
    }

#define HL_REGISTRATE_REFLACTION_TYPE_2ID(ftbl, type_, ID)                      \
    HL_DEFINE_META_STORAGE(ftbl);                                               \
    HL_REGISTRATE_REFLACTION_TYPE_2ID_IMPL(ftbl, (type_), ID);

/**
 *    This is a define to make metadata
 * @parameter ftbl name of meta storage
 * @parameter type_ is a type which we would like to save in storage
 */
#define HL_REGISTRATE_REFLACTION_TYPE_EXTERN(class_, ftbl, type_)               \
    template <template <int > class Arg__ >                                     \
    struct class_::ftbl<Arg__<ms::hl::refl_iterator<class_::ftbl                \
                                , type_>::value > >                             \
    {                                                                           \
      struct _Reg_tag;                                                          \
      typedef type_ type;                                                       \
    }


#endif // REFLECTION_HPP_8E517050_63A9_11E2_B014_D29A6188709B_INCLUDED
