/***************************/

#ifndef PP_FOREACH_HPP_SSDKFHGDFMHNDFMGHKDFJTGOYHERJRKDFETHJDFKGJHDFKGHJDFKGHJDFKG
#define PP_FOREACH_HPP_SSDKFHGDFMHNDFMGHKDFJTGOYHERJRKDFETHJDFKGJHDFKGHJDFKGHJDFKG

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4)))
# pragma GCC system_header
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)
#define GET_FIRST__(FIRST, ...) FIRST
#define GET_REST__(FIRST, ... ) __VA_ARGS__

#define GET_FIRST(FIRST, ...) GET_FIRST__(FIRST, __VA_ARGS__)
#define GET_REST(FIRST, ... ) GET_REST__(FIRST, __VA_ARGS__)

#define  HL_PP_FOREACH1(Prefix, Postfix,  Delimiter, m, mp, pp, Pair0) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Postfix
#define  HL_PP_FOREACH2(Prefix, Postfix,  Delimiter, m, mp, pp, Pair0, Pair1)    EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter m(mp, pp, Delimiter, Pair1) EAT_PTH Postfix
#define  HL_PP_FOREACH3(Prefix, Postfix,  Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter \
                        HL_PP_FOREACH2((),(), Delimiter, m, mp, pp,  GET_FIRST(__VA_ARGS__), GET_REST(__VA_ARGS__)) EAT_PTH Postfix

#define  HL_PP_FOREACH4(Prefix, Postfix,  Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH3((),(),  Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH5(Prefix, Postfix,  Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH4((),(),  Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH6(Prefix, Postfix,  Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH5((),(),  Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH7(Prefix, Postfix,  Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH6((),(),  Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH8(Prefix, Postfix,  Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH7((),(),  Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH9(Prefix, Postfix,  Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH8((),(),  Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH10(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH9((),(),  Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH11(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH10((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH12(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH11((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH13(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH12((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH14(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH13((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH15(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH14((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH16(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH15((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH17(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH16((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH18(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH17((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH19(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH18((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH20(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH29((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH21(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH20((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH22(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH21((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH23(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH22((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH24(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH23((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH25(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH24((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH26(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH25((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH27(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH26((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH28(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH27((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH29(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH28((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH30(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH29((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH31(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH30((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH32(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH31((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH33(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH32((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH34(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH33((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH35(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH34((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH36(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH35((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH37(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH36((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH38(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH37((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH39(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH38((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH40(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH39((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH41(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH40((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH42(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH41((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix
#define  HL_PP_FOREACH43(Prefix, Postfix, Delimiter, m, mp, pp, Pair0, ...) EAT_PTH Prefix  m(mp, pp, Delimiter, Pair0) EAT_PTH Delimiter HL_PP_FOREACH42((),(), Delimiter, m, mp, pp,  __VA_ARGS__) EAT_PTH Postfix

#endif
