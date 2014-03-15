/*******************/

#ifndef PP_CONCAT_HPP_DFGJHKDFJGKHDJFKGHJKDFOGWERTVNBGDJGFKHOREW
#define PP_CONCAT_HPP_DFGJHKDFJGKHDJFKGHJKDFOGWERTVNBGDJGFKHOREW

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
# pragma GCC system_header
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)
#define HL_PP_CONCATINATION_I(Token, Value) Token##Value

#define HL_PP_CONCATINATION(Token, Value) \
            HL_PP_CONCATINATION_I(Token, Value)

#define MAKE_TOKEN_WITH_COUNT_PARM_ID(Token, ...)    \
            HL_PP_CONCATINATION(Token, HL_PP_COUNT_PRMS(__VA_ARGS__))

#define MAKE_TOKEN_WITH_COUNT_PARM_ID_RMPTH(Token, ...)    \
            HL_PP_CONCATINATION(Token, HL_PP_COUNT_PRMS __VA_ARGS__)

#endif
