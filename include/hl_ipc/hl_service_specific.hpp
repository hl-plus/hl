#ifndef hl_SERVICE_SPECIFIC_HPP_DLKGFJHKDFHDFJH
#define hl_SERVICE_SPECIFIC_HPP_DLKGFJHKDFHDFJH

#if defined (HL_INSTALLED)
    #include "pbn_json_backend.hpp"
#else
    #include "pbn_json_backend.hpp"
#endif


namespace hl
{
    //
    template <typename Type>
    struct noname
    {
        Type value_;
    };
}

namespace hl
{
template <typename String, typename Invoker>
struct hl_svc_server
    :  hl::PbnJsonBackend<String, Invoker>
{
    // This is server side
    struct is_server__;
    typedef std::string result_type;

};

template <typename Type>
struct optional {  };

template <typename Type>
struct np {  };

template <typename... _Ts>
struct parse
{
    enum { value = sizeof... (_Ts)
        , is_abstract = 1
        , np_count = 0
        , optional_count = 0
    };
};

template <typename Type, typename... _Ts>
struct parse<Type, _Ts... >
{
    typedef parse<_Ts... > next_type;
    enum { value = sizeof... (_Ts) + 1
            , is_abstract = 0
            , np_count = next_type::np_count
            , optional_count = next_type::optional_count
    };
};

template <typename Type, typename... _Ts>
struct parse<optional<Type>, _Ts... >
{
    typedef parse<_Ts... > next_type;
    enum {  value = sizeof... (_Ts) + 1
        , is_abstract = 0
        , np_count = next_type::np_count
        , optional_count = next_type::optional_count + 1
    };
};

template <typename Type, typename... _Ts>
struct parse<np<Type>, _Ts... >
{
    typedef parse<_Ts... > next_type;
    enum {  value = sizeof... (_Ts) + 1
        , is_abstract = 0
        , np_count = next_type::np_count + 1
        , optional_count = next_type::optional_count
    };
};

}

#endif // hl_SERVICE_SPECIFIC_HPP_DLKGFJHKDFHDFJH
