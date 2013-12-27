/******************/

#ifndef TYPE_ID_HPP_047735E4_5FE5_11E2_B78E_CEE86188709B_INCLUDED
#define TYPE_ID_HPP_047735E4_5FE5_11E2_B78E_CEE86188709B_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
    #include "msvc/type_id.hpp"
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
# pragma GCC system_header
    #include "gcc/type_id.hpp"
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)


#endif // TYPE_ID_HPP_INCLUDED
