/*****************/

#ifndef INTERFACE_REFLECTION_HPP_SDKFJGKDSFGDSKFHGKSDHFGKDHSKFGKSDHFGKDHFSGKDSKFHGKSDHFGDSFKGKSDHFGKSDHFKG
#define INTERFACE_REFLECTION_HPP_SDKFJGKDSFGDSKFHGKSDHFGKDHSKFGKSDHFGKDHFSGKDSKFHGKSDHFGDSFKGKSDHFGKSDHFKG

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
# pragma GCC system_header
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

namespace hl
{

// Args iterator
// This class should provide the iteration by arguments
template<typename Class>
struct args_iterator
{
    template<typename Accessor, int I, typename Callback>
    void for_each_defualts_(Callback& callback, hl::id2type<0>)
    {    }

    template<typename Accessor, int I, typename Callback, typename IterateId>
    void for_each_defualts_(Callback& callback, IterateId iterate) {
        callback.template on_arg<I> (Accessor::template argName<I>(),
                Accessor::template getDefaultArgument<I>());
        this->template for_each_defualts_<Accessor, I + 1> (callback,
                hl::id2type<IterateId::value - 1>());
    }

    template <typename Callback, typename ArgId, typename Accessor, typename... Args>
    void for_each_(Callback& callback, ArgId argid, Accessor accessor, Args&... )
    {
        enum {
            default_arguments_count = hl::GetDefaultArgumentsCount<typename Accessor::def_args_type>::value
            , rest_default_args = Accessor::args_count - ArgId::value};

        static_assert(rest_default_args <= default_arguments_count
                , "Don't match call. Missing arguments?");

        // this place to counting where the arguments is rest
        this->template for_each_defualts_<Accessor, ArgId::value>(callback, hl::id2type<rest_default_args>());
    }

    template <typename Callback, typename ArgId, typename Accessor, typename Type, typename... Args>
    void for_each_(Callback& callback, ArgId argid, Accessor accessor, Type &arg, Args&... args)
    {
        callback.template on_arg<ArgId::value>(accessor.template argName<ArgId::value>(), arg);
        this->for_each_(callback, hl::id2type<ArgId::value + 1>(), accessor, args...);
    }

    template <typename Accessor, typename Callback, typename... Args>
    void for_each_args(Callback& callback, Args&... args)
    {
        this->for_each_(callback, hl::id2type<0>(), Accessor(), args...);
    }
};

template <typename Class>
struct value_iterator
{
    typedef typename
    traits_resolver<Class>::string_type StringType;

    typedef value_iterator<Class> this_t;

    template <typename Accessor, typename Iterator, typename Values, typename Arch>
    static void
    for_each_(Values& values, Arch& arch,  bool is_args, hl::false_type)
    {}

    template <typename Accessor, typename Iterator, typename Values, typename Arch>
    static void
    for_each_(Values& values, Arch& arch, bool is_args, hl::true_type)
    {
        // This getting the value typename
        typedef typename
            Iterator::__tag_name value_type_name;

        // This calculated next step to iteration
        typedef typename
            Iterator::next_type next_type;

        typedef typename
            Iterator::type value_type;

        value_type& v = values.template get<value_type_name>();
        enum {    where = Values::template get_id_by_name<value_type_name>::value    };

        // Take the result id, or take the parameter id
        decltype(Accessor::template resultName<where>()) name = is_args ?
                Accessor::template argName<where>() : Accessor::template resultName<where>();

        // Push value to arch
        arch >>
            std::pair<StringType, value_type&>(name, v);

        this_t::template for_each_<Accessor, next_type>
        (values, arch, is_args, hl::id2type<!hl::is_same<typename next_type::next_type, hl::null_type>::value >() );
    }

    template <typename Accessor, typename Values, typename Arch>
    static void
    for_each_values(Values& values, Arch& arch, bool is_args = false)
    {
        this_t::template for_each_<Accessor, Values>(values, arch, is_args, hl::id2type<true >());
    }
};
}

#endif
