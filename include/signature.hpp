#ifndef SIGNATURES_HPP_DFKGHJKDFGJHKDFJGDHJGKDHKGFJHDVBNCN
#define SIGNATURES_HPP_DFKGHJKDFGJHKDFJGDHJGKDHKGFJHDVBNCN

namespace hl
{
    // This is class to making type from class methods
    //
    template <typename Type
    , typename Return
    , typename... Params>
    struct parse_signature
    {
        typedef Return (Type::*Function)(Params...);

        template <Function Func>
        struct specify
        {
            // should research const expr static const Function function_ = Func;
            static constexpr Function
            func()
            {   return Func;    }
        };
    };

    // This function should return the type from which we can get type of this function
    template <typename Type
    , typename Return, typename... Args >
    inline parse_signature<Type, Return, Args... >
    _func_get_signature__(Return (Type::*ptr)(Args...));

#define HL_SIG_FUNCTION_TYPE(func) \
            typename decltype(_func_get_signature__(func))::template specify<func>

}

#endif // SIGNATURES_HPP_DFKGHJKDFGJHKDFJGDHJGKDHKGFJHDVBNCN
