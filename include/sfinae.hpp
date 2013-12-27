/******************/


//This file contains basic SFENAE functionality

#ifndef SFINAE_HPP_
#define SFINAE_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
# pragma GCC system_header
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

namespace hl
{

  /**
   *  This is a basic type which use in dummy role.
   */
  struct sfinae_empty;

  /**
   *  This type will use to make Substitution fault is not error logic.
   */
  template <typename type>
  struct dummy { typedef sfinae_empty dummy_type; };

} // namespace hl


/**
 *   This is define to SFENAE declaration
 *  @parameter test_type is a type which we will use to make checking
 *  @parameter what ia a children type which we lookfor inside the test_type.
 */
#define HL_SFINAE_DECL(test_type, what)\
  template <typename type, typename sfinae_test = hl::sfinae_empty>\
  struct test_type { enum { value = 0 }; };\
  template <typename type>\
  struct test_type<type, typename hl::dummy<typename type::what>::dummy_type >\
    { enum { value = 1 };    };

#endif
