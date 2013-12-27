/***************/

#ifndef ANY2STR_HPP_SDKFJHGLKDSFJHLGDF_INCLUDED
#define ANY2STR_HPP_SDKFJHGLKDSFJHLGDF_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
# pragma GCC system_header
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)
#include <sstream>

namespace hl
{

/**
 * @brief The any2str struct
 *      To convert some value from same type to string
 *  and could get any type. Like this:
 *          int _555 = 0;
 *          (any2str() << "555") >> _555;
 */
struct any2str
{
    any2str() :
        ss_()
    {
    }

    /**
     * @brief operator <<
     * @param v
     */
    template<typename type>
    inline any2str&
    operator <<(type v)
    {
        ss_ << v;
        return (*this);
    }

    template<typename type>
    inline type get()
    {
        type ret;
        ss_ >> ret;
        return ret;
    }

    template<typename _out_type>
    any2str& operator >>(_out_type& tt)
    {
        ss_ >> tt;
        return (*this);
    }

    inline std::string str()
    {
        return ss_.str();
    }

    std::stringstream ss_;
};

struct any2wstr
{
    any2wstr() :
        ss_()
    {
    }

    template<typename _in_type>
    any2wstr& operator <<(_in_type tt)
    {
        ss_ << tt;
        return (*this);
    }

    template<typename _out_type>
    any2wstr& operator >>(_out_type& tt)
    {
        ss_ >> tt;
        return (*this);
    }

    template<typename _out_type>
    _out_type convert()
    {
        _out_type v = _out_type();
        operator >>(v);
        return v;
    }

    inline std::wstring str()
    {
        return ss_.str();
    }

    std::wstringstream ss_;
};

}//namespase hl

#endif // ANY2STR_HPP_SDKFJHGLKDSFJHLGDF_INCLUDED
