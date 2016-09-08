/**********************/

#ifndef VALUES_HPP_INCLUDED_6A09BABA_6BB8_11E2_A34C_5C276288709B
#define VALUES_HPP_INCLUDED_6A09BABA_6BB8_11E2_A34C_5C276288709B

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
# pragma GCC system_header
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if defined (BOOST_INSTALLED)
#    include <boost/mpl/if.hpp>
#    include <boost/type_traits/is_same.hpp>
#else
#if defined (HL_INSTALLED)
#    include <hl/typename.hpp>
#    include <hl/bool_types.hpp>
#    include <hl/make_types.hpp>
#    include <hl/sfinae.hpp>
#    include <hl/is_same.hpp>
#    include <hl/if.hpp>
#else
#    include "../include/typename.hpp"
#    include "../include/bool_types.hpp"
#    include "../include/make_types.hpp"
#    include "../include/sfinae.hpp"
#    include "../include/is_same.hpp"
#    include "../include/if.hpp"
#endif
#endif

#define opt(type) \
    boost::optional<type>

namespace hl
{

#define _(type, name)\
            hl::pair_<type, struct name >

template <typename Type
    , typename Name>
struct pair_
{
    typedef Name value_name;
    typedef Type type;

    pair_() : value_()
        {   }
    pair_(Type const& value)
        : value_(value)
    {  }

    static char const*
    name__()
    {
        static char* name__l = 0;
        if (!name__l)
        {
            //lock();
            if (!name__l)
            {
                static std::string str__ = __PRETTY_FUNCTION__;
                str__[str__.length() - 1] = '\0';
                size_t pp = str__.rfind("::");
                str__ = str__.substr(pp + 2, (str__.length() - pp) - 1);
                name__l = const_cast<char* >(str__.c_str());
            }
        }

        return name__l;
    }

    inline char const*
    name() const { return name__();   }

    inline char const*
    name() { return name__();   }

    Type value_;
};

namespace detail
{
    struct null_type;

    template <int id__
        , typename... Types_>
    struct get_by_id
    {
        enum { value = 0 };
        typedef null_type type;
        typedef null_type name;
        typedef pair_<null_type, null_type> ThisPairType;
        typedef ThisPairType pair_type;
    };

    template <int id__
        , typename Type
        , typename Name
        , typename... Types_>
    struct get_by_id <id__
                , pair_<Type, Name>, Types_... >
    {
       typedef get_by_id<id__ - 1, Types_... > next_type;
       typedef typename
           next_type::ThisPairType ThisPairType;

       typedef ThisPairType pair_type;

       enum { v_step = id__ };

       typedef typename
           pair_type::value_name name;
       typedef typename
           pair_type::type type;
    };

    template <typename Type
        , typename Name
        , typename... Types_>
    struct get_by_id <0
                , pair_<Type, Name>, Types_... >
    {
        typedef pair_<Type, Name> ThisPairType;

        enum {    value = 1 };
        typedef pair_<Type, Name> pair_type;
        typedef typename pair_type::type type;
        typedef typename pair_type::value_name name;
    };

    template <typename tag
        , typename... Types_>
    struct get_by_name
    {
        enum { value = 0 };
        typedef null_type type;
    };

    template <typename tag
        , typename Type
        , typename name
        , typename... Types_>
    struct get_by_name <tag
                , pair_<Type, name>, Types_... >
    {
       typedef get_by_name<tag, Types_... > next_type;
       enum { v_step = hl::is_same<tag, name>::value };
       enum {  value = v_step ? 1 : next_type::value  };

       typedef typename
       hl::if_c<v_step
                 , Type
                 , typename next_type::type
                >::type type;
    };

    template <typename tag
        , int I = 0
        , int Found = 0
        , typename... Types_>
    struct get_id_by_name
    {
        enum { value = -1, count = I };
        typedef null_type type;
    };

    template <typename tag
        , int I
        , int Found
        , typename Type
        , typename name
        , typename... Types>
    struct get_id_by_name <tag, I, Found
                , pair_<Type, name>, Types... >
    {
       typedef get_id_by_name<tag, I + 1
                       , hl::is_same<tag, name>::value, Types... > next_type;
       enum {      value = hl::is_same<tag, name>::value ? I : next_type::value  };
    };

    template <typename tag
        , int I
        , typename Type
        , typename name
        , typename... Types>
    struct get_id_by_name <tag, I, 1
                , pair_<Type, name>, Types... >
    {
       enum {      value = I  };
    };

}

template<typename Value>
struct HL_VALUE_RPC_TYPE_TAG_TYPE
{
    struct HL_VALUE_RPC_TYPE_TAG    {    };
};

HL_SFINAE_DECL(isValue, HL_VALUE_RPC_TYPE_TAG);

template <typename... Types>
struct values
    : HL_VALUE_RPC_TYPE_TAG_TYPE<values<Types...> >
{
    enum {  is_value = 0 };
    struct __tag_name;
    typedef hl::null_type types;
    typedef hl::null_type next_type;
    typedef hl::null_type type;

    values(values const&)
        {   }

    values()
        {   }

    template <typename... Types_>
    values(Types_... v)
        {   }

    template <typename tag_type_, typename type_>
    inline type_&
    get__(false_type())
    {
        //ToDo : STATIC ASSERT
        static type_ v;
        return v;
    }

    template <typename tag_type_, typename type_>
    inline type_ const&
    get__(false_type()) const
    {
        //ToDo : STATIC ASSERT
        static type_ v;
        return v;
    }

    template <typename Arch, typename Self>
    static Arch& serrialize(Arch& arch, Self& )
    {
        return arch;
    };

    template <typename tag>
    struct get_type
    {   typedef detail::null_type type;    };

    template <typename Pred, typename Self>
    static Pred&
    for_each(Pred& pred, Self& self)
    {
        return pred;
    }

    //
    // This plase we should moving to more depth layer self value and
    //  recursive call in last level.
    template <typename Return
        , typename Inst, typename Func, typename... Args>
    inline Return
    forward_call_(Inst& this_, Func func_ptr, Args&... args)
    {
        return (this_.*func_ptr)(args...);
    }
};

template <typename Type
    , typename Name
    , typename... Rest>
struct values<pair_<Type, Name>, Rest...   >
    : values<Rest... >
      , pair_<Type, Name>
      , HL_VALUE_RPC_TYPE_TAG_TYPE<values<pair_<Type, Name>, Rest...   > >
{
    typedef Name __tag_name;
    typedef Type type;
    typedef pair_<Type, Name> named_value;
    typedef values<Rest... > next_type;
    typedef values<Rest... > const next_type_const;

    typedef typename
        hl::make_types<pair_<Type, Name>, Rest... >::type types;

    enum {  is_value = 1
            , size_ = sizeof...(Rest) + 1 };

    values()
        : named_value()
        , next_type()
    {   }

    template <typename Type_, typename... Types_>
    values(Type_ v, Types_... vvs)
            : named_value(v)
            , next_type(vvs... )
    {   }

    values(values const& vv)
            : named_value(vv.named_value::value_)
            , next_type(static_cast<next_type const&>(vv))
    {   }

    template <typename tag>
    struct get_type
    {
        typedef typename
        detail::get_by_name<tag, named_value, Rest... >::type type;
    };

    template <typename tag_type_, typename type_>
    inline type_&
    get__(false_type)
    {
        enum { is_here
               = hl::is_same<typename next_type::__tag_name, tag_type_>::value };
        next_type* this_next = static_cast<next_type*>(this);
        return this_next->next_type::template get__<tag_type_, type_>(hl::id2type<is_here> ());
    }

    template <typename tag_type_, typename type_>
    inline type_&
    get__(true_type)
    {
        return this->named_value::value_;
    }

    template <typename tag_type_, typename type_>
    inline type_ const&
    get__(false_type) const
    {
        enum { is_here
               = hl::is_same<typename next_type::__tag_name, tag_type_>::value };
        next_type const* this_next = static_cast<next_type const*>(this);
        return this_next->next_type::template get__<tag_type_, type_>(hl::id2type<is_here> ());
    }

    template <typename tag_type_, typename type_>
    inline type_ const&
    get__(true_type) const
    {
        return this->named_value::value_;
    }

public:
    template <typename tag_type_>
    inline typename get_type<tag_type_>::type&
    get()
    {
        enum { is_here
               = hl::is_same<Name, tag_type_>::value };

        typedef typename
        detail::get_by_name<tag_type_, named_value, Rest... >::type type;
        return this->get__<tag_type_, type>(hl::id2type<is_here> ());
    }

    template <typename tag_type_>
    inline typename get_type<tag_type_>::type const&
    get() const
    {
        enum { is_here
               = hl::is_same<Name, tag_type_>::value };

        typedef typename
        detail::get_by_name<tag_type_, named_value, Rest... >::type type;
        return this->get__<tag_type_, type>(hl::id2type<is_here> ());
    }

    template <int I>
    struct get_type_by_id
            : detail::get_by_id<I, named_value, Rest... >
    {
        // Getting type value which determined by I
        typedef typename
        detail::get_by_id<I, named_value, Rest... >::type type;

        // The Name type suitable to I
        typedef typename
        detail::get_by_id<I, named_value, Rest... >::name name;
    };

    template <typename Tag>
    struct get_id_by_name
        : detail::get_id_by_name<Tag, 0, 0, named_value, Rest... >
    {

    };

    template <int I>
    typename get_type_by_id<I>::type&
    get_by_id()
    {
        typedef typename
            get_type_by_id<I>::name Name;
        return this->template get<Name>();
    }

    template <int I>
    typename get_type_by_id<I>::type const&
    get_by_id() const
    {
        typedef typename get_type_by_id<I>::name Name;
        return this->template get<Name>();
    }

    inline next_type_const&
    next_() const
    { return *this; }

    inline next_type&
    next_()
    { return *this; }

    template <typename Pred, typename Self>
    static Pred&
    for_each(Pred& pred, Self& self)
    {
        pred(std::pair<Name*, typename Self::named_value::type&>
            ((Name*)0, self.named_value::value_));

        return next_type::for_each(pred, self.next_());
    }

    //
    // This plase we should moving to more depth layer self value and
    //  recursive call in last level.
    template <typename Return
        , typename Inst, typename Func, typename... Args>
    inline Return
    forward_call_(Inst& this_, Func func_ptr, Args&... args)
    {
        return this->next_type::
            template forward_call_<Return>(this_, func_ptr, args..., this->named_value::value_);
    }

    //
    // Top layer to values recursive call
    //  recursive call in last level.
    template <typename This, typename Inst
        , typename Return, typename... Args>
    inline Return
    forward_call(This& this_, Return (Inst::*func_ptr)(Args... ))
    {
        Inst& this_i = static_cast<Inst&>(this_);
        return this->
            template forward_call_<Return>(this_i, func_ptr);
    }
};

template <typename... Type>
struct is_value : hl::false_type
{ enum { value = 0 }; };

template <typename... Type>
struct is_value<values<Type... > > : hl::true_type
{    enum { value = 1 }; };

} //namespace hl

#endif // VALUES_HPP_INCLUDED
