
#ifndef THROW_HPP_INCLUDED_SDKFJGDNMFGBNXCMBVNMCVNBMCVNBMNCMBVNDFKLGHSJ
#define THROW_HPP_INCLUDED_SDKFJGDNMFGBNXCMBVNMCVNBMCVNBMNCMBVNDFKLGHSJ

#include <stdexcept>

namespace hl
{
    inline void
    std_throw_(std::string const& exc)
    {
        throw std::runtime_error(exc.c_str());
    }

    template<typename Error>
    class explicit_exception : public std::exception
    {
    public:

        explicit
        explicit_exception(Error const& error) noexcept(true)
            : error_(error)
        {   }

        virtual const char*
        what() const noexcept(true)
        {
            return ((std::string)error_).c_str();
        }

        ~explicit_exception() noexcept(true)
        {   }

        Error error_;
    };

    template <typename Error>
    inline void
    std_throw_expl_(Error const& err)
    {
        throw explicit_exception<Error>(err);
    }

}

#endif // THROW_HPP
