#ifndef CONVENTION_NAMES_HPP_SDKLFJGKDSJGFKDHHERTUIHDRKFBXJ
#define CONVENTION_NAMES_HPP_SDKLFJGKDSJGFKDHHERTUIHDRKFBXJ
namespace hl
{
    // Argument name getter
    template<typename Accessor
            , typename Class = typename Accessor::class_type>
    struct argument_name
    {
        // Class of names
        typedef Class class_type;

        // Get name by RpcType
        template <typename RpcType, typename Name>
        static typename
            class_type::string_type
        get()
        {
            // Take id by name tag type
            enum { I = RpcType::template get_id_by_name<Name>::value  };

            // Take name from RPC type accessory
            return typename
                class_type::string_type(Accessor::template argName<I>());
        }
    };

    // Argument name getter
    template<typename Accessor
            , typename Class = typename Accessor::class_type>
    struct return_value_name
    {
        typedef Class class_type;

        template <typename RpcType, typename Name>
        static typename
            class_type::string_type
        get()
        {
            typedef typename
                class_type::string_type string_type;

            enum {  I = RpcType::template get_id_by_name<Name>::value };

            return string_type(Accessor::template resultName<I>());
        }
    };

    template <typename Accessor
                , typename Class = typename Accessor::class_type>
    struct rpc_type_name
    {
        typedef Class class_type;

        template <typename RpcType, typename Name>
        static typename
            class_type::string_type
        get()
        {
            enum {  I = RpcType::template get_id_by_name<Name>::value };

            return
                typename class_type::string_type(class_type::template NameAccessor<hl::HolderType<RpcType> >::template name<I>());
        }
    };

}
#endif // CONVENTION_NAMES_HPP_SDKLFJGKDSJGFKDHHERTUIHDRKFBXJ
