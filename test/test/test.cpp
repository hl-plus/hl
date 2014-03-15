// test.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

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
 *   This is define to SFINAE declaration
 *  @parameter test_type is a type which we will use to make checking
 *  @parameter what ia a children type which we lookfor inside the test_type.
 */
#define HL_SFINAE_DECL(test_type, what)\
  template <typename type, typename sfinae_test = hl::sfinae_empty>\
  struct test_type { enum { value = 0 }; };\
  template <typename type>\
  struct test_type<type, typename hl::dummy<typename type::what>::dummy_type >\
    { enum { value = 1 };    };

HL_SFINAE_DECL(is_sub, sub_type);


template <typename Type, typename Tail>
struct v_item 
{	typedef Type type; typedef Tail tail; };

namespace mpl 
{
struct null_type;

template <typename Type
	, template <typename > class Pred
	, template <typename > class Next
	, int end_ = Pred<Type>::value >
struct for_
{
	typedef typename
		  Next<Type>::next next;

	typedef for_<next
		, Pred
		, Next>::type type;
};

template <typename Type
	, template <typename > class Pred
	, template <typename > class Next >
struct for_ <Type, Pred, Next, 1>
{	

};

}

#define MPL_FOREACH(list, Pred)		\
									\

typedef typename 
	 MPL_FOREACH(tlist, hl::end<tlist>)

template <typename Type> struct next_type 
{	
	typedef typename 
	Type::tail tail;	
};

int _tmain(int argc, _TCHAR* argv[])
{
	//typedef mpl::find_if<Tlist
		//		, if_c_pred<mpl::is_same, int>::pred >::type result;
	// for_<typelist, is_same_pred<int>, next_type >
	return 0;
}

