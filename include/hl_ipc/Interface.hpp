/*******************/

#ifndef INTERFACE_HPP_SDKFHGSDKFGIRETGKREBGNDFGDKGJHKDGFLHLDGFKJFKLDLJGFLKJDFANSCVDFLBG
#define INTERFACE_HPP_SDKFHGSDKFGIRETGKREBGNDFGDKGJHKDGFLHLDGFKJFKLDLJGFLKJDFANSCVDFLBG

#include <functional>
#include <vector>
#include <memory>
#include <algorithm>

#if defined (__HL_INSTALLED)
    #include <hl/include/values.hpp>
    #include <hl/include/sizer.hpp>
    #include <hl/include/hl_ipc/hl_ipc_specific.hpp>
    #include <hl/include/hl_ipc/pp_hl_ipc.hpp>
    #include <hl/include/hl_ipc/interface_traits.hpp>
    #include <hl/include/hl_ipc/optional.hpp>
    #include <hl/include/hl_ipc/naming_conventions.hpp>
#else
    #include "../../include/values.hpp"
    #include "../../include/sizer.hpp"
    #include "../../include/hl_ipc/hl_ipc_specific.hpp"
    #include "../../include/hl_ipc/pp_hl_ipc.hpp"
    #include "../../include/hl_ipc/interface_traits.hpp"
    #include "../../include/hl_ipc/optional.hpp"
    #include "../../include/hl_ipc/naming_conventions.hpp"
#endif

// Overriding traits to resolving an Interface implementation
namespace hl
{
    template<typename Service, typename StringType, typename Backend>
        struct Interface;
}

namespace hl
{
    template<typename Service, typename StringType, typename Backend>
    struct traits_resolver<hl::Interface<Service, StringType, Backend> > {
        typedef StringType string_type;

        // When we use approacgh with one interface
        // we will use hl::Impl to describe and assigne interface
        typedef typename
                hl::impl_resolve<Service>::interface_type service_type;
        typedef Backend backend_type;
    };
}

#include "../hl_ipc/interface_reflection.hpp"


namespace hl
{

struct indefiniteness
{   };

// The service should support an a service
template <typename Service, typename StringType
          , typename Backend >
struct Interface
    : hl::args_iterator<Interface<Service, StringType, Backend> >
    , hl::value_iterator<Interface<Service, StringType, Backend> >
    , Backend
    , hl::if_c< hl::impl_resolve<Service>::value
                , typename hl::impl_resolve<Service>::interface_type
                , indefiniteness >::type
{
    typedef StringType string_type;
    typedef Backend base;
    typedef hl::args_iterator<Interface<Service, StringType, Backend> > ArgsIterator;

    // Interface type
    // This type can be not equal with service_type
    typedef typename
        hl::impl_resolve<Service>::interface_type interface_type;

    // Instance type
    typedef typename
        hl::impl_resolve<Service>::service_type service_type;


    // This is raw type, it can be hl::Impl<service_type, interface>
    // this approach we should use to work
    // with one interface on a client and server side
    typedef Service raw_service_type;

    typedef std::shared_ptr<bool > Life;


    Interface(): base()
            , live_(new bool(true))
    {}

    template <typename QuestAccessor
        , int isAccessor = 0>
    struct GetSpecific : hl::if_c<
                        interface_type::template AccessorSpec<hl::HolderType<QuestAccessor> >::value
                        , typename interface_type::template AccessorSpec<hl::HolderType<QuestAccessor> >::type
                        , QuestAccessor
                    >::type
    {
        typedef typename
            hl::if_c< interface_type::template AccessorSpec<hl::HolderType<QuestAccessor> >::value
                , typename interface_type::template AccessorSpec<hl::HolderType<QuestAccessor> >::type
                , QuestAccessor    >::type accessor;
    };

    // ./luna-send -n 1 s_ hl://com.hl.smartKey/search '{ "query": "hallo", "context": "start", "quick": "false"}'
    template <typename Accessor>
    struct args_format
    {
        typedef typename
            Backend::template Archive<Service, Accessor>::type Archive;

        args_format(Archive& arch, bool empty = true)
        : arch_(arch)
        {
            // start root object
            if (empty && arch.empty())
                arch_.begin_object("");
        }

        template <typename RpcType
              , typename NameResolver = rpc_type_name<Accessor, service_type> >
        struct o_values
        {
            o_values(args_format& format)
            : format_(format)
            {}

            // type type is null_paramter
            template <typename Name, typename Value>
            inline o_values&
            add_arg_(std::pair<Name*, Value&> const& value
                        , hl::true_type const&)
            {
                return *this;
            }

            // False type is not null_paramter
            template <typename Name, typename Value>
            inline o_values&
            add_arg_(std::pair<Name*, Value&> const& value
                        , hl::false_type const&)
            {
                typedef typename Accessor::class_type class_;

                // Take name from RPC type accessory
                format_.add_arg(
                        NameResolver::template get<RpcType, Name>()
                        , value.second);

                return *this;
            }

            template <typename Name, typename Value>
            inline o_values&
            operator ()(std::pair<Name*, Value&> const& value)
            {
                return this->add_arg_(value
                            , hl::is_same<Value, hl::null_parameter>());
            }

            args_format &format_;
        };

        template <typename RpcType
            , typename NameResolver = rpc_type_name<Accessor, service_type> >
        struct in_values
        {
            in_values (args_format &format)
                : format_(format)
            {    }

            template <typename Name, typename Value>
            inline in_values&
            operator ()(std::pair<Name*, Value&> const& value)
            {
                typedef typename Accessor::class_type class_type;

                format_ >> std::pair<StringType, Value&>(
                        NameResolver::template get<RpcType, Name>()
                        , value.second);
                return *this;
            }

            args_format& format_;
        };

        // Pack value to
        template <typename NameAccessor, typename Value>
        void pack(Value& v)
        {
            // pack to values
            o_values<Value, NameAccessor> ov(*this);
            Value::for_each(ov, v);
        }

        template <typename Argname, typename Value>
        void add_arg(Argname n, Value& v, hl::true_type)
        {
            // create object
            arch_.begin_object(n);

            // Pack value to arch
            this->template pack<rpc_type_name<Accessor, service_type > >(v);

            // push object to parent
            arch_.end_object();
        }

        template <typename ArgName, typename Value>
        void add_arg_(ArgName n, Value& value, hl::true_type)
        {   }

        template <typename ArgName, typename Value>
        void add_arg_(ArgName n, Value& value, hl::false_type)
        {
            arch_ << std::pair<StringType, Value&>(StringType(n), value);
        }

        template <typename ArgName, typename Value>
        void add_arg(ArgName n, Value& value, hl::false_type)
        {
            this->add_arg_(n, value
                       , hl::is_same<Value, hl::null_parameter>() );
        }

        template <typename ArgName, typename Value>
        void add_arg(ArgName an, std::vector<Value>& value)
        {
            arch_.begin_array(an, value.size());

#if defined __HL_USED_LAMBDA
            std::for_each(value.begin(), value.end()
                    , [this](Value& v){ this->add_arg(StringType(""), v); } );
#else
            // Local object as applier to apply the argument
            struct applier {
                applier(args_format& ds)
                    : ds_(ds) {}
                void operator () (Value& v)    {    ds_.add_arg(StringType(""), v);    }
                args_format& ds_;
            };

            std::for_each(value.begin(), value.end()
                        , applier(*this));
#endif

            arch_.end_array();
        }

        // Add argument to archive
        template <typename ArgName, typename Value>
        void add_arg(ArgName an, Value& value)
        {
            this->add_arg(an, value
                        , hl::id2type<hl::is_value<Value>::value >());
        }

        template <typename Type>
        inline void    print_tt()
        {
#ifdef LOGGABLE
            std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        }

        template <int I, typename ArgName, typename Arg>
        inline void
        on_arg(ArgName an, Arg& v)
        {
            typedef typename
                Accessor::args_type args_type;
            typedef typename
                args_type::template get_type_by_id<I>::type arg_type;
            typedef typename
                hl::remove_const<Arg>::type Argument;

            typedef typename
                hl::if_c<
                    hl::is_same<arg_type, Argument>::value
                    , typename hl::remove_const<arg_type>::type&
                    , arg_type >::type Solved;

            static_assert(hl::is_explicitly_convertible<Solved, Argument>::value, "Isn't convertible types in call.");
            Solved value = v;
            this->add_arg(StringType(an), value);
        }

        template <typename Index, typename Value>
        void assign_return(std::pair<Index, Value&> const& value
                    , hl::true_type)
        {
            // create object
            arch_.begin_object(value.first, true);
            in_values<Value> in(*this);
            Value::for_each(in, value.second);

            // push object to parent
            arch_.end_object(true);
        }

        template <typename Index, typename Value>
        void assign_return(std::pair<Index, Value&> const& value
                , hl::false_type)
        {
            arch_ >> value;
        }

        template <typename Value>
        inline args_format&
        operator >> (std::pair<StringType, std::vector<Value>&> const& value)
        {
            std::vector<Value>& values = value.second;

            // TODO: check empty array
            int _Size = arch_.begin_array(value.first, 0, true);
            if (_Size)
            {
                values.resize(_Size);
                int count = 0;

                // We have to check the c++ 0x11 because some places in our projects don't have an
#               if defined __HL_USED_LAMBDA

                // We serialize from archive to values by index
                std::for_each(values.begin(), values.end()
                        , [this, &count](Value& v) {
                            (*this) >> std::pair<int, Value&>(count++, v);
                        });
#               else
                // Local object
                struct applier {
                    applier(args_format& ds, int& count)
                        : ds_(ds)
                        , count_(count)
                    {    }

                    void operator () (Value& v)    {
                        ds_ >> std::pair<int, Value&>(count_++, v);
                    }

                    args_format& ds_;
                    int& count_;
                };

                std::for_each(values.begin(), values.end()
                        , applier(*this, count));

#                endif
            }
            arch_.end_array(true);
            return *this;
        }

        // This is taking value by name from archive
        template <typename Value>
        inline args_format&
        operator >> (std::pair<StringType, Value&> const& value)
        {
            this->assign_return(value
                    , hl::id2type<hl::is_value<Value>::value>());
            return *this;
        }

        // This is an index in array
        template <typename Value>
        inline args_format&
        operator >> (std::pair<int, Value&> const& value)
        {
            this->assign_return(value
                    , hl::id2type<hl::is_value<Value>::value>());
            return *this;
        }

        Archive& arch_;
    };

    template <typename Type>
    struct IsDefault {enum {value = 0};};

    template <typename Type>
    struct IsDefault<hl::Default<Type > >
    {
        enum {value = 1};
    };

    template <typename Describe
        , int ShouldCheck = 0>
    struct CheckDescribeDefualt
    {
        enum {value =
            (!ShouldCheck || IsDefault<typename hl::is_vi_item<Describe>::type::value_name >::value)
            && (CheckDescribeDefualt<typename hl::is_vi_item<Describe>::base
                    , IsDefault<typename hl::is_vi_item<Describe>::type::value_name >::value >::value)
        };
    };

    template<typename Type, int ShouldCheck>
    struct CheckDescribeDefualt<hl::end_of_tlist<Type>, ShouldCheck >
    {
        enum {
            value = (!ShouldCheck || IsDefault<typename Type::value_name >::value)
        };
    };

    // Here we should check that
    // our parameters has correct format
    template <typename Args
        , typename Result = hl::empty_type>
    struct CheckIsOptionalCorrect
    {
        typedef typename
            hl::is_vi_item<Args>::base next;

        typedef typename
            hl::is_vi_item<Args>::type arg_type;

        typedef typename
            hl::if_c<
                hl::is_same<hl::empty_type, Result>::value
                    , typename hl::end_of_tlist<arg_type>
                    , typename hl::push_front<arg_type, Result>::type >::type
            result_type;

        // If not correct you should set to zero
        enum {
            value = CheckIsOptionalCorrect<next, result_type >::value
        };

        // Push to next iteration
        typedef typename
            CheckIsOptionalCorrect<next, result_type >::type type;
    };

    // Here we should check that
    // our parameters has correct format
    template <typename Type, typename Result>
    struct CheckIsOptionalCorrect<hl::end_of_tlist<Type>, Result >
    {
        enum { value = 0 };
        typedef Result type;
    };


    /*template <typename Type>
    inline void print__ ()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }*/

    // Filling arguments to create values
    // And after which values will convert to Archive::formatter
    template <typename Accessor, typename Arch, typename... Args>
    inline void
    fill_args(Arch& arch, Args&... args)
    {
        // This specific
        typedef typename GetSpecific<Accessor>::accessor accessor_type;
        typedef typename accessor_type::result_type result_type;
        typedef typename accessor_type::args_describe args_describe;

        typedef typename
            hl::impl_resolve<Service>::interface_type interface_type;

        // Asserting section
        static_assert(interface_type::template
                OwnerCheck<hl::HolderType2<interface_type, accessor_type> >::value
                , "This class don't have method.");

        // Check that we don't have a not default args after default
        static_assert(CheckDescribeDefualt<args_describe>::value
                , "default argument missing for parameter.");

        // Check is that args count less then
        static_assert(sizeof... (args) <= accessor_type::args_count
                , "Can't matching call signature in RPC call.");

        this->template for_each_args<accessor_type>(arch, args...);
    }

private :

    /**
     * @parameter Accessor this is an accessory of invoker
     * @parameter Args
     */
    template <typename Accessor, typename... Args>
    inline typename GetSpecific<Accessor>::result_type
    invoke_client_side_(Args&... args)
    {
        // This is a accessory getting
        // we can call by selector tag here.
        // This specific
        typedef typename GetSpecific<Accessor>::accessor accessor_type;
        typedef typename accessor_type::result_type result_type;
        typedef typename accessor_type::args_describe args_describe;

        // Archive instance
        typedef typename
            args_format<accessor_type>::Archive Archive;

        // Here we should make the instance of
        // abstract archivier
        Archive arch_;

        args_format<accessor_type> format(arch_);

        // Filling arguments
        // the client should be implement methods
        // which should support.
        this->template fill_args<accessor_type>(format, args...);

#if defined HL_TRACE
        HL_TRACE(arch_.str_2cchar((StringType) arch_));
#endif

        // Call Backend
        this->base::invoke(arch_);

        result_type v;

        // Ans empty result payload was
        if (arch_.empty())
            return v;

        // Preparing result values
        this->template for_each_values<accessor_type>(v, format);

        return v;
    }

    /**
     * @parameter Accessor this is an accessory of invoker
     * @parameter Args
     */
    template <typename Accessor, typename Func, typename... Args>
    inline StringType
    invoke_server_side_(Func func_ptr, Args&... args)
    {
        // This is a accessory getting
        // we can call by selector tag here.
        // This specific
        typedef typename GetSpecific<Accessor>::accessor accessor_type;
        typedef typename accessor_type::result_type result_type;
        typedef typename accessor_type::args_type args_type;

        // Archive instance
        typedef typename
            args_format<accessor_type>::Archive Archive;

        Archive arch_(args...);

        args_format<accessor_type> format(arch_);

        args_type args_value;

        // Iterate by arguments
        // Also we will iside use getArgname or getReultName
        // to get accessing in format
        this->template for_each_values<accessor_type>(args_value, format, true);

        // Calling the function with reparsed parameters
        result_type result
            = args_value.forward_call(*this, func_ptr);

        // Preparing to fill result
        arch_.clear_stack();

        arch_.begin_object("");
        format.template pack<return_value_name<accessor_type, service_type > >(result);
        // arch_.end_object(true);

        return (StringType)arch_;
    }

public :
    /**
     * @parameter Accessor this is an accessory of invoker
     * @parameter Args
     */
    template <typename Accessor, typename... Args>
    inline typename
    GetSpecific<Accessor>::result_type
    invoke_c__(Args&... args)
    {
        // We can usse enherited interfcae from a server side
        static_assert(
                (!hl::is_server<Backend>::value
                    || hl::is_client<Service>::value)
                , "Call should occur on a client side." );

        return this->template invoke_client_side_<Accessor>(args...);
    }

    /**
     * @parameter Accessor this is an accessory of invoker
     * @parameter Args
     */
    template <typename Accessor, typename... Args>
    inline typename
    GetSpecific<Accessor>::result_type
    invoke(Args... args)
    {
        // We can usse enherited interfcae from a server side
        static_assert(
                (!hl::is_server<Backend>::value
                    || hl::is_client<Service>::value)
                , "Call should occur on a client side." );

        return this->template invoke_client_side_<Accessor>(args...);
    }

    /**
     * @parameter Accessor this is an accessory of invoker
     * @parameter Args
     */
    template <typename Accessor
        , typename Func, typename... Args>
    inline StringType
    invoke__(Func func_ptr, Args&... args)
    {
        // We should use service registration
        static_assert((hl::is_server<Backend>::value
                        && !hl::is_client<Backend>::value)
                , "This should be call as service side only." );
        return this->template invoke_server_side_<Accessor>(func_ptr, args...);
    }

    template <typename Accessor, typename Callback, typename Archive>
    void callback(std::string const& payload, Callback cb, std::shared_ptr<Archive> arch, Life live)
    {
        // Check is was deleted
        if (!*live.get())
            return ;

        // Archive instance
        typedef typename GetSpecific<Accessor>::accessor accessor_type;
        typedef typename accessor_type::result_type result_type;
        typedef typename accessor_type::args_describe args_describe;

        // Archive instance
        args_format<accessor_type> format(*arch.get(), false);
        arch->set_result(payload);

        typename accessor_type::result_type v;
        Interface::template for_each_values<accessor_type>(v, format);

        ((static_cast<Service*>(this))->*cb)(v);
    }

    template <typename Accessor, typename... ArgsType>
    inline void
    async_invoke(void (Service::*subscriber)(typename GetSpecific<Accessor>::result_type&)
                        , ArgsType... args)
    {
        using namespace std::placeholders;

        // Archive instance
        typedef typename GetSpecific<Accessor>::accessor accessor_type;
        typedef typename accessor_type::result_type result_type;
        typedef typename accessor_type::args_describe args_describe;

        typedef void (Service::*subscriber_type)(typename GetSpecific<Accessor>::result_type&);

        // Archive instance
        typedef typename
            args_format<accessor_type>::Archive Archive;

        std::shared_ptr<Archive > arch_(new Archive());
        args_format<accessor_type> format(*arch_.get());

        // Filling arguments
        this->template fill_args<accessor_type>(format, args...);

        // Call Backend
#if defined(__HL_USED_LAMBDA)
        this->base::asyncInvoke(arch_,
            [this, subscriber, arch_, live_](char const* payload)
            { this->template callback<Accessor>(payload, subscriber, arch_); }
        );
#else
        std::function<void (std::string const&)>
            callback = std::bind(
                    &Interface::template callback<accessor_type, subscriber_type, Archive>
                    , this, std::_Placeholder<1>(), subscriber, arch_, live_);
        this->base::async_invoke(*arch_.get(), callback);
#endif
    }

    virtual ~Interface()
    {
        *live_.get() = false;
    }

    Life live_;
};

}

#endif
