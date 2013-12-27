#ifndef ENVIRONMENT_HPP_XCLBFJHKCFJGHFGNJGFMHCV
#define ENVIRONMENT_HPP_XCLBFJHKCFJGHFGNJGFMHCV

#include <stdlib.h>
#include <string>

#include "../any2str.hpp"

namespace hl
{
    namespace environment
    {
        // This class should get environment
        // variable
        struct variable
        {
            variable (std::string const& name)
                    : name_(name)
            {   }

            template <typename Type>
            inline Type get ()
            {
                char* env_v = getenv(name_.c_str());
                if (env_v)
                {
                    Type v ;
                    (hl::any2str() << env_v) >> v;
                    return v;
                }

                return Type();
            }

            std::string name_;
        };
    }
}
#endif // ENVIRONMENT_HPP_XCLBFJHKCFJGHFGNJGFMHCV
