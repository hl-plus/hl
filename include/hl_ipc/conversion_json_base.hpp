#ifndef CONVERSION_JSON_BASE_HPP_DKLGJHDFKGJHKDFGHJFKG
#define CONVERSION_JSON_BASE_HPP_DKLGJHDFKGJHKDFGHJFKG

#if defined (INSTANTIATION_WORK)
    #include <hl/include/hl_ipc/conversion.hpp>
    #include <hl/include/hl_ipc/hl_ipc_specific.hpp>
#else
    #include "../hl_ipc/hl_ipc_specific.hpp"
    #include "../hl_ipc/conversion.hpp"
#endif


namespace hl
{
#define CHECK_OBJ(json_obj)                 \
    if (!json_obj || is_error(json_obj))    \
        return ;

//
// This is a basically conversation
// to backend parser type cjson
// TODO: move to hl_json_conversion
struct conversion_json_base
{
    // To check is implemented converter
    struct _Converter;

    //
    // This conversions from value to json
    static void
    convert(json_object* json, bool& v)
    {
        CHECK_OBJ(json);
        v= json_object_get_boolean(json);
    }

    static void
    convert(json_object* json, std::string& v)
    {
        CHECK_OBJ(json);
        v= json_object_get_string(json);
    }

    static void
    convert(json_object* json, double& v)
    {
        CHECK_OBJ(json);
        v= json_object_get_double(json);
    }

    static void
    convert(json_object* json, int& v)
    {
        CHECK_OBJ(json);
        v= json_object_get_int(json);
    }
    // End convention segment

    //
    // This conversions from values to json_object

    // This branch we should move
    // To the Interface scope
    // Also you can use default parameter to describe the optional parameters
    // currently
    template <typename Type>
    static json_object*
    convert(hl::optional<Type > const&)
    {
        hl::std_throw_(std::string("Not implemented ") + __PRETTY_FUNCTION__);
        return 0;
    }

    //
    // Basically converters
    static json_object*
    convert(char* const& str)
    {
        return json_object_new_string(str);
    }

    static json_object*
    convert(std::string& str)
    {
        return json_object_new_string(str.c_str());
    }

    // Conversion from string
    static json_object*
    convert(std::string const& str) {
        return json_object_new_string(str.c_str());
    }

    static json_object*
    convert(bool& value) {
        return json_object_new_boolean(value);
    }

    static json_object*
    convert(bool const& value) {
        return json_object_new_boolean(value);
    }

    static json_object*
    convert(int& value) {
        return json_object_new_int(value);
    }

    static json_object*
    convert(int const& value) {
        return json_object_new_int(value);
    }
};

template <typename Type>
struct conversion : conversion_json_base
{
    struct _Converter;

};


// This is a optional conversion
//
template <typename Type>
struct conversion<hl::optional<Type> >
{
    struct _Converter;

    static void
    convert(json_object* jobj, hl::optional<Type>& v)
    {
        if (!jobj || is_error(jobj))
        {
            v.set_is_set(false);
            return ;
        }

        v.set_is_set(true);

        //
        // Delegate the conversion to the basic
        // conversion type
        conversion<Type>::convert(jobj, v.get());
    }
};

}

#endif // CONVERSION_JSON_BASE_HPP_DKLGJHDFKGJHKDFGHJFKG
