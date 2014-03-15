/**********************/

#ifndef TYPENAME_HPP_A85FA7C8_5FE9_11E2_B9A2_6FED6188709B_INCLUDED
#define TYPENAME_HPP_A85FA7C8_5FE9_11E2_B9A2_6FED6188709B_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
# pragma GCC system_header
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

namespace hl
{
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
    // The debug version to getting name typename
    template <typename type>
    inline const char *__cdecl
    get_typename()
    {
        static char* str_ = 0;
        if (!str_)
        {
            //boost::guard_lock<struct tag__DHFIGKDF> g;
            if (!str_)
            {
#define __PREFIX_OF_ "const char *__cdecl hl::get_typename<struct "
#define __SUFFIX_OF_ ">(void)"
                static std::string ss_type = __FUNCSIG__;
                unsigned int begin_ = sizeof(__PREFIX_OF_) - 1
                    , end_ = ss_type.rfind(">(void)");
                ss_type = ss_type.substr(begin_, end_ - begin_);
                str_ = const_cast<char *> (ss_type.c_str());
            }
        }

        return str_;
    }

    template <typename type>
    inline std::string const&
    get_xml_typename ()
    {
        static std::string* ss_ = 0;
        if (!ss_)
        {
            //guard_lock(type_SHDJFHGJDSF);
            if (!ss_)
            {
                static std::string
                    sst_ = get_typename<type>();
                bool fnd = true;
                while (fnd)
                {
                  fnd = false;
                          for (size_t p = 0; std::string::npos
                                              != (p = sst_.find("::", p)); ++p)
                          {
                    sst_ = sst_.replace(p, sizeof("::")-1, ".");
                    fnd = true;
                  }
                }

                ss_ = &sst_;
            }
        }

        return *ss_;
    }
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
    template <typename type>
    inline char const*
    typename_ ()
    {
        static char* name__l = 0;
        if (!name__l)
        {
            //lock();
            if (!name__l)
            {
                static std::string str__ = __PRETTY_FUNCTION__;
                str__[str__.length() - 1] = '\0';
                size_t pp = str__.rfind("::")
                        , ppe = str__.rfind("= ");
                pp = std::max(pp, ppe);
                   str__ = str__.substr(pp + 2, (str__.length() - pp) - 1);
                name__l = const_cast<char* >(str__.c_str());
            }
        }

        return name__l;
    }
#endif
}

#endif
