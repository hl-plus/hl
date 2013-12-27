/*******************/

#ifndef XML_SETTINGS_HPP_A85FA7C8_5FE9_11E2_B9A2_6FED6188709B_INCLUDED

#define XML_SETTINGS_HPP_A85FA7C8_5FE9_11E2_B9A2_6FED6188709B_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
# pragma GCC system_header
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if defined (__BOOST_INSTALLED)
    #include <boost_1_53_0\boost\property_tree\ptree.hpp>
    #include <boost_1_53_0\boost\property_tree\xml_parser.hpp>
#else
    #include "boost\property_tree\ptree.hpp"
    #include "boost\property_tree\xml_parser.hpp"
#endif

namespace hl
{
struct xml_settings
{
    xml_settings()
        : pt_()
        , xml_path_()
    {
        reload();
    }

    xml_settings(std::string const& path)
        : pt_()
        , xml_path_(path)
    {
        reload();
    }

    void reload()
    {
        using namespace boost::property_tree;
        if (!pt_.empty())
            pt_.clear();
        read_xml(get_ui_xml_path(), pt_);
    }

    std::string
    get_ui_xml_path()
    {   return xml_path_;   }

    template <typename as_type, typename type>
    inline as_type
    get(std::string const& field)
    {
        return pt_.get<as_type>((hl::get_xml_typename<type>() + ".") + field);
    }

    template <typename as_type, typename type>
    inline as_type
    get(std::string const& field, as_type const& default_)
    {
        return pt_.get<as_type>((hl::get_xml_typename<type>() + ".") + field, default_);
    }

    boost::property_tree::ptree pt_;
    std::string xml_path_;
};

}

#endif
