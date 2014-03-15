/******************/

#ifndef LUNA_INVOKE_BACKEND_HPP_INCLUDE_JXHFJGSDJFGBMEWRBGJDSHFVGKSDJFGIIIIIYHDFJBNDSJDSHFDSHJHFKG
#define LUNA_INVOKE_BACKEND_HPP_INCLUDE_JXHFJGSDJFGBMEWRBGJDSHFVGKSDJFGIIIIIYHDFJBNDSJDSHFDSHJHFKG
#include <sstream>
#include "luna_invoke.hpp"
#include "../any2str.hpp"
#include "../atomic_st_value.hpp"

namespace svc
{

#define NOT_C_PLUS_PLUS_0x11_LAMBDA

/**
* @brief This class is invoking implementation.
*
* @param  uri
* @param  payload
* @param  listener
*
* @retval 0 if message could not be sent.
* @retval >0 serial number for the message.
*/
struct LunaInvokeBackend
{
    LunaInvokeBackend()
        : mutex_accessor_lock_()
    {
    }

    struct EmptyCallback {    };

    template <typename Callback>
    struct luna_listener
            : hl::invoke_listener_base
    {
    public:
        luna_listener(bool async = false)
            : callback_()
            , async_(async)
        {    }

        luna_listener(Callback callback, bool async = false)
            : callback_(callback)
            , async_(async)
        {    }

        virtual ~luna_listener()
        {    }

        template <typename Type>
        inline void
        response_(std::string const& body, const unsigned long responseToken, hl::true_type)
        {
            payload_ = body;
            responceToken_ = responseToken;
        }

        template <typename Type>
        inline void
        response_(std::string const& body, const unsigned long responseToken, hl::false_type)
        {
            payload_ = body;
            responceToken_ = responseToken;

            callback_(body);
            if (async_)
               delete this;
        }

        struct Solver;

        virtual void
        operator()(std::string const& body, LSMessageToken token)
        {
            this->template response_<Solver>(body.c_str(), token
                        , hl::id2type<hl::is_same<EmptyCallback, Callback>::value
                            || hl::is_same<EmptyCallback&, Callback>::value > ());
        }

        Callback callback_;
        bool async_;
        std::string payload_;
        unsigned long responceToken_;
    };

    inline hl::service_invoker&
    get_svc_invoker()
    {
        LOG(__PRETTY_FUNCTION__);
        return *hl::service_invoker::instance();
    }

private:
    typedef hl::svc_accessor* svc_accessor_ptr;
public:
    void stop_backend_loop()
    {
        // lock first concurent access
        std::lock_guard<std::mutex > lock(mutex_accessor_lock_);
        get_svc_invoker().clear();
    }

    template <typename Backend>
    hl::svc_accessor*
    get_accessor()
    {
        LOG(__PRETTY_FUNCTION__);
        typedef typename
            Backend::service_type service_type;

        //
        static svc_accessor_ptr accessor_ = 0;

        // Tag to access static value
        struct get_accessor_tag {    };

        // if we didn't have access
        if (!hl::atomic_st_value<bool
                , get_accessor_tag>::value_.load())
        {
            // lock first concurent access
            std::lock_guard<std::mutex > lock(mutex_accessor_lock_);

            // if didn't two concurent
            if (!hl::atomic_st_value<bool
                    , get_accessor_tag>::value_.load())
            {
                // create accessor to svc invoking
                svc_accessor_ptr acc = &get_svc_invoker()
                        .accessor(service_type::svc_name(), (hl::any2str() << getpid()).str());

                // if it is not runned service
                // run service main loop
                if (!acc->main_loop_.get())
                    acc->run();

                accessor_ = acc;

                //Unlock  creation
                hl::atomic_st_value<bool
                                , get_accessor_tag>::value_ = true;
            }
        }

        return accessor_;
    }

    template <typename Backend>
    inline void
    invoke(Backend& backend)
    {
        LOG(__PRETTY_FUNCTION__);
#if defined (NOT_C_PLUS_PLUS_0x11_LAMBDA)
        luna_listener<EmptyCallback> listener;

        bool usePrivateBus = true;
        get_svc_invoker().call(this->template get_accessor<Backend>()
                                          , backend.get_uri(), backend.get_args(), &listener, usePrivateBus);
        if (!listener.payload_.empty())
            backend.set_result(listener.payload_);
#else
        get_svc_invoker().call_0x(this->template get_accessor<Backend>()
                                  , backend.get_uri()
                                  , backend.get_args()
                                  , [&backend](std::string const& payload){  backend.set_result(payload); }
                                  , false);
#endif

    }

    //typedef std::future async_result_type;

    virtual ~LunaInvokeBackend()
    {    }

    template <typename Backend, typename CallBack>
    inline void
    async_invoke(Backend& backend, CallBack callback)
    {
        LOG(__PRETTY_FUNCTION__);
        luna_listener<CallBack>* listener = new luna_listener<CallBack>(callback, true);
        bool use_private_bus = true;
        // Run luna async call
        get_svc_invoker().async_call(this->template get_accessor<Backend>()
                                      , backend.get_uri(), backend.get_args(), listener, use_private_bus);
    }

private:
    std::mutex mutex_accessor_lock_;
};

}

#endif // LUNA_INVOKE_BACKEND_HPP_INCLUDE_JXHFJGSDJFGBMEWRBGJDSHFVGKSDJFGIIIIIYHDFJBNDSJDSHFDSHJHFKG
