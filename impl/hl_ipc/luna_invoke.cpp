#define INSTANTIATION_WORK

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sstream>
#include <thread>
#include <future>
#include <iostream>

#if defined (INSTANTIATION_WORK)
    #include <glib.h>
    #include <luna-service2/lunaservice.h>
#endif

#include "../../include/throw.hpp"
#include "../../include/atomic_st_value.hpp"
#include "../../include/hl_ipc/ls_error.hpp"
#include "../../include/hl_ipc/luna_invoke.hpp"
#include "../../include/lock_guard.hpp"

namespace hl
{

/**
* @brief Obtains the singleton service_invoker.
*
* @retval the service_invoker
*/
service_invoker* service_invoker::instance()
{
    static std::unique_ptr<service_invoker > s;
    struct create_instance_tag { };

    // should be atomic
    if (!hl::atomic_st_value<bool
                , create_instance_tag>::value_.load())
    {
        GUARD(get_instance);
        if (!hl::atomic_st_value<bool
                , create_instance_tag>::value_.load())
        {
            s = std::unique_ptr<service_invoker>(new service_invoker());
            hl::atomic_st_value<bool
                , create_instance_tag>::value_ = true;
        }
    }

    return s.get();
}

#define CHECK_OK(val, msg)          \
     if (!val)                      \
         hl::std_throw_(msg);

/**
* @brief Private constructor to enforce singleton.
*/
service_invoker::service_invoker()
{
}

svc_accessor::svc_accessor(svc_accessor&& acc)
    : main_loop_(std::move(acc.main_loop_))
        , main_context_(std::move(acc.main_context_))
        , svc_name_(std::move(acc.svc_name_))
        , svc_(std::move(acc.svc_))
        , bus_(acc.bus_)
        , private_bus_(acc.private_bus_)
        , id_(acc.id_)
        , priority_(acc.priority_)
        , loop_thread_(std::move(acc.loop_thread_))
{  LOG("svc_accessor(&&) " << this); }

svc_accessor::svc_accessor(std::string const& svc_name, std::string const& id, std::size_t priority)
    : main_loop_()
    , svc_name_(svc_name)
    , svc_()
    , bus_()
    , private_bus_()
    , id_(id)
    , priority_(priority)
{   LOG("svc_accessor() " << this); }

void svc_accessor::run()
{
    // Create context
    main_context_ = std::shared_ptr<GMainContext>(g_main_context_new(), g_main_context_unref);

    // Run loop
    main_loop_ = std::shared_ptr<GMainLoop>
      (g_main_loop_new(main_context_.get(), TRUE), g_main_loop_unref);

    LShlService* svc = 0;
    // Service handle
    hl::ls_error lserror;
    if (!LSRegisterhlService(svc_name_.c_str(), &svc, &lserror))
        lserror.warning("Error register service.");

    svc_ = std::shared_ptr<LShlService >(
             svc
             , [](LShlService* svc)
               {
                  hl::ls_error lserror;
                  if (!LSUnregisterhlService(svc, &lserror))
                    lserror.warning("LSUnregisterhlService ");
               }
            );

    LSGmainAttachhlService(svc_.get(), main_loop_.get(), &lserror);

    // The bus handle
    if (!(private_bus_ = LShlServiceGetPrivateConnection(svc_.get()))
        || !LSGmainSetPriority(private_bus_, priority_, &lserror))
    {
        lserror.warning("Set priority error.");
    }

    if (!(bus_ = LShlServiceGetPublicConnection(svc_.get()))
            || !LSGmainSetPriority(bus_, priority_, &lserror))
    {
        lserror.warning("Set priority error.");
    }

    std::shared_ptr<GMainLoop > locloop = main_loop_;
    loop_thread_ = std::unique_ptr<std::thread > (
        new std::thread([locloop]()
        {
            g_main_loop_run(locloop.get());
        })
    );
}

void svc_accessor::stop()
{
    // stop main loop
    if (main_loop_)
    {
        GMainLoop* loop = main_loop_.get();
        if (loop && g_main_loop_is_running(loop))
        {
            g_main_loop_quit(loop);
            loop_thread_->join();

            // wait for exit thread
            loop_thread_.reset();
        }

        // wait for clear context
        GMainContext* main_context = g_main_loop_get_context(loop);
        while(!g_main_context_acquire(main_context))
                sched_yield();

        g_main_context_release(main_context_.get());
        main_context_.reset();
        main_loop_.reset();
        // unregister service
        if (svc_)
            svc_.reset();
    }
}

svc_accessor::~svc_accessor()
{
    LOG("~svc_accessor()" << this);
    if (main_loop_.get())
        this->stop();

}

void service_invoker::clear()
{
    LOG(__PRETTY_FUNCTION__);
    accessors_.clear();
}

svc_accessor& service_invoker::accessor(std::string const& svc_name
                                , std::string const& id /*= std::string()*/
                               , std::size_t priority /*= G_PRIORITY_DEFAULT*/)
{
    LOG(__PRETTY_FUNCTION__);

    typedef typename
        accessors_type::iterator iterator_type;

    // Check is present
    iterator_type where = accessors_.lower_bound(svc_name);
    if (where != accessors_.end()
            && where->first == svc_name)
    {
        return where->second;
    }

    // insert new value
    where = accessors_.insert(where, std::make_pair(svc_name
                       , std::move(svc_accessor(svc_name, id, priority))));

    return where->second;
}

// Here we need to clear
service_invoker::~service_invoker()
{
    LOG(__PRETTY_FUNCTION__);

    accessors_.clear();
    LOG(__PRETTY_FUNCTION__ <<" Exit ");
}

#if !defined (INSTANTIATION_WORK)
static char const* testvalue =
    "{\"spelledCorrectly\": true, \"guesses\":[{ \"str\": \"hallo\", \"sp\": true }, { \"str\": \"hall\", \"sp\": true },"
    " { \"str\": \"halo\", \"sp\": true }, { \"str\": \"hallos\", \"sp\": true }, { \"str\": \"hallow\", \"sp\": true }]"
    ", \"arrayGuess\":[1,2,3,4,5]"
    ", \"returnValue\": true"
    ", \"accessType\": { \"descriptor\":123.456, \"accessType\":\"NAME_OF_ACCESS_ALL\"} }";
#endif

/**
* @brief Internal callback for service responses.
*
* @param  sh
* @param  reply
* @param  ctx
*
* @retval
*/
template <typename Type>
static bool
message_filter(LSHandle *sh, LSMessage* reply, void* ctx)
{
    LOG(__PRETTY_FUNCTION__);

    const char* payload = LSMessageGetPayload(reply);

#if !defined (INSTANTIATION_WORK)
    payload = testvalue;
#endif
    const LSMessageToken responseToken = LSMessageGetResponseToken(reply);
    Type* listener = static_cast<Type* >(ctx);
    if (payload)
        listener->set_value(payload);
    listener->cv_.notify_one();
    return true;
}

/**
* @brief Internal callback for service responses.
*
* @param  sh
* @param  reply
* @param  ctx
*
* @retval
*/
static bool
message_filter_async(LSHandle *sh, LSMessage* reply, void* ctx)
{
    LOG(__PRETTY_FUNCTION__);
    const char* payload = LSMessageGetPayload(reply);

#if !defined (INSTANTIATION_WORK)
    // Set the test value
    payload = returnTestValue;
#endif
    const LSMessageToken responseToken = LSMessageGetResponseToken(reply);
    invoke_listener_base* listener = static_cast<invoke_listener_base* >(ctx);

    if (listener && payload)
    {
        (*listener)(payload, responseToken);
        return true;
    }

    return false;
}

void invoke_listener_base::set_value(std::string const& value)
{
    value_ = value;
}

void invoke_listener_base::operator ()(LSMessageToken token)
{
    token_ = token;
    (*this)(value_, token);
}

/**
* @brief This method will make the call to DBUS.
*
* @param  accessor
* @param  uri
* @param  payload
* @param  listener
* @param  use_private_bus_
*
* @retval 0 if message could not be sent.
* @retval >0 serial number for the message.
*/
std::size_t service_invoker::call(svc_accessor* accessor
        , const char* uri
        , const char* payload
        , invoke_listener_base* listener
        , bool use_private_bus_)
{
    LOG(__PRETTY_FUNCTION__);
    if (!listener)
        hl::std_throw_("The listener was not set.");

    // This place we had many errors.
    // We can't use service created as -active
    hl::ls_error lserror;

    // Set the accessor to
    std::mutex locker;
    std::unique_lock<std::mutex> lock(locker);

    if (LSCall(use_private_bus_ ? accessor->private_bus_ : accessor->bus_
               , uri, payload, message_filter<invoke_listener_base>, listener, 0, &lserror))
    {
        listener->cv_.wait(lock);
        (*listener)(0);
        return 1;
    }


    return 0;
}

/**
* @brief This method will make the async call to DBUS.
*
* @param  uri
* @param  payload
* @param  listener
*
* @retval 0 if message could not be sent.
* @retval >0 serial number for the message.
*/
unsigned long
service_invoker::async_call(svc_accessor* accessor
    , const char* uri
    , const char* payload
    , invoke_listener_base* listener
    , bool use_private_bus_)
{
    LOG(__PRETTY_FUNCTION__);

    hl::ls_error lserror;
    LSMessageToken token = 0;

    //com.hl.luna-
    if (!listener)
        hl::std_throw_("The listener not set.");

    if (LSCall(use_private_bus_ ? accessor->private_bus_ : accessor->bus_
               , uri
               , payload
               , message_filter_async, listener, &token, &lserror))
    {
        listener->token_ = token;
    }

    return token;
}

/**
 * @brief Terminates a call causing any subscription for responses to end.
 *        This is also called by garbage collector's collect()
 *        when no more references to listener exist.
 *
 * @param  listener
 */
void service_invoker::cancel(invoke_listener_base* listener)
{
    LOG(__PRETTY_FUNCTION__);
    hl::ls_error lserror;

    if (!LSCallCancel(listener->sh_, listener->token_, &lserror))
        lserror.warning("Cancel ");

    // set the token to zero to indicate we have been canceled
    listener->token_ = 0;
}
};
