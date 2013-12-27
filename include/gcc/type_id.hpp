/********************************************************************************
 *   Copyright(c) 2013 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 ********************************************************************************/

#ifndef TYPE_ID_HPP_047735E4_5FE5_11E2_B78E_CEE86188709B_INCLUDED
#define TYPE_ID_HPP_047735E4_5FE5_11E2_B78E_CEE86188709B_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
    #include "msvc/type_id.hpp"
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
# pragma GCC system_header
    #include "gcc/type_id.hpp"
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

namespace hl
{

#define MAX_DEEP 100

template <int II>
struct type_id_sizer {    char bf_[II]; };

template <int I = MAX_DEEP>
struct recurse_inst : recurse_inst<I-1>
{  };

template<>
struct recurse_inst<0>
{   };


template <typename type>
inline type_id_sizer<1> ___type_id_jump(...);

template<typename type_>
struct type_id
{
private:
    template<int id = sizeof(___type_id_jump<type_>((recurse_inst<MAX_DEEP>*)0))>
    struct impl
    {
        enum { v = id + 1 };
        template <typename type>
        friend type_id_sizer<v> ___type_id_jump(recurse_inst<v>* );

        static const int val = id - 1;
    };
public:
    enum { value = impl<>::val };
};

} //namespace hl


#endif // TYPE_ID_HPP_INCLUDED
