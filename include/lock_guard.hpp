#ifndef LOCK_GUARD_HPP_INCLUDED_DSKFGDKJFKHJDFKGHDFGJHKDFJGKNVBCVBN
#define LOCK_GUARD_HPP_INCLUDED_DSKFGDKJFKHJDFKGHDFGJHKDFJGKNVBCVBN
#include <mutex>
namespace hl
{

template <typename Branch>
struct lock_guard
{
    lock_guard()
    {
        this->static_mutex().lock();
    }

    ~lock_guard()
    {
        this->static_mutex().unlock();
    }

    inline std::mutex&
    static_mutex()
    {
        static std::mutex mutex;
        return mutex;
    }
};

}

#define GUARD(branch) \
    hl::lock_guard<struct _Struct_##branch> _Guard_##branch

#endif // LOCK_GUARD_HPP_INCLUDED_DSKFGDKJFKHJDFKGHDFGJHKDFJGKNVBCVBN
