#if !defined (COMPRESSED_DFA_JDHFGJDHFGJCNVXVVHJDHFGDHFJGDFJG)
#define COMPRESSED_DFA_JDHFGJDHFGJCNVXVVHJDHFGDHFJGDFJG

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <limits>
#include <ext/hash_map>
#include <assert.h>

#ifdef __USE_CUSTOM_MAP
    #include "std_map.hpp"
#else
    namespace std
    {
        //  Declaration of a not presented custom autpomation map
        // we can use it on a GPL
        template <typename _Key, typename _Tp, typename _Compare = std::less<_Key>,
                  typename _Alloc = std::allocator<std::pair<const _Key, _Tp> > >
          class _Lb_map;
    }
#endif


template<int I>
struct id2type
{
    enum
    {
        value = I
    };
};

// gl_plus_sketch.cpp : Defines the entry point for the console application.
//
#ifdef MSVCVER
#include "stdafx.h"
#endif

#include <string>
#include <vector>
#include <algorithm>

#ifdef __DEBUG_
    #define TRACE(some) std::cout << some << std::endl;
#else
    #define TRACE(some)
#endif

#define Is(identifier) \
		struct type_##identifier

namespace hl
{

template<typename Char>
struct buffer_access
{
    typedef Char char_type;
};

#ifdef ENABLE_GL_ASSER
    #define GL_ASSERT(what) assert(what)
#else
    #define GL_ASSERT(what)
#endif

template<typename dfa_type>
inline void print_dfa(dfa_type& dfa_);

template<typename dfa_type_iterator>
inline void print_dfa(dfa_type_iterator begin, dfa_type_iterator end);

}

namespace hl
{
struct null_type;

//  This is a default trace
// TODO in future we should implement
// detailed traces
template<typename type>
struct traits
{
    typedef typename
        type::iterator iterator;
    typedef typename
        type::const_iterator const_iterator;
};

template<typename type>
inline typename traits<type>::const_iterator
begin(type const& s)
{
    return s.begin();
}

template<typename type>
inline typename traits<type>::const_iterator
end(type const& s)
{
    return s.end();
}

//  Traces to use inside class scope
// we should use as not explicit
// to gcc compiler
#define TRAITS_DECLARE(Trait, Type)               	\
    template <template <typename > class shell__ > 	\
    struct _Traits<shell__<Trait> >         		\
    {                                             	\
      typedef Type type;                          	\
    };

template<typename type>
struct stl_accessor
{
    // Empty base specialization
    // we should use static asserts
    struct Empty;
};

//   This specialization to
// standard STD map using inside automation
//
template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
struct stl_accessor<std::map<_Key, _Tp, _Compare, _Alloc> >
{
    typedef std::map<_Key, _Tp, _Compare, _Alloc> _Map_type;
    typedef typename _Map_type::iterator iterator;
    typedef typename _Map_type::const_iterator const_iterator;

    stl_accessor(_Map_type &mp) :
        map_(mp)
    {
    }

    inline iterator
    lower_bound(iterator begin, iterator end, _Key const& key)
    {
        return map_.lower_bound(key);
    }

    inline const_iterator
    lower_bound(iterator begin, iterator end, _Key const& key) const
    {
        return map_.lower_bound(key);
    }

    _Map_type& map_;
};

// This specialization can be used
template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
struct stl_accessor<std::_Lb_map<_Key, _Tp, _Compare, _Alloc> >
{
    typedef std::_Lb_map<_Key, _Tp, _Compare, _Alloc> _Map_type;

    typedef typename
        _Map_type::_Rep_type::iterator iterator;
    typedef typename
        _Map_type::_Rep_type::const_iterator const_iterator;

    typedef typename
        _Map_type::_Rep_type::_Link_type _Link_type;

    typedef typename
        _Map_type::_Rep_type _Rep_type;

    stl_accessor(_Map_type &mp) :
        map_(mp)
    {
    }

    inline _Rep_type&
    get_rep()
    {
        return map_._M_t;
    }

    inline _Rep_type const&
    get_rep() const
    {
        return map_._M_t;
    }

    template<typename _Link_type0>
    inline _Link_type0 _To_max_link(iterator& where)
    {
        return _To_link(static_cast<_Link_type0> (_Link_type0::_S_maximum(
                where._M_node)));
    }

    template<typename _Link_type_need, typename _Link_type_base>
    inline _Link_type_need _To_link_cast(_Link_type_base link)
    {
        return static_cast<_Link_type_need> (link);
    }

    template<typename _Link_>
    inline _Link_type _To_link(_Link_& where, bool parent_ = false)
    {
        return parent_ ? _To_link_cast<_Link_type> (
                static_cast<_Link_type> (where._M_node)->_M_parent)
                : static_cast<_Link_type> (where._M_node);
    }

    inline iterator lower_bound(iterator begin, iterator end, _Key const& key)
    {
        return map_._M_t._M_lower_bound(_To_link(begin, true), _To_link(end),
                key);
    }

    inline const_iterator lower_bound(iterator begin, iterator end,
            _Key const& key) const
    {
        return get_rep()._M_lower_bound(begin, end, key);
    }

    _Map_type& map_;
};

#ifdef __WORK_WITHOUT_HL

template<int I> struct int_type
{
    enum
    {
        value = I
    };
};

typedef int_type<1> true_type;
typedef int_type<0> false_type;

template<typename _Ty0, typename _Ty1>
struct is_same
{
    enum
    {
        value = 0
    };
};

template<typename _Ty>
struct is_same<_Ty, _Ty>
{
    enum
    {
        value = 1
    };
};

#endif

template<typename > struct __sh;

template<typename _Ty>
struct true_if_type
{
};

template<>
struct true_if_type<true_type>
{
    struct type
    {
        type(int)
        {
        }
    };
};

template<int I>
struct true_if_c_type
{
};

template<>
struct true_if_c_type<1>
{
    struct type
    {
        type(int)
        {
        }
    };
};

template<typename _Ty>
struct is_extended: true_type
{
};

namespace detail
{
struct vector_node_binary_tag;
struct vector_node_indexed_tag;

template<typename _Node_type>
struct traits
{
};
}

//  This is a base dfa compiler class
// we use more than one approaches
// on a binary map based
template<typename _Key_type, typename _Type, template<typename , typename ,
        typename , typename > class Ranges = /*std::_Lb_map*/std::map>
struct dfa_compiler
{
    //To gcc approach
    template<typename >
    struct _Shell_traits;

    template<typename Type>
    struct _Traits
    {
        typedef hl::null_type type;
    };

    // Traits related to
    TRAITS_DECLARE(std::string, char);
    TRAITS_DECLARE(std::wstring, wchar_t);
    TRAITS_DECLARE(std::vector<char>, char);
    TRAITS_DECLARE(std::vector<unsigned char>, unsigned char);
    TRAITS_DECLARE(hl::buffer_access<unsigned char>, unsigned char);
    TRAITS_DECLARE(hl::buffer_access<char>, char);
#if defined (__ICU_INSTALLED)
    TRAITS_DECLARE(icu::UncideString, icu::UChar);
#endif

    typedef typename
        _Traits<_Shell_traits<_Key_type> >::type elem_type;

    //  Foreign declaration services types
    // Can be moved from this scope in future
    struct iterator;
    struct key_range;

    //   This is a ranges type
    // we currently have two approach
    // in which we use adopted STD map with method lower_bound (begin, end)
    // to allows ranged lower bound
    // and with standard map
    typedef Ranges<key_range, iterator
                , std::less<key_range>
                , std::allocator<std::pair<const key_range, iterator> > >
        ranges_type;

    // Should be parsed
    typedef typename ranges_type::iterator range_iterator;

    typedef stl_accessor<ranges_type> map_accessor;

    dfa_compiler() :
        ranges_(), current_(0), map_accessor_(ranges_), id_(0), binary_(),
                binary_current_(0)
    {
    }

    template<typename _Cont_type>
    struct container_traits
    {
        enum
        {
            is_vector = 0, _Is_tag = 0
        };

        typedef _Cont_type container_type;

        typedef typename _Cont_type::iterator iterator;
        typedef typename _Cont_type::const_iterator const_iterator;
    };

    template<typename _Type_0, typename _Alloc>
    struct container_traits<std::vector<_Type_0, _Alloc> >
    {
        enum
        {
            is_vector = 1, _Is_tag = 0
        };
        typedef std::vector<_Type_0, _Alloc> container_type;

        typedef typename container_type::iterator iterator;

        typedef typename container_type::const_iterator const_iterator;
    };

    template<typename _Cont_tag_type>
    struct _Node;
    typedef _Node<detail::vector_node_binary_tag> binary_node_type;

    template<template<class > class _Node_templ_type>
    struct container_traits<_Node_templ_type<detail::vector_node_binary_tag> >
    {
        enum
        {
            _Is_tag = 1, is_vector = 1
        };
        typedef std::vector<_Node_templ_type<detail::vector_node_binary_tag> >
                container_type;
        //typedef int iterator;
        typedef typename container_type::iterator iterator;
        typedef typename container_type::const_iterator const_iterator;
    };

    struct _Base_node
    {
        typedef int idd_type;
        _Base_node()
        {
        }

        _Base_node(idd_type idd, idd_type parent, elem_type el) :
            id_(idd), parent_(parent), jump_(el)
        {
        }

        idd_type id_, parent_;
        elem_type jump_;
        bool is_value_;
    };

    template<typename _Cont_type>
    struct _Node: std::pair<
            typename container_traits<_Node<_Cont_type> >::iterator,
            typename container_traits<_Node<_Cont_type> >::iterator>,
            _Base_node
    {
        typedef _Node<_Cont_type> _M_type;
        typedef typename container_traits<_Node<_Cont_type> >::iterator
                _Iterator;

        typedef typename container_traits<_M_type>::container_type
                container_type;

        typedef std::pair<_Iterator, _Iterator> base;
        typedef typename _Base_node::idd_type idd_type;
        _Node() :
            base(), _Base_node()
        {
        }

        _Node(_Iterator const& begin, _Iterator const& end) :
            base(begin, end), _Base_node()
        {
        }

        _Node(idd_type id, idd_type parent, elem_type jmp) :
            base(), _Base_node(id, parent, jmp)
        {
        }

        template<typename Iterator, typename NodeType>
        inline _Node&
        operator =(std::pair<Iterator, NodeType> const& nd)
        {
            this->_Base_node::id_ = nd.first.id_;
            this->_Base_node::parent_ = nd.first.parent_;
            this->_Base_node::jump_ = nd.first.jump_;
            this->_Base_node::is_value_ = nd.second.is_value_;
            value_ = nd.second.value_;
            return *this;
        }

        template<typename Iterator>
        inline _Node&
        operator =(Iterator const& I)
        {
            this->_Base_node::id_ = I.id_;
            this->_Base_node::jump_ = I.jump_;
            this->_Base_node::is_value_ = I.is_value_;
            value_ = I.value_;

            return *this;
        }

        template<typename Iterator>
        inline bool operator <(Iterator const& I)
        {
#ifdef __DEBUG_
            if (__get_static_print_flag())
            {
                bool __is_ = false;
                if (this->_Base_node::parent_ < I.parent_)
                __is_ = true;
                else if (this->_Base_node::parent_ == I.parent_)
                __is_ = (this->_Base_node::jump_ < I.jump_);

                TRACE("{" << this->_Base_node::parent_
                        << ", " << this->_Base_node::jump_ << "} == {"
                        << I.parent_ << ", " << I.jump_ << "} = " << __is_);
            }
#endif
            if (this->_Base_node::parent_ < I.parent_)
                return true;
            else if (this->_Base_node::parent_ == I.parent_)
                return (this->_Base_node::jump_ < I.jump_);
            return false;
        }

        template<typename _Ty, typename _Alloc>
        inline _Node *at_(std::vector<_Ty, _Alloc> const& vc,
                _Iterator const& where)
        {
            return &vc.at(where);
        }

#ifdef __DEBUG_
        int& __get_static_print_flag()
        {
            static int __is_print = 0;
            return __is_print;
        }
#endif

        typedef _Node* _Node_ptr;

        inline _Node_ptr
        jump (container_type const& vc, elem_type const& e)
        {
            GL_ASSERT(std::distance(this->first, this->second) > 0);

#ifdef __DEBUG_
            if (!__get_static_print_flag())
            __get_static_print_flag() = 1;
#endif
            //-2 is a marker that we find in scope where id isn't need compare
            _Iterator where = std::lower_bound(this->first, this->second,
                    _Base_node(0, this->_Base_node::id_, e));

#ifdef __DEBUG_
            if (__get_static_print_flag() && where != vc.end())
            {
                TRACE((e ? e : (elem_type const) '@') << "->" << "{"<< where->id_ << ", " << where->jump_ << "}");
            }
#endif
            if (where != this->second && where->jump_ == e)
            {
                return &(*where);
            }

            return _Node_ptr();
        }

        _Type value_;
    };

    // comparator
    struct key_range
    {
        typedef int iid_type;
        key_range() :
            id_(-1), parent_(-1), jump_()
        {
        }

        key_range(key_range const& kr) :
            id_(kr.id_), parent_(kr.parent_), jump_(kr.jump_)
        {
        }

        key_range(iid_type iid, iid_type parent, elem_type const& el) :
            id_(iid), parent_(parent), jump_(el)
        {
        }

        template<typename type>
        inline bool
        operator <(type const& what) const
        {
            if (parent_ < what.parent_)
                return true;
            else if (parent_ == what.parent_)
                return jump_ < what.jump_;

            return false;
        }

        iid_type id_, parent_;
        elem_type jump_;
    };

    //To compilation only
    struct iterator: public std::pair<range_iterator, range_iterator>
    {
        typedef int idd_type;
        typedef std::pair<range_iterator, range_iterator> base;

        iterator(idd_type idd, int flags, elem_type ju, iterator* parent = 0) :
            base()
            , jump_(ju)
            , flags_(flags)
            , id_(idd)
            , value_()
            , parent_(parent)
            , is_value_(false)
        {
        }

        iterator() :
            base()
            , jump_()
            , flags_(NOT_COMPILED_ID)
            , id_()
            , value_()
            , parent_(0)
            , is_value_(false)
        {
        }

        iterator(iterator const& other) :
                base(other.first, other.second)
                , jump_(other.jump_)
                , flags_(other.flags_)
                , id_(other.id_)
                , value_(other.value_)
                , parent_(other.parent_)
                , is_value_(other.is_value_)
        {
        }

        inline iterator*
        set_(_Type const& value)
        {
            value_ = value;
            is_value_ = true;
            return this;
        }

        elem_type jump_;
        int flags_;

        idd_type id_;
        _Type value_;
        iterator* parent_;
        bool is_value_;
    };

    inline iterator&
    insert(_Key_type const& key, _Type const& v)
    {
        return *this->insert_(key, v);
    }

    enum
    {
        ALIGN_LEFT = (1), ALIGN_RIGHT = (1 << 1)
    };

    inline iterator*
    move(elem_type const& el, bool align_leftright = 0)
    {
        if (!current_)
            current_ = &this->begin();

        range_iterator where_ =
                this->map_accessor_.lower_bound(current_->first,
                        current_->second, key_range(current_->id_, el));
#if defined __PRINT_TREE__
        TRACE(std::endl << "_____");
        print_dfa(current_->first, current_->second);
        TRACE("_____");
#endif

#ifdef  __DEBUG_
        if (where_ != ranges_.end())
        TRACE("from " << (char)el << "("<< (*where_).first.id_ << ":" << (*where_).first.jump_ << ") ");
#endif

        if (where_ != current_->second && (*where_).first.jump_ == el
                && (*where_).first.id_ == current_->id_)
        {
            current_ = &(*where_).second;

            return (current_);
        }

        return 0;
    }

    //private:
    inline iterator*
    insert_(_Key_type const& key, _Type const& v)
    {

        return compile_key_(key)->set_(v);
    }

    enum
    {
        ROOT_ID = (1 << 1),
        NOT_COMPILED_ID = (1 << 2),
        TO_JUMP_CHAR_COMPARSION_ONLY = (1 << 3)
    };

    //Applying to compilation
    inline iterator*
    apply(iterator* cur_, elem_type el)
    {
        iterator& cur = *cur_;
        range_iterator where;

        if ((cur.flags_ & NOT_COMPILED_ID))
        {
            //set compiled flags
            cur.flags_ &= ~NOT_COMPILED_ID;

            range_iterator end = ranges_.end();
            if (cur.parent_)
                end = cur.parent_->second;

            //find the place to new iterator
            cur.first = this->map_accessor_.lower_bound(ranges_.begin(),
                    ranges_.end(), key_range(0, cur.id_ - 1,
                            std::numeric_limits<elem_type>::max()));
            cur.second = end;
            where = cur.first;

            TRACE(" where->second = " << &where->second << ", cur.id_ = " << cur.id_ );
        }
        else
        {
            //	This place is a connection
            // to certain node and find inside range
            range_iterator where = this->map_accessor_.lower_bound(cur.first,
                    cur.second, key_range(0, cur.id_, el));

            TRACE(" where->second = " << &where->second << ", cur.id_ = " << cur.id_);

            if (where != cur.second && where->second.jump_ == el
                    && where->second.id_ == cur.id_)
                return &where->second;
        }

        // Get the new ID which will child for cur->id_
        typename iterator::idd_type inew = this->new_id();

        range_iterator ww = ranges_.insert(std::make_pair(key_range(inew,
                cur.id_, el), iterator(inew, NOT_COMPILED_ID, el, cur_))).first;
#if defined __PRINT_TREE__
        print_dfa(cur.first, cur.second);
#endif
        (*ww).second.parent_ = &cur;
        return &(*ww).second;
    }

    template<typename _Cont_type>
    void convert_(_Cont_type& container, typename hl::true_if_type<
            hl::is_extended<_Cont_type> >::type vv = 1)
    {
        //hl::is_extended<_Cont_type>::type(this)
        //(ranges_, container);
    }

    template<int _Is_binary, typename _Cont_type>
    inline void convert_vc_(_Cont_type& container, typename hl::true_if_c_type<
            _Is_binary>::type vv = 1)
    {
        typedef _Node<detail::vector_node_binary_tag> _Node_type;
        typedef std::vector<_Node<detail::vector_node_binary_tag> >
                vector_dfa_binary;

#if defined __DEBUG_
        TRACE("_________________________________________");
        for(typename
                ranges_type::iterator cur_range = ranges_.begin();
                cur_range != ranges_.end(); ++cur_range)
        {
            TRACE( "{("<< cur_range->first.parent_ << ")->(" << cur_range->first.id_ << ")"
                    << ", " << (cur_range->first.jump_ ? cur_range->first.jump_ : '@' ) << "}");
        }

        TRACE("_________________________________________");
#endif

        //This is method is not valid ..!!
        vector_dfa_binary& vc = container;
        vc.resize(ranges_.size(), _Node_type(-1, -1, '\0'));

        int vc_where = 0, max_id = 0;
        for (typename ranges_type::iterator cur_range = ranges_.begin(); cur_range
                != ranges_.end(); ++cur_range, ++vc_where)
        {
            _Node_type& node = vc[vc_where];
            node = *cur_range;

            TRACE( "{"<< node.parent_ << ", " << (node.jump_ ? node.jump_ : '@' ) << "}");

            max_id = std::max(max_id, cur_range->second.id_);
        }

        //If need
        /*std::sort(vc.begin(), vc.end()
         //, [](_Node_type const& first, _Node_type const& second)
         //{	return (first.id_ < second.id_) && (first.jump_ < second.jump_); }
         );*/

        typedef typename container_traits<_Cont_type>::iterator vc_iterator;
        typedef container_traits<_Cont_type> traits;

        std::vector<vc_iterator> idss;
        idss.resize(max_id, vc.end());

#if defined __DEBUG_
        std::cout << "_________________________________________" << std::endl;
#endif

        vc_iterator cur = vc.begin(), begin = vc.begin(), end = vc.end();
        for (int id = -1; cur != end; ++cur)
        {
            vc_iterator begin_ = vc.begin(), end_ = vc.end();

#if defined __DEBUG_
            std::cout << "{" << cur->parent_ << "("<< cur->id_ << ")"
            << ", " << (cur->jump_ ? cur->jump_ : '@' ) << "} -> " << std::flush;
#endif
            if (!cur->jump_ && false)
            {
                cur->first = begin_;
                cur->second = end;
            }
            else
            {
                id = cur->id_;
                cur->first = std::lower_bound(begin_, end, _Node_type(0,
                        id - 1, std::numeric_limits<elem_type>::max()));
                cur->second = std::lower_bound(begin_, end, _Node_type(0, id
                        + 1, std::numeric_limits<elem_type>::min()));
            }

#if defined __DEBUG_
            std::cout << ":";
            if (cur->second != vc.end())
            ;//print_item(cur->second, true);

            else
            {   std::cout << "{end}" << std::endl;}
#endif
        }
    }

    template<typename _Cont_type>
    void convert_(_Cont_type& vc, typename hl::true_if_c_type<container_traits<
            _Cont_type>::is_vector>::type vv = 1)
    {
        typedef _Node<detail::vector_node_binary_tag> _Node_type;
        typedef std::vector<_Node<detail::vector_node_binary_tag> >
                vector_dfa_binary;

        typedef std::vector<_Node<detail::vector_node_indexed_tag> >
                vector_dfa_indexed;

        enum
        {
            is_vc_binary_approaqch = hl::is_same<vector_dfa_binary, _Cont_type>::value,
            _Is_vc_indexed_approach = hl::is_same<vector_dfa_indexed,
                    _Cont_type>::value
        };

        GL_ASSERT(!vc.size());
        this->convert_vc_<is_vc_binary_approaqch> (vc);

    }

    template<typename _Cont_type>
    void convert(_Cont_type& vc)
    {
        this->convert_(vc);
    }

    inline binary_node_type*
    binary_start()
    {
        return &binary_[0];
    }

    template<typename el_type>
    inline binary_node_type*
    jump(el_type const& el)
    {
        binary_current_ = binary_current_->jump(binary_, el);
    }

    template<typename el_type>
    inline binary_node_type*
    jump(binary_node_type* ss, el_type const& el)
    {
        return ss->jump(binary_, el);
    }

    void compile_binary()
    {
        this->convert_(binary_);
        GL_ASSERT(binary_.size());
        binary_current_ = &binary_[0];
    }

    inline iterator&
    begin()
    {
        if (ranges_.empty())
        {
            typename iterator::idd_type newid = this->new_id();
            iterator& I = (*(ranges_.insert(std::make_pair(key_range(newid, -1,
                    elem_type()), iterator(newid, NOT_COMPILED_ID | ROOT_ID,
                    std::numeric_limits<elem_type>::min()))).first)).second;
            return I;
        }

        return (*ranges_.begin()).second;
    }

    inline iterator*
    compile_key_(_Key_type const& key)
    {
        iterator* where = &this->begin();
        for (typename hl::traits<_Key_type>::const_iterator e = hl::begin(key); e
                != hl::end(key); ++e)
        {
            where = this->apply(where, *e);
        }

        return where;
    }

    int new_id()
    {
        return ++id_;
    }

    ranges_type ranges_;
    iterator* current_;
    map_accessor map_accessor_;

    //compilation segment
    int id_;

    typedef std::vector<_Node<detail::vector_node_binary_tag> > binary_vector;
    binary_vector binary_;
    _Node<detail::vector_node_binary_tag>* binary_current_;
};

template<typename _Type>
struct approach_traits
{

};

template<typename _Key_type, typename _Type,
        typename _Base_type = detail::vector_node_binary_tag>
struct dfa_i
{
};

template<typename _Key_type, typename _Type>
struct dfa_i<_Key_type, _Type, detail::vector_node_binary_tag> : approach_traits<
        dfa_i<_Key_type, _Type, detail::vector_node_binary_tag> >
{
    typedef dfa_compiler<_Key_type, _Type> compiler_type;
    typedef typename compiler_type:: template _Node<
            detail::vector_node_binary_tag> _Node_type;

    typedef std::vector<_Node_type> binary_vector;

    dfa_i() :
        compiler_(new compiler_type())
    {
    }

    void compile()
    {
        if (compiler_)
        {
            compiler_->compile(binary_);
            delete compiler_;
            compiler_ = 0;
        }
    }

    binary_vector binary_;
    compiler_type* compiler_;
};

}

namespace hl
{
template<typename Type, int Sz>
inline Type*
end_(Type(&a)[Sz])
{
    return a + Sz;
}
}

//This place is describe the situation when or
#define PP(where) (*where).first << " : " << (*where).second.c_str()

template<typename dfa_type>
inline void
print_dfa(dfa_type& dfa_);

template<typename dfa_type_iterator>
inline void
print_dfa(dfa_type_iterator begin, dfa_type_iterator end);

template<typename _Dfa_type, typename _Type_check>
inline void
test_(_Dfa_type &dfa_, _Type_check const& mega_test);

template<typename _Dfa_type, typename _Type_check, typename _Node_type>
inline void test_binary(_Dfa_type &dfa_, _Type_check const& mega_test,
        _Node_type cur_)
{
    typedef _Dfa_type dfa_type;
    for (typename _Type_check::const_iterator where = mega_test.begin(); where
            != mega_test.end(); ++where)
    {
        cur_ = dfa_.jump(cur_, *where);

        if (cur_ && cur_->is_value_)
        {
            (cur_->value_)();
        }
        else if (!cur_)
        {
            std::cout << "not found: " << mega_test.c_str() << std::endl;
            break;
        }
    }

}

template<int I>
inline void print_num()
{
    int ___ = 0;
    std::cout << "sU: " << I << std::endl;
}

int void__(char* ptr)
{
    std::cout << "void" << std::endl;
    return 1;
}

#ifdef __IS_CPP

int main()
{
    std::cout << "main " << std::endl;
    std::cout << singleton::instance() <<std::endl;

    std::map<std::string, dict_item::handler_type> binary_map;
    typedef hl::dfa_compiler<std::vector<char>, dict_item::handler_type > dfa_type_vc;
    struct __Test
    {   static void on_()
        {   std::cout << "Ok" << std::endl;}};

    dfa_type_vc vv;
    vv.insert(std::vector<char>(), &__Test::on_);
    vv.insert(std::vector<char>(), &__Test::on_);

    typedef hl::dfa_compiler<std::string, dict_item::handler_type > dfa_type;
    hl::dfa_compiler<std::string, dict_item::handler_type > dfa_, dfa_bugtest;

    dfa_bugtest.insert("9a9", &__Test::on_);
    dfa_bugtest.insert("99a99", &__Test::on_);
    //dfa_bugtest.insert("ameg", &__Test::on_);
    //dfa_bugtest.insert("amegu", &__Test::on_);

    dfa_bugtest.compile_binary();
    test_binary(dfa_bugtest, std::string("9a9"), dfa_bugtest.binary_start());

    return 0;
    std::list<std::string> appliers;
    enum
    {   countaddition_items = 20000};
    int cnt_add = 0, index = countaddition_items;
    for (;cnt_add<countaddition_items; ++cnt_add)
    for (dict_item* cur = dict;
            cur != hl::end_(dict); ++cur )
    {
        std::stringstream ss;
        ss << cnt_add << cur->key_.c_str() << cnt_add;
        std::string applier = /*cur->key_ +*/ss.str();
        //std::cout << applier.c_str() << std::endl;
        appliers.push_back(applier);
        dfa_.insert(applier, cur->handler_);
        binary_map[applier] = cur->handler_;
    }
    std::cout << " start test " << binary_map.size() << std::endl;
    dfa_.compile_binary();
    typename dfa_type::binary_node_type* position = dfa_.binary_start();
    enum
    {   countrepeat = 2};
    int V = countrepeat;
    int __1 = clock();
    while (--V)
    for (std::list<std::string>::iterator applier = appliers.begin();
            applier != appliers.end(); ++applier)
    {
        dfa_.current_ = 0;
        test_binary(dfa_, *applier, position);
    }

    int __2 = clock();
    V = countrepeat;
    while (--V)
    for (std::list<std::string>::iterator applier = appliers.begin();
            applier != appliers.end(); ++applier)
    {
        dict_item::handler_type h = binary_map[*applier];
        if (h)
        (h)();
        else std::cout << "!!!!!!!!!!!!!" << std::endl;
    }
    int __3 = clock();
    std::cout << "auto: " << __2 - __1 << ", binary: " << __3 - __2 << std::endl;
    return 0;
}

#endif

template<typename _Dfa_type, typename _Type_check>
inline void test_(_Dfa_type &dfa_, _Type_check const& mega_test)
{
    typedef _Dfa_type dfa_type;

    typename dfa_type::iterator *cur_ = 0;
    for (typename _Type_check::const_iterator where = mega_test.begin(); where
            != mega_test.end(); ++where)
    {
        cur_ = dfa_.move(*where);

        if (cur_ && cur_->is_value_)
            (cur_->value_)();
        else if (!cur_)
        {
            std::cout << "not found!!!" << std::endl;
            break;
        }
    }

}

template<typename dfa_type>
inline void print_dfa(dfa_type& dfa_)
{
    print_dfa(dfa_.ranges_.begin(), dfa_.ranges_.end());
}

template<typename dfa_type_iterator>
inline void print_dfa(dfa_type_iterator begin, dfa_type_iterator end)
{
    for (dfa_type_iterator where = begin; where != end; ++where)
    {
        std::cout << " {" << (*where).first.id_ << "(" << (*where).first.id_
                << ")" << ":" << ((*where).first.jump_ ? (*where).first.jump_
                : '$') << "} " << std::flush;
    }

    std::cout << std::endl;
}

#if defined(__ENABLE_RULES)
SYNTAX_RULES()

RULE(any_string) char_rule() & (char_rule() | digit_rule());
RULE(variable) "$" & any_string_rule();
RULE(range_syntax_token) "{" & digits_rule() & "}";

END_SYNTAX_RULES()
#endif

#define REMOVE_PARENCESS_SRC_CODE(...)	\
   #__VA_ARGS__

#define COMPILE_(name_, src) \
		REMOVE_PARENCESS_SRC_CODE src

static std::string
        src =
                COMPILE_(mans_code,
                        (
                                template
                                <typename Prefixer>
                                struct MansParsing
                                {
                                    $prefix_string : Prefixer.$prefix?
                                    rule_string;

                                    $name(string cxx) : ($first_name=prefix_string($second_name=Prefixer.$prefix?string)?);

                                    $man_description(string cxx)
                                    : $name($lem=~$email)?
                                    | $jump<$name>(cxx)
                                    ;

                                    $mans_description : $man_description
                                    ($emails[]=$man_description.$email_right)
                                    | $mans_description $man_description;
                                };

                                struct EnglandPrefix
                                {
                                    $Prefix : "Mr."|"sir.";
                                };

                                struct RussianPrefix
                                {
                                    $Prefix
                                    : "Ув."
                                    |"Уважаемый"
                                    |"Дорогой"
                                    |"Достопочтенный"
                                    |&"Др.?гр"
                                    :
                                    {
                                        action<style>()->set_time
                                        (calculate_time_beginer(L"Достопочтенный"));
                                    }
                                    ;
                                };

                                type_array<RussianPrefix>() = "rus";
                                Mans
                        ));
#endif // COMPRESSED_DFA_JDHFGJDHFGJCNVXVVHJDHFGDHFJGDFJG
