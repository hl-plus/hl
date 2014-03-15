
#ifndef LS_ERROR_HPP_DSXKFGMBNDFVJBKDJSFGKLHJDKFGJHKDRJHKNDMFBNDMSFB
#define LS_ERROR_HPP_DSXKFGMBNDFVJBKDJSFGKLHJDKFGJHKDRJHKNDMFBNDMSFB

#include <stdexcept>
#include <sstream>

#include <luna-service2/lunaservice.h>

namespace hl
{
    // Wrapper on a LSError
    struct ls_error
    {
        ls_error ()
            : error_()
            , owner_(true)
        {
            LSErrorInit(&error_);
        }

        ls_error (ls_error const& error)
            : error_(error.error_)
        {
            error.owner_ = false;
        }

        ls_error& operator = (ls_error const& err)
        {
            error_ = err.error_;
            err.owner_ = false;
            return *this;
        }

        inline LSError*
        operator &()
        {
            return &error_;
        }

        operator LSError()
        {
            return error_;
        }

        inline LSError*
        get()
        {
            return &error_;
        }

        inline LSError*
        operator ->()
        {
            return &error_;
        }

        inline std::string
        message(std::string const& mess = "Error ") const
        {
            std::stringstream ss;

            ss << mess.c_str() << " ERROR " << error_.error_code << ": " << error_.message
               <<"( " << error_.func << " @ " << error_.file << ":" << error_.line << ")";

            return ss.str();
        }

        operator std::string() const
        {
            return this->message();
        }

        void warning(std::string const& msg = "Error ") const
        {
            std::cout << msg.c_str() << message().c_str() << std::endl;
            g_warning("%s%s", msg.c_str(), message().c_str());
        }

        ~ls_error()
        {
            if (owner_)
                LSErrorFree(&error_);
        }

        LSError error_;
        mutable bool owner_;
    };
}
#endif // LS_ERROR_HPP_DSXKFGMBNDFVJBKDJSFGKLHJDKFGJHKDRJHKNDMFBNDMSFB
