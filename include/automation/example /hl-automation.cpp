/*
 *
 * HL demo implementation
 *
 * */
#define ____MAP

#ifdef ____MAP
#include <random>
#include <atomic>
#include <iostream>
#include <sstream>

#include <hl/include/sfinae.hpp>
#include <hl/include/hl_ipc/conversion.hpp>
#include <hl/include/mpl_foreach.hpp>
#include <hl/include/hl_ipc/hl_ipc_specific.hpp>

#ifdef __J_ACTIVE
    #include <hl/include/hl_ipc/hl_json_backend.hpp>
#endif

#include <hl/include/hl_ipc/Interface.hpp>
#include <hl/include/linux/environment.hpp>
#include <hl/include/atomic_st_value.hpp>

#include "include/compressed_dfa.hpp"

inline void test_map_run() ;

//  The global test runner
// we should use this only as global
int main()
{
    test_map_run();
    return 0;
}

struct event {
    template <typename type>
    inline static void
    on_()   {
        static int __count = 0;
        ++__count;
    }
};

struct dict_item {
    void typedef (*handler_type)();

    std::string key_;
    handler_type handler_;
};


#define HANDLER(type) \
        {   #type,  &event::on_<struct type>} ,

struct __Test
{
    template <int I>
    static void on_()
    {
        std::cout <<"O yes I am matched!! : " << __PRETTY_FUNCTION__ << std::endl;
    }
};

static dict_item dict[] =
{
    HANDLER(amega)
    HANDLER(amegufun)
    HANDLER(amegufag)
    HANDLER(amagufag)
    HANDLER(apegufag)
    HANDLER(aaegufag)
    HANDLER(aabgufag)
    HANDLER(ameg_)
    HANDLER(bmega)
    HANDLER(bmega)
    HANDLER(bmegufun)
    HANDLER(bmegufag)
    HANDLER(bmagufag)
    HANDLER(bpegufag)
    HANDLER(baegufag)
    HANDLER(babgufag)
    HANDLER(bmeg_)
    HANDLER(cmega)
    HANDLER(cmega)
    HANDLER(cmegufun)
    HANDLER(cmegufag)
    HANDLER(cmagufag)
    HANDLER(cpegufag)
    HANDLER(caegufag)
    HANDLER(cabgufag)
    HANDLER(cmeg_)
    HANDLER(dmega)
    HANDLER(dmega)
    HANDLER(dmegufun)
    HANDLER(dmegufag)
    HANDLER(dmagufag)
    HANDLER(dpegufag)
    HANDLER(daegufag)
    HANDLER(dabgufag)
    HANDLER(dmeg_)
    HANDLER(emega)
    HANDLER(emega)
    HANDLER(emegufun)
    HANDLER(emegufag)
    HANDLER(emagufag)
    HANDLER(epegufag)
    HANDLER(eaegufag)
    HANDLER(eabgufag)
    HANDLER(emeg_)
    HANDLER(fmega)
    HANDLER(fmega)
    HANDLER(fmegufun)
    HANDLER(fmegufag)
    HANDLER(fmagufag)
    HANDLER(fpegufag)
    HANDLER(faegufag)
    HANDLER(fabgufag)
    HANDLER(fmeg_)
    HANDLER(gmega)
    HANDLER(gmega)
    HANDLER(gmegufun)
    HANDLER(gmegufag)
    HANDLER(gmagufag)
    HANDLER(gpegufag)
    HANDLER(gaegufag)
    HANDLER(gabgufag)
    HANDLER(gmeg_)

};

inline void test_map_run()
{
    // Make the equals test
    std::map<std::string, dict_item::handler_type> binary_map;

    typedef hl::dfa_compiler<std::string, dict_item::handler_type > dfa_type;
    hl::dfa_compiler<std::string, dict_item::handler_type > dfa_bugtest, dfa_correct;

    dfa_bugtest.insert("99a99", &__Test::on_<1>);
    dfa_bugtest.insert("9a9", &__Test::on_<0>);
    dfa_bugtest.compile_binary();

    dfa_correct.insert("9a9", &__Test::on_<2>);
    dfa_correct.insert("99a99", &__Test::on_<3>);
    dfa_correct.compile_binary();

    test_binary(dfa_bugtest, std::string("9a9"), dfa_bugtest.binary_start());
    test_binary(dfa_correct, std::string("9a9"), dfa_correct.binary_start());
    test_binary(dfa_correct, std::string("99a99"), dfa_correct.binary_start());
}
#endif
