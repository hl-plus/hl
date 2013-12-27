/*******************/

#ifndef PBN_JSON_BACKEND_HPP
#define PBN_JSON_BACKEND_HPP

#include <pbnjson.hpp>
#include <list>

#define LG_ASSERT(o) \
    if (!o) hl::std_throw_(std::string("exception in: ") + __PRETTY_FUNCTION__);

#if defined (__HL_INSTALLED)
    #include <hl/include/throw.hpp>
    #include <hl/include/hl_ipc/hl_ipc_specific.hpp>
    #include <hl/include/hl_ipc/optional.hpp>
    #include <hl/include/conversion_pnbjson.hpp>
#else
    #include "../throw.hpp"
    #include "../hl_ipc/hl_ipc_specific.hpp"
    #include "../hl_ipc/optional.hpp"
    #include "../hl_ipc/conversion_pnbjson.hpp"
#endif



namespace hl
{

template <typename StringType, typename Invoker>
struct PbnJsonBackend : Invoker
{
    template <typename Service, typename Accessor>
    struct json_format
    {
        typedef Service service_type;

        json_format() : m_uri((StringType(Service::uri()) + "/") + Accessor::functionName()) {}
        // This is to calling
        json_format(StringType const& uri, StringType const& func) : m_uri((uri + "/") + func) {}
        // This is to parse return value
        json_format(StringType const& returnValue) { set_result(returnValue); }

        bool empty() const { return m_objects.empty(); }

        int begin_array(StringType const& name, unsigned int size, bool read = false)
        {
            if(read)
            {
                LG_ASSERT(!m_objects.empty());
                pbnjson::JValue v = m_objects.back().value[string_to_std(name)];
                LG_ASSERT(v.isArray());
                m_objects.push_back(v);
                return v.arraySize();
            }

            m_objects.push_back(Object(name, pbnjson::Array()));
            return 0;
        }

        void end_array(bool read = false) { end_object(read); }

        void begin_object(StringType const& label, bool read = false)
        {
            if(!read)
                m_objects.push_back(label);
            else
            {
                LG_ASSERT(!m_objects.empty());
                pbnjson::JValue v = m_objects.back().value[string_to_std(label)];
                LG_ASSERT(v.isObject());
                m_objects.push_back(v);
            }
        }

        void begin_object(int I, bool read = false)
        {
            LG_ASSERT(!m_objects.empty());
            LG_ASSERT(m_objects.back().value.isArray());
            if(read)
            {
                m_objects.push_back(m_objects.back().value[I]);
                LG_ASSERT(m_objects.back().value.isObject());
            }
            else
                m_objects.push_back(static_cast<ssize_t>(I));
        }

        void end_object(bool read = false)
        {
            LG_ASSERT(!m_objects.empty());

            if(!read)
            {
                // dont remove last object - it serves as a root object
                if(m_objects.size() == 1)
                    return;

                // pop last object from list, and append it to pre-last
                Object last = m_objects.back();
                m_objects.pop_back();
                Object &parent = m_objects.back();
                if(parent.value.isObject())
                {
                    LG_ASSERT(last.isName());
                    parent.value.put(last.name, last.value);
                }
                else if(parent.value.isArray())
                {
                    LG_ASSERT(last.isIndex());
                    parent.value.put(last.index, last.value);
                }
                else // only objects and arrays are capable containing values... getting here means failure, so just throw
                    hl::std_throw_(std::string("Attempted to add sub-object to a non-object item in: ") + __PRETTY_FUNCTION__);
            }
            else
            {
                LG_ASSERT(m_objects.size() > 1);
                m_objects.pop_back();
            }
        }

        char const * get_args()
        {
            // only root object must remain in list
            LG_ASSERT(m_objects.size() == 1);

            pbnjson::JGenerator serializer(NULL);
            pbnjson::JSchemaFragment schema("{}");
            if (!serializer.toString((*m_objects.begin()).value, schema, m_serialized))
                hl::std_throw_(std::string("JGenerator::toString failed in: ") + __PRETTY_FUNCTION__);

            return str_2cchar(m_serialized);
        }

        char const * get_uri() const { return str_2cchar(m_uri); }

        void clear_stack()
        {
            m_objects.clear();
        }

        operator StringType()
        {
            get_args();
            return m_serialized;
        }

        void set_result(const StringType &payload)
        {
            m_objects.clear();

            if (isempty(payload))
                return;

            pbnjson::JSchemaFragment inputSchema("{}");
            pbnjson::JDomParser parser(NULL);
            if(!parser.parse(payload, inputSchema, NULL))
                hl::std_throw_(std::string("JDomParser::parse failed in: ") + __PRETTY_FUNCTION__);

            m_objects.push_back(parser.getDom());
        }

        template <typename Value>
        inline json_format & operator << (std::pair<StringType, Value&> v)
        {
            LG_ASSERT(!m_objects.empty());
            m_objects.back().value.put(v.first, hl::conversion<Value>::convert(v.second));
            return *this;
        }

        template <typename Value>
        inline json_format & operator >> (std::pair<StringType, Value&> const& v)
        {
            LG_ASSERT(!m_objects.empty());
            LG_ASSERT(m_objects.back().value.isObject());
            hl::conversion<Value>::convert(m_objects.back().value[string_to_std(v.first)], v.second);
            return *this;
        }

        template <typename Value>
        inline json_format & operator >> (std::pair<int, Value&> const& v)
        {
            LG_ASSERT(!m_objects.empty());
            LG_ASSERT(m_objects.back().value.isArray());
            hl::conversion<Value>::convert(m_objects.back().value[v.first], v.second);
            return *this;
        }

    private:
        struct Object
        {
            Object(const StringType &s, const pbnjson::JValue &v = pbnjson::Object()) :
                name(s),
                value(v),
                m_type(Name)
            {}
            Object(ssize_t i, const pbnjson::JValue &v = pbnjson::Object()) :
                index(i),
                value(v),
                m_type(Index)
            {}
            Object(const pbnjson::JValue &v) :
                value(v),
                m_type(Undefined)
            {}

            StringType name;
            ssize_t index;
            pbnjson::JValue value;

            bool isName() const { return m_type == Name; }
            bool isIndex() const { return m_type == Index; }

        private:
            enum { Name, Index, Undefined } m_type;
        };

    private:
        std::list<Object> m_objects;
        StringType m_uri;
        StringType m_serialized;

    private:
        static char const * str_2cchar(std::string const& str) { return str.c_str(); }
        static bool isempty(std::string const& str) { return str.empty(); }
        static const std::string & string_to_std(const std::string &string) { return string; }
        // add overloads for other string types, if you want PbnJsonBackend to work with strings different from std::string
    };

    template <typename Service, typename Accessor>
    struct Archive
    {
        typedef json_format<Service, Accessor> type;
    };
};

}

#endif // PBN_JSON_BACKEND_HPP
