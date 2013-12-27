#ifndef hl_IPC_SPECIFIC_HPP_OKLJSGKDJSFGKDFJGKJBVXCDTGFUHUG
#define hl_IPC_SPECIFIC_HPP_OKLJSGKDJSFGKDFJGKJBVXCDTGFUHUG

#if defined (__HL_INSTALLED)
    #include <hl/include/type_traits.hpp>
    #include <hl/include/throw.hpp>
    #include <hl/include/sfinae.hpp>
    #include <hl/include/hl_ipc/optional.hpp>

    #include <hl/include/register_type.hpp>
    #include <hl/include/reflection.hpp>
    #include <hl/include/lock_guard.hpp>
#else
    #include "../../include/type_traits.hpp"
    #include "../../include/throw.hpp"
    #include "../../include/sfinae.hpp"
    #include "../../include/hl_ipc/optional.hpp"

    #include "../../include/register_type.hpp"
    #include "../../include/reflection.hpp"
    #include "../../include/lock_guard.hpp"
#endif

namespace hl
{

    ///
    // This is a type by which I can use
    // implementation approach with one interface
    template <typename Service, typename Interface>
    struct Impl : Interface
    {
        typedef Interface interface_type__;

        static char const*
        uri()   { return Service::uri(); }

        static char const*
        svc_name()  { return Service::svc_name(); }

        static char const*
        name()  { return Service::name(); }
    };
}

namespace hl
{
    // This is sfinae about server specification
    HL_SFINAE_DECL(is_server, is_server__);
    HL_SFINAE_DECL(is_client, is_client__);

    template <typename Type>
    struct impl_resolve
    {
        enum { value = 0    };
        typedef Type service_type;
        typedef Type interface_type;
    };

    template <typename Service, typename Interface>
    struct impl_resolve <hl::Impl<Service, Interface> >
                : public Interface
    {
        enum { value = 1 };
        typedef Service service_type;
        typedef Interface interface_type;
    };
}

namespace hl
{
    template<typename Type>
    struct HolderType
    {
        typedef Type type;
    };

    template<typename Type, typename Type2>
    struct HolderType2
    {
        typedef Type type;
        typedef Type2 type2;
    };

}


#endif // hl_IPC_SPECIFIC_HPP
