/*******************/

#ifndef T_LIST_HELPER_HPP_DFROKIGSDKEFHGDFKSGKDFJGHLFDGJHJDFGKHJDFG
#define T_LIST_HELPER_HPP_DFROKIGSDKEFHGDFKSGKDFJGHLFDGJHJDFGKHJDFG
namespace hl
{
struct null_type;

template <typename Type>
struct end_of_tlist;

template <typename Type, typename Base, int I>
struct v_item;

template <typename Type>
struct vi_extract
{
    enum { value = 0 };
    typedef null_type type;
    typedef null_type base;
    typedef null_type next;
};

template <typename Type>
struct vi_extract<hl::end_of_tlist<Type> >
{
    enum { value = 1 };
    typedef Type type;
    typedef Type base;
    typedef null_type next;
};

template <typename Type, typename Base, int I>
struct vi_extract<hl::v_item<Type, Base, I> >
{
    enum { value = 1
           , V = I };

    typedef Type type;
    typedef Base base;
    typedef Base next;
};

template <typename Type>
struct get_base
{
    typedef Type type;
};

template <typename Type, typename Base, int I>
struct get_base <v_item<Type, Base, I> >
{
    typedef Base type;
};

// TODO Have to implement for boost

template <typename Type>
struct is_list
{
    enum { value = 0 };
};

template <typename Type, typename Base, int I>
struct is_list <v_item<Type, Base, I> >
{
    enum { value = 1 };
};

namespace detail
{
    template <typename Type
        , int I = 0
        , int IsList = is_list<Type >::value>
    struct size
    {
        enum {
            value = size<typename
                        get_base<Type>::type, I + 1>::value
        };
    };

    //  The last point,
    // but we can stop compile if want
    template <typename Type, int I>
    struct size<Type, I, 0>
    {
#ifdef __0x11_ENABLE
        template <typename Type> struct compile_static_assert {
            static_assert(I >= 0, "This is must be list");
        };
#endif
        // If we have o zero point we can return this type
        enum { value = I };
    };

    template <typename Type, int I>
    struct size<hl::end_of_tlist<Type>, I, 0>
    {
#ifdef __0x11_ENABLE
        template <typename Type> struct compile_static_assert {
            static_assert(I >= 0, "This is must be list");
        };
#endif
        // If we have o zero point we can return this type
        enum { value = I + 1 };
    };


    template <typename Type
        , int I>
    struct at_c
    {
        static_assert(is_list<Type >::value
                , "Compilation of at_c<typelist > error: Isn't correct index.");

        typedef typename at_c<typename get_base<Type>::type
                            , I - 1>::type type;
    };

    template <typename Type>
    struct at_c <Type, 0>
    {
        typedef typename
            vi_extract<Type>::type type;
    };
}

template <typename Type
    , int I >
struct at_c : detail::at_c<Type, I>
{    };

template <typename Type>
struct size : detail::size<Type>
{    };

}
#endif // T_LIST_HELPER_HPP
