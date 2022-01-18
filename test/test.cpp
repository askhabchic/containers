// -*- C++ -*-
//===------------------------------ vector --------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include <iterator>
#include <vector>

#ifndef _LIBCPP_VECTOR
#define _LIBCPP_VECTOR

/*
    vector synopsis

namespace std
{

template <class T, class Allocator = allocator<T> >
class vector
{
public:
    typedef T                                        value_type;
    typedef Allocator                                allocator_type;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef implementation-defined                   iterator;
    typedef implementation-defined                   const_iterator;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef std::reverse_iterator<iterator>          reverse_iterator;
    typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;

    vector()
        noexcept(is_nothrow_default_constructible<allocator_type>::value);
    explicit vector(const allocator_type&);
    explicit vector(size_type n);
    explicit vector(size_type n, const allocator_type&); // C++14
    vector(size_type n, const value_type& value, const allocator_type& = allocator_type());
    template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type& = allocator_type());
    vector(const vector& x);
    vector(vector&& x)
        noexcept(is_nothrow_move_constructible<allocator_type>::value);
    vector(initializer_list<value_type> il);
    vector(initializer_list<value_type> il, const allocator_type& a);
    ~vector();
    vector& operator=(const vector& x);
    vector& operator=(vector&& x)
        noexcept(
             allocator_type::propagate_on_container_move_assignment::value ||
             allocator_type::is_always_equal::value); // C++17
    vector& operator=(initializer_list<value_type> il);
    template <class InputIterator>
        void assign(InputIterator first, InputIterator last);
    void assign(size_type n, const value_type& u);
    void assign(initializer_list<value_type> il);

    allocator_type get_allocator() const noexcept;

    iterator               begin() noexcept;
    const_iterator         begin()   const noexcept;
    iterator               end() noexcept;
    const_iterator         end()     const noexcept;

    reverse_iterator       rbegin() noexcept;
    const_reverse_iterator rbegin()  const noexcept;
    reverse_iterator       rend() noexcept;
    const_reverse_iterator rend()    const noexcept;

    const_iterator         cbegin()  const noexcept;
    const_iterator         cend()    const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend()   const noexcept;

    size_type size() const noexcept;
    size_type max_size() const noexcept;
    size_type capacity() const noexcept;
    bool empty() const noexcept;
    void reserve(size_type n);
    void shrink_to_fit() noexcept;

    reference       operator[](size_type n);
    const_reference operator[](size_type n) const;
    reference       at(size_type n);
    const_reference at(size_type n) const;

    reference       front();
    const_reference front() const;
    reference       back();
    const_reference back() const;

    value_type*       data() noexcept;
    const value_type* data() const noexcept;

    void push_back(const value_type& x);
    void push_back(value_type&& x);
    template <class... Args>
        reference emplace_back(Args&&... args); // reference in C++17
    void pop_back();

    template <class... Args> iterator emplace(const_iterator position, Args&&... args);
    iterator insert(const_iterator position, const value_type& x);
    iterator insert(const_iterator position, value_type&& x);
    iterator insert(const_iterator position, size_type n, const value_type& x);
    template <class InputIterator>
        iterator insert(const_iterator position, InputIterator first, InputIterator last);
    iterator insert(const_iterator position, initializer_list<value_type> il);

    iterator erase(const_iterator position);
    iterator erase(const_iterator first, const_iterator last);

    void clear() noexcept;

    void resize(size_type sz);
    void resize(size_type sz, const value_type& c);

    void swap(vector&)
        noexcept(allocator_traits<allocator_type>::propagate_on_container_swap::value ||
                 allocator_traits<allocator_type>::is_always_equal::value);  // C++17

    bool __invariants() const;
};

template <class Allocator = allocator<T> >
class vector<bool, Allocator>
{
public:
    typedef bool                                     value_type;
    typedef Allocator                                allocator_type;
    typedef implementation-defined                   iterator;
    typedef implementation-defined                   const_iterator;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef iterator                                 pointer;
    typedef const_iterator                           const_pointer;
    typedef std::reverse_iterator<iterator>          reverse_iterator;
    typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;

    class reference
    {
    public:
        reference(const reference&) noexcept;
        operator bool() const noexcept;
        reference& operator=(const bool x) noexcept;
        reference& operator=(const reference& x) noexcept;
        iterator operator&() const noexcept;
        void flip() noexcept;
    };

    class const_reference
    {
    public:
        const_reference(const reference&) noexcept;
        operator bool() const noexcept;
        const_iterator operator&() const noexcept;
    };

    vector()
        noexcept(is_nothrow_default_constructible<allocator_type>::value);
    explicit vector(const allocator_type&);
    explicit vector(size_type n, const allocator_type& a = allocator_type()); // C++14
    vector(size_type n, const value_type& value, const allocator_type& = allocator_type());
    template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type& = allocator_type());
    vector(const vector& x);
    vector(vector&& x)
        noexcept(is_nothrow_move_constructible<allocator_type>::value);
    vector(initializer_list<value_type> il);
    vector(initializer_list<value_type> il, const allocator_type& a);
    ~vector();
    vector& operator=(const vector& x);
    vector& operator=(vector&& x)
        noexcept(
             allocator_type::propagate_on_container_move_assignment::value ||
             allocator_type::is_always_equal::value); // C++17
    vector& operator=(initializer_list<value_type> il);
    template <class InputIterator>
        void assign(InputIterator first, InputIterator last);
    void assign(size_type n, const value_type& u);
    void assign(initializer_list<value_type> il);

    allocator_type get_allocator() const noexcept;

    iterator               begin() noexcept;
    const_iterator         begin()   const noexcept;
    iterator               end() noexcept;
    const_iterator         end()     const noexcept;

    reverse_iterator       rbegin() noexcept;
    const_reverse_iterator rbegin()  const noexcept;
    reverse_iterator       rend() noexcept;
    const_reverse_iterator rend()    const noexcept;

    const_iterator         cbegin()  const noexcept;
    const_iterator         cend()    const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend()   const noexcept;

    size_type size() const noexcept;
    size_type max_size() const noexcept;
    size_type capacity() const noexcept;
    bool empty() const noexcept;
    void reserve(size_type n);
    void shrink_to_fit() noexcept;

    reference       operator[](size_type n);
    const_reference operator[](size_type n) const;
    reference       at(size_type n);
    const_reference at(size_type n) const;

    reference       front();
    const_reference front() const;
    reference       back();
    const_reference back() const;

    void push_back(const value_type& x);
    template <class... Args> reference emplace_back(Args&&... args);  // C++14; reference in C++17
    void pop_back();

    template <class... Args> iterator emplace(const_iterator position, Args&&... args);  // C++14
    iterator insert(const_iterator position, const value_type& x);
    iterator insert(const_iterator position, size_type n, const value_type& x);
    template <class InputIterator>
        iterator insert(const_iterator position, InputIterator first, InputIterator last);
    iterator insert(const_iterator position, initializer_list<value_type> il);

    iterator erase(const_iterator position);
    iterator erase(const_iterator first, const_iterator last);

    void clear() noexcept;

    void resize(size_type sz);
    void resize(size_type sz, value_type x);

    void swap(vector&)
        noexcept(allocator_traits<allocator_type>::propagate_on_container_swap::value ||
                 allocator_traits<allocator_type>::is_always_equal::value);  // C++17
    void flip() noexcept;

    bool __invariants() const;
};

template <class InputIterator, class Allocator = allocator<typename iterator_traits<InputIterator>::value_type>>
   vector(InputIterator, InputIterator, Allocator = Allocator())
   -> vector<typename iterator_traits<InputIterator>::value_type, Allocator>;

template <class Allocator> struct hash<std::vector<bool, Allocator>>;

template <class T, class Allocator> bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
template <class T, class Allocator> bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y);
template <class T, class Allocator> bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
template <class T, class Allocator> bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y);
template <class T, class Allocator> bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
template <class T, class Allocator> bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);

template <class T, class Allocator>
void swap(vector<T,Allocator>& x, vector<T,Allocator>& y)
    noexcept(noexcept(x.swap(y)));

template <class T, class Allocator, class U>
    void erase(vector<T, Allocator>& c, const U& value);       // C++20
template <class T, class Allocator, class Predicate>
    void erase_if(vector<T, Allocator>& c, Predicate pred);    // C++20

}  // std

*/

#include <__config>
#include <iosfwd> // for forward declaration of vector
#include <__bit_reference>
#include <type_traits>
#include <climits>
#include <limits>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <cstring>
#include <__cxx_version>
#include <__split_buffer>
#include <__functional_base>

#include <__debug>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_PUSH_MACROS
#include <__undef_macros>


_LIBCPP_BEGIN_NAMESPACE_STD

template <bool>
class __vector_base_common
{
protected:
 __vector_base_common() {}
    void __throw_length_error() const;
    void __throw_out_of_range() const;
};

template <bool __b>
void
__vector_base_common<__b>::__throw_length_error() const
{
    _VSTD::__throw_length_error("vector");
}

template <bool __b>
void
__vector_base_common<__b>::__throw_out_of_range() const
{
    _VSTD::__throw_out_of_range("vector");
}

template <class _Tp, class _Allocator>
class __vector_base
    : protected __vector_base_common<true>
{
public:
    typedef _Allocator                               allocator_type;
    typedef allocator_traits<allocator_type>         __alloc_traits;
    typedef typename __alloc_traits::size_type       size_type;
protected:
    typedef _Tp                                      value_type;
    typedef value_type&                              reference;
    typedef const value_type&                        const_reference;
    typedef typename __alloc_traits::difference_type difference_type;
    typedef typename __alloc_traits::pointer         pointer;
    typedef typename __alloc_traits::const_pointer   const_pointer;
    typedef pointer                                  iterator;
    typedef const_pointer                            const_iterator;

    pointer                                         __begin_;
    pointer                                         __end_;
    __compressed_pair<pointer, allocator_type> __end_cap_;


    allocator_type& __alloc() _NOEXCEPT
        {return __end_cap_.second();}

    const allocator_type& __alloc() const _NOEXCEPT
        {return __end_cap_.second();}

    pointer& __end_cap() _NOEXCEPT
        {return __end_cap_.first();}

    const pointer& __end_cap() const _NOEXCEPT
        {return __end_cap_.first();}


    __vector_base()
        _NOEXCEPT_(is_nothrow_default_constructible<allocator_type>::value);
 __vector_base(const allocator_type& __a);
#ifndef _LIBCPP_CXX03_LANG
 __vector_base(allocator_type&& __a) _NOEXCEPT;
#endif
    ~__vector_base();


    void clear()  {__destruct_at_end(__begin_);}

    size_type capacity() const 
        {return static_cast<size_type>(__end_cap() - __begin_);}


    void __destruct_at_end(pointer __new_last) ;


    void __copy_assign_alloc(const __vector_base& __c)
        {__copy_assign_alloc(__c, integral_constant<bool,
                      __alloc_traits::propagate_on_container_copy_assignment::value>());}


    void __move_assign_alloc(__vector_base& __c)
        _(
            !__alloc_traits::propagate_on_container_move_assignment::value ||
            is_nothrow_move_assignable<allocator_type>::value)
        {__move_assign_alloc(__c, integral_constant<bool,
                      __alloc_traits::propagate_on_container_move_assignment::value>());}
private:
    
    void __copy_assign_alloc(const __vector_base& __c, true_type)
        {
            if (__alloc() != __c.__alloc())
            {
                clear();
                __alloc_traits::deallocate(__alloc(), __begin_, capacity());
                __begin_ = __end_ = __end_cap() = nullptr;
            }
            __alloc() = __c.__alloc();
        }


    void __copy_assign_alloc(const __vector_base&, false_type)
        {}


    void __move_assign_alloc(__vector_base& __c, true_type)
        _(is_nothrow_move_assignable<allocator_type>::value)
        {
            __alloc() = _VSTD::move(__c.__alloc());
        }


    void __move_assign_alloc(__vector_base&, false_type)
        
        {}
};

template <class _Tp, class _Allocator>
inline
void
__vector_base<_Tp, _Allocator>::__destruct_at_end(pointer __new_last) 
{
    pointer __soon_to_be_end = __end_;
    while (__new_last != __soon_to_be_end)
        __alloc_traits::destroy(__alloc(), _VSTD::__to_raw_pointer(--__soon_to_be_end));
    __end_ = __new_last;
}

template <class _Tp, class _Allocator>
inline
__vector_base<_Tp, _Allocator>::__vector_base()
        _(is_nothrow_default_constructible<allocator_type>::value)
    : __begin_(nullptr),
      __end_(nullptr),
      __end_cap_(nullptr)
{
}

template <class _Tp, class _Allocator>
inline
__vector_base<_Tp, _Allocator>::__vector_base(const allocator_type& __a)
    : __begin_(nullptr),
      __end_(nullptr),
      __end_cap_(nullptr, __a)
{
}

#ifndef _LIBCPP_CXX03_LANG
template <class _Tp, class _Allocator>
inline
__vector_base<_Tp, _Allocator>::__vector_base(allocator_type&& __a) 
    : __begin_(nullptr),
      __end_(nullptr),
      __end_cap_(nullptr, std::move(__a)) {}
#endif

template <class _Tp, class _Allocator>
__vector_base<_Tp, _Allocator>::~__vector_base()
{
    if (__begin_ != nullptr)
    {
        clear();
        __alloc_traits::deallocate(__alloc(), __begin_, capacity());
    }
}

template <class _Tp, class _Allocator /* = allocator<_Tp> */>
class _LIBCPP_TEMPLATE_VIS vector
    : private __vector_base<_Tp, _Allocator>
{
private:
    typedef __vector_base<_Tp, _Allocator>           __base;
    typedef allocator<_Tp>                           __default_allocator_type;
public:
    typedef vector                                   __self;
    typedef _Tp                                      value_type;
    typedef _Allocator                               allocator_type;
    typedef typename __base::__alloc_traits          __alloc_traits;
    typedef typename __base::reference               reference;
    typedef typename __base::const_reference         const_reference;
    typedef typename __base::size_type               size_type;
    typedef typename __base::difference_type         difference_type;
    typedef typename __base::pointer                 pointer;
    typedef typename __base::const_pointer           const_pointer;
    typedef __wrap_iter<pointer>                     iterator;
    typedef __wrap_iter<const_pointer>               const_iterator;
    typedef _VSTD::reverse_iterator<iterator>         reverse_iterator;
    typedef _VSTD::reverse_iterator<const_iterator>   const_reverse_iterator;

    static_assert((is_same<typename allocator_type::value_type, value_type>::value),
                  "Allocator::value_type must be same type as value_type");


    vector() _(is_nothrow_default_constructible<allocator_type>::value){ }
 
 explicit vector(const allocator_type& __a)
        : __base(__a){}
    explicit vector(size_type __n);
    vector(size_type __n, const value_type& __x);
    vector(size_type __n, const value_type& __x, const allocator_type& __a);
    template <class _InputIterator>
        vector(_InputIterator __first,
               typename enable_if<__is_input_iterator  <_InputIterator>::value &&
                                 !__is_forward_iterator<_InputIterator>::value &&
                                 is_constructible<
                                    value_type,
                                    typename iterator_traits<_InputIterator>::reference>::value,
                                 _InputIterator>::type __last);
    template <class _InputIterator>
        vector(_InputIterator __first, _InputIterator __last, const allocator_type& __a,
               typename enable_if<__is_input_iterator  <_InputIterator>::value &&
                                 !__is_forward_iterator<_InputIterator>::value &&
                                 is_constructible<
                                    value_type,
                                    typename iterator_traits<_InputIterator>::reference>::value>::type* = 0);
    template <class _ForwardIterator>
        vector(_ForwardIterator __first,
               typename enable_if<__is_forward_iterator<_ForwardIterator>::value &&
                                 is_constructible<
                                    value_type,
                                    typename iterator_traits<_ForwardIterator>::reference>::value,
                                 _ForwardIterator>::type __last);
    template <class _ForwardIterator>
        vector(_ForwardIterator __first, _ForwardIterator __last, const allocator_type& __a,
               typename enable_if<__is_forward_iterator<_ForwardIterator>::value &&
                                 is_constructible<
                                    value_type,
                                    typename iterator_traits<_ForwardIterator>::reference>::value>::type* = 0);


    ~vector()    { __annotate_delete();    }

    vector(const vector& __x);
    vector(const vector& __x, const allocator_type& __a);

    vector& operator=(const vector& __x);

#ifndef _LIBCPP_CXX03_LANG

    vector(initializer_list<value_type> __il);


    vector(initializer_list<value_type> __il, const allocator_type& __a);


    vector(vector&& __x)
        _(is_nothrow_move_constructible<allocator_type>::value);
#endif


    vector(vector&& __x, const allocator_type& __a);

    vector& operator=(vector&& __x)
        _((__move_assign_container<_Allocator, __alloc_traits>::value));


    vector& operator=(initializer_list<value_type> __il)
        {assign(__il.begin(), __il.end()); return *this;}

#endif  // !_LIBCPP_CXX03_LANG

    template <class _InputIterator>
        typename enable_if
        <
             __is_input_iterator  <_InputIterator>::value &&
            !__is_forward_iterator<_InputIterator>::value &&
            is_constructible<
                 value_type,
                 typename iterator_traits<_InputIterator>::reference>::value,
            void
        >::type
        assign(_InputIterator __first, _InputIterator __last);
    template <class _ForwardIterator>
        typename enable_if
        <
            __is_forward_iterator<_ForwardIterator>::value &&
            is_constructible<
                 value_type,
                 typename iterator_traits<_ForwardIterator>::reference>::value,
            void
        >::type
        assign(_ForwardIterator __first, _ForwardIterator __last);

    void assign(size_type __n, const_reference __u);

#ifndef _LIBCPP_CXX03_LANG

    void assign(initializer_list<value_type> __il)
        {assign(__il.begin(), __il.end());}
#endif


    allocator_type get_allocator() const 
        {return this->__alloc();}

 iterator               begin() ;
 const_iterator         begin()   const ;
 iterator               end() ;
 const_iterator         end()     const ;


    reverse_iterator       rbegin() 
        {return       reverse_iterator(end());}

    const_reverse_iterator rbegin()  const 
        {return const_reverse_iterator(end());}

    reverse_iterator       rend() 
        {return       reverse_iterator(begin());}

    const_reverse_iterator rend()    const 
        {return const_reverse_iterator(begin());}


    const_iterator         cbegin()  const 
        {return begin();}

    const_iterator         cend()    const 
        {return end();}

    const_reverse_iterator crbegin() const 
        {return rbegin();}

    const_reverse_iterator crend()   const 
        {return rend();}


    size_type size() const 
        {return static_cast<size_type>(this->__end_ - this->__begin_);}

    size_type capacity() const 
        {return __base::capacity();}
    bool empty() const 
        {return this->__begin_ == this->__end_;}
    size_type max_size() const ;
    void reserve(size_type __n);
    void shrink_to_fit() ;

 reference       operator[](size_type __n);
 const_reference operator[](size_type __n) const;
    reference       at(size_type __n);
    const_reference at(size_type __n) const;

 reference       front()    {
        return *this->__begin_;
}

const_reference front() const  {
        return *this->__begin_;
}

reference       back()    {
        return *(this->__end_ - 1);
}

const_reference back()  const    {
        return *(this->__end_ - 1);
}


value_type*       data()        {
	return _VSTD::__to_raw_pointer(this->__begin_);
}

const value_type* data() const        {
	return _VSTD::__to_raw_pointer(this->__begin_);
}

#ifdef _LIBCPP_CXX03_LANG

    void __emplace_back(const value_type& __x) { push_back(__x); }
#else
    template <class _Arg>

    void __emplace_back(_Arg&& __arg) {
      emplace_back(_VSTD::forward<_Arg>(__arg));
    }
#endif

 void push_back(const_reference __x);

#ifndef _LIBCPP_CXX03_LANG
 void push_back(value_type&& __x);

    template <class... _Args>
    
#if _LIBCPP_STD_VER > 14
        reference emplace_back(_Args&&... __args);
#else
        void      emplace_back(_Args&&... __args);
#endif
#endif // !_LIBCPP_CXX03_LANG


void pop_back();

iterator insert(const_iterator __position, const_reference __x);

#ifndef _LIBCPP_CXX03_LANG
    iterator insert(const_iterator __position, value_type&& __x);
    template <class... _Args>
        iterator emplace(const_iterator __position, _Args&&... __args);
#endif  // !_LIBCPP_CXX03_LANG

    iterator insert(const_iterator __position, size_type __n, const_reference __x);
    template <class _InputIterator>
        typename enable_if
        <
             __is_input_iterator  <_InputIterator>::value &&
            !__is_forward_iterator<_InputIterator>::value &&
            is_constructible<
                 value_type,
                 typename iterator_traits<_InputIterator>::reference>::value,
            iterator
        >::type
        insert(const_iterator __position, _InputIterator __first, _InputIterator __last);
    template <class _ForwardIterator>
        typename enable_if
        <
            __is_forward_iterator<_ForwardIterator>::value &&
            is_constructible<
                 value_type,
                 typename iterator_traits<_ForwardIterator>::reference>::value,
            iterator
        >::type
        insert(const_iterator __position, _ForwardIterator __first, _ForwardIterator __last);

#ifndef _LIBCPP_CXX03_LANG

    iterator insert(const_iterator __position, initializer_list<value_type> __il)
        {return insert(__position, __il.begin(), __il.end());}
#endif

 iterator erase(const_iterator __position);
    iterator erase(const_iterator __first, const_iterator __last);


    void clear() 
    {
        size_type __old_size = size();
        __base::clear();
        __annotate_shrink(__old_size);
        __invalidate_all_iterators();
    }

    void resize(size_type __sz);
    void resize(size_type __sz, const_reference __x);

    void swap(vector&);

_DEBUG_(!__alloc_traits::propagate_on_container_swap::value || __is_nothrow_swappable<allocator_type>::value);

bool __invariants() const;

private:
 void __invalidate_all_iterators();
 void __invalidate_iterators_past(pointer __new_last);
    void __vallocate(size_type __n);
    void __vdeallocate() ;
 size_type __recommend(size_type __new_size) const;
    void __construct_at_end(size_type __n);

    void __construct_at_end(size_type __n, const_reference __x);
    template <class _ForwardIterator>
        typename enable_if
        <
            __is_forward_iterator<_ForwardIterator>::value,
            void
        >::type
        __construct_at_end(_ForwardIterator __first, _ForwardIterator __last, size_type __n);
    void __append(size_type __n);
    void __append(size_type __n, const_reference __x);

    iterator       __make_iter(pointer __p) ;

    const_iterator __make_iter(const_pointer __p) const ;
    void __swap_out_circular_buffer(__split_buffer<value_type, allocator_type&>& __v);
    pointer __swap_out_circular_buffer(__split_buffer<value_type, allocator_type&>& __v, pointer __p);
    void __move_range(pointer __from_s, pointer __from_e, pointer __to);
    void __move_assign(vector& __c, true_type)
        _(is_nothrow_move_assignable<allocator_type>::value);
    void __move_assign(vector& __c, false_type)
        _(__alloc_traits::is_always_equal::value);

    void __destruct_at_end(pointer __new_last) 
    {
        __invalidate_iterators_past(__new_last);
        size_type __old_size = size();
        __base::__destruct_at_end(__new_last);
        __annotate_shrink(__old_size);
    }

#ifndef _LIBCPP_CXX03_LANG
    template <class _Up> void __push_back_slow_path(_Up&& __x);

    template <class... _Args>
    void __emplace_back_slow_path(_Args&&... __args);
#else
    template <class _Up> void __push_back_slow_path(_Up& __x);
#endif

    // The following functions are no-ops outside of AddressSanitizer mode.
    // We call annotatations only for the default Allocator because other allocators
    // may not meet the AddressSanitizer alignment constraints.
    // See the documentation for __sanitizer_annotate_contiguous_container for more details.
#ifndef _LIBCPP_HAS_NO_ASAN
    void __annotate_contiguous_container(const void *__beg, const void *__end,
                                         const void *__old_mid,
                                         const void *__new_mid) const
    {

      if (__beg && is_same<allocator_type, __default_allocator_type>::value)
        __sanitizer_annotate_contiguous_container(__beg, __end, __old_mid, __new_mid);
    }
#else

    void __annotate_contiguous_container(const void*, const void*, const void*,
                                         const void*) const {}
#endif

    void __annotate_new(size_type __current_size) const {
      __annotate_contiguous_container(data(), data() + capacity(),
                                      data() + capacity(), data() + __current_size);
    }


    void __annotate_delete() const {
      __annotate_contiguous_container(data(), data() + capacity(),
                                      data() + size(), data() + capacity());
    }


    void __annotate_increase(size_type __n) const
    {
      __annotate_contiguous_container(data(), data() + capacity(),
                                      data() + size(), data() + size() + __n);
    }


    void __annotate_shrink(size_type __old_size) const
    {
      __annotate_contiguous_container(data(), data() + capacity(),
                                      data() + __old_size, data() + size());
    }
#ifndef _LIBCPP_HAS_NO_ASAN
    // The annotation for size increase should happen before the actual increase,
    // but if an exception is thrown after that the annotation has to be undone.
    struct __RAII_IncreaseAnnotator {
      __RAII_IncreaseAnnotator(const vector &__v, size_type __n = 1)
        : __commit(false), __v(__v), __old_size(__v.size() + __n) {
        __v.__annotate_increase(__n);
      }
      void __done() { __commit = true; }
      ~__RAII_IncreaseAnnotator() {
        if (__commit) return;
        __v.__annotate_shrink(__old_size);
      }
      bool __commit;
      const vector &__v;
      size_type __old_size;
    };
#else
    struct __RAII_IncreaseAnnotator {
    
      __RAII_IncreaseAnnotator(const vector &, size_type = 1) {}
     void __done() {}
    };
#endif

};

#ifndef _LIBCPP_HAS_NO_DEDUCTION_GUIDES
template<class _InputIterator,
         class _Alloc = typename std::allocator<typename iterator_traits<_InputIterator>::value_type>,
         class = typename enable_if<__is_allocator<_Alloc>::value, void>::type
         >
vector(_InputIterator, _InputIterator)
  -> vector<typename iterator_traits<_InputIterator>::value_type, _Alloc>;

template<class _InputIterator,
         class _Alloc,
         class = typename enable_if<__is_allocator<_Alloc>::value, void>::type
         >
vector(_InputIterator, _InputIterator, _Alloc)
  -> vector<typename iterator_traits<_InputIterator>::value_type, _Alloc>;
#endif

template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::__swap_out_circular_buffer(__split_buffer<value_type, allocator_type&>& __v)
{
    __annotate_delete();
    __alloc_traits::__construct_backward(this->__alloc(), this->__begin_, this->__end_, __v.__begin_);
    _VSTD::swap(this->__begin_, __v.__begin_);
    _VSTD::swap(this->__end_, __v.__end_);
    _VSTD::swap(this->__end_cap(), __v.__end_cap());
    __v.__first_ = __v.__begin_;
    __annotate_new(size());
    __invalidate_all_iterators();
}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::pointer
vector<_Tp, _Allocator>::__swap_out_circular_buffer(__split_buffer<value_type, allocator_type&>& __v, pointer __p)
{
    __annotate_delete();
    pointer __r = __v.__begin_;
    __alloc_traits::__construct_backward(this->__alloc(), this->__begin_, __p, __v.__begin_);
    __alloc_traits::__construct_forward(this->__alloc(), __p, this->__end_, __v.__end_);
    _VSTD::swap(this->__begin_, __v.__begin_);
    _VSTD::swap(this->__end_, __v.__end_);
    _VSTD::swap(this->__end_cap(), __v.__end_cap());
    __v.__first_ = __v.__begin_;
    __annotate_new(size());
    __invalidate_all_iterators();
    return __r;
}

//  Allocate space for __n objects
//  throws length_error if __n > max_size()
//  throws (probably bad_alloc) if memory run out
//  Precondition:  __begin_ == __end_ == __end_cap() == 0
//  Precondition:  __n > 0
//  Postcondition:  capacity() == __n
//  Postcondition:  size() == 0
template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::__vallocate(size_type __n)
{
    if (__n > max_size())
        this->__throw_length_error();
    this->__begin_ = this->__end_ = __alloc_traits::allocate(this->__alloc(), __n);
    this->__end_cap() = this->__begin_ + __n;
    __annotate_new(0);
}

template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::__vdeallocate() 
{
    if (this->__begin_ != nullptr)
    {
        clear();
        __alloc_traits::deallocate(this->__alloc(), this->__begin_, capacity());
        this->__begin_ = this->__end_ = this->__end_cap() = nullptr;
    }
}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::size_type
vector<_Tp, _Allocator>::max_size() const 
{
    return _VSTD::min<size_type>(__alloc_traits::max_size(this->__alloc()),
                                 numeric_limits<difference_type>::max());
}

//  Precondition:  __new_size > capacity()
template <class _Tp, class _Allocator>
inline
typename vector<_Tp, _Allocator>::size_type
vector<_Tp, _Allocator>::__recommend(size_type __new_size) const
{
    const size_type __ms = max_size();
    if (__new_size > __ms)
        this->__throw_length_error();
    const size_type __cap = capacity();
    if (__cap >= __ms / 2)
        return __ms;
    return _VSTD::max<size_type>(2*__cap, __new_size);
}

//  Default constructs __n objects starting at __end_
//  throws if construction throws
//  Precondition:  __n > 0
//  Precondition:  size() + __n <= capacity()
//  Postcondition:  size() == size() + __n
template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::__construct_at_end(size_type __n)
{
    allocator_type& __a = this->__alloc();
    do
    {
        __RAII_IncreaseAnnotator __annotator(*this);
        __alloc_traits::construct(__a, _VSTD::__to_raw_pointer(this->__end_));
        ++this->__end_;
        --__n;
        __annotator.__done();
    } while (__n > 0);
}

//  Copy constructs __n objects starting at __end_ from __x
//  throws if construction throws
//  Precondition:  __n > 0
//  Precondition:  size() + __n <= capacity()
//  Postcondition:  size() == old size() + __n
//  Postcondition:  [i] == __x for all i in [size() - __n, __n)
template <class _Tp, class _Allocator>
inline
void
vector<_Tp, _Allocator>::__construct_at_end(size_type __n, const_reference __x)
{
    allocator_type& __a = this->__alloc();
    do
    {
        __RAII_IncreaseAnnotator __annotator(*this);
        __alloc_traits::construct(__a, _VSTD::__to_raw_pointer(this->__end_), __x);
        ++this->__end_;
        --__n;
        __annotator.__done();
    } while (__n > 0);
}

template <class _Tp, class _Allocator>
template <class _ForwardIterator>
typename enable_if
<
    __is_forward_iterator<_ForwardIterator>::value,
    void
>::type
vector<_Tp, _Allocator>::__construct_at_end(_ForwardIterator __first, _ForwardIterator __last, size_type __n)
{
    allocator_type& __a = this->__alloc();
    __RAII_IncreaseAnnotator __annotator(*this, __n);
    __alloc_traits::__construct_range_forward(__a, __first, __last, this->__end_);
    __annotator.__done();
}

//  Default constructs __n objects starting at __end_
//  throws if construction throws
//  Postcondition:  size() == size() + __n
//  Exception safety: strong.
template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::__append(size_type __n)
{
    if (static_cast<size_type>(this->__end_cap() - this->__end_) >= __n)
        this->__construct_at_end(__n);
    else
    {
        allocator_type& __a = this->__alloc();
        __split_buffer<value_type, allocator_type&> __v(__recommend(size() + __n), size(), __a);
        __v.__construct_at_end(__n);
        __swap_out_circular_buffer(__v);
    }
}

//  Default constructs __n objects starting at __end_
//  throws if construction throws
//  Postcondition:  size() == size() + __n
//  Exception safety: strong.
template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::__append(size_type __n, const_reference __x)
{
    if (static_cast<size_type>(this->__end_cap() - this->__end_) >= __n)
        this->__construct_at_end(__n, __x);
    else
    {
        allocator_type& __a = this->__alloc();
        __split_buffer<value_type, allocator_type&> __v(__recommend(size() + __n), size(), __a);
        __v.__construct_at_end(__n, __x);
        __swap_out_circular_buffer(__v);
    }
}

template <class _Tp, class _Allocator>
vector<_Tp, _Allocator>::vector(size_type __n) {
    if (__n > 0)    {
        __vallocate(__n);
        __construct_at_end(__n);
    }
}


template <class _Tp, class _Allocator>
vector<_Tp, _Allocator>::vector(size_type __n, const value_type& __x) {
    if (__n > 0)    {
        __vallocate(__n);
        __construct_at_end(__n, __x);
    }
}

template <class _Tp, class _Allocator>
vector<_Tp, _Allocator>::vector(size_type __n, const value_type& __x, const allocator_type& __a) : __base(__a) {
    if (__n > 0)    {
        __vallocate(__n);
        __construct_at_end(__n, __x);
    }
}

template <class _Tp, class _Allocator>
template <class _InputIterator>
vector<_Tp, _Allocator>::vector(_InputIterator __first,
       typename enable_if<__is_input_iterator  <_InputIterator>::value &&
                         !__is_forward_iterator<_InputIterator>::value &&
                         is_constructible<
                            value_type,
                            typename iterator_traits<_InputIterator>::reference>::value,
                          _InputIterator>::type __last)
{
    for (; __first != __last; ++__first)
        __emplace_back(*__first);
}

template <class _Tp, class _Allocator>
template <class _InputIterator>
vector<_Tp, _Allocator>::vector(_InputIterator __first, _InputIterator __last, const allocator_type& __a,
       typename enable_if<__is_input_iterator  <_InputIterator>::value &&
                         !__is_forward_iterator<_InputIterator>::value &&
                         is_constructible<
                            value_type,
                            typename iterator_traits<_InputIterator>::reference>::value>::type*)
    : __base(__a)
{
    for (; __first != __last; ++__first)
        __emplace_back(*__first);
}

template <class _Tp, class _Allocator>
template <class _ForwardIterator>
vector<_Tp, _Allocator>::vector(_ForwardIterator __first,
                                typename enable_if<__is_forward_iterator<_ForwardIterator>::value &&
                                is_constructible<
                                   value_type,
                                   typename iterator_traits<_ForwardIterator>::reference>::value,
                                                   _ForwardIterator>::type __last)
{
    size_type __n = static_cast<size_type>(_VSTD::distance(__first, __last));
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__first, __last, __n);
    }
}

template <class _Tp, class _Allocator>
template <class _ForwardIterator>
vector<_Tp, _Allocator>::vector(_ForwardIterator __first, _ForwardIterator __last, const allocator_type& __a,
                                typename enable_if<__is_forward_iterator<_ForwardIterator>::value &&
                                is_constructible<
                                   value_type,
                                   typename iterator_traits<_ForwardIterator>::reference>::value>::type*)
    : __base(__a)
{
    size_type __n = static_cast<size_type>(_VSTD::distance(__first, __last));
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__first, __last, __n);
    }
}

template <class _Tp, class _Allocator>
vector<_Tp, _Allocator>::vector(const vector& __x)
    : __base(__alloc_traits::select_on_container_copy_construction(__x.__alloc()))
{
    size_type __n = __x.size();
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__x.__begin_, __x.__end_, __n);
    }
}

template <class _Tp, class _Allocator>
vector<_Tp, _Allocator>::vector(const vector& __x, const allocator_type& __a)
    : __base(__a)
{
    size_type __n = __x.size();
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__x.__begin_, __x.__end_, __n);
    }
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Tp, class _Allocator>
inline
vector<_Tp, _Allocator>::vector(vector&& __x)
        _(is_nothrow_move_constructible<allocator_type>::value)
    : __base(_VSTD::move(__x.__alloc()))
{
    this->__begin_ = __x.__begin_;
    this->__end_ = __x.__end_;
    this->__end_cap() = __x.__end_cap();
    __x.__begin_ = __x.__end_ = __x.__end_cap() = nullptr;
}

template <class _Tp, class _Allocator>
inline
vector<_Tp, _Allocator>::vector(vector&& __x, const allocator_type& __a)
    : __base(__a)
{
    if (__a == __x.__alloc())    {
        this->__begin_ = __x.__begin_;
        this->__end_ = __x.__end_;
        this->__end_cap() = __x.__end_cap();
        __x.__begin_ = __x.__end_ = __x.__end_cap() = nullptr;
    }
    else    {
        typedef move_iterator<iterator> _Ip;
        assign(_Ip(__x.begin()), _Ip(__x.end()));
    }
}

template <class _Tp, class _Allocator>
inline
vector<_Tp, _Allocator>::vector(initializer_list<value_type> __il) {
    if (__il.size() > 0)    {
        __vallocate(__il.size());
        __construct_at_end(__il.begin(), __il.end(), __il.size());
    }
}

template <class _Tp, class _Allocator>
inline
vector<_Tp, _Allocator>::vector(initializer_list<value_type> __il, const allocator_type& __a)
    : __base(__a)
{
    if (__il.size() > 0)    {
        __vallocate(__il.size());
        __construct_at_end(__il.begin(), __il.end(), __il.size());
    }
}

template <class _Tp, class _Allocator>
inline
vector<_Tp, _Allocator>&
vector<_Tp, _Allocator>::operator=(vector&& __x)
    _((__move_assign_container<_Allocator, __alloc_traits>::value))
{
    __move_assign(__x, integral_constant<bool,
          __alloc_traits::propagate_on_container_move_assignment::value>());
    return *this;
}

template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::__move_assign(vector& __c, false_type)
    _(__alloc_traits::is_always_equal::value)
{
    if (__base::__alloc() != __c.__alloc())
    {
        typedef move_iterator<iterator> _Ip;
        assign(_Ip(__c.begin()), _Ip(__c.end()));
    }
    else
        __move_assign(__c, true_type());
}

template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::__move_assign(vector& __c, true_type)
    _(is_nothrow_move_assignable<allocator_type>::value)
{
    __vdeallocate();
    __base::__move_assign_alloc(__c); // this can throw
    this->__begin_ = __c.__begin_;
    this->__end_ = __c.__end_;
    this->__end_cap() = __c.__end_cap();
    __c.__begin_ = __c.__end_ = __c.__end_cap() = nullptr;
}

#endif  // !_LIBCPP_CXX03_LANG

template <class _Tp, class _Allocator>
inline
vector<_Tp, _Allocator>&
vector<_Tp, _Allocator>::operator=(const vector& __x)
{
    if (this != &__x)
    {
        __base::__copy_assign_alloc(__x);
        assign(__x.__begin_, __x.__end_);
    }
    return *this;
}

template <class _Tp, class _Allocator>
template <class _InputIterator>
typename enable_if
<
     __is_input_iterator  <_InputIterator>::value &&
    !__is_forward_iterator<_InputIterator>::value &&
    is_constructible<
       _Tp,
       typename iterator_traits<_InputIterator>::reference>::value,
    void
>::type
vector<_Tp, _Allocator>::assign(_InputIterator __first, _InputIterator __last)
{
    clear();
    for (; __first != __last; ++__first)
        __emplace_back(*__first);
}

template <class _Tp, class _Allocator>
template <class _ForwardIterator>
typename enable_if
<
    __is_forward_iterator<_ForwardIterator>::value &&
    is_constructible<
       _Tp,
       typename iterator_traits<_ForwardIterator>::reference>::value,
    void
>::type
vector<_Tp, _Allocator>::assign(_ForwardIterator __first, _ForwardIterator __last)
{
    size_type __new_size = static_cast<size_type>(_VSTD::distance(__first, __last));
    if (__new_size <= capacity())
    {
        _ForwardIterator __mid = __last;
        bool __growing = false;
        if (__new_size > size())
        {
            __growing = true;
            __mid =  __first;
            _VSTD::advance(__mid, size());
        }
        pointer __m = _VSTD::copy(__first, __mid, this->__begin_);
        if (__growing)
            __construct_at_end(__mid, __last, __new_size - size());
        else
            this->__destruct_at_end(__m);
    }
    else
    {
        __vdeallocate();
        __vallocate(__recommend(__new_size));
        __construct_at_end(__first, __last, __new_size);
    }
    __invalidate_all_iterators();
}

template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::assign(size_type __n, const_reference __u) {
    if (__n <= capacity())    {
        size_type __s = size();
        _VSTD::fill_n(this->__begin_, _VSTD::min(__n, __s), __u);
        if (__n > __s)
            __construct_at_end(__n - __s, __u);
        else
            this->__destruct_at_end(this->__begin_ + __n);
    }
    else    {
        __vdeallocate();
        __vallocate(__recommend(static_cast<size_type>(__n)));
        __construct_at_end(__n, __u);
    }
    __invalidate_all_iterators();
}

template <class _Tp, class _Allocator>
inline
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::__make_iter(pointer __p) {
    return iterator(__p);
}

template <class _Tp, class _Allocator>
inline
typename vector<_Tp, _Allocator>::const_iterator
vector<_Tp, _Allocator>::__make_iter(const_pointer __p) const {
    return const_iterator(__p);
}

template <class _Tp, class _Allocator>
inline
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::begin() 
{
    return __make_iter(this->__begin_);
}

template <class _Tp, class _Allocator>
inline
typename vector<_Tp, _Allocator>::const_iterator
vector<_Tp, _Allocator>::begin() const 
{
    return __make_iter(this->__begin_);
}

template <class _Tp, class _Allocator>
inline
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::end() 
{
    return __make_iter(this->__end_);
}

template <class _Tp, class _Allocator>
inline
typename vector<_Tp, _Allocator>::const_iterator
vector<_Tp, _Allocator>::end() const 
{
    return __make_iter(this->__end_);
}

template <class _Tp, class _Allocator>
inline
typename vector<_Tp, _Allocator>::reference
vector<_Tp, _Allocator>::operator[](size_type __n) {
    return this->__begin_[__n];
}

template <class _Tp, class _Allocator>
inline
typename vector<_Tp, _Allocator>::const_reference
vector<_Tp, _Allocator>::operator[](size_type __n) const {
    return this->__begin_[__n];
}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::reference
vector<_Tp, _Allocator>::at(size_type __n) {
    if (__n >= size())
        this->__throw_out_of_range();
    return this->__begin_[__n];
}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::const_reference
vector<_Tp, _Allocator>::at(size_type __n) const {
    if (__n >= size())
        this->__throw_out_of_range();
    return this->__begin_[__n];
}

template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::reserve(size_type __n) {
    if (__n > capacity())    {
        allocator_type& __a = this->__alloc();
        __split_buffer<value_type, allocator_type&> __v(__n, size(), __a);
        __swap_out_circular_buffer(__v);
    }
}

template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::shrink_to_fit() {
    if (capacity() > size())    {
#ifndef _LIBCPP_NO_EXCEPTIONS
        try
        {
#endif  // _LIBCPP_NO_EXCEPTIONS
            allocator_type& __a = this->__alloc();
            __split_buffer<value_type, allocator_type&> __v(size(), size(), __a);
            __swap_out_circular_buffer(__v);
        }
    }
}

template <class _Tp, class _Allocator>
template <class _Up>
void
#ifndef _LIBCPP_CXX03_LANG
vector<_Tp, _Allocator>::__push_back_slow_path(_Up&& __x)
#else
vector<_Tp, _Allocator>::__push_back_slow_path(_Up& __x)
#endif
{
    allocator_type& __a = this->__alloc();
    __split_buffer<value_type, allocator_type&> __v(__recommend(size() + 1), size(), __a);
    // __v.push_back(_VSTD::forward<_Up>(__x));
    __alloc_traits::construct(__a, _VSTD::__to_raw_pointer(__v.__end_), _VSTD::forward<_Up>(__x));
    __v.__end_++;
    __swap_out_circular_buffer(__v);
}

template <class _Tp, class _Allocator>
inline
void
vector<_Tp, _Allocator>::push_back(const_reference __x)
{
    if (this->__end_ != this->__end_cap())
    {
        __RAII_IncreaseAnnotator __annotator(*this);
        __alloc_traits::construct(this->__alloc(),
                                  _VSTD::__to_raw_pointer(this->__end_), __x);
        __annotator.__done();
        ++this->__end_;
    }
    else
        __push_back_slow_path(__x);
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Tp, class _Allocator>
inline
void
vector<_Tp, _Allocator>::push_back(value_type&& __x)
{
    if (this->__end_ < this->__end_cap())
    {
        __RAII_IncreaseAnnotator __annotator(*this);
        __alloc_traits::construct(this->__alloc(),
                                  _VSTD::__to_raw_pointer(this->__end_),
                                  _VSTD::move(__x));
        __annotator.__done();
        ++this->__end_;
    }
    else
        __push_back_slow_path(_VSTD::move(__x));
}

template <class _Tp, class _Allocator>
template <class... _Args>
void
vector<_Tp, _Allocator>::__emplace_back_slow_path(_Args&&... __args)
{
    allocator_type& __a = this->__alloc();
    __split_buffer<value_type, allocator_type&> __v(__recommend(size() + 1), size(), __a);
//    __v.emplace_back(_VSTD::forward<_Args>(__args)...);
    __alloc_traits::construct(__a, _VSTD::__to_raw_pointer(__v.__end_), _VSTD::forward<_Args>(__args)...);
    __v.__end_++;
    __swap_out_circular_buffer(__v);
}

template <class _Tp, class _Allocator>
template <class... _Args>
inline
void
vector<_Tp, _Allocator>::emplace_back(_Args&&... __args)
{
    if (this->__end_ < this->__end_cap())
    {
        __RAII_IncreaseAnnotator __annotator(*this);
        __alloc_traits::construct(this->__alloc(),
                                  _VSTD::__to_raw_pointer(this->__end_),
                                  _VSTD::forward<_Args>(__args)...);
        __annotator.__done();
        ++this->__end_;
    }
    else
        __emplace_back_slow_path(_VSTD::forward<_Args>(__args)...);
}

#endif  // !_LIBCPP_CXX03_LANG

template <class _Tp, class _Allocator>
inline
void
vector<_Tp, _Allocator>::pop_back() {
    this->__destruct_at_end(this->__end_ - 1);
}

template <class _Tp, class _Allocator>
inline
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::erase(const_iterator __position) {
    difference_type __ps = __position - cbegin();
    pointer __p = this->__begin_ + __ps;
    this->__destruct_at_end(_VSTD::move(__p + 1, this->__end_, __p));
    this->__invalidate_iterators_past(__p-1);
    iterator __r = __make_iter(__p);
    return __r;
}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::erase(const_iterator __first, const_iterator __last)
{
    pointer __p = this->__begin_ + (__first - begin());
    if (__first != __last) {
        this->__destruct_at_end(_VSTD::move(__p + (__last - __first), this->__end_, __p));
        this->__invalidate_iterators_past(__p - 1);
    }
    iterator __r = __make_iter(__p);
    return __r;
}

template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::__move_range(pointer __from_s, pointer __from_e, pointer __to)
{
    pointer __old_last = this->__end_;
    difference_type __n = __old_last - __to;
    for (pointer __i = __from_s + __n; __i < __from_e; ++__i, ++this->__end_)
        __alloc_traits::construct(this->__alloc(),
                                  _VSTD::__to_raw_pointer(this->__end_),
                                  _VSTD::move(*__i));
    _VSTD::move_backward(__from_s, __from_s + __n, __old_last);
}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::insert(const_iterator __position, const_reference __x)
{
    pointer __p = this->__begin_ + (__position - begin());
    if (this->__end_ < this->__end_cap())
    {
        __RAII_IncreaseAnnotator __annotator(*this);
        if (__p == this->__end_)
        {
            __alloc_traits::construct(this->__alloc(),
                                      _VSTD::__to_raw_pointer(this->__end_), __x);
            ++this->__end_;
        }
        else
        {
            __move_range(__p, this->__end_, __p + 1);
            const_pointer __xr = pointer_traits<const_pointer>::pointer_to(__x);
            if (__p <= __xr && __xr < this->__end_)
                ++__xr;
            *__p = *__xr;
        }
        __annotator.__done();
    }
    else
    {
        allocator_type& __a = this->__alloc();
        __split_buffer<value_type, allocator_type&> __v(__recommend(size() + 1), __p - this->__begin_, __a);
        __v.push_back(__x);
        __p = __swap_out_circular_buffer(__v, __p);
    }
    return __make_iter(__p);
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::insert(const_iterator __position, value_type&& __x)
{
    pointer __p = this->__begin_ + (__position - begin());
    if (this->__end_ < this->__end_cap())
    {
        __RAII_IncreaseAnnotator __annotator(*this);
        if (__p == this->__end_)
        {
            __alloc_traits::construct(this->__alloc(),
                                      _VSTD::__to_raw_pointer(this->__end_),
                                      _VSTD::move(__x));
            ++this->__end_;
        }
        else
        {
            __move_range(__p, this->__end_, __p + 1);
            *__p = _VSTD::move(__x);
        }
        __annotator.__done();
    }
    else
    {
        allocator_type& __a = this->__alloc();
        __split_buffer<value_type, allocator_type&> __v(__recommend(size() + 1), __p - this->__begin_, __a);
        __v.push_back(_VSTD::move(__x));
        __p = __swap_out_circular_buffer(__v, __p);
    }
    return __make_iter(__p);
}

template <class _Tp, class _Allocator>
template <class... _Args>
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::emplace(const_iterator __position, _Args&&... __args)
{
    pointer __p = this->__begin_ + (__position - begin());
    if (this->__end_ < this->__end_cap())
    {
        __RAII_IncreaseAnnotator __annotator(*this);
        if (__p == this->__end_)
        {
            __alloc_traits::construct(this->__alloc(),
                                      _VSTD::__to_raw_pointer(this->__end_),
                                      _VSTD::forward<_Args>(__args)...);
            ++this->__end_;
        }
        else
        {
            __temp_value<value_type, _Allocator> __tmp(this->__alloc(), _VSTD::forward<_Args>(__args)...);
            __move_range(__p, this->__end_, __p + 1);
            *__p = _VSTD::move(__tmp.get());
        }
        __annotator.__done();
    }
    else
    {
        allocator_type& __a = this->__alloc();
        __split_buffer<value_type, allocator_type&> __v(__recommend(size() + 1), __p - this->__begin_, __a);
        __v.emplace_back(_VSTD::forward<_Args>(__args)...);
        __p = __swap_out_circular_buffer(__v, __p);
    }
    return __make_iter(__p);
}

#endif  // !_LIBCPP_CXX03_LANG

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::insert(const_iterator __position, size_type __n, const_reference __x)
{
    pointer __p = this->__begin_ + (__position - begin());
    if (__n > 0)
    {
        if (__n <= static_cast<size_type>(this->__end_cap() - this->__end_))
        {
            size_type __old_n = __n;
            pointer __old_last = this->__end_;
            if (__n > static_cast<size_type>(this->__end_ - __p))
            {
                size_type __cx = __n - (this->__end_ - __p);
                __construct_at_end(__cx, __x);
                __n -= __cx;
            }
            if (__n > 0)
            {
                __RAII_IncreaseAnnotator __annotator(*this, __n);
                __move_range(__p, __old_last, __p + __old_n);
                __annotator.__done();
                const_pointer __xr = pointer_traits<const_pointer>::pointer_to(__x);
                if (__p <= __xr && __xr < this->__end_)
                    __xr += __old_n;
                _VSTD::fill_n(__p, __n, *__xr);
            }
        }
        else
        {
                allocator_type& __a = this->__alloc();
                __split_buffer<value_type, allocator_type&> __v(__recommend(size() + __n), __p - this->__begin_, __a);
                __v.__construct_at_end(__n, __x);
                __p = __swap_out_circular_buffer(__v, __p);
        }
    }
    return __make_iter(__p);
}

template <class _Tp, class _Allocator>
template <class _InputIterator>
typename enable_if
<
     __is_input_iterator  <_InputIterator>::value &&
    !__is_forward_iterator<_InputIterator>::value &&
    is_constructible<
       _Tp,
       typename iterator_traits<_InputIterator>::reference>::value,
    typename vector<_Tp, _Allocator>::iterator
>::type
vector<_Tp, _Allocator>::insert(const_iterator __position, _InputIterator __first, _InputIterator __last)
{
    difference_type __off = __position - begin();
    pointer __p = this->__begin_ + __off;
    allocator_type& __a = this->__alloc();
    pointer __old_last = this->__end_;
    for (; this->__end_ != this->__end_cap() && __first != __last; ++__first)
    {
        __RAII_IncreaseAnnotator __annotator(*this);
        __alloc_traits::construct(__a, _VSTD::__to_raw_pointer(this->__end_),
                                  *__first);
        ++this->__end_;
        __annotator.__done();
    }
    __split_buffer<value_type, allocator_type&> __v(__a);
    if (__first != __last)
    {
            __v.__construct_at_end(__first, __last);
            difference_type __old_size = __old_last - this->__begin_;
            difference_type __old_p = __p - this->__begin_;
            reserve(__recommend(size() + __v.size()));
            __p = this->__begin_ + __old_p;
            __old_last = this->__begin_ + __old_size;
    }
    __p = _VSTD::rotate(__p, __old_last, this->__end_);
    insert(__make_iter(__p), make_move_iterator(__v.begin()),
                                    make_move_iterator(__v.end()));
    return begin() + __off;
}

template <class _Tp, class _Allocator>
template <class _ForwardIterator>
typename enable_if
<
    __is_forward_iterator<_ForwardIterator>::value &&
    is_constructible<
       _Tp,
       typename iterator_traits<_ForwardIterator>::reference>::value,
    typename vector<_Tp, _Allocator>::iterator
>::type
vector<_Tp, _Allocator>::insert(const_iterator __position, _ForwardIterator __first, _ForwardIterator __last)
{
    pointer __p = this->__begin_ + (__position - begin());
    difference_type __n = _VSTD::distance(__first, __last);
    if (__n > 0)
    {
        if (__n <= this->__end_cap() - this->__end_)
        {
            size_type __old_n = __n;
            pointer __old_last = this->__end_;
            _ForwardIterator __m = __last;
            difference_type __dx = this->__end_ - __p;
            if (__n > __dx)
            {
                __m = __first;
                difference_type __diff = this->__end_ - __p;
                _VSTD::advance(__m, __diff);
                __construct_at_end(__m, __last, __n - __diff);
                __n = __dx;
            }
            if (__n > 0)
            {
                __RAII_IncreaseAnnotator __annotator(*this, __n);
                __move_range(__p, __old_last, __p + __old_n);
                __annotator.__done();
                _VSTD::copy(__first, __m, __p);
            }
        }
        else
        {
            allocator_type& __a = this->__alloc();
            __split_buffer<value_type, allocator_type&> __v(__recommend(size() + __n), __p - this->__begin_, __a);
            __v.__construct_at_end(__first, __last);
            __p = __swap_out_circular_buffer(__v, __p);
        }
    }
    return __make_iter(__p);
}

template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::resize(size_type __sz)
{
    size_type __cs = size();
    if (__cs < __sz)
        this->__append(__sz - __cs);
    else if (__cs > __sz)
        this->__destruct_at_end(this->__begin_ + __sz);
}

template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::resize(size_type __sz, const_reference __x)
{
    size_type __cs = size();
    if (__cs < __sz)
        this->__append(__sz - __cs, __x);
    else if (__cs > __sz)
        this->__destruct_at_end(this->__begin_ + __sz);
}

template <class _Tp, class _Allocator>
void
vector<_Tp, _Allocator>::swap(vector& __x)
{
    _VSTD::swap(this->__begin_, __x.__begin_);
    _VSTD::swap(this->__end_, __x.__end_);
    _VSTD::swap(this->__end_cap(), __x.__end_cap());
    __swap_allocator(this->__alloc(), __x.__alloc(),
        integral_constant<bool,__alloc_traits::propagate_on_container_swap::value>());
}

template <class _Tp, class _Allocator>
bool
vector<_Tp, _Allocator>::__invariants() const
{
    if (this->__begin_ == nullptr)
    {
        if (this->__end_ != nullptr || this->__end_cap() != nullptr)
            return false;
    }
    else
    {
        if (this->__begin_ > this->__end_)
            return false;
        if (this->__begin_ == this->__end_cap())
            return false;
        if (this->__end_ > this->__end_cap())
            return false;
    }
    return true;
}

template <class _Tp, class _Allocator>
inline
void
vector<_Tp, _Allocator>::__invalidate_all_iterators() {}


template <class _Tp, class _Allocator>
inline
void
vector<_Tp, _Allocator>::__invalidate_iterators_past(pointer __new_last) {
  ((void)__new_last);
}

// vector<bool>

template <class _Allocator> class vector<bool, _Allocator>;

template <class _Allocator> struct hash<vector<bool, _Allocator> >;

template <class _Allocator>
struct __has_storage_type<vector<bool, _Allocator> >
{
    static const bool value = true;
};

template <class _Allocator>
class _LIBCPP_TEMPLATE_VIS vector<bool, _Allocator>
    : private __vector_base_common<true>
{
public:
    typedef vector                                   __self;
    typedef bool                                     value_type;
    typedef _Allocator                               allocator_type;
    typedef allocator_traits<allocator_type>         __alloc_traits;
    typedef typename __alloc_traits::size_type       size_type;
    typedef typename __alloc_traits::difference_type difference_type;
    typedef size_type __storage_type;
    typedef __bit_iterator<vector, false>            pointer;
    typedef __bit_iterator<vector, true>             const_pointer;
    typedef pointer                                  iterator;
    typedef const_pointer                            const_iterator;
    typedef _VSTD::reverse_iterator<iterator>         reverse_iterator;
    typedef _VSTD::reverse_iterator<const_iterator>   const_reverse_iterator;

private:
    typedef typename __rebind_alloc_helper<__alloc_traits, __storage_type>::type __storage_allocator;
    typedef allocator_traits<__storage_allocator>    __storage_traits;
    typedef typename __storage_traits::pointer       __storage_pointer;
    typedef typename __storage_traits::const_pointer __const_storage_pointer;

    __storage_pointer                                      __begin_;
    size_type                                              __size_;
    __compressed_pair<size_type, __storage_allocator> __cap_alloc_;
public:
    typedef __bit_reference<vector>                  reference;
    typedef __bit_const_reference<vector>            const_reference;
private:

    size_type& __cap() 
        {return __cap_alloc_.first();}

    const size_type& __cap() const 
        {return __cap_alloc_.first();}

    __storage_allocator& __alloc() 
        {return __cap_alloc_.second();}

    const __storage_allocator& __alloc() const 
        {return __cap_alloc_.second();}

    static const unsigned __bits_per_word = static_cast<unsigned>(sizeof(__storage_type) * CHAR_BIT);


    static size_type __internal_cap_to_external(size_type __n) 
        {return __n * __bits_per_word;}

    static size_type __external_cap_to_internal(size_type __n) 
        {return (__n - 1) / __bits_per_word + 1;}

public:

    vector() _(is_nothrow_default_constructible<allocator_type>::value);

 explicit vector(const allocator_type& __a)
#if _LIBCPP_STD_VER <= 14
        _(is_nothrow_copy_constructible<allocator_type>::value);
#else
        ;
#endif
    ~vector();
    explicit vector(size_type __n);
    vector(size_type __n, const value_type& __v);
    vector(size_type __n, const value_type& __v, const allocator_type& __a);
    template <class _InputIterator>
        vector(_InputIterator __first, _InputIterator __last,
               typename enable_if<__is_input_iterator  <_InputIterator>::value &&
                                 !__is_forward_iterator<_InputIterator>::value>::type* = 0);
    template <class _InputIterator>
        vector(_InputIterator __first, _InputIterator __last, const allocator_type& __a,
               typename enable_if<__is_input_iterator  <_InputIterator>::value &&
                                 !__is_forward_iterator<_InputIterator>::value>::type* = 0);
    template <class _ForwardIterator>
        vector(_ForwardIterator __first, _ForwardIterator __last,
               typename enable_if<__is_forward_iterator<_ForwardIterator>::value>::type* = 0);
    template <class _ForwardIterator>
        vector(_ForwardIterator __first, _ForwardIterator __last, const allocator_type& __a,
               typename enable_if<__is_forward_iterator<_ForwardIterator>::value>::type* = 0);

    vector(const vector& __v);
    vector(const vector& __v, const allocator_type& __a);
    vector& operator=(const vector& __v);

#ifndef _LIBCPP_CXX03_LANG
    vector(initializer_list<value_type> __il);
    vector(initializer_list<value_type> __il, const allocator_type& __a);


    vector(vector&& __v)
        _(is_nothrow_move_constructible<allocator_type>::value);
#endif
    vector(vector&& __v, const allocator_type& __a);

    vector& operator=(vector&& __v)
        _((__move_assign_container<_Allocator, __alloc_traits>::value));


    vector& operator=(initializer_list<value_type> __il)
        {assign(__il.begin(), __il.end()); return *this;}

#endif  // !_LIBCPP_CXX03_LANG

    template <class _InputIterator>
        typename enable_if
        <
            __is_input_iterator<_InputIterator>::value &&
           !__is_forward_iterator<_InputIterator>::value,
           void
        >::type
        assign(_InputIterator __first, _InputIterator __last);
    template <class _ForwardIterator>
        typename enable_if
        <
            __is_forward_iterator<_ForwardIterator>::value,
           void
        >::type
        assign(_ForwardIterator __first, _ForwardIterator __last);

    void assign(size_type __n, const value_type& __x);

#ifndef _LIBCPP_CXX03_LANG

    void assign(initializer_list<value_type> __il)
        {assign(__il.begin(), __il.end());}
#endif

 allocator_type get_allocator() const 
        {return allocator_type(this->__alloc());}

    size_type max_size() const ;

    size_type capacity() const 
        {return __internal_cap_to_external(__cap());}

    size_type size() const 
        {return __size_;}
    bool empty() const 
        {return __size_ == 0;}
    void reserve(size_type __n);
    void shrink_to_fit() ;


iterator begin() {
	return __make_iter(0);
}

const_iterator begin() const {
	return __make_iter(0);
}

iterator end()    {
	return __make_iter(__size_);
}

const_iterator end()   const   {
	return __make_iter(__size_);
}

reverse_iterator rbegin()    {
	return       reverse_iterator(end());
}

const_reverse_iterator rbegin() const {
	return const_reverse_iterator(end());
}

reverse_iterator rend() {
	return       reverse_iterator(begin());
}

const_reverse_iterator rend()   const {
	return const_reverse_iterator(begin());
}

const_iterator         cbegin()  const {
	return __make_iter(0);
}

const_iterator         cend()    const {
	return __make_iter(__size_);
}

const_reverse_iterator crbegin() const {
	return rbegin();
}

const_reverse_iterator crend()   const {
	return rend();
}

reference       operator[](size_type __n)       {
	return __make_ref(__n);
}

const_reference operator[](size_type __n) const {
	return __make_ref(__n);
}

reference       at(size_type __n);
const_reference at(size_type __n) const;

reference       front()       {
	return __make_ref(0);
}

const_reference front() const {
	return __make_ref(0);
}

reference       back()        {
	return __make_ref(__size_ - 1);
}

const_reference back()  const {
	return __make_ref(__size_ - 1);
}

void push_back(const value_type& __x);
void      emplace_back(_Args&&... __args)  {
    push_back ( value_type ( _VSTD::forward<_Args>(__args)... ));

void pop_back() {--__size_;}

#endif

    iterator insert(const_iterator __position, const value_type& __x);
    iterator insert(const_iterator __position, size_type __n, const value_type& __x);
    iterator insert(const_iterator __position, size_type __n, const_reference __x);
    template <class _InputIterator>
        typename enable_if
        <
             __is_input_iterator  <_InputIterator>::value &&
            !__is_forward_iterator<_InputIterator>::value,
            iterator
        >::type
        insert(const_iterator __position, _InputIterator __first, _InputIterator __last);
    template <class _ForwardIterator>
        typename enable_if
        <
            __is_forward_iterator<_ForwardIterator>::value,
            iterator
        >::type
        insert(const_iterator __position, _ForwardIterator __first, _ForwardIterator __last);

#ifndef _LIBCPP_CXX03_LANG

    iterator insert(const_iterator __position, initializer_list<value_type> __il)
        {return insert(__position, __il.begin(), __il.end());}
#endif

 iterator erase(const_iterator __position);
    iterator erase(const_iterator __first, const_iterator __last);


    void clear()  {__size_ = 0;}

    void swap(vector&)
        _(!__alloc_traits::propagate_on_container_swap::value ||
                    __is_nothrow_swappable<allocator_type>::value);
    static void swap(reference __x, reference __y)  { _VSTD::swap(__x, __y); }

    void resize(size_type __sz, value_type __x = false);
    void flip() ;

    bool __invariants() const;

private:
 void __invalidate_all_iterators();
    void __vallocate(size_type __n);
    void __vdeallocate() ;

    static size_type __align_it(size_type __new_size) 
        {return __new_size + (__bits_per_word-1) & ~((size_type)__bits_per_word-1);}
  size_type __recommend(size_type __new_size) const;
 void __construct_at_end(size_type __n, bool __x);
    template <class _ForwardIterator>
        typename enable_if
        <
            __is_forward_iterator<_ForwardIterator>::value,
            void
        >::type
        __construct_at_end(_ForwardIterator __first, _ForwardIterator __last);
    void __append(size_type __n, const_reference __x);

    reference __make_ref(size_type __pos) 
        {return reference(__begin_ + __pos / __bits_per_word, __storage_type(1) << __pos % __bits_per_word);}

    const_reference __make_ref(size_type __pos) const 
        {return const_reference(__begin_ + __pos / __bits_per_word, __storage_type(1) << __pos % __bits_per_word);}

    iterator __make_iter(size_type __pos) 
        {return iterator(__begin_ + __pos / __bits_per_word, static_cast<unsigned>(__pos % __bits_per_word));}

    const_iterator __make_iter(size_type __pos) const 
        {return const_iterator(__begin_ + __pos / __bits_per_word, static_cast<unsigned>(__pos % __bits_per_word));}

    iterator __const_iterator_cast(const_iterator __p) 
        {return begin() + (__p - cbegin());}


    void __copy_assign_alloc(const vector& __v)
        {__copy_assign_alloc(__v, integral_constant<bool,
                      __storage_traits::propagate_on_container_copy_assignment::value>());}

    void __copy_assign_alloc(const vector& __c, true_type)
        {
            if (__alloc() != __c.__alloc())
                __vdeallocate();
            __alloc() = __c.__alloc();
        }


    void __copy_assign_alloc(const vector&, false_type)
        {}

    void __move_assign(vector& __c, false_type);
    void __move_assign(vector& __c, true_type)
        _(is_nothrow_move_assignable<allocator_type>::value);

    void __move_assign_alloc(vector& __c)
        _(
            !__storage_traits::propagate_on_container_move_assignment::value ||
            is_nothrow_move_assignable<allocator_type>::value)
        {__move_assign_alloc(__c, integral_constant<bool,
                      __storage_traits::propagate_on_container_move_assignment::value>());}

    void __move_assign_alloc(vector& __c, true_type)
        _(is_nothrow_move_assignable<allocator_type>::value)
        {
            __alloc() = _VSTD::move(__c.__alloc());
        }


    void __move_assign_alloc(vector&, false_type)
        
        {}

    size_t __hash_code() const ;

    friend class __bit_reference<vector>;
    friend class __bit_const_reference<vector>;
    friend class __bit_iterator<vector, false>;
    friend class __bit_iterator<vector, true>;
    friend struct __bit_array<vector>;
    friend struct _LIBCPP_TEMPLATE_VIS hash<vector>;
};

template <class _Allocator>
inline
void
vector<bool, _Allocator>::__invalidate_all_iterators()
{
}

//  Allocate space for __n objects
//  throws length_error if __n > max_size()
//  throws (probably bad_alloc) if memory run out
//  Precondition:  __begin_ == __end_ == __cap() == 0
//  Precondition:  __n > 0
//  Postcondition:  capacity() == __n
//  Postcondition:  size() == 0
template <class _Allocator>
void
vector<bool, _Allocator>::__vallocate(size_type __n)
{
    if (__n > max_size())
        this->__throw_length_error();
    __n = __external_cap_to_internal(__n);
    this->__begin_ = __storage_traits::allocate(this->__alloc(), __n);
    this->__size_ = 0;
    this->__cap() = __n;
}

template <class _Allocator>
void
vector<bool, _Allocator>::__vdeallocate() 
{
    if (this->__begin_ != nullptr)
    {
        __storage_traits::deallocate(this->__alloc(), this->__begin_, __cap());
        __invalidate_all_iterators();
        this->__begin_ = nullptr;
        this->__size_ = this->__cap() = 0;
    }
}

template <class _Allocator>
typename vector<bool, _Allocator>::size_type
vector<bool, _Allocator>::max_size() const 
{
    size_type __amax = __storage_traits::max_size(__alloc());
    size_type __nmax = numeric_limits<size_type>::max() / 2;  // end() >= begin(), always
    if (__nmax / __bits_per_word <= __amax)
        return __nmax;
    return __internal_cap_to_external(__amax);
}

//  Precondition:  __new_size > capacity()
template <class _Allocator>
inline
typename vector<bool, _Allocator>::size_type
vector<bool, _Allocator>::__recommend(size_type __new_size) const
{
    const size_type __ms = max_size();
    if (__new_size > __ms)
        this->__throw_length_error();
    const size_type __cap = capacity();
    if (__cap >= __ms / 2)
        return __ms;
    return _VSTD::max(2*__cap, __align_it(__new_size));
}

//  Default constructs __n objects starting at __end_
//  Precondition:  __n > 0
//  Precondition:  size() + __n <= capacity()
//  Postcondition:  size() == size() + __n
template <class _Allocator>
inline
void
vector<bool, _Allocator>::__construct_at_end(size_type __n, bool __x)
{
    size_type __old_size = this->__size_;
    this->__size_ += __n;
    if (__old_size == 0 || ((__old_size - 1) / __bits_per_word) != ((this->__size_ - 1) / __bits_per_word))
    {
        if (this->__size_ <= __bits_per_word)
            this->__begin_[0] = __storage_type(0);
        else
            this->__begin_[(this->__size_ - 1) / __bits_per_word] = __storage_type(0);
    }
    _VSTD::fill_n(__make_iter(__old_size), __n, __x);
}

template <class _Allocator>
template <class _ForwardIterator>
typename enable_if
<
    __is_forward_iterator<_ForwardIterator>::value,
    void
>::type
vector<bool, _Allocator>::__construct_at_end(_ForwardIterator __first, _ForwardIterator __last)
{
    size_type __old_size = this->__size_;
    this->__size_ += _VSTD::distance(__first, __last);
    if (__old_size == 0 || ((__old_size - 1) / __bits_per_word) != ((this->__size_ - 1) / __bits_per_word))
    {
        if (this->__size_ <= __bits_per_word)
            this->__begin_[0] = __storage_type(0);
        else
            this->__begin_[(this->__size_ - 1) / __bits_per_word] = __storage_type(0);
    }
    _VSTD::copy(__first, __last, __make_iter(__old_size));
}

template <class _Allocator>
inline
vector<bool, _Allocator>::vector()
    _(is_nothrow_default_constructible<allocator_type>::value)
    : __begin_(nullptr),
      __size_(0),
      __cap_alloc_(0)
{
}

template <class _Allocator>
inline
vector<bool, _Allocator>::vector(const allocator_type& __a)
#if _LIBCPP_STD_VER <= 14
        _(is_nothrow_copy_constructible<allocator_type>::value)
#else
        
#endif
    : __begin_(nullptr),
      __size_(0),
      __cap_alloc_(0, static_cast<__storage_allocator>(__a))
{
}

template <class _Allocator>
vector<bool, _Allocator>::vector(size_type __n)
    : __begin_(nullptr),
      __size_(0),
      __cap_alloc_(0)
{
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__n, false);
    }
}

#if _LIBCPP_STD_VER > 11
template <class _Allocator>
vector<bool, _Allocator>::vector(size_type __n, const allocator_type& __a)
    : __begin_(nullptr),
      __size_(0),
      __cap_alloc_(0, static_cast<__storage_allocator>(__a))
{
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__n, false);
    }
}
#endif

template <class _Allocator>
vector<bool, _Allocator>::vector(size_type __n, const value_type& __x)
    : __begin_(nullptr),
      __size_(0),
      __cap_alloc_(0)
{
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__n, __x);
    }
}

template <class _Allocator>
vector<bool, _Allocator>::vector(size_type __n, const value_type& __x, const allocator_type& __a)
    : __begin_(nullptr),
      __size_(0),
      __cap_alloc_(0, static_cast<__storage_allocator>(__a))
{
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__n, __x);
    }
}

template <class _Allocator>
template <class _InputIterator>
vector<bool, _Allocator>::vector(_InputIterator __first, _InputIterator __last,
       typename enable_if<__is_input_iterator  <_InputIterator>::value &&
                         !__is_forward_iterator<_InputIterator>::value>::type*)
    : __begin_(nullptr),
      __size_(0),
      __cap_alloc_(0)
{
#ifndef _LIBCPP_NO_EXCEPTIONS
    try
    {
#endif  // _LIBCPP_NO_EXCEPTIONS
        for (; __first != __last; ++__first)
            push_back(*__first);
#ifndef _LIBCPP_NO_EXCEPTIONS
    }
    catch (...)
    {
        if (__begin_ != nullptr)
            __storage_traits::deallocate(__alloc(), __begin_, __cap());
        __invalidate_all_iterators();
        throw;
    }
#endif  // _LIBCPP_NO_EXCEPTIONS
}

template <class _Allocator>
template <class _InputIterator>
vector<bool, _Allocator>::vector(_InputIterator __first, _InputIterator __last, const allocator_type& __a,
       typename enable_if<__is_input_iterator  <_InputIterator>::value &&
                         !__is_forward_iterator<_InputIterator>::value>::type*)
    : __begin_(nullptr),
      __size_(0),
      __cap_alloc_(0, static_cast<__storage_allocator>(__a))
{
#ifndef _LIBCPP_NO_EXCEPTIONS
    try
    {
#endif  // _LIBCPP_NO_EXCEPTIONS
        for (; __first != __last; ++__first)
            push_back(*__first);
#ifndef _LIBCPP_NO_EXCEPTIONS
    }
    catch (...)
    {
        if (__begin_ != nullptr)
            __storage_traits::deallocate(__alloc(), __begin_, __cap());
        __invalidate_all_iterators();
        throw;
    }
#endif  // _LIBCPP_NO_EXCEPTIONS
}

template <class _Allocator>
template <class _ForwardIterator>
vector<bool, _Allocator>::vector(_ForwardIterator __first, _ForwardIterator __last,
                                typename enable_if<__is_forward_iterator<_ForwardIterator>::value>::type*)
    : __begin_(nullptr),
      __size_(0),
      __cap_alloc_(0)
{
    size_type __n = static_cast<size_type>(_VSTD::distance(__first, __last));
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__first, __last);
    }
}

template <class _Allocator>
template <class _ForwardIterator>
vector<bool, _Allocator>::vector(_ForwardIterator __first, _ForwardIterator __last, const allocator_type& __a,
                                typename enable_if<__is_forward_iterator<_ForwardIterator>::value>::type*)
    : __begin_(nullptr),
      __size_(0),
      __cap_alloc_(0, static_cast<__storage_allocator>(__a))
{
    size_type __n = static_cast<size_type>(_VSTD::distance(__first, __last));
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__first, __last);
    }
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Allocator>
vector<bool, _Allocator>::vector(initializer_list<value_type> __il)
    : __begin_(nullptr),
      __size_(0),
      __cap_alloc_(0)
{
    size_type __n = static_cast<size_type>(__il.size());
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__il.begin(), __il.end());
    }
}

template <class _Allocator>
vector<bool, _Allocator>::vector(initializer_list<value_type> __il, const allocator_type& __a)
    : __begin_(nullptr),
      __size_(0),
      __cap_alloc_(0, static_cast<__storage_allocator>(__a))
{
    size_type __n = static_cast<size_type>(__il.size());
    if (__n > 0)
    {
        __vallocate(__n);
        __construct_at_end(__il.begin(), __il.end());
    }
}

#endif  // _LIBCPP_CXX03_LANG

template <class _Allocator>
vector<bool, _Allocator>::~vector()
{
    if (__begin_ != nullptr)
        __storage_traits::deallocate(__alloc(), __begin_, __cap());
    __invalidate_all_iterators();
}

template <class _Allocator>
vector<bool, _Allocator>::vector(const vector& __v)
    : __begin_(nullptr),
      __size_(0),
      __cap_alloc_(0, __storage_traits::select_on_container_copy_construction(__v.__alloc()))
{
    if (__v.size() > 0)
    {
        __vallocate(__v.size());
        __construct_at_end(__v.begin(), __v.end());
    }
}

template <class _Allocator>
vector<bool, _Allocator>::vector(const vector& __v, const allocator_type& __a)
    : __begin_(nullptr),
      __size_(0),
      __cap_alloc_(0, __a)
{
    if (__v.size() > 0)
    {
        __vallocate(__v.size());
        __construct_at_end(__v.begin(), __v.end());
    }
}

template <class _Allocator>
vector<bool, _Allocator>&
vector<bool, _Allocator>::operator=(const vector& __v)
{
    if (this != &__v)
    {
        __copy_assign_alloc(__v);
        if (__v.__size_)
        {
            if (__v.__size_ > capacity())
            {
                __vdeallocate();
                __vallocate(__v.__size_);
            }
            _VSTD::copy(__v.__begin_, __v.__begin_ + __external_cap_to_internal(__v.__size_), __begin_);
        }
        __size_ = __v.__size_;
    }
    return *this;
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Allocator>
inline vector<bool, _Allocator>::vector(vector&& __v)
#if _LIBCPP_STD_VER > 14
    
#else
    _(is_nothrow_move_constructible<allocator_type>::value)
#endif
    : __begin_(__v.__begin_),
      __size_(__v.__size_),
      __cap_alloc_(std::move(__v.__cap_alloc_)) {
    __v.__begin_ = nullptr;
    __v.__size_ = 0;
    __v.__cap() = 0;
}

template <class _Allocator>
vector<bool, _Allocator>::vector(vector&& __v, const allocator_type& __a)
    : __begin_(nullptr),
      __size_(0),
      __cap_alloc_(0, __a)
{
    if (__a == allocator_type(__v.__alloc()))
    {
        this->__begin_ = __v.__begin_;
        this->__size_ = __v.__size_;
        this->__cap() = __v.__cap();
        __v.__begin_ = nullptr;
        __v.__cap() = __v.__size_ = 0;
    }
    else if (__v.size() > 0)
    {
        __vallocate(__v.size());
        __construct_at_end(__v.begin(), __v.end());
    }
}

template <class _Allocator>
inline
vector<bool, _Allocator>&
vector<bool, _Allocator>::operator=(vector&& __v)
    _((__move_assign_container<_Allocator, __alloc_traits>::value))
{
    __move_assign(__v, integral_constant<bool,
          __storage_traits::propagate_on_container_move_assignment::value>());
    return *this;
}

template <class _Allocator>
void
vector<bool, _Allocator>::__move_assign(vector& __c, false_type)
{
    if (__alloc() != __c.__alloc())
        assign(__c.begin(), __c.end());
    else
        __move_assign(__c, true_type());
}

template <class _Allocator>
void
vector<bool, _Allocator>::__move_assign(vector& __c, true_type)
    _(is_nothrow_move_assignable<allocator_type>::value)
{
    __vdeallocate();
    __move_assign_alloc(__c);
    this->__begin_ = __c.__begin_;
    this->__size_ = __c.__size_;
    this->__cap() = __c.__cap();
    __c.__begin_ = nullptr;
    __c.__cap() = __c.__size_ = 0;
}

#endif  // !_LIBCPP_CXX03_LANG

template <class _Allocator>
void
vector<bool, _Allocator>::assign(size_type __n, const value_type& __x)
{
    __size_ = 0;
    if (__n > 0)
    {
        size_type __c = capacity();
        if (__n <= __c)
            __size_ = __n;
        else
        {
            vector __v(__alloc());
            __v.reserve(__recommend(__n));
            __v.__size_ = __n;
            swap(__v);
        }
        _VSTD::fill_n(begin(), __n, __x);
    }
  __invalidate_all_iterators();
}

template <class _Allocator>
template <class _InputIterator>
typename enable_if
<
    __is_input_iterator<_InputIterator>::value &&
   !__is_forward_iterator<_InputIterator>::value,
   void
>::type
vector<bool, _Allocator>::assign(_InputIterator __first, _InputIterator __last)
{
    clear();
    for (; __first != __last; ++__first)
        push_back(*__first);
}

template <class _Allocator>
template <class _ForwardIterator>
typename enable_if
<
    __is_forward_iterator<_ForwardIterator>::value,
   void
>::type
vector<bool, _Allocator>::assign(_ForwardIterator __first, _ForwardIterator __last)
{
    clear();
    difference_type __ns = _VSTD::distance(__first, __last);
    _LIBCPP_ASSERT(__ns >= 0, "invalid range specified");
    const size_t __n = static_cast<size_type>(__ns);
    if (__n)
    {
        if (__n > capacity())
        {
            __vdeallocate();
            __vallocate(__n);
        }
        __construct_at_end(__first, __last);
    }
}

template <class _Allocator>
void
vector<bool, _Allocator>::reserve(size_type __n)
{
    if (__n > capacity())
    {
        vector __v(this->__alloc());
        __v.__vallocate(__n);
        __v.__construct_at_end(this->begin(), this->end());
        swap(__v);
        __invalidate_all_iterators();
    }
}

template <class _Allocator>
void
vector<bool, _Allocator>::shrink_to_fit() 
{
    if (__external_cap_to_internal(size()) > __cap())
    {
#ifndef _LIBCPP_NO_EXCEPTIONS
        try
        {
#endif  // _LIBCPP_NO_EXCEPTIONS
            vector(*this, allocator_type(__alloc())).swap(*this);
#ifndef _LIBCPP_NO_EXCEPTIONS
        }
        catch (...)
        {
        }
#endif  // _LIBCPP_NO_EXCEPTIONS
    }
}

template <class _Allocator>
typename vector<bool, _Allocator>::reference
vector<bool, _Allocator>::at(size_type __n)
{
    if (__n >= size())
        this->__throw_out_of_range();
    return (*this)[__n];
}

template <class _Allocator>
typename vector<bool, _Allocator>::const_reference
vector<bool, _Allocator>::at(size_type __n) const
{
    if (__n >= size())
        this->__throw_out_of_range();
    return (*this)[__n];
}

template <class _Allocator>
void
vector<bool, _Allocator>::push_back(const value_type& __x)
{
    if (this->__size_ == this->capacity())
        reserve(__recommend(this->__size_ + 1));
    ++this->__size_;
    back() = __x;
}

template <class _Allocator>
typename vector<bool, _Allocator>::iterator
vector<bool, _Allocator>::insert(const_iterator __position, const value_type& __x)
{
    iterator __r;
    if (size() < capacity())
    {
        const_iterator __old_end = end();
        ++__size_;
        _VSTD::copy_backward(__position, __old_end, end());
        __r = __const_iterator_cast(__position);
    }
    else
    {
        vector __v(__alloc());
        __v.reserve(__recommend(__size_ + 1));
        __v.__size_ = __size_ + 1;
        __r = _VSTD::copy(cbegin(), __position, __v.begin());
        _VSTD::copy_backward(__position, cend(), __v.end());
        swap(__v);
    }
    *__r = __x;
    return __r;
}

template <class _Allocator>
typename vector<bool, _Allocator>::iterator
vector<bool, _Allocator>::insert(const_iterator __position, size_type __n, const value_type& __x)
{
    iterator __r;
    size_type __c = capacity();
    if (__n <= __c && size() <= __c - __n)
    {
        const_iterator __old_end = end();
        __size_ += __n;
        _VSTD::copy_backward(__position, __old_end, end());
        __r = __const_iterator_cast(__position);
    }
    else
    {
        vector __v(__alloc());
        __v.reserve(__recommend(__size_ + __n));
        __v.__size_ = __size_ + __n;
        __r = _VSTD::copy(cbegin(), __position, __v.begin());
        _VSTD::copy_backward(__position, cend(), __v.end());
        swap(__v);
    }
    _VSTD::fill_n(__r, __n, __x);
    return __r;
}

template <class _Allocator>
template <class _InputIterator>
typename enable_if
<
     __is_input_iterator  <_InputIterator>::value &&
    !__is_forward_iterator<_InputIterator>::value,
    typename vector<bool, _Allocator>::iterator
>::type
vector<bool, _Allocator>::insert(const_iterator __position, _InputIterator __first, _InputIterator __last)
{
    difference_type __off = __position - begin();
    iterator __p = __const_iterator_cast(__position);
    iterator __old_end = end();
    for (; size() != capacity() && __first != __last; ++__first)
    {
        ++this->__size_;
        back() = *__first;
    }
    vector __v(__alloc());
    if (__first != __last)
    {
#ifndef _LIBCPP_NO_EXCEPTIONS
        try
        {
#endif  // _LIBCPP_NO_EXCEPTIONS
            __v.assign(__first, __last);
            difference_type __old_size = static_cast<difference_type>(__old_end - begin());
            difference_type __old_p = __p - begin();
            reserve(__recommend(size() + __v.size()));
            __p = begin() + __old_p;
            __old_end = begin() + __old_size;
#ifndef _LIBCPP_NO_EXCEPTIONS
        }
        catch (...)
        {
            erase(__old_end, end());
            throw;
        }
#endif  // _LIBCPP_NO_EXCEPTIONS
    }
    __p = _VSTD::rotate(__p, __old_end, end());
    insert(__p, __v.begin(), __v.end());
    return begin() + __off;
}

template <class _Allocator>
template <class _ForwardIterator>
typename enable_if
<
    __is_forward_iterator<_ForwardIterator>::value,
    typename vector<bool, _Allocator>::iterator
>::type
vector<bool, _Allocator>::insert(const_iterator __position, _ForwardIterator __first, _ForwardIterator __last)
{
    const difference_type __n_signed = _VSTD::distance(__first, __last);
    _LIBCPP_ASSERT(__n_signed >= 0, "invalid range specified");
    const size_type __n = static_cast<size_type>(__n_signed);
    iterator __r;
    size_type __c = capacity();
    if (__n <= __c && size() <= __c - __n)
    {
        const_iterator __old_end = end();
        __size_ += __n;
        _VSTD::copy_backward(__position, __old_end, end());
        __r = __const_iterator_cast(__position);
    }
    else
    {
        vector __v(__alloc());
        __v.reserve(__recommend(__size_ + __n));
        __v.__size_ = __size_ + __n;
        __r = _VSTD::copy(cbegin(), __position, __v.begin());
        _VSTD::copy_backward(__position, cend(), __v.end());
        swap(__v);
    }
    _VSTD::copy(__first, __last, __r);
    return __r;
}

template <class _Allocator>
inline
typename vector<bool, _Allocator>::iterator
vector<bool, _Allocator>::erase(const_iterator __position)
{
    iterator __r = __const_iterator_cast(__position);
    _VSTD::copy(__position + 1, this->cend(), __r);
    --__size_;
    return __r;
}

template <class _Allocator>
typename vector<bool, _Allocator>::iterator
vector<bool, _Allocator>::erase(const_iterator __first, const_iterator __last)
{
    iterator __r = __const_iterator_cast(__first);
    difference_type __d = __last - __first;
    _VSTD::copy(__last, this->cend(), __r);
    __size_ -= __d;
    return __r;
}

template <class _Allocator>
void
vector<bool, _Allocator>::swap(vector& __x)
#if _LIBCPP_STD_VER >= 14
    
#else
    _(!__alloc_traits::propagate_on_container_swap::value ||
                __is_nothrow_swappable<allocator_type>::value)
#endif
{
    _VSTD::swap(this->__begin_, __x.__begin_);
    _VSTD::swap(this->__size_, __x.__size_);
    _VSTD::swap(this->__cap(), __x.__cap());
    __swap_allocator(this->__alloc(), __x.__alloc(),
        integral_constant<bool, __alloc_traits::propagate_on_container_swap::value>());
}

template <class _Allocator>
void
vector<bool, _Allocator>::resize(size_type __sz, value_type __x)
{
    size_type __cs = size();
    if (__cs < __sz)
    {
        iterator __r;
        size_type __c = capacity();
        size_type __n = __sz - __cs;
        if (__n <= __c && __cs <= __c - __n)
        {
            __r = end();
            __size_ += __n;
        }
        else
        {
            vector __v(__alloc());
            __v.reserve(__recommend(__size_ + __n));
            __v.__size_ = __size_ + __n;
            __r = _VSTD::copy(cbegin(), cend(), __v.begin());
            swap(__v);
        }
        _VSTD::fill_n(__r, __n, __x);
    }
    else
        __size_ = __sz;
}

template <class _Allocator>
void
vector<bool, _Allocator>::flip() 
{
    // do middle whole words
    size_type __n = __size_;
    __storage_pointer __p = __begin_;
    for (; __n >= __bits_per_word; ++__p, __n -= __bits_per_word)
        *__p = ~*__p;
    // do last partial word
    if (__n > 0)
    {
        __storage_type __m = ~__storage_type(0) >> (__bits_per_word - __n);
        __storage_type __b = *__p & __m;
        *__p &= ~__m;
        *__p |= ~__b & __m;
    }
}

template <class _Allocator>
bool
vector<bool, _Allocator>::__invariants() const
{
    if (this->__begin_ == nullptr)
    {
        if (this->__size_ != 0 || this->__cap() != 0)
            return false;
    }
    else
    {
        if (this->__cap() == 0)
            return false;
        if (this->__size_ > this->capacity())
            return false;
    }
    return true;
}

template <class _Allocator>
size_t
vector<bool, _Allocator>::__hash_code() const 
{
    size_t __h = 0;
    // do middle whole words
    size_type __n = __size_;
    __storage_pointer __p = __begin_;
    for (; __n >= __bits_per_word; ++__p, __n -= __bits_per_word)
        __h ^= *__p;
    // do last partial word
    if (__n > 0)
    {
        const __storage_type __m = ~__storage_type(0) >> (__bits_per_word - __n);
        __h ^= *__p & __m;
    }
    return __h;
}

template <class _Allocator>
struct _LIBCPP_TEMPLATE_VIS hash<vector<bool, _Allocator> >
    : public unary_function<vector<bool, _Allocator>, size_t>
{

    size_t operator()(const vector<bool, _Allocator>& __vec) const 
        {return __vec.__hash_code();}
};

template <class _Tp, class _Allocator>
inline
bool
operator==(const vector<_Tp, _Allocator>& __x, const vector<_Tp, _Allocator>& __y)
{
    const typename vector<_Tp, _Allocator>::size_type __sz = __x.size();
    return __sz == __y.size() && _VSTD::equal(__x.begin(), __x.end(), __y.begin());
}

template <class _Tp, class _Allocator>
inline
bool
operator!=(const vector<_Tp, _Allocator>& __x, const vector<_Tp, _Allocator>& __y)
{
    return !(__x == __y);
}

template <class _Tp, class _Allocator>
inline
bool
operator< (const vector<_Tp, _Allocator>& __x, const vector<_Tp, _Allocator>& __y)
{
    return _VSTD::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
}

template <class _Tp, class _Allocator>
inline
bool
operator> (const vector<_Tp, _Allocator>& __x, const vector<_Tp, _Allocator>& __y)
{
    return __y < __x;
}

template <class _Tp, class _Allocator>
inline
bool
operator>=(const vector<_Tp, _Allocator>& __x, const vector<_Tp, _Allocator>& __y)
{
    return !(__x < __y);
}

template <class _Tp, class _Allocator>
inline
bool
operator<=(const vector<_Tp, _Allocator>& __x, const vector<_Tp, _Allocator>& __y)
{
    return !(__y < __x);
}

template <class _Tp, class _Allocator>
inline
void
swap(vector<_Tp, _Allocator>& __x, vector<_Tp, _Allocator>& __y)
    _(_(__x.swap(__y)))
{
    __x.swap(__y);
}


#endif  // _LIBCPP_VECTOR
