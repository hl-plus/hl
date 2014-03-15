#ifndef CONVERSION_PNBJSON_HPP58dcdca6ebfdff420d3613b506ef5762f31767ba
#define CONVERSION_PNBJSON_HPP58dcdca6ebfdff420d3613b506ef5762f31767ba

#if defined (INSTANTIATION_WORK)
    #include "../hl_ipc/conversion.hpp"
    #include "../sfinae.hpp"
#else
    #include <hl/include/sfinae.hpp>
    #include <hl/include/hl_ipc/conversion.hpp>
#endif

namespace hl
{

struct conversion_pbnjson_base
{
    struct _Converter;

    static void convert(const pbnjson::JValue &j, bool &v)
    {
        LG_ASSERT(j.isBoolean());
        v = j.asBool();
    }

    static void convert(const pbnjson::JValue &j, std::string &v)
    {
        LG_ASSERT(j.isString());
        v = j.asString();
    }

    static void convert(const pbnjson::JValue &j, double &v)
    {
        LG_ASSERT(j.isNumber());
        v = j.asNumber<double>();
    }

    static void convert(const pbnjson::JValue &j, int &v)
    {
        LG_ASSERT(j.isNumber());
        v = j.asNumber<int>();
    }

    static pbnjson::JValue convert(bool v)
    {
        return pbnjson::JValue(v);
    }

    static pbnjson::JValue convert(std::string v)
    {
        return pbnjson::JValue(v);
    }

    static pbnjson::JValue convert(double v)
    {
        return pbnjson::JValue(v);
    }

    static pbnjson::JValue convert(int v)
    {
        return pbnjson::JValue(v);
    }
};

template <typename Type>
struct conversion : conversion_pbnjson_base
{
    struct _Converter;
};

template <typename Type>
struct conversion<hl::optional<Type> >
{
    struct _Converter;

    static void
    convert(const pbnjson::JValue &j, hl::optional<Type>& v)
    {
        if(j.isNull())
        {
            v.set_is_set(false);
            return;
        }
        v.set_is_set(true);

        //
        // Delegate the conversion to the basic
        // conversion type
        conversion<Type>::convert(j, v.get());
    }
};

}

#endif // CONVERSION_PNBJSON_HPP
