/********/


#ifndef INTERFACE_TRAITS_HPP_DSHFJGDJHFGJDHSFGJDSFHGJSDHFGJSDHFGJSDKFGJKDSDVNBXCMVNKDSFGJIFGUHDIFUHDFGIHUDF
#define INTERFACE_TRAITS_HPP_DSHFJGDJHFGJDHSFGJDSFHGJSDHFGJSDHFGJSDKFGJKDSDVNBXCMVNKDSFGJIFGUHDIFUHDFGIHUDF

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
# pragma GCC system_header
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)



namespace hl
{

template<typename WrapService>
struct traits_resolver {
    typedef hl::null_type string_type;
    typedef hl::null_type service_type;
    typedef hl::null_type backend_type;
};

} //namespace hl


#endif
