/*******************/

#ifndef PP_hl_IPC_HPP_SDFRDGKFHGJDHFGDHSJHGERUITREJHGJDSHFGEEEEEEE
#define PP_hl_IPC_HPP_SDFRDGKFHGJDHFGDHSJHGERUITREJHGJDSHFGEEEEEEE

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
# pragma GCC system_header
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if defined (__HL_INSTALLED)
    #include <hl/include/preprocessor/pp_foreach.hpp>
    #include <hl/include/preprocessor/pp_concat.hpp>
    #include <hl/include/preprocessor/pp_count.hpp>
    #include <hl/include/register_type.hpp>
    #include <hl/include/reflection.hpp>
    #include <hl/include/lock_guard.hpp>
#else
    #include "../preprocessor/pp_foreach.hpp"
    #include "../preprocessor/pp_concat.hpp"
    #include "../preprocessor/pp_count.hpp"
    #include "../register_type.hpp"
    #include "../../include/signature.hpp"
    #include "../../include/reflection.hpp"
    #include "../lock_guard.hpp"
#endif

/*
       This is local helper types
     TODO: We will have to move it to other hpp, to more generality
 */
namespace hl
{

// To exclude the parameters
struct null_parameter
{ };

template<typename Type>
struct remove_const {
    typedef Type type;
};

template<typename Type>
struct remove_const<const Type> {
    typedef Type type;
};

template<typename Type>
struct remove_const<const Type*> {
    typedef Type* type;
};

template<typename Type>
struct remove_const<Type const&> {
    typedef Type type;
};

template<typename Type>
struct remove_const<Type&> {
    typedef Type type;
};

template<typename Type>
struct Default {
};

// The types is convertible if
// To has constructor to convert from From
template <typename To, typename From>
struct is_explicitly_convertible
{
    static hl::sizer<8> convert(...);
    static hl::sizer<1> convert(To const&);

    enum { value = sizeof(convert(*(From*)0))
        == sizeof(hl::sizer<1>)    };
};

} // namespace hl

/*
     This is the specific classes used to interface reflection, we need to save it here because
    we have quote it in #defines
 */
namespace hl
{

template<typename ValuesType>
struct values_assigner
{
    values_assigner(ValuesType& v)
        : v_(v)
    {    }

    template<typename Type>
    inline void
    copy_(Type& v, hl::true_type)
    {    }

    template<typename Type>
    inline void copy_(Type& v, hl::false_type) {
        v_.template get<typename Type::value_name> () = v.value_;
    }

    template<typename Type>
    inline values_assigner&
    operator <<(Type v) {
        this->copy_(v, hl::id2type<hl::is_same<typename Type::type,
                hl::empty_type>::value>());
        return (*this);
    }

    ValuesType& v_;
};

template <typename... Args>
inline values_assigner<hl::values<Args... > >
assign(hl::values<Args... >& values)
{
    return values_assigner<hl::values<Args... > >(values);
}

template <typename... Args>
struct GetDefaultArgumentsCount
{    enum {value = 0};};

template <typename... Args>
struct GetDefaultArgumentsCount<hl::values<Args... > >
{
    typedef hl::values<Args... > values_type;
    template <int I, typename... args_type>
    struct impl
    {
        enum { value = I };
    };

    template <int I, typename Type, typename Name, typename... args_type>
    struct impl<I, hl::pair_<Type, Name>, args_type... >
    {
        enum {
            value = impl<I + !(hl::is_same<Type, hl::empty_type>::value), args_type... >::value
        };
    };

    enum {value = impl<0, Args...>::value};
};
} //namespace hl

#define EAT_PTH(...) __VA_ARGS__
#define DELIMITER_COMA ,

#define MAKE_PAIR_IMPL2(Delimiter, Type, Name)     \
            Type EAT_PTH Delimiter struct Name

#define MAKE_PAIR_IMPL3(Delimiter, Type, Name, DefaultValue)     \
            Type EAT_PTH Delimiter struct Name

#define MAKE_PAIR__(Prefix, Postfix, Delimiter, m, ...) \
        Prefix m(Delimiter, __VA_ARGS__) Postfix

#define MAKE_PAIR(Prefix, Postfix, Delimiter, ...) \
            MAKE_PAIR__(Prefix, Postfix, Delimiter, MAKE_TOKEN_WITH_COUNT_PARM_ID_RMPTH(MAKE_PAIR_IMPL, __VA_ARGS__), EAT_PTH __VA_ARGS__)

#define MAKE_PAIR_CHECK_IMPL2(Delimiter, Type, Name)     \
            Type EAT_PTH Delimiter struct Name

#define MAKE_PAIR_CHECK_IMPL3(Delimiter, Type, Name, DefaultValue)     \
            Type EAT_PTH Delimiter hl::Default<struct Name >

#define MAKE_PAIR_CHECK__(Prefix, Postfix, Delimiter, m, ...) \
        Prefix m(Delimiter, __VA_ARGS__) Postfix

#define MAKE_PAIR_CHECK(Prefix, Postfix, Delimiter, ...) \
            MAKE_PAIR__(Prefix, Postfix, Delimiter, MAKE_TOKEN_WITH_COUNT_PARM_ID_RMPTH(MAKE_PAIR_CHECK_IMPL, __VA_ARGS__), EAT_PTH __VA_ARGS__)

#define MAKE_NAME_IMPL2(Delimiter, Type, Name) #Name

#define MAKE_NAME_IMPL3(Delimiter, Type, Name, DefaultValue) #Name

#define MAKE_NAME__(Prefix, Postfix, Delimiter, m, ...) m(Delimiter, __VA_ARGS__)

#define MAKE_NAME(Prefix, Postfix, Delimiter, ...) \
            MAKE_NAME__(Prefix, Postfix, Delimiter, MAKE_TOKEN_WITH_COUNT_PARM_ID_RMPTH(MAKE_NAME_IMPL, __VA_ARGS__), EAT_PTH __VA_ARGS__)

#define MAKE_DEF_ARG_IMPL2(Delimiter, Type, Name) hl::pair_<hl::empty_type, Name>(hl::empty_type())

#define MAKE_DEF_ARG_IMPL3(Delimiter, Type, Name, DefaultValue) hl::pair_<Type, Name>(DefaultValue)

#define MAKE_DEF_ARG__(Prefix, Postfix, Delimiter, m, ...) m(Delimiter, __VA_ARGS__)

#define MAKE_DEF_ARG(Prefix, Postfix, Delimiter, ...) \
            MAKE_DEF_ARG__(Prefix, Postfix, Delimiter, MAKE_TOKEN_WITH_COUNT_PARM_ID_RMPTH(MAKE_DEF_ARG_IMPL, __VA_ARGS__), EAT_PTH __VA_ARGS__)


#define MAKE_ARGS_IMPL2(Delimiter, Type, Name) Type Name##_param
#define MAKE_ARGS_IMPL3(Delimiter, Type, Name, DefaultValue) Type Name##_param

#define MAKE_ARGS__(Prefix, Postfix, Delimiter, m, ...) m(Delimiter, __VA_ARGS__)

#define MAKE_ARGUMENTS(Prefix, Postfix, Delimiter, ...) \
            MAKE_ARGS__(Prefix, Postfix, Delimiter, MAKE_TOKEN_WITH_COUNT_PARM_ID_RMPTH(MAKE_ARGS_IMPL, __VA_ARGS__), EAT_PTH __VA_ARGS__)


// This is without default value expression
// predicate
// We should set as hl::empty_type, to calculate and nowing about
// how match default argumets we have
#define MAKE_PAIR_DEF_IMPL2(Delimiter, Type, Name)                  \
            hl::empty_type EAT_PTH Delimiter struct Name

// This is with default value expression
// declaration predicate
#define MAKE_PAIR_DEF_IMPL3(Delimiter, Type, Name, DefaultValue)     \
            Type EAT_PTH Delimiter struct Name
//
#define MAKE_PAIR_DEF__(Prefix, Postfix, Delimiter, m, ...) \
            Prefix m(Delimiter, __VA_ARGS__) Postfix

#define MAKE_PAIR_DEF(Prefix, Postfix, Delimiter, ...) \
            MAKE_PAIR_DEF__(Prefix, Postfix, Delimiter, MAKE_TOKEN_WITH_COUNT_PARM_ID_RMPTH(MAKE_PAIR_DEF_IMPL, __VA_ARGS__), EAT_PTH __VA_ARGS__)

#define hl_RPC_MAKE_VALUES_IMPL_ID(Prefix, Postfix, Delimiter, m, ItemPrefix, ItemPostfix, ...) \
            MAKE_TOKEN_WITH_COUNT_PARM_ID(hl_PP_FOREACH, __VA_ARGS__)(Prefix, Postfix, Delimiter, m, ItemPrefix, ItemPostfix, __VA_ARGS__)

#define hl_RPC_MAKE_VALUES_IMPL(...)        \
            hl_RPC_MAKE_VALUES_IMPL_ID(typedef hl::values <, > type, (DELIMITER_COMA), MAKE_PAIR, hl::pair_ < , > ,__VA_ARGS__)

#define HL_ITERATE_GROUP(PrefixName, PostfixName, Delimiter, m, ItemPrefix, ItemPostfix, ...) \
            hl_RPC_MAKE_VALUES_IMPL_ID(PrefixName, PostfixName, Delimiter, m, ItemPrefix, ItemPostfix, __VA_ARGS__)

#define ADD_PTH(...) (__VA_ARGS__)

#define TRANSLATE(m, ... )  \
           EAT_PTH m __VA_ARGS__

#define HL_ITERATE_GROUP_PTH(PrefixName, PostfixName, Delimiter, m, ItemPrefix, ItemPostfix, ...)       \
            TRANSLATE(                                                                                  \
                (hl_RPC_MAKE_VALUES_IMPL_ID)                                                          \
                    , (PrefixName, PostfixName, Delimiter, m, ItemPrefix, ItemPostfix, __VA_ARGS__))


#define hl_RPC_FUNCTION(ReturnType, Function, Args)                                                                       \
            struct Function##_accessor         {                                                                            \
                typedef ClassType class_type;                                                                               \
                HL_ITERATE_GROUP((typedef hl::values <), (> result_type),                                                   \
                            (DELIMITER_COMA), MAKE_PAIR, hl::pair_ <, >, EAT_PTH ReturnType);                               \
                HL_ITERATE_GROUP((typedef hl::values <), (> args_type),                                                     \
                            (DELIMITER_COMA), MAKE_PAIR, hl::pair_ <, >, EAT_PTH Args);                                     \
                HL_ITERATE_GROUP((typedef hl::values <), (>) def_args_type,                                                 \
                            (DELIMITER_COMA), MAKE_PAIR_DEF, hl::pair_ <, >, EAT_PTH Args);                                 \
                                                                                                                            \
                                                                                                                            \
                HL_ITERATE_GROUP((typedef hl::make_types<), (>::type args_describe),                                        \
                                            (DELIMITER_COMA), MAKE_PAIR_CHECK, hl::pair_ <, >, EAT_PTH Args);               \
                                                                                                                            \
                /*typedef StringType string_type;*/                                                                         \
                                                                                                                            \
                enum {    args_count = HL_PP_COUNT_PRMS(EAT_PTH Args)                                                       \
                        ,  defargs_count = 0 };                                                                             \
                template <int I>                                                                                            \
                inline static char const*                                                                                   \
                resultName()    {                                                                                           \
                    HL_ITERATE_GROUP((static char const* names[]={), (}),                                                   \
                            (DELIMITER_COMA), MAKE_NAME,,, EAT_PTH ReturnType);                                             \
                    return names[I];                                                                                        \
                }                                                                                                           \
                                                                                                                            \
                template <int I>                                                                                            \
                inline static char const*                                                                                   \
                argName()    {                                                                                              \
                    HL_ITERATE_GROUP((static char const* arg_name[]={), (}), (DELIMITER_COMA), MAKE_NAME,,, EAT_PTH Args);  \
                    return arg_name[I];                                                                                     \
                }                                                                                                           \
                                                                                                                            \
                static char const* functionName()    {    return #Function;     }                                           \
                                                                                                                            \
                static def_args_type& get_def_args()                                                                        \
                {                                                                                                           \
                    static def_args_type def_args;                                                                          \
                    struct get_def_args___;                                                                                 \
                    if (!hl::atomic_st_value<bool                                                                           \
                                    , get_def_args___>::value_.load())                                                      \
                    {                                                                                                       \
                        GUARD(fill_on_args);                                                                                \
                        if (!hl::atomic_st_value<bool, get_def_args___>::value_.load())                                     \
                        {                                                                                                   \
                            hl::assign(def_args)    <<                                                                      \
                                HL_ITERATE_GROUP((), (),(<<), MAKE_DEF_ARG,,, EAT_PTH Args );                               \
                            /* Set flag about filled */                                                                     \
                            hl::atomic_st_value<bool, get_def_args___>::value_ = true;                                      \
                        }                                                                                                   \
                    }                                                                                                       \
                                                                                                                            \
                    return def_args;                                                                                        \
                }                                                                                                           \
                                                                                                                            \
                template <int I>                                                                                            \
                static typename args_type::get_type_by_id<I>::type&                                                         \
                getDefaultArgument()    {                                                                                   \
                    static_assert((def_args_type::size_ > I) && (I > (args_type::size_ - def_args_type::size_ - 1))         \
                                , "Not suitable default argument count.");                                                  \
                    return get_def_args().template get_by_id<I>();                                                          \
                }                                                                                                           \
                                                                                                                            \
                template <typename>                                                                                         \
                struct function_accessor;                                                                                   \
                                                                                                                            \
                /* We use the specialization (not explicit) to leazy instantiation of type function_accessor */             \
                template <template <typename > class Holder, typename Branch>                                               \
                struct function_accessor<Holder<Branch> >                                                                   \
                {                                                                                                           \
                    typedef result_type (Branch::*srv_accessor)(                                                            \
                                               HL_ITERATE_GROUP_PTH((), (),                                                 \
                                                        (DELIMITER_COMA), MAKE_ARGUMENTS,,, EAT_PTH Args)                   \
                                                                );                                                          \
                    static srv_accessor func() {   return &Branch::Function##_impl;    };                                   \
                    /*typedef HL_SIG_FUNCTION_TYPE(&Branch::Function##_impl) function_call_accessor;*/                      \
                };                                                                                                          \
            };                                                                                                              \
            HL_REGISTRATE_REFLACTION_TYPE_IMPL(ftbl, Function##_accessor);                                                  \
            typedef typename Function##_accessor::result_type Function##_result;                                            \
            template <template <typename, typename > class Holder >                                                         \
            struct OwnerCheck<Holder<ClassType, Function##_accessor> > {    enum { value = 1 };    };                       \
                                                                                                                            \
            template <template <typename > class AccessorHolder>                                                            \
            struct AccessorSpec<AccessorHolder<struct Function##_selector>  >                                               \
            {                                                                                                               \
                typedef Function##_accessor type;                                                                           \
                enum { value = 1 };                                                                                         \
            };                                                                                                              \
                                                                                                                            \
            template <typename... Type >                                                                                    \
            inline typename Function##_accessor::result_type                                                                \
            Function(Type... Params)                                                                                        \
            {   return this->template invoke_c__<Function##_accessor>(Params...); }                                         \
                                                                                                                            \
            typename Function##_accessor::result_type                                                                       \
            Function##_impl (                                                                                               \
                HL_ITERATE_GROUP_PTH((), (),                                                                                \
                                (DELIMITER_COMA), MAKE_ARGUMENTS,,, EAT_PTH Args) )                                         \



#define hl_META_CLASS_DECLARATION(Class)                                                                                  \
                                typedef Class ClassType;                                                                    \
                                template <typename Type>                                                                    \
                                    struct OwnerCheck    {    enum {value = 0 }; };                                         \
                                template <typename accessor>                                                                \
                                    struct AccessorSpec                                                                     \
                                {    enum { value = 0 }; typedef accessor type;    };                                       \
                                /*This is reflection activation */                                                          \
                                HL_DEFINE_META_STORAGE(ftbl);                                                               \

#define hl_RPC_CLIENT_DNS_DECLARATION(SvcName, Uri, Name)                                                                 \
                                static char const* svc_name()    {  return SvcName;    }                                    \
                                static char const* uri()         {  return Uri;    }                                        \
                                static char const* name()        {  return Name;    }                                       \

#define hl_RPC_SERVICE_CLIENT_DECLARATION(ServiceType, SvcName, Uri, Name)                                                \
                                struct is_client__;                                                                         \
                                hl_META_CLASS_DECLARATION(ServiceType)                                                    \
                                hl_RPC_CLIENT_DNS_DECLARATION(SvcName, Uri, Name)


#define hl_RPC_SERVICE_NAME_DECLARATION(Name)                                                                             \
                                static char const* svc_name()    {  return Name;    }                                       \


#define hl_RPC_SERVICE_DECLARATION(ServiceType, Name)                                                                     \
                                hl_META_CLASS_DECLARATION(ServiceType)                                                    \
                                hl_RPC_SERVICE_NAME_DECLARATION(Name)

#define NOARGS (hl::null_parameter, _0, hl::null_parameter())

#define hl_RPC_TYPE(Args, Identifier)                                                                                     \
            template <typename> struct NameAccessor;                                                                        \
            HL_ITERATE_GROUP((typedef hl::values <), (> Identifier),                                                        \
                                    (DELIMITER_COMA), MAKE_PAIR, hl::pair_ <, >, EAT_PTH Args);                             \
            template <template <typename > class Holder>                                                                    \
            struct NameAccessor <Holder<Identifier>  >                                                                      \
            {                                                                                                               \
                template <int I>                                                                                            \
                inline static char const*                                                                                   \
                name()    {                                                                                                 \
                    HL_ITERATE_GROUP((static char const* name[]={), (}), (DELIMITER_COMA), MAKE_NAME,,, EAT_PTH Args);      \
                    return name[I];                                                                                         \
                }                                                                                                           \
            };                                                                                                              \


#endif
