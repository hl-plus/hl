#ifndef CONVERSION_HPP_INCLUDED_XDKFGGGGHJGHDFKGHJFBNNDFKGB
#define CONVERSION_HPP_INCLUDED_XDKFGGGGHJGHDFKGHJFBNNDFKGB

#if defined (INSTANTIATION_WORK)
    #include "../hl_ipc/optional.hpp"
    #include "../sfinae.hpp"
#else
    #include <hl/include/hl_ipc/optional.hpp>
    #include <hl/include/sfinae.hpp>
#endif

namespace hl
{
    HL_SFINAE_DECL(is_converter, _Converter);

    //
    // This a basically class which not contains
    // any implemented methods to stop link error in unimplemented
    // some conversions
    template <typename To>
    struct conversion;
}

#endif // CONVERSION_HPP
