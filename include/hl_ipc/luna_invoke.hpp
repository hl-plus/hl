/**/

#ifndef SERVICE_INVOKER_HPP_KDJFKGJDMFFDGBHKDFGJHFGHJFDKGHKRJEFDKTGHJRYKEY
#define SERVICE_INVOKER_HPP_KDJFKGJDMFFDGBHKDFGJHFGHJFDKGHKRJEFDKTGHJRYKEY

#include <memory>
#include <vector>
#include <deque>
#include <mutex>
#include <future>
#include <hash_map>
#include <map>
#include <condition_variable>

#define GLIB_OPEN
#if defined (INSTANTIATION_WORK)
    #include <luna-service2/lunaservice.h>
#elif defined (GLIB_OPEN)
    #include <glib-2.0/glib.h>
#endif
//#define LOG_ENABLE
#if defined(LOG_ENABLE )
    #define LOG(...) \
        std::cout << __VA_ARGS__ << std::endl;
#else
    #define LOG(...)
#endif

namespace hl
{

// The hl accessor fromwhich we should communicate
// with main loop of accessor
class svc_accessor;

struct invoke_listener_base
{
    // Constructor description
    invoke_listener_base()
        :   token_(LSMESSAGE_TOKEN_INVALID)
            , sh_(0)
            , accessor_(0)
            , cv_()
            , value_()
    { }

    virtual ~invoke_listener_base()
    { }

    virtual void operator ()(std::string const& body, LSMessageToken token) = 0;
            void operator ()(LSMessageToken token);
    void set_value(std::string const& v);

    LSMessageToken token_;
    LSHandle* sh_;
    svc_accessor* accessor_;

    std::condition_variable cv_;
    std::string value_;
};

//   Service accessor class
// It is need to more confortable work
// I can't undertand three similar approaches
struct svc_accessor
{
    // The construnct description
    svc_accessor(std::string const& svc_name, std::string const& id, std::size_t priority = G_PRIORITY_DEFAULT);
    svc_accessor(svc_accessor&& acc);

    ~svc_accessor();

    // This is register service and attach to g_main_loop
    void register_();

    // In this section will run gmain loop
    // and register service
    // and attach service to gmainloop
    void run();

    // In this section will stop gmain loop
    // and unregister service
    // and dettach service to gmainloop
    void stop();

    // Main loop to sync call
    std::shared_ptr<GMainLoop > main_loop_;

    // Main context
    std::shared_ptr<GMainContext
        /*, decltype(g_main_context_unref)*/> main_context_;

    // The service name by which will register
    std::string svc_name_;

    // Service handle
    std::shared_ptr<LShlService > svc_;

    // The bus handle
    LSHandle* bus_, *private_bus_;

    // Id of service
    std::string id_;

    // Priority
    std::size_t priority_;

    //gmain loop thread
    std::unique_ptr<std::thread> loop_thread_;
};

//
//  service_invoker
//
// This class is a singleton which handles all the client requests
// for a WebKit instance.
struct service_invoker
{
    //typedef __gnu_cxx::hash_map<std::string, svc_accessor> accessors_type;
    typedef std::map<std::string, svc_accessor> accessors_type;

    ~service_invoker();

    static service_invoker* instance();
    unsigned long async_call(svc_accessor* accessor, const char* uri
                            , const char* payload, invoke_listener_base* listener, bool use_private_bus_ = false);
    std::size_t call(svc_accessor* accessor, const char* uri
                            , const char* payload, invoke_listener_base* listener, bool use_private_bus_ = false);

    void cancel(invoke_listener_base* listener);

    svc_accessor& accessor(std::string const& svc_name
                  , std::string const& id = std::string()
            , std::size_t priority = G_PRIORITY_DEFAULT);
    void clear();
private:
    service_invoker();
    std::string service_name_;
    accessors_type accessors_;
};

}

#endif
