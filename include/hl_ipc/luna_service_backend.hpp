#ifndef LUNA_SERVICE_BACKEND_HPP_DFSKLJGKDSFHJGKDJFHHHHHHHHHHHHDF
#define LUNA_SERVICE_BACKEND_HPP_DFSKLJGKDSFHJGKDJFHHHHHHHHHHHHDF

#include <iterator>
#include <utility>
#if defined (HL_INSTALLED)
    #include <hl/include/hl_ipc/hl_ipc_specific.hpp>
    #include <hl/include/is_same.hpp>
#else
    #include "../../include/is_same.hpp"
    #include "../../include/hl_ipc/hl_ipc_specific.hpp"
#endif

namespace hl
{
    // this is a base of service functionality
    //
    struct service_backend_base
    {
        typedef std::vector<LSMethod> ipc_table_type;
        service_backend_base()
        {   }

        void run_loop()
        {
            if(m_gmain_loop && !g_main_loop_is_running(m_gmain_loop.get()))
                g_main_loop_run(m_gmain_loop.get());
        }
        void stop_loop()
        {
            if(m_gmain_loop && g_main_loop_is_running(m_gmain_loop.get()))
                g_main_loop_quit(m_gmain_loop.get());
        }

        ~service_backend_base()
        {
            stop_loop();
        }

    protected:
        virtual ipc_table_type&
        get_ipc_table() = 0;

    protected:
        std::shared_ptr<LShlService> service_handle() { return m_service_handle; }
        std::shared_ptr<GMainLoop> gmain_loop() { return m_gmain_loop; }

        void set_service_handle(const std::shared_ptr<LShlService> &service_handle) { m_service_handle = service_handle; }
        void set_gmain_loop(const std::shared_ptr<GMainLoop> &gmain_loop) { m_gmain_loop = gmain_loop; }

        void set_service_handle(LShlService *service_handle)
        {
            m_service_handle = std::shared_ptr<LShlService>
                    (service_handle, [](LShlService* svc)
                        {
                            hl::ls_error lserror;
                            if (!LSUnregisterhlService(svc, &lserror))
                                lserror.warning("LSUnregisterhlService ");
                        }
                    );
        }
        void set_gmain_loop(GMainLoop *gmain_loop)
        {
            m_gmain_loop = std::shared_ptr<GMainLoop>(gmain_loop, g_main_loop_unref);
        }

    private:
        std::shared_ptr<LShlService> m_service_handle;
        std::shared_ptr<GMainLoop> m_gmain_loop;
    };

    template <typename Type> struct holder_;

    template <typename Class
            , typename Handler>
    struct handler_init
    {
        handler_init(typename Class::ipc_table_type& handlers)
            : handlers_ (handlers.begin())
            , cur_(handlers.begin())
            , last_(--handlers.end())
        {   }

        template <typename Type>
        bool operator ()()
        {
            (*cur_) = {  Type::functionName()
                           , &Class::template ipc_svc_handler<Type> };

            // Should be zero
            if (++cur_ == last_)
                *cur_ = { 0, 0 };

            return false;
        }

        Handler handlers_, cur_, last_;
    };

    template <typename Service>
    struct service_backend
            : public service_backend_base
    {
        service_backend()
            :  ipc_table_()
        {
        }

        template <typename Meta>
        void init_handlers()
        {
            enum {  Size = hl::size<Meta>::value};
            ipc_table_.resize(Size + 1);

            hl::for_each<Meta>(
                 handler_init<service_backend, ipc_table_type::iterator> (ipc_table_)
                    );
        }

private:
        virtual ipc_table_type&
        get_ipc_table() {   return ipc_table_;  }
public:

        template <typename ReflectAccessor>
        static bool
        ipc_svc_handler(LSHandle *sh, LSMessage *message, void *instance)
        {
            // Calculate the service type
            typedef Service service_type;

            try
            {
                service_type* svc
                    = static_cast<service_type*>(instance);

                const char* payload = LSMessageGetPayload(message);
                // const LSMessageToken responseToken = LSMessageGetResponseToken(message);

                if (!payload)
                    hl::std_throw_("Empty payload.");

                auto func =
                        ReflectAccessor::template function_accessor<holder_<service_type> >::func();

                // Call service functional
                std::string pl = svc->template invoke__<ReflectAccessor>(func, payload);

                hl::ls_error lserror;
                if (!LSMessageRespond(message, pl.c_str(), &lserror)
                        || LSErrorIsSet(&lserror))
                   hl::std_throw_expl_(lserror);
            }
            catch(std::exception& exc)
            {
    #if defined(ENABLE_LOGGING)
            std::cout << exc.what() << std::endl;
    #endif
            }

            return true;
        }

        template <typename Branch>
        void register_on_bus()
        {
            if(service_handle())
                return;

            hl::ls_error lserror;
            LShlService *svc = 0;

            if(!LSRegisterhlService(Branch::svc_name(), &svc, &lserror))
                hl::std_throw_expl_(lserror);

            set_service_handle(svc);

            if(!LShlServiceRegisterCategory(svc, "/", ipc_table_.data(),
                                              ipc_table_.data(), NULL, NULL, &lserror))
                hl::std_throw_expl_(lserror);

            if(!LSCategorySetData(LShlServiceGetPrivateConnection(svc),
                                  "/", this, &lserror))
                hl::std_throw_expl_(lserror);
            if(!LSCategorySetData(LShlServiceGetPublicConnection(svc),
                                  "/", this, &lserror))
                hl::std_throw_expl_(lserror);

            if(!gmain_loop())
                set_gmain_loop(g_main_loop_new(0, false));

            if(!LSGmainAttachhlService(svc, gmain_loop().get(), &lserror))
                hl::std_throw_expl_(lserror);
        }

private:
        template <typename Service_>
        friend bool
        hl::register_service(Service_* svc);

        service_backend_base::ipc_table_type ipc_table_;
    };

    // Work arround to gcc 4.6.3
    template <typename Type>
    struct resolve_refl_extract
    {
        typedef hl::empty_type type;
    };

    // Extraction methods
    template <template <typename > class Templ
                , typename Type>
    struct resolve_refl_extract<Templ<Type> >
    {
        typedef typename
            hl::refl_extract<Templ>::type type;
    };

    struct fake;

    template <typename Service>
    inline bool
    register_service(Service* svc)
    {
        // Check is that Impl<Service, Interface>
        typedef hl::impl_resolve<typename Service::raw_service_type> impl_type;

        //  Take the interface type
        // we can use Impl<Service, Interface> this place
        typedef typename
            impl_type::interface_type interface_type;

        // getting the ftbl
        // to serialize the methods
        typedef typename
            interface_type::template ftbl<struct fake> ftbl_type;

        // extract it to type list
        typedef typename
            resolve_refl_extract<ftbl_type>::type ipc_tbl_type;

        static_assert(!hl::is_same<ipc_tbl_type, hl::empty_type>::value,
                        "Can not resolve ftbl.");

        svc->template init_handlers<ipc_tbl_type>();
        svc->template register_on_bus<typename impl_type::service_type >();

        return true;
    }
}

#endif // LUNA_SERVICE_BACKEND_HPP_DFSKLJGKDSFHJGKDJFHHHHHHHHHHHHDF
