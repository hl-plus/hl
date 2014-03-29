// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include <iostream>
#include <mpllibs/metaparse/string.hpp>
#include <boost/mpl/if.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/string.hpp>
#include <string.h>
#pragma GCC diagnostic pop

template <typename >
struct rule {   };

typedef MPLLIBS_STRING("we can make some dictionary") regexp_type;

#define REM(...) __VA_ARGS__

#define HL_2_STR__(...) MPLLIBS_STRING(#__VA_ARGS__)
#define $(sl) MPLLIBS_STRING(#sl)
#define HL_RULE(id, src) typedef HL_2_STR__ src id

#define TTF typedef typename

HL_RULE(WORD, (\\w*));

HL_RULE(HUMANS, (
  ##import 'humans'
));

HL_RULE(CITIES,(
  ##import <cities>
));

HL_RULE(CITY
        , (ic:{object={CITIES}\\w*(is|there)}));
HL_RULE(HUMAN
        , (ic:{object={HUMANS}\\w*(is|there)}));

HL_RULE(OBJECT, (
    {CITY}|{HUMAN}
));

HL_RULE(DELIMITER, (
    ( |,|   |;|-|...|?|!|@|#|$|%|^|&|&|*|')'|'('|'\'')
));

HL_RULE(OBJECTS,(
    {objects=({OBJECT}{DELIMITER}?)*}
));

#define ttf typedef typename

struct null_type;

#ifdef USE_BOOST_MPL_V_ITEM
    #define v_it boost::mpl::v_item
#else

template <typename Type
    , typename Tail, int >
struct v_it
{
    typedef Type type;
    typedef Tail base;
};

#endif

template <typename Type>
struct is_v_item
{
    typedef Type type;
    typedef null_type base;
    enum { value = 0, direct = 0 };
};

template <typename Type, typename Tail, int D>
struct is_v_item<v_it<Type, Tail, D> >
{
    typedef Type type;
    typedef Tail base;
    enum { value = 1, direct = D };
};

template <typename Type>
struct rule_compile
{
    template <typename T>
    rule_compile(T) { }

    template <typename Field>
    inline void
    get() {   /*std::cout << __PRETTY_FUNCTION__ << std::endl;*/  }
};


template <typename type>
inline int
mpl_print()
{
    rule_compile<CITY>("jjjjLonDon").get<$(city)>();
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return 0;
}

// static int __o = mpl_print<CITY>();
struct root;
struct begin_group;
struct begin_group_0;
struct end_group;
struct empty_node;
struct block;

template <char... Cs> struct string_;

template <typename Type>
struct algoritm
{

template <typename Seq, Type char_>
struct find_if
{    };

template <template <Type... > class Seq
    , Type... chars, Type char_>
struct find_if <Seq<chars...>, char_ >
{

};

};

template <template <char... > class dst, typename src>
struct copy_chars_ {    typedef null_type type; };

template <char... Cs, template <char... > class dst, template <char... > class src>
struct copy_chars_<dst, src<Cs...> >
{  typedef dst<Cs...> type;  };

template<typename string_type, char C>
struct push_back_2str { typedef null_type type; };

template<typename string_type, char C>
struct push_front_2str { typedef null_type type; };

template <char C,
    template <char...> class string_type, char... Cs>
struct push_back_2str <string_type<Cs...>, C >
{
    typedef string_type<Cs..., C> type;
};

template <char C,
    template <char...> class string_type, char... Cs>
struct push_front_2str <string_type<Cs...>, C >
{
    typedef string_type<C, Cs...> type;
};

template <typename Seq, typename Type>
struct push_back
{
    // if we don't have null_terminated type
    // typedef v_it<Seq, v_it<Type, null_type> > type;
    /// Skip Seq as a last null_type
    typedef typename boost::mpl::if_c<
                boost::is_same<Seq, null_type>::value
                , v_it<Type, null_type, 0>
                , v_it<Seq, Type, 0>
            >::type type;

};

template <typename Seq, typename Tail, int D, typename Type>
struct push_back<v_it<Seq, Tail, D>, Type >
{
    typedef
        v_it<Seq
            , typename push_back<Tail, Type>::type
            , 0
        > type;
};

template <char... Cs>
struct eat_spaces
{
    typedef eat_spaces<Cs...> type;

    template < template <char... Cs_> class fn >
    struct specify
    {   typedef fn<Cs...> type; };
};

template <char C, char... Cs>
struct eat_spaces<C, Cs...>
{
    typedef typename eat_spaces<Cs...>::type type;
};

template <char... Cs>
struct eat_spaces <' ', Cs...>
{
    typedef typename eat_spaces<Cs...>::type type;

    template < template <char... Cs_> class fn >
    struct specify
    {   typedef fn<Cs...> type; };
};

template <char C>
struct is_char {  enum { value = (C > '0') && (C < '9') }; };

template <char... Cs>
struct is_first_char {  enum { value = 0 }; };

template <char C, char... Cs>
struct is_first_char<C, Cs...> {  enum { value = is_char<C>::value }; };

#ifdef TABUSING
template <char... Cs>
struct eat_spaces <'    ', Cs...>
{
    typedef eat_spaces<Cs...> type;
};
#endif // TABUSING

template <char C>
struct char_seq {  enum { char_ = C };  };

template <typename Prefix
    , template <char C> class fn
    , char... Cs >
struct while_imp_
{
    template < template <char... Cs_> class spc >
    struct specify
    {
        typedef spc<Cs...> tail;
        typedef typename copy_chars_<spc, Prefix>::type type;
    };

    typedef while_imp_ type;
};

template <typename Prefix, template <char C> class fn
    , char C, char... Cs >
struct while_imp_ <Prefix, fn, C, Cs... >
{
    template < template <char... Cs_> class spc >
    struct specify
    {
        typedef spc<C, Cs...> tail;
        typedef typename copy_chars_<spc, Prefix>::type type;
    };

    typedef typename while_imp_ <
            typename push_back_2str<Prefix, C>::type
            , fn, Cs... >::type nx_;

    typedef typename boost::mpl::if_c<
            fn<C>::value
            , while_imp_ <Prefix, fn, C, Cs... >
            , nx_>::type type;
};

template <
     template <char C> class fn
    , char... Cs >
struct split_
    : while_imp_ <string_<>, fn, Cs... >
{ };

template <char C> struct is_c {
    template <char C_>
    struct is { enum { value = C_ == C }; };
};

template <char... C>
struct string_;

template <char C>
struct dbg
{
    template <char... txt>
    inline static int
    debug()
    {
        typedef typename
            split_<is_c<C>::template is
        , txt... >::type::template specify<string_>::tail __result;

        typedef typename
            split_<is_c<C>::template is
        , txt... >::type::template specify<string_>::type pref;

        mpl_print<__result>();
        mpl_print<pref>();
    }
};

// static int __ = dbg<')'>::debug<'F', 'a', 'G', 'c', 'p', '\\', ')', 'K' >();

template <typename string_type>
struct rule_block {   };

template <int V, typename Seq, char... Cs >
struct pss_r_obj_i
{
    typedef typename
        eat_spaces<Cs... >::type::template specify<string_ >::type name;

    typedef rule_block<name> rule_type ;
    typedef typename
        push_back<Seq
            , rule_type >::type New;
};

/// This is numbers repeater
template <typename Seq, char... Cs>
struct pss_r_obj_i<0, Seq, Cs...>
{
    struct todo_parse_repeater;
    typedef todo_parse_repeater type;
};

template <typename Seq
    , char... Cs >
struct pss_r_obj
    : pss_r_obj_i<eat_spaces<Cs...>::type
        ::template specify<is_first_char >::type::value, Seq, Cs... >
{};

template <char... Cs>
struct cs_end
{ enum { is_last_value = 1, value = 0 };  };

template <char C, char... Cs>
struct cs_end <C, Cs...>
{
    enum { is_last_value = 0 };
    static const char value = cs_end <Cs...>::is_last_value
        ? C : cs_end <Cs...>::value;
};

struct Block;

/// Scope
template <typename Repeater, typename Seq>
struct seq_scope
{  };

struct skip_node;

template <typename Seq, typename Rule>
struct wait  {   typedef Seq seq; typedef Rule rule; };

template <typename Seq, typename Type>
struct push_
{
    enum { is_wait = 0 };
    typedef typename
        boost::mpl::if_c<
            boost::is_same<skip_node, Seq>::value
            , Type
            , typename
                push_back<Seq, Type>::type
         >::type type;

    typedef null_type seq;
};

template <typename Seq, typename Rule, typename Type>
struct push_<wait<Seq, Rule>, Type >
{
    enum { is_wait = 1 };

    typedef wait<Seq, Rule> type;
    typedef Seq seq;
};

template <int I>
struct apply_allways
{ enum { apply_2v_item = I }; };

/// replacing
template <typename Type
    , template <typename, typename > class Pred
    , int next_
        = Pred<typename is_v_item<Type>::type
            , typename is_v_item<Type>::base >::value  >
struct replace_if
{
    typedef typename
        boost::mpl::if_c <
            Pred<Type, null_type>::value
            , typename Pred<Type, null_type>::type
            , Type >::type type;
};

template <typename Type, typename Tail, int D
    , template <typename, typename > class Pred>
struct replace_if<v_it<Type, Tail, D >
        , Pred, 2 >
{
    enum {
        apply_2v_item = Pred<Type, Tail>::apply_2v_item };

    typedef v_it<typename
                    Pred<Type, Tail>::type
                , typename replace_if<Tail, Pred>::type, D> type;
};

template <typename Type, typename Tail, int D
    , template <typename, typename > class Pred>
struct replace_if<v_it<Type, Tail, D >
        , Pred, 1 >
{
    enum {
        apply_2v_item = Pred<Type, Tail>::apply_2v_item };

    ttf boost::mpl::if_c< apply_2v_item
                    , v_it<typename Pred<Type, Tail>::type, Tail, D>
                    , typename Pred<Type, Tail>::type
        >::type type;
};

template <typename Type, typename Tail, int D
    , template <typename, typename > class Pred, int val>
struct replace_if <v_it<Type, Tail, D>, Pred, val >
{
    typedef v_it<Type
        , typename replace_if<Tail, Pred>::type, D > type;
};
/// end replacing

/// Move scope_state to next recursive
template <typename Seq, typename Data>
struct scope_state
{
    typedef Seq seq;
    typedef Data data;
};

template <typename State>
struct parse_state
{
    enum { value = 0 };
    typedef State seq;
    typedef State data;
};

template <typename Seq, typename Data>
struct parse_state<scope_state<Seq, Data> >
{
    enum { value = 1 };
    typedef Seq seq;
    typedef Data data;
};

#define tf typedef
#define tn typename

template <typename Type, typename Tail>
struct apply_to_string_seq
{
    enum {  value = 0 };
    typedef Type type;
};

template <char... Cs, char C>
struct apply_to_string_seq<string_<Cs... >, char_seq<C> >
{
    enum { value = 1, apply_2v_item = 0 };

    typedef typename
        push_back_2str<string_<Cs...>, C >::type type;
};

template <char C0, char C1>
struct apply_to_string_seq<char_seq<C0 >, char_seq<C1> >
{
    enum { value = 1, apply_2v_item = 0 };
    typedef typename
        push_back_2str<string_<>, C0 >::type type_C0;

    typedef typename
        push_back_2str<type_C0, C1 >::type type;

    template <typename Type_
                , typename Tail>
    struct if_
    {
        typedef typename
        boost::mpl::if_c<
                boost::is_same<Tail, null_type>::value
                , typename push_back_2str<Type_, C0>::type
                , Type_
            >::type type;
    };
};

template <typename Seq>
struct apply_last_char
{
    ttf replace_if<Seq
        , apply_to_string_seq>::type type;
};

template <typename Seq, typename Data>
struct apply_last_char<scope_state<Seq, Data > >
{
    ttf replace_if<Seq
        , apply_to_string_seq>::type sec_;

    typedef scope_state<sec_, Data > type;
};

/// !!TODO: group scope changing
template <typename Seq
    , typename Data, typename Type>
struct push_<scope_state<Seq, Data >, Type >
{
    enum { is_wait = 1 };

    typedef Data data;
    ttf push_back<Seq, Type>::type sequence;

    // Move data to next
    typedef scope_state<sequence, Data> type;
};

/// begin group scope
/// we should change it
template <typename Data, typename Type>
struct push_<scope_state<begin_group, Data >, Type >
{
    enum { is_wait = 1 };

    typedef Data data;
    typedef Type sequence;

    // Move data to next
    typedef scope_state<sequence, Data> type;
};

template <typename... Seq>
struct alter_scope
{   };

template <typename Type, typename Tail>
struct replace_by_alter: apply_allways<0>
{
    typedef typename boost::mpl::if_c<
        boost::is_same<Tail, null_type>::value
              /// TODO: change is_last<Tail>::value: v_i<_1, _2>
            , alter_scope<Type>
            , alter_scope<Type, Tail> >::type type;
    enum { value = 1/*boost::is_same<Tail, null_type>::value*/ };
};

template <typename... Seq, typename Tail>
struct replace_by_alter<alter_scope<Seq...>, Tail >: apply_allways<0>
{
    typedef typename boost::mpl::if_c<
        boost::is_same<Tail, null_type>::value
            , Tail
            , alter_scope<Seq..., Tail> >::type type;
    enum { value = ! boost::is_same<Tail, null_type>::value };
};

template <typename Seq>
struct apply_altern
{
    ttf replace_if<
        typename apply_last_char<Seq>::type, replace_by_alter>::type type;
};

template <typename Seq, typename Data>
struct apply_altern<scope_state<Seq, Data > >
{
    typedef scope_state<typename apply_altern<Seq>::type, Data > type;
};

/// Last step processing
template <typename Seq, char... Cs>
struct r_obj
{
    enum { value = 0 };

    /// Apply the last alternative
    ttf apply_altern<
            typename apply_last_char<Seq>::type >::type type;
};

template <typename Seq, char C, char... Cs>
struct r_obj<Seq, C, Cs... >
{
    enum { value = 0 };

    ttf apply_last_char<Seq>::type seq_with_applied_string_;

    typedef typename
        push_<seq_with_applied_string_
                , char_seq<C> >::type New;

    typedef typename
        r_obj<New, Cs...>::type type;
};

template <typename Seq, char... C>
struct r_obj<Seq, '\\', C...>
{
    struct Escape;
};

template <typename Seq, char... C>
struct r_obj<Seq, '{', C...>
{
    enum { value = 1 };
    typedef typename
        pss_r_obj<Seq, C...>::type type;
};

template <typename Seq>
struct scope {  };

template <typename Seq, char... Cs>
struct r_obj<Seq, '(', Cs...>
{
    enum { value = 1 };

    ttf apply_last_char<Seq>::type complete_seq;

    typedef typename
        r_obj<scope_state<begin_group, complete_seq>
                    , Cs... >::type type;
};

template <typename Seq, char... Cs>
struct r_obj<Seq, ')', Cs...>
{
    enum { value = 1 };

    ttf apply_altern<
        typename apply_last_char<Seq>::type >::type altern;

    typedef parse_state< altern > state_parser;

    static_assert(state_parser::value, "Should be '(' before ')'");

    ttf apply_last_char<typename state_parser::seq>::type group_type;

    // final group sequence
    ttf push_<typename state_parser::data
                    /// last change this place we
                    , scope<group_type> >::type seq;

    typedef typename
        r_obj<seq, Cs...>::type type;
};

template <typename Seq, char... C>
struct r_obj<Seq, '|', C...>
{
    ttf r_obj<
        typename apply_altern<Seq>::type, C...>::type type;
};

template <int, int >
struct repeater
{

};

template <int I0, int I1>
struct repeater_pred
{
    template <typename Type, typename Tail>
    struct repeater_apply : apply_allways<0>
    {
        typedef typename boost::mpl::if_c<
            boost::is_same<Tail, null_type>::value
                , seq_scope <repeater<I0, I1>, Type >
                , Type >::type type;

        enum { value = boost::is_same<Tail, null_type>::value };

    };
};

template <typename Seq, char... C>
struct r_obj<Seq, '*', C...>
{
    ttf replace_if<Seq, repeater_pred<0, -1>::repeater_apply>::type tr;
    ttf r_obj<tr, C...>::type type;
};

template <typename > struct W;

template <typename Type, typename Tail>
struct Test
{
    enum { value = boost::is_same<Type, char>::value ? 2 : 0 };
    typedef W<Type> type;
};

template <typename Type>
struct compile
{

};

template <typename Quant, typename... Seq>
struct compile <alter_scope<Quant, Seq... > >
{
    /// ttf state::push_alter<Quant>::type;
};

int main()
{
    // typedef push_back<v_it<int, v_it<char, v_it<char, int, 0>, 0>, 0>, double>::type type;
    // mpl_print<typename replace_if<type, Test>::type >();
    mpl_print<r_obj<root, '(', 'a', 'b', ')', '*', '|', 'c' >::type >();

    mpl_print<r_obj<root, '(', 'a', ')', 'b', '*'
                   , '|', 'c', '!', '(', 'd', '|', 'k', 'j', ')', '!', '|' ,'G', 'j' >::type >();
    //mpl_print<r_obj<root, 'a', '|', '(', 'b', ')', 'b', 'p', '|', 'p', 'c' >::type >();
    //mpl_print<r_obj<root, 'a', 'b', '|', 'c', 'd'>::type >();
    //mpl_print<r_obj<root, 'a', 'b', '|', '(', 'c', 'd', ')', 'b', 'p', '|', 'p', 'c' >::type >();

    // mpl_print< r_obj<struct Top, '(', '{', 'g', 'p', '}', '|', '(', 's', ')',')', '{', '4', ',', '5', '}'>::type >();
    // mpl_print< r_obj<root, '(', 'a', 'b', '(', 's', '(', '0', ')', ')',')'>::type >();
    // mpl_print< r_obj<root, '(', '%', '(', 'a', 'b', ')', 'c', 'c', '!', ')', '|', 'd'>::type >();
    // std::cout << r_obj<root, '(', '{','g','p','}','|', 's', ')'>::value << std::endl;
    return 1;
}

