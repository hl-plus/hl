
#ifndef OPTIONAL_HPP_INCLUDED_DKSFJGKDHJSFKGSFVBSDVKFBHSKDFHJGKRESTG
#define OPTIONAL_HPP_INCLUDED_DKSFJGKDHJSFKGSFVBSDVKFBHSKDFHJGKRESTG

#if defined (INSTANTIATION_WORK)
    #include <hl/include/type_traits.hpp>
#else
    #include "../../include/type_traits.hpp"
#endif

namespace hl
{
    // The class describe behaviour the optional parameter
    // which can be, or not.
    // perhaps we should skip if this argument isn't set
    template <typename Type>
    struct optional
    {
        // constructor
        optional ()
            : set_(false)
                , value_()
        {   }

        optional (Type const& value)
            : set_(true)
                , value_(value)
        {  }

        // can be false before call set
        // return: true is arguemnts wasn't set
        bool empty()
        {
            return !set_;
        }

        // We should use this unit to
        // describe hat value wasn't set
        bool set_is_set(bool set)
        {
            bool old_set = set_;
            set_ = set;
            return old_set;
        }

        void set(Type const& v)
        {
            value_ = v;
            set_ = true;
        }

        inline Type&
        get()
        {
            return value_;
        }

    private:
        bool set_;
        Type value_;
    };

    template <typename Type
        , typename Tag>
    struct optional_value : optional<Type>
    {
        typedef optional<Type> base;
        optional_value ()
            : base()
        { }

        optional_value (Type const& value)
            : base(value)
        { }
    };

    template <typename Tag, typename Type>
    inline optional_value <Type, Tag>
    opt (Type const& v)
    {
        // This should be tested is the class have a ref
        optional_value<Type, Tag> ov(v);
        return ov;
    }

    // This is checkr about this is optional
    // we should it check by compilations in somewhere
    template <typename Type >
    struct is_optional
    {
        enum {  value = false };
        typedef hl::empty_type type;
    };

    // This is specitalixzation
    // if true of optional
    template <typename Type>
    struct is_optional<optional<Type> >
    {
        enum { value = 1 };
        typedef Type type;
    };

} // hl

#endif // OPTIONAL_HPP_INCLUDED_DKSFJGKDHJSFKGSFVBSDVKFBHSKDFHJGKRESTG
