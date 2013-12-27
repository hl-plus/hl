/*********************/

#ifndef REGISTER_HPP_A85FA7C8_5FE9_11E2_B9A2_6FED6188709B_INCLUDED
#define REGISTER_HPP_A85FA7C8_5FE9_11E2_B9A2_6FED6188709B_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
# pragma GCC system_header
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if defined(__HL_INSTALLED)
//
// This class contains registration type implementation
//
  #include <hl/sfinae.hpp>
  #include <hl/vi_item.hpp>
  #include <hl/sizer.hpp>
#else
  #include "sfinae.hpp"
  #include "vi_item.hpp"
  #include "sizer.hpp"
#endif


namespace hl
{
  /**
   * The null_type we use e.g. to finalization some operation
   */
  struct null_type;

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
  typedef hl::sizer<1> true_sizer;
  typedef hl::sizer<2> false_sizer;

  template <typename type, typename _Branch_type>
  inline false_sizer _Has_reg_function(...);

  template <typename type, typename _Branch_type>
  inline true_sizer _Has_reg_function(typename type::_Reg_tag* ptr = 0);

  template <typename type, typename Branch>
  struct reg_sfinae
  {
      enum { value = (sizeof(_Has_reg_function<type, Branch>())
                        == sizeof(true_sizer)) };
  };

#else
  /**
   *   This class allows to make SFENAE concept
   *  this class  we use to resolve _Reg_tag availbility
   *  @parameter type is a type in which we look for the child type _Reg_tag
   *  @parameter Branch is a branch to instatiation
   *  @parameter sfinae test is a calculated parameter to substitution try
   */
  template <typename type, typename Branch, typename sfinae_test = sfinae_empty>
  struct reg_sfinae
    { enum { value = 0 }; };

  /**
   *    It is a ok branch to substitution when class has _Reg_tag as children type
   *  the expression hl::dummy<typename type::_Reg_tag>::dummy_type is a expression
   *  to try make a substitituon. If this expression can't compile
   *  will compile expression with value = 0
   *  @parameter type is a type in which we look for the child type _Reg_tag
   *  @parameter Branch is a branch to instatiation
   */
  template <typename type, typename Branch>
  struct reg_sfinae<type, Branch, typename hl::dummy<typename type::_Reg_tag>::dummy_type>
    { enum { value = 1 }; };
#endif


  namespace detail
  {
    /**
     *    This a class which convert type to shell_type
     * @parameter type It is a instantiator
     *
     */
    template <typename type>
    struct register_shell;

    /**
     *  This class allows to create type instance from default branch.
     */
    struct root_reflection_branch;

    /**
     *   This class allows iteration by some class metadata storage
     * @parameter collector Is a storage for which iteration ran.
     * @parameter Branch is a branch to iterator instantiation
     * @parameter II is a calculated parameter in which we have depth of iteration step
     * @parameter isreg is a calculated parameter to take end of iteration.
     */
    template <
        template <int> class collector
      , typename Branch = detail::root_reflection_branch
      , int II = 0
      , int isreg = hl::reg_sfinae<collector<II>, Branch >::value >
    struct Iterator
    {
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
        enum { Id = Iterator<collector, Branch, II + 1>::Id };
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
      enum { Id = Iterator<collector, Branch, II + 1 >::Id };
#endif

    };

    /**
     * Last step of iteration
     */
    template <
        template <int> class collector
      , typename Branch
      , int II
      >
    struct Iterator <collector, Branch, II, 0 >
    {
      enum { Id = II };
    };
  } // namespace detail

  /**
   *   This class allows collect metadata by metadata storage
   * @parameter collector Is a storage for which iteration ran.
   * @parameter Branch is a branch to iterator instantiation
   * @parameter base is a template structure base of compile time list
   * @parameter II is a calculated parameter in which we have depth of iteration step
   * @parameter isreg is a calculated parameter to take end of iteration.
   */
  template<
      template <int III> class collector
    , typename Branch = detail::root_reflection_branch
    , template <typename, typename, int > class base = hl::vi_type//boost::mpl::v_item//detail::tl_item
    , int II = 0
    , int isreg = hl::reg_sfinae<collector<II>, Branch >::value
    >
  struct manual_extract
  {
    /**
     * Current type calculate
     */
    typedef typename
      collector<II>::type type_;

    /**
     *  Recursive next type calculate
     */
    typedef typename
      manual_extract<collector, Branch, base, II + 1>::type next_type;

    /**
     *  Collection create
     */
#if defined (__USE_BASIC_HL)
   typedef typename
       base<type_, next_type, 1 >::type next_;
#else
    typedef typename
        boost::mpl::if_<
          boost::is_same<next_type, null_type>
        , boost::mpl::vector1<type_>
        , typename base<type_, next_type, 1 >::type
    >::type next_;
#endif

    typedef next_ type;
  };

  /**
   * Extractor finalize
   */
  template <
      template <int III> class collector
    , typename Branch
    , template <typename, typename, int > class base
    , int II
    >
  struct manual_extract<collector, Branch, base, II, 0 >
  {
     typedef null_type type;
  };
} // namespace hl


/**
 *  This a defaine to metada decration
 */
#define MS_HL_SET(set_ident) \
    template <int I> struct set_ident;

/**
 *  This is a define to push to storage som type.
 *    @paraeter collector is storage to colect data
 *  @parameter type_ is a type which we would like to add to storage @collector@
 */
#define HL_REFLECTION_TYPE(collector, type_)                                                                 \
    template <>                                                                                              \
    struct collector<hl::detail::Iterator<collector, ::hl::detail::register_shell<type_> >::Id > :           \
         boost::mpl::int_<::hl::detail::Iterator<collector, ::hl::detail::register_shell<type_> >::Id>       \
    { struct _Reg_tag; typedef type_ type; };

#define HL_REFLECTION_TYPE_2ID(collector, type_, ID)                                                         \
    template <>                                                                                              \
    struct collector<ID > :                                                                                  \
         boost::mpl::int_<ID >                                                                               \
    { struct _Reg_tag; typedef type_ type; };

namespace hl
{
    template <typename Type>
    struct stg_key
    {
        template <int > struct key;
    };
}

/**
 * This is saving to personal key where the key is a simpel type. Not template
 */
#define MS_HL_PUSH_2KEY(key_, type_)                                                         \
    template <>                                                                              \
    hl::stg_key<key_>::key<                                                                  \
            hl::detail::Iterator<                                                            \
              hl::stg_key<key_>::template key                                                \
            , hl::detail::register_shell<type_> >::Id >                                      \
    {                                                                                        \
        struct _Reg_tag;                                                                     \
        enum { Id = hl::detail::Iterator<hl::stg_key<key_>::template key                     \
                                            , hl::detail::register_shell<type_> >::Id };     \
        typedef type_ type;                                                                  \
    };

#define HL_REGISTER_TYPE(key_, type_)                                                        \
    template <>                                                                              \
    struct key_<                                                                             \
            hl::detail::Iterator<                                                            \
              key_                                                                           \
            , hl::detail::register_shell<type_> >::Id >                                      \
    {                                                                                        \
        struct _Reg_tag;                                                                     \
        enum { Id = hl::detail::Iterator<key_, hl::detail::register_shell<type_> >::Id };    \
        typedef type_ type;                                                                  \
    };


#define MS_HL_REG_ID(collector, type_)    \
    hl::detail::Iterator<collector, hl::detail::register_shell<type_> >::Id



#endif
