// -*- C++ -*-
//===-------------------------- iterator ----------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_ITERATOR
#define _LIBCPP_ITERATOR

/*
    iterator synopsis

namespace std
{

template<class Iterator>
struct iterator_traits
{
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::iterator_category iterator_category;
};

template<class T>
struct iterator_traits<T*>
{
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef random_access_iterator_tag iterator_category;
};

template<class Category, class T, class Distance = ptrdiff_t,
         class Pointer = T*, class Reference = T&>
struct iterator
{
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
};

struct input_iterator_tag  {};
struct output_iterator_tag {};
struct forward_iterator_tag       : public input_iterator_tag         {};
struct bidirectional_iterator_tag : public forward_iterator_tag       {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// 27.4.3, iterator operations
// extension: second argument not conforming to C++03
template <class InputIterator>  // constexpr in C++17
  constexpr void advance(InputIterator& i,
             typename iterator_traits<InputIterator>::difference_type n);

template <class InputIterator>  // constexpr in C++17
  constexpr typename iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last);

template <class InputIterator>  // constexpr in C++17
  constexpr InputIterator next(InputIterator x,
typename iterator_traits<InputIterator>::difference_type n = 1);

template <class BidirectionalIterator>  // constexpr in C++17
  constexpr BidirectionalIterator prev(BidirectionalIterator x,
    typename iterator_traits<BidirectionalIterator>::difference_type n = 1);    

template <class Iterator>
class reverse_iterator
    : public iterator<typename iterator_traits<Iterator>::iterator_category,
                      typename iterator_traits<Iterator>::value_type,
                      typename iterator_traits<Iterator>::difference_type,
                      typename iterator_traits<Iterator>::pointer,
                      typename iterator_traits<Iterator>::reference>
{
protected:
    Iterator current;
public:
    typedef Iterator                                            iterator_type;
    typedef typename iterator_traits<Iterator>::difference_type difference_type;
    typedef typename iterator_traits<Iterator>::reference       reference;
    typedef typename iterator_traits<Iterator>::pointer         pointer;

    constexpr reverse_iterator();
    constexpr explicit reverse_iterator(Iterator x);
    template <class U> constexpr reverse_iterator(const reverse_iterator<U>& u);
    template <class U> constexpr reverse_iterator& operator=(const reverse_iterator<U>& u);
    constexpr Iterator base() const;
    constexpr reference operator*() const;
    constexpr pointer   operator->() const;
    constexpr reverse_iterator& operator++();
    constexpr reverse_iterator  operator++(int);
    constexpr reverse_iterator& operator--();
    constexpr reverse_iterator  operator--(int);
    constexpr reverse_iterator  operator+ (difference_type n) const;
    constexpr reverse_iterator& operator+=(difference_type n);
    constexpr reverse_iterator  operator- (difference_type n) const;
    constexpr reverse_iterator& operator-=(difference_type n);
    constexpr reference         operator[](difference_type n) const;
};

template <class Iterator1, class Iterator2>
constexpr bool                          // constexpr in C++17
operator==(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool                          // constexpr in C++17
operator<(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool                          // constexpr in C++17
operator!=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool                          // constexpr in C++17
operator>(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool                          // constexpr in C++17
operator>=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool                          // constexpr in C++17
operator<=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr auto
operator-(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y)
-> decltype(__y.base() - __x.base());   // constexpr in C++17

template <class Iterator>
constexpr reverse_iterator<Iterator>
operator+(typename reverse_iterator<Iterator>::difference_type n, 
          const reverse_iterator<Iterator>& x);   // constexpr in C++17

template <class Iterator>
constexpr reverse_iterator<Iterator> make_reverse_iterator(Iterator i); // C++14, constexpr in C++17

template <class Container>
class back_insert_iterator
{
protected:
    Container* container;
public:
    typedef Container                   container_type;
    typedef void                        value_type;
    typedef void                        difference_type;
    typedef void                        reference;
    typedef void                        pointer;

    explicit back_insert_iterator(Container& x);
    back_insert_iterator& operator=(const typename Container::value_type& value);
    back_insert_iterator& operator*();
    back_insert_iterator& operator++();
    back_insert_iterator  operator++(int);
};

template <class Container> back_insert_iterator<Container> back_inserter(Container& x);

template <class Container>
class front_insert_iterator
{
protected:
    Container* container;
public:
    typedef Container                    container_type;
    typedef void                         value_type;
    typedef void                         difference_type;
    typedef void                         reference;
    typedef void                         pointer;

    explicit front_insert_iterator(Container& x);
    front_insert_iterator& operator=(const typename Container::value_type& value);
    front_insert_iterator& operator*();
    front_insert_iterator& operator++();
    front_insert_iterator  operator++(int);
};

template <class Container> front_insert_iterator<Container> front_inserter(Container& x);

template <class Container>
class insert_iterator
{
protected:
    Container* container;
    typename Container::iterator iter;
public:
    typedef Container              container_type;
    typedef void                   value_type;
    typedef void                   difference_type;
    typedef void                   reference;
    typedef void                   pointer;

    insert_iterator(Container& x, typename Container::iterator i);
    insert_iterator& operator=(const typename Container::value_type& value);
    insert_iterator& operator*();
    insert_iterator& operator++();
    insert_iterator& operator++(int);
};

template <class Container, class Iterator>
insert_iterator<Container> inserter(Container& x, Iterator i);

template <class Iterator>
class move_iterator {
public:
    typedef Iterator                                              iterator_type;
    typedef typename iterator_traits<Iterator>::difference_type   difference_type;
    typedef Iterator                                              pointer;
    typedef typename iterator_traits<Iterator>::value_type        value_type;
    typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
    typedef value_type&&                                          reference;
 
    constexpr move_iterator();  // all the constexprs are in C++17
    constexpr explicit move_iterator(Iterator i);
    template <class U>
      constexpr move_iterator(const move_iterator<U>& u);
    template <class U>
      constexpr move_iterator& operator=(const move_iterator<U>& u);
    constexpr iterator_type base() const;
    constexpr reference operator*() const;
    constexpr pointer operator->() const;
    constexpr move_iterator& operator++();
    constexpr move_iterator operator++(int);
    constexpr move_iterator& operator--();
    constexpr move_iterator operator--(int);
    constexpr move_iterator operator+(difference_type n) const; 
    constexpr move_iterator& operator+=(difference_type n); 
    constexpr move_iterator operator-(difference_type n) const; 
    constexpr move_iterator& operator-=(difference_type n); 
    constexpr unspecified operator[](difference_type n) const;
private:
    Iterator current; // exposition only
};

template <class Iterator1, class Iterator2>
constexpr bool   // constexpr in C++17
operator==(const move_iterator<Iterator1>& x, const move_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool   // constexpr in C++17
operator!=(const move_iterator<Iterator1>& x, const move_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool   // constexpr in C++17
operator<(const move_iterator<Iterator1>& x, const move_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool   // constexpr in C++17
operator<=(const move_iterator<Iterator1>& x, const move_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool   // constexpr in C++17
operator>(const move_iterator<Iterator1>& x, const move_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool   // constexpr in C++17
operator>=(const move_iterator<Iterator1>& x, const move_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr auto   // constexpr in C++17
operator-(const move_iterator<Iterator1>& x,
          const move_iterator<Iterator2>& y) -> decltype(x.base() - y.base());

template <class Iterator>
constexpr move_iterator<Iterator> operator+(   // constexpr in C++17
            typename move_iterator<Iterator>::difference_type n, 
            const move_iterator<Iterator>& x);

template <class Iterator>   // constexpr in C++17
constexpr  move_iterator<Iterator> make_move_iterator(const Iterator& i);


template <class T, class charT = char, class traits = char_traits<charT>, class Distance = ptrdiff_t>
class istream_iterator
    : public iterator<input_iterator_tag, T, Distance, const T*, const T&>
{
public:
    typedef charT char_type;
    typedef traits traits_type;
    typedef basic_istream<charT,traits> istream_type;

    constexpr istream_iterator();
    istream_iterator(istream_type& s);
    istream_iterator(const istream_iterator& x);
    ~istream_iterator();

    const T& operator*() const;
    const T* operator->() const;
    istream_iterator& operator++();
    istream_iterator  operator++(int);
};

template <class T, class charT, class traits, class Distance>
bool operator==(const istream_iterator<T,charT,traits,Distance>& x,
                const istream_iterator<T,charT,traits,Distance>& y);
template <class T, class charT, class traits, class Distance>
bool operator!=(const istream_iterator<T,charT,traits,Distance>& x,
                const istream_iterator<T,charT,traits,Distance>& y);

template <class T, class charT = char, class traits = char_traits<charT> >
class ostream_iterator
    : public iterator<output_iterator_tag, void, void, void ,void>
{
public:
    typedef charT char_type;
    typedef traits traits_type;
    typedef basic_ostream<charT,traits> ostream_type;

    ostream_iterator(ostream_type& s);
    ostream_iterator(ostream_type& s, const charT* delimiter);
    ostream_iterator(const ostream_iterator& x);
    ~ostream_iterator();
    ostream_iterator& operator=(const T& value);

    ostream_iterator& operator*();
    ostream_iterator& operator++();
    ostream_iterator& operator++(int);
};

template<class charT, class traits = char_traits<charT> >
class istreambuf_iterator
    : public iterator<input_iterator_tag, charT,
                      typename traits::off_type, unspecified,
                      charT>
{
public:
    typedef charT                         char_type;
    typedef traits                        traits_type;
    typedef typename traits::int_type     int_type;
    typedef basic_streambuf<charT,traits> streambuf_type;
    typedef basic_istream<charT,traits>   istream_type;

    istreambuf_iterator() noexcept;
    istreambuf_iterator(istream_type& s) noexcept;
    istreambuf_iterator(streambuf_type* s) noexcept;
    istreambuf_iterator(a-private-type) noexcept;

    charT                operator*() const;
    pointer operator->() const;
    istreambuf_iterator& operator++();
    a-private-type       operator++(int);

    bool equal(const istreambuf_iterator& b) const;
};

template <class charT, class traits>
bool operator==(const istreambuf_iterator<charT,traits>& a,
                const istreambuf_iterator<charT,traits>& b);
template <class charT, class traits>
bool operator!=(const istreambuf_iterator<charT,traits>& a,
                const istreambuf_iterator<charT,traits>& b);

template <class charT, class traits = char_traits<charT> >
class ostreambuf_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
{
public:
    typedef charT                         char_type;
    typedef traits                        traits_type;
    typedef basic_streambuf<charT,traits> streambuf_type;
    typedef basic_ostream<charT,traits>   ostream_type;

    ostreambuf_iterator(ostream_type& s) noexcept;
    ostreambuf_iterator(streambuf_type* s) noexcept;
    ostreambuf_iterator& operator=(charT c);
    ostreambuf_iterator& operator*();
    ostreambuf_iterator& operator++();
    ostreambuf_iterator& operator++(int);
    bool failed() const noexcept;
};

template <class C> constexpr auto begin(C& c) -> decltype(c.begin());
template <class C> constexpr auto begin(const C& c) -> decltype(c.begin());
template <class C> constexpr auto end(C& c) -> decltype(c.end());
template <class C> constexpr auto end(const C& c) -> decltype(c.end());
template <class T, size_t N> constexpr T* begin(T (&array)[N]);
template <class T, size_t N> constexpr T* end(T (&array)[N]);

template <class C> auto constexpr cbegin(const C& c) -> decltype(std::begin(c));        // C++14
template <class C> auto constexpr cend(const C& c) -> decltype(std::end(c));            // C++14
template <class C> auto constexpr rbegin(C& c) -> decltype(c.rbegin());                 // C++14
template <class C> auto constexpr rbegin(const C& c) -> decltype(c.rbegin());           // C++14
template <class C> auto constexpr rend(C& c) -> decltype(c.rend());                     // C++14
template <class C> constexpr auto rend(const C& c) -> decltype(c.rend());               // C++14
template <class E> reverse_iterator<const E*> constexpr rbegin(initializer_list<E> il); // C++14
template <class E> reverse_iterator<const E*> constexpr rend(initializer_list<E> il);   // C++14
template <class T, size_t N> reverse_iterator<T*> constexpr rbegin(T (&array)[N]);      // C++14
template <class T, size_t N> reverse_iterator<T*> constexpr rend(T (&array)[N]);        // C++14
template <class C> constexpr auto crbegin(const C& c) -> decltype(std::rbegin(c));      // C++14
template <class C> constexpr auto crend(const C& c) -> decltype(std::rend(c));          // C++14

// 24.8, container access:
template <class C> constexpr auto size(const C& c) -> decltype(c.size());         // C++17
template <class T, size_t N> constexpr size_t size(const T (&array)[N]) noexcept; // C++17
template <class C> constexpr auto empty(const C& c) -> decltype(c.empty());       // C++17
template <class T, size_t N> constexpr bool empty(const T (&array)[N]) noexcept;  // C++17
template <class E> constexpr bool empty(initializer_list<E> il) noexcept;         // C++17
template <class C> constexpr auto data(C& c) -> decltype(c.data());               // C++17
template <class C> constexpr auto data(const C& c) -> decltype(c.data());         // C++17
template <class T, size_t N> constexpr T* data(T (&array)[N]) noexcept;           // C++17
template <class E> constexpr const E* data(initializer_list<E> il) noexcept;      // C++17

}  // std

*/

#include <__config>
#include <iosfwd> // for forward declarations of vector and string.
#include <__functional_base>
#include <type_traits>
#include <cstddef>
#include <initializer_list>
#include <__cxx_version>
#ifdef __APPLE__
#include <Availability.h>
#endif

#include <__debug>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag       : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class _Tp>
struct __has_iterator_typedefs  {
private:
    struct __two {char __lx; char __lxx;};
    template <class _Up> static __two __test(...);
    template <class _Up> static char __test(typename std::__void_t<typename _Up::iterator_category>::type* = 0,
    										typename std::__void_t<typename _Up::difference_type>::type* = 0,
    										typename std::__void_t<typename _Up::value_type>::type* = 0,
    										typename std::__void_t<typename _Up::reference>::type* = 0,
    										typename std::__void_t<typename _Up::pointer>::type* = 0
    										);
public:
    static const bool value = sizeof(__test<_Tp>(0,0,0,0,0)) == 1;
};


template <class _Tp>
struct __has_iterator_category  {
private:
    struct __two {char __lx; char __lxx;};
    template <class _Up> static __two __test(...);
    template <class _Up> static char __test(typename _Up::iterator_category* = 0);
public:
    static const bool value = sizeof(__test<_Tp>(0)) == 1;
};

template <class _Iter, bool> struct __iterator_traits_impl {};

template <class _Iter>
struct __iterator_traits_impl<_Iter, true>  {
    typedef typename _Iter::difference_type   difference_type;
    typedef typename _Iter::value_type        value_type;
    typedef typename _Iter::pointer           pointer;
    typedef typename _Iter::reference         reference;
    typedef typename _Iter::iterator_category iterator_category;
};

template <class _Iter, bool> struct __iterator_traits {};

template <class _Iter>
struct __iterator_traits<_Iter, true>
    :  __iterator_traits_impl
      <
        _Iter,
        is_convertible<typename _Iter::iterator_category, input_iterator_tag>::value ||
        is_convertible<typename _Iter::iterator_category, output_iterator_tag>::value
      >
{};

// iterator_traits<Iterator> will only have the nested types if Iterator::iterator_category
//    exists.  Else iterator_traits<Iterator> will be an empty class.  This is a
//    conforming extension which allows some programs to compile and behave as
//    the client expects instead of failing at compile time.

template <class _Iter>
struct iterator_traits
    : __iterator_traits<_Iter, __has_iterator_typedefs<_Iter>::value> {};

template<class _Tp>
struct iterator_traits<_Tp*>  {
    typedef ptrdiff_t difference_type;
    typedef typename remove_cv<_Tp>::type value_type;
    typedef _Tp* pointer;
    typedef _Tp& reference;
    typedef random_access_iterator_tag iterator_category;
};

template <class _Tp, class _Up, bool = __has_iterator_category<iterator_traits<_Tp> >::value>
struct __has_iterator_category_convertible_to
    : public integral_constant<bool, is_convertible<typename iterator_traits<_Tp>::iterator_category, _Up>::value>
{};

template <class _Tp, class _Up>
struct __has_iterator_category_convertible_to<_Tp, _Up, false> : public false_type {};

template <class _Tp>
struct __is_input_iterator : public __has_iterator_category_convertible_to<_Tp, input_iterator_tag> {};

template <class _Tp>
struct __is_forward_iterator : public __has_iterator_category_convertible_to<_Tp, forward_iterator_tag> {};

template <class _Tp>
struct __is_bidirectional_iterator : public __has_iterator_category_convertible_to<_Tp, bidirectional_iterator_tag> {};

template <class _Tp>
struct __is_random_access_iterator : public __has_iterator_category_convertible_to<_Tp, random_access_iterator_tag> {};

template <class _Tp>
struct __is_exactly_input_iterator
    : public integral_constant<bool, 
         __has_iterator_category_convertible_to<_Tp, input_iterator_tag>::value && 
        !__has_iterator_category_convertible_to<_Tp, forward_iterator_tag>::value> {};

template<class _Category, class _Tp, class _Distance = ptrdiff_t,
         class _Pointer = _Tp*, class _Reference = _Tp&>
struct iterator
{
    typedef _Tp        value_type;
    typedef _Distance  difference_type;
    typedef _Pointer   pointer;
    typedef _Reference reference;
    typedef _Category  iterator_category;
};

template <class _InputIter>
void __advance(_InputIter& __i,
             typename iterator_traits<_InputIter>::difference_type __n, input_iterator_tag)  {
    for (; __n > 0; --__n)
        ++__i;
}

template <class _BiDirIter>
void __advance(_BiDirIter& __i,
             typename iterator_traits<_BiDirIter>::difference_type __n, bidirectional_iterator_tag)
{
    if (__n >= 0)
        for (; __n > 0; --__n)
            ++__i;
    else
        for (; __n < 0; ++__n)
            --__i;
}

template <class _RandIter>
void __advance(_RandIter& __i,
             typename iterator_traits<_RandIter>::difference_type __n, random_access_iterator_tag)  {
   __i += __n;
}

template <class _InputIter>
void advance(_InputIter& __i,
             typename iterator_traits<_InputIter>::difference_type __n)  {
    __advance(__i, __n, typename iterator_traits<_InputIter>::iterator_category());
}

template <class _InputIter>
typename iterator_traits<_InputIter>::difference_type
__distance(_InputIter __first, _InputIter __last, input_iterator_tag)  {
    typename iterator_traits<_InputIter>::difference_type __r(0);
    for (; __first != __last; ++__first)
        ++__r;
    return __r;
}

template <class _RandIter>
typename iterator_traits<_RandIter>::difference_type
__distance(_RandIter __first, _RandIter __last, random_access_iterator_tag)  {
    return __last - __first;
}

template <class _InputIter>
typename iterator_traits<_InputIter>::difference_type
distance(_InputIter __first, _InputIter __last)  {
    return __distance(__first, __last, typename iterator_traits<_InputIter>::iterator_category());
}

template <class _InputIter>
typename enable_if< __is_input_iterator<_InputIter>::value, _InputIter>::type next(_InputIter __x,
     typename iterator_traits<_InputIter>::difference_type __n = 1)  {
    _VSTD::advance(__x, __n);
    return __x;
}

template <class _BidirectionalIter>
typename enable_if
<
    __is_bidirectional_iterator<_BidirectionalIter>::value, 
    _BidirectionalIter
>::type
prev(_BidirectionalIter __x,
     typename iterator_traits<_BidirectionalIter>::difference_type __n = 1)  {
    _VSTD::advance(__x, -__n);
    return __x;
}


template <class _Tp, class = void>
struct __is_stashing_iterator : false_type {};

template <class _Tp>
struct __is_stashing_iterator<_Tp, typename __void_t<typename _Tp::__stashing_iterator_tag>::type>
  : true_type {};

template <class _Iter>
class reverse_iterator
    : public iterator<typename iterator_traits<_Iter>::iterator_category,
                      typename iterator_traits<_Iter>::value_type,
                      typename iterator_traits<_Iter>::difference_type,
                      typename iterator_traits<_Iter>::pointer,
                      typename iterator_traits<_Iter>::reference>
{
private:
    /*mutable*/ _Iter __t;  // no longer used as of LWG #2360, not removed due to ABI break

    static_assert(!__is_stashing_iterator<_Iter>::value,
      "The specified iterator type cannot be used with reverse_iterator; "
      "Using stashing iterators with reverse_iterator causes undefined behavior");

protected:
    _Iter current;
public:
    typedef _Iter                                            iterator_type;
    typedef typename iterator_traits<_Iter>::difference_type difference_type;
    typedef typename iterator_traits<_Iter>::reference       reference;
    typedef typename iterator_traits<_Iter>::pointer         pointer;

    reverse_iterator() : __t(), current() {}
    explicit reverse_iterator(_Iter __x) : __t(__x), current(__x) {}
    template <class _Up>

        reverse_iterator(const reverse_iterator<_Up>& __u) : __t(__u.base()), current(__u.base()) {}
    template <class _Up>

        reverse_iterator& operator=(const reverse_iterator<_Up>& __u)
            { __t = current = __u.base(); return *this; }
    _Iter base() const {return current;}
    reference operator*() const {_Iter __tmp = current; return *--__tmp;}
    pointer  operator->() const {return _VSTD::addressof(operator*());}
    reverse_iterator& operator++() {--current; return *this;}
    reverse_iterator  operator++(int) {reverse_iterator __tmp(*this); --current; return __tmp;}
    reverse_iterator& operator--() {++current; return *this;}
    reverse_iterator  operator--(int) {reverse_iterator __tmp(*this); ++current; return __tmp;}
    reverse_iterator  operator+ (difference_type __n) const {return reverse_iterator(current - __n);}
    reverse_iterator& operator+=(difference_type __n) {current -= __n; return *this;}
    reverse_iterator  operator- (difference_type __n) const {return reverse_iterator(current + __n);}
    reverse_iterator& operator-=(difference_type __n) {current += __n; return *this;}
    reference         operator[](difference_type __n) const {return *(*this + __n);}
};

template <class _Iter1, class _Iter2>
bool operator==(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)  {
    return __x.base() == __y.base();
}

template <class _Iter1, class _Iter2>
bool operator<(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)  {
    return __x.base() > __y.base();
}

template <class _Iter1, class _Iter2>
bool operator!=(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)  {
    return __x.base() != __y.base();
}

template <class _Iter1, class _Iter2>
bool operator>(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)  {
    return __x.base() < __y.base();
}

template <class _Iter1, class _Iter2>
bool operator>=(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)  {
    return __x.base() <= __y.base();
}

template <class _Iter1, class _Iter2>
bool operator<=(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)  {
    return __x.base() >= __y.base();
}

#ifndef _LIBCPP_CXX03_LANG
template <class _Iter1, class _Iter2>
auto
operator-(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
-> decltype(__y.base() - __x.base())  {
    return __y.base() - __x.base();
}
#else
template <class _Iter1, class _Iter2>
inline
typename reverse_iterator<_Iter1>::difference_type
operator-(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __y.base() - __x.base();
}
#endif

template <class _Iter>
reverse_iterator<_Iter>
operator+(typename reverse_iterator<_Iter>::difference_type __n, const reverse_iterator<_Iter>& __x)  {
    return reverse_iterator<_Iter>(__x.base() - __n);
}

template <class _Container>
class back_insert_iterator
    : public iterator<output_iterator_tag,
                      void,
                      void,
                      void,
                      void>
{
protected:
    _Container* container;
public:
    typedef _Container container_type;

 explicit back_insert_iterator(_Container& __x) : container(_VSTD::addressof(__x)) {}
 back_insert_iterator& operator=(const typename _Container::value_type& __value_)
        {container->push_back(__value_); return *this;}
#ifndef _LIBCPP_CXX03_LANG
 back_insert_iterator& operator=(typename _Container::value_type&& __value_)
        {container->push_back(_VSTD::move(__value_)); return *this;}
#endif  // _LIBCPP_CXX03_LANG
 back_insert_iterator& operator*()     {return *this;}
 back_insert_iterator& operator++()    {return *this;}
 back_insert_iterator  operator++(int) {return *this;}
};

template <class _Container>
inline
back_insert_iterator<_Container>
back_inserter(_Container& __x)  {
    return back_insert_iterator<_Container>(__x);
}

template <class _Container>
class front_insert_iterator
    : public iterator<output_iterator_tag,
                      void,
                      void,
                      void,
                      void>
{
protected:
    _Container* container;
public:
    typedef _Container container_type;

 explicit front_insert_iterator(_Container& __x) : container(_VSTD::addressof(__x)) {}
 front_insert_iterator& operator=(const typename _Container::value_type& __value_)
        {container->push_front(__value_); return *this;}
#ifndef _LIBCPP_CXX03_LANG
 front_insert_iterator& operator=(typename _Container::value_type&& __value_)
        {container->push_front(_VSTD::move(__value_)); return *this;}
#endif  // _LIBCPP_CXX03_LANG
 front_insert_iterator& operator*()     {return *this;}
 front_insert_iterator& operator++()    {return *this;}
 front_insert_iterator  operator++(int) {return *this;}
};

template <class _Container>
inline
front_insert_iterator<_Container>
front_inserter(_Container& __x)  {
    return front_insert_iterator<_Container>(__x);
}

template <class _Container>
class insert_iterator
    : public iterator<output_iterator_tag,
                      void,
                      void,
                      void,
                      void>
{
protected:
    _Container* container;
    typename _Container::iterator iter;
public:
    typedef _Container container_type;

 insert_iterator(_Container& __x, typename _Container::iterator __i)
        : container(_VSTD::addressof(__x)), iter(__i) {}
 insert_iterator& operator=(const typename _Container::value_type& __value_)
        {iter = container->insert(iter, __value_); ++iter; return *this;}
#ifndef _LIBCPP_CXX03_LANG
 insert_iterator& operator=(typename _Container::value_type&& __value_)
        {iter = container->insert(iter, _VSTD::move(__value_)); ++iter; return *this;}
#endif  // _LIBCPP_CXX03_LANG
 insert_iterator& operator*()        {return *this;}
 insert_iterator& operator++()       {return *this;}
 insert_iterator& operator++(int)    {return *this;}
};

template <class _Container>
inline
insert_iterator<_Container>
inserter(_Container& __x, typename _Container::iterator __i)  {
    return insert_iterator<_Container>(__x, __i);
}

template <class _Tp, class _CharT = char,
          class _Traits = char_traits<_CharT>, class _Distance = ptrdiff_t>
class istream_iterator
    : public iterator<input_iterator_tag, _Tp, _Distance, const _Tp*, const _Tp&>
{
public:
    typedef _CharT char_type;
    typedef _Traits traits_type;
    typedef basic_istream<_CharT,_Traits> istream_type;
private:
    istream_type* __in_stream_;
    _Tp __value_;
public:
 _LIBCPP_CONSTEXPR istream_iterator() : __in_stream_(0), __value_() {}
 istream_iterator(istream_type& __s) : __in_stream_(_VSTD::addressof(__s))          {
            if (!(*__in_stream_ >> __value_))
                __in_stream_ = 0;
        }

 const _Tp& operator*() const {return __value_;}
 const _Tp* operator->() const {return _VSTD::addressof((operator*()));}
 istream_iterator& operator++()          {
            if (!(*__in_stream_ >> __value_))
                __in_stream_ = 0;
            return *this;
        }
 istream_iterator  operator++(int)
        {istream_iterator __t(*this); ++(*this); return __t;}

    template <class _Up, class _CharU, class _TraitsU, class _DistanceU>
    friend      bool      operator==(const istream_iterator<_Up, _CharU, _TraitsU, _DistanceU>& __x,
               const istream_iterator<_Up, _CharU, _TraitsU, _DistanceU>& __y);

    template <class _Up, class _CharU, class _TraitsU, class _DistanceU>
    friend      bool      operator==(const istream_iterator<_Up, _CharU, _TraitsU, _DistanceU>& __x,
               const istream_iterator<_Up, _CharU, _TraitsU, _DistanceU>& __y);
};

template <class _Tp, class _CharT, class _Traits, class _Distance>
bool operator==(const istream_iterator<_Tp, _CharT, _Traits, _Distance>& __x,
           const istream_iterator<_Tp, _CharT, _Traits, _Distance>& __y)  {
    return __x.__in_stream_ == __y.__in_stream_;
}

template <class _Tp, class _CharT, class _Traits, class _Distance>
bool operator!=(const istream_iterator<_Tp, _CharT, _Traits, _Distance>& __x,
           const istream_iterator<_Tp, _CharT, _Traits, _Distance>& __y)  {
    return !(__x == __y);
}

template <class _Tp, class _CharT = char, class _Traits = char_traits<_CharT> >
class ostream_iterator
    : public iterator<output_iterator_tag, void, void, void, void>  {
public:
    typedef _CharT char_type;
    typedef _Traits traits_type;
    typedef basic_ostream<_CharT,_Traits> ostream_type;
private:
    ostream_type* __out_stream_;
    const char_type* __delim_;
public:
 ostream_iterator(ostream_type& __s) _NOEXCEPT
        : __out_stream_(_VSTD::addressof(__s)), __delim_(0) {}
 ostream_iterator(ostream_type& __s, const _CharT* __delimiter) _NOEXCEPT
        : __out_stream_(_VSTD::addressof(__s)), __delim_(__delimiter) {}
 ostream_iterator& operator=(const _Tp& __value_)          {
            *__out_stream_ << __value_;
            if (__delim_)
                *__out_stream_ << __delim_;
            return *this;
        }

 ostream_iterator& operator*()     {return *this;}
 ostream_iterator& operator++()    {return *this;}
 ostream_iterator& operator++(int) {return *this;}
};

template<class _CharT, class _Traits>
class istreambuf_iterator
    : public iterator<input_iterator_tag, _CharT,
                      typename _Traits::off_type, _CharT*,
                      _CharT>
{
public:
    typedef _CharT                          char_type;
    typedef _Traits                         traits_type;
    typedef typename _Traits::int_type      int_type;
    typedef basic_streambuf<_CharT,_Traits> streambuf_type;
    typedef basic_istream<_CharT,_Traits>   istream_type;
private:
    mutable streambuf_type* __sbuf_;

    class __proxy      {
        char_type __keep_;
        streambuf_type* __sbuf_;
     __proxy(char_type __c, streambuf_type* __s)
            : __keep_(__c), __sbuf_(__s) {}
        friend class istreambuf_iterator;
    public:
     char_type operator*() const {return __keep_;}
    };


    bool __test_for_eof() const      {
        if (__sbuf_ && traits_type::eq_int_type(__sbuf_->sgetc(), traits_type::eof()))
            __sbuf_ = 0;
        return __sbuf_ == 0;
    }
public:
 _LIBCPP_CONSTEXPR istreambuf_iterator() _NOEXCEPT : __sbuf_(0) {}
 istreambuf_iterator(istream_type& __s) _NOEXCEPT
        : __sbuf_(__s.rdbuf()) {}
 istreambuf_iterator(streambuf_type* __s) _NOEXCEPT
        : __sbuf_(__s) {}
 istreambuf_iterator(const __proxy& __p) _NOEXCEPT
        : __sbuf_(__p.__sbuf_) {}

 char_type  operator*() const
        {return static_cast<char_type>(__sbuf_->sgetc());}
 istreambuf_iterator& operator++()          {
            __sbuf_->sbumpc();
            return *this;
        }
 __proxy              operator++(int)          {
            return __proxy(__sbuf_->sbumpc(), __sbuf_);
        }

 bool equal(const istreambuf_iterator& __b) const
        {return __test_for_eof() == __b.__test_for_eof();}
};

template <class _CharT, class _Traits>
bool operator==(const istreambuf_iterator<_CharT,_Traits>& __a,
                const istreambuf_iterator<_CharT,_Traits>& __b)
                {return __a.equal(__b);}

template <class _CharT, class _Traits>
bool operator!=(const istreambuf_iterator<_CharT,_Traits>& __a,
                const istreambuf_iterator<_CharT,_Traits>& __b)
                {return !__a.equal(__b);}

template <class _CharT, class _Traits>
class ostreambuf_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
{
public:
    typedef _CharT                          char_type;
    typedef _Traits                         traits_type;
    typedef basic_streambuf<_CharT,_Traits> streambuf_type;
    typedef basic_ostream<_CharT,_Traits>   ostream_type;
private:
    streambuf_type* __sbuf_;
public:
 ostreambuf_iterator(ostream_type& __s) _NOEXCEPT
        : __sbuf_(__s.rdbuf()) {}
 ostreambuf_iterator(streambuf_type* __s) _NOEXCEPT
        : __sbuf_(__s) {}
 ostreambuf_iterator& operator=(_CharT __c)
        {
            if (__sbuf_ && traits_type::eq_int_type(__sbuf_->sputc(__c), traits_type::eof()))
                __sbuf_ = 0;
            return *this;
        }
 ostreambuf_iterator& operator*()     {return *this;}
 ostreambuf_iterator& operator++()    {return *this;}
 ostreambuf_iterator& operator++(int) {return *this;}
 bool failed() const _NOEXCEPT {return __sbuf_ == 0;}

#if !defined(__APPLE__) || \
    (defined(__MAC_OS_X_VERSION_MIN_REQUIRED) && __MAC_OS_X_VERSION_MIN_REQUIRED > __MAC_10_8) || \
    (defined(__IPHONE_OS_VERSION_MIN_REQUIRED) && __IPHONE_OS_VERSION_MIN_REQUIRED > __IPHONE_6_0)

    template <class _Ch, class _Tr>
    friend
    ostreambuf_iterator<_Ch, _Tr>
    __pad_and_output(ostreambuf_iterator<_Ch, _Tr> __s,
                     const _Ch* __ob, const _Ch* __op, const _Ch* __oe,
                     ios_base& __iob, _Ch __fl);
#endif
};

template <class _Iter>
class move_iterator
{
private:
    _Iter __i;
public:
    typedef _Iter                                            iterator_type;
    typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
    typedef typename iterator_traits<iterator_type>::value_type value_type;
    typedef typename iterator_traits<iterator_type>::difference_type difference_type;
    typedef iterator_type pointer;
#ifndef _LIBCPP_CXX03_LANG
    typedef typename iterator_traits<iterator_type>::reference __reference;
    typedef typename conditional<
            is_reference<__reference>::value,
            typename remove_reference<__reference>::type&&,
            __reference
        >::type reference;
#else
    typedef typename iterator_traits<iterator_type>::reference reference;
#endif

    move_iterator() : __i() {}
    explicit move_iterator(_Iter __x) : __i(__x) {}
    template <class _Up>

      move_iterator(const move_iterator<_Up>& __u) : __i(__u.base()) {} _Iter base() const {return __i;} 
    reference operator*() const { return static_cast<reference>(*__i); }
    pointer  operator->() const { return __i;}
    move_iterator& operator++() {++__i; return *this;}
    move_iterator  operator++(int) {move_iterator __tmp(*this); ++__i; return __tmp;}
    move_iterator& operator--() {--__i; return *this;}
    move_iterator  operator--(int) {move_iterator __tmp(*this); --__i; return __tmp;}
    move_iterator  operator+ (difference_type __n) const {return move_iterator(__i + __n);}
    move_iterator& operator+=(difference_type __n) {__i += __n; return *this;}
    move_iterator  operator- (difference_type __n) const {return move_iterator(__i - __n);}
    move_iterator& operator-=(difference_type __n) {__i -= __n; return *this;}
    reference operator[](difference_type __n) const { return static_cast<reference>(__i[__n]); }
};

template <class _Iter1, class _Iter2>
bool operator==(const move_iterator<_Iter1>& __x, const move_iterator<_Iter2>& __y)  {
    return __x.base() == __y.base();
}

template <class _Iter1, class _Iter2>
bool operator<(const move_iterator<_Iter1>& __x, const move_iterator<_Iter2>& __y)  {
    return __x.base() < __y.base();
}

template <class _Iter1, class _Iter2>
bool operator!=(const move_iterator<_Iter1>& __x, const move_iterator<_Iter2>& __y)  {
    return __x.base() != __y.base();
}

template <class _Iter1, class _Iter2>
bool operator>(const move_iterator<_Iter1>& __x, const move_iterator<_Iter2>& __y)  {
    return __x.base() > __y.base();
}

template <class _Iter1, class _Iter2>
bool operator>=(const move_iterator<_Iter1>& __x, const move_iterator<_Iter2>& __y)  {
    return __x.base() >= __y.base();
}

template <class _Iter1, class _Iter2>
bool operator<=(const move_iterator<_Iter1>& __x, const move_iterator<_Iter2>& __y)  {
    return __x.base() <= __y.base();
}

#ifndef _LIBCPP_CXX03_LANG
template <class _Iter1, class _Iter2>
auto
operator-(const move_iterator<_Iter1>& __x, const move_iterator<_Iter2>& __y)
-> decltype(__x.base() - __y.base())  {
    return __x.base() - __y.base();
}
#else
template <class _Iter1, class _Iter2>
inline
typename move_iterator<_Iter1>::difference_type
operator-(const move_iterator<_Iter1>& __x, const move_iterator<_Iter2>& __y)  {
    return __x.base() - __y.base();
}
#endif

template <class _Iter>
move_iterator<_Iter>
operator+(typename move_iterator<_Iter>::difference_type __n, const move_iterator<_Iter>& __x) {
    return move_iterator<_Iter>(__x.base() + __n);
}

template <class _Iter>
move_iterator<_Iter>
make_move_iterator(_Iter __i) {
    return move_iterator<_Iter>(__i);
}

// __wrap_iter

template <class _Iter> class __wrap_iter;

template <class _Iter1, class _Iter2> bool operator==(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) ;

template <class _Iter1, class _Iter2> bool operator<(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) ;

template <class _Iter1, class _Iter2> bool operator!=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) ;

template <class _Iter1, class _Iter2> bool operator>(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) ;

template <class _Iter1, class _Iter2> bool operator>=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) ;

template <class _Iter1, class _Iter2> bool operator<=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) ;

#ifndef _LIBCPP_CXX03_LANG
template <class _Iter1, class _Iter2> auto
operator-(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) 
-> decltype(__x.base() - __y.base());
#else
template <class _Iter1, class _Iter2>
typename __wrap_iter<_Iter1>::difference_type
operator-(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) ;
#endif

template <class _Iter> __wrap_iter<_Iter>
operator+(typename __wrap_iter<_Iter>::difference_type, __wrap_iter<_Iter>) ;

template <class _Ip, class _Op> _Op copy(_Ip, _Ip, _Op);
template <class _B1, class _B2> _B2 copy_backward(_B1, _B1, _B2);
template <class _Ip, class _Op> _Op move(_Ip, _Ip, _Op);
template <class _B1, class _B2> _B2 move_backward(_B1, _B1, _B2);


template <class _Tp>
inline typename enable_if<is_trivially_copy_assignable<_Tp>::value, __wrap_iter<_Tp*>>::type
__unwrap_iter(__wrap_iter<_Tp*> __i);

#endif

template <class _Iter>
class __wrap_iter
{
public:
    typedef _Iter                                                      iterator_type;
    typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
    typedef typename iterator_traits<iterator_type>::value_type        value_type;
    typedef typename iterator_traits<iterator_type>::difference_type   difference_type;
    typedef typename iterator_traits<iterator_type>::pointer           pointer;
    typedef typename iterator_traits<iterator_type>::reference         reference;
private:
    iterator_type __i;
public:
 __wrap_iter() 

    {    }
    template <class _Up>
        __wrap_iter(const __wrap_iter<_Up>& __u,
            typename enable_if<is_convertible<_Up, iterator_type>::value>::type* = 0) 
            : __i(__u.base())
    {  }
reference operator*() const                         {return *__i;    }
pointer  operator->() const                         {return (pointer)_VSTD::addressof(*__i);    }
__wrap_iter& operator++()                           {++__i; return *this;    }
__wrap_iter  operator++(int)                        {__wrap_iter __tmp(*this); ++(*this); return __tmp;   }
__wrap_iter& operator--()                           {--__i; return *this;    }
__wrap_iter  operator--(int)                        {__wrap_iter __tmp(*this); --(*this); return __tmp;   }
__wrap_iter  operator+ (difference_type __n) const  {__wrap_iter __w(*this); __w += __n; return __w; }
__wrap_iter& operator+=(difference_type __n)        {__i += __n;        return *this;    }
__wrap_iter  operator- (difference_type __n) const  {return *this + (-__n); }
__wrap_iter& operator-=(difference_type __n)        {*this += -__n; return *this; }
reference    operator[](difference_type __n) const  {return __i[__n];    }
iterator_type base() const                          {return __i;    }

private:
 __wrap_iter(iterator_type __x)  : __i(__x) {}

    template <class _Up> friend class __wrap_iter;
    template <class _CharT, class _Traits, class _Alloc> friend class basic_string;
    template <class _Tp, class _Alloc> friend class vector;
    template <class _Tp, ptrdiff_t> friend class span;

    template <class _Iter1, class _Iter2>
    friend    bool    operator==(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) ;

    template <class _Iter1, class _Iter2>
    friend    bool    operator<(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) ;

    template <class _Iter1, class _Iter2>
    friend    bool    operator!=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) ;

    template <class _Iter1, class _Iter2>
    friend    bool    operator>(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) ;

    template <class _Iter1, class _Iter2>
    friend    bool    operator>=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) ;

    template <class _Iter1, class _Iter2>
    friend    bool    operator<=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) ;

#ifndef _LIBCPP_CXX03_LANG
    template <class _Iter1, class _Iter2>
    friend    auto    operator-(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) 
    -> decltype(__x.base() - __y.base());
#else
    template <class _Iter1, class _Iter2>
    friend
    typename __wrap_iter<_Iter1>::difference_type
    operator-(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) ;
#endif

    template <class _Iter1>
    friend    __wrap_iter<_Iter1>
    operator+(typename __wrap_iter<_Iter1>::difference_type, __wrap_iter<_Iter1>) ;

    template <class _Ip, class _Op> friend _Op copy(_Ip, _Ip, _Op);
    template <class _B1, class _B2> friend _B2 copy_backward(_B1, _B1, _B2);
    template <class _Ip, class _Op> friend _Op move(_Ip, _Ip, _Op);
    template <class _B1, class _B2> friend _B2 move_backward(_B1, _B1, _B2);

  template <class _Tp>
  inline   typename enable_if
  <
      is_trivially_copy_assignable<_Tp>::value,
      __wrap_iter<_Tp*>
  >::type
  __unwrap_iter(__wrap_iter<_Tp*> __i);
};

template <class _Iter1, class _Iter2>
inline bool operator==(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) {
    return __x.base() == __y.base();
}

template <class _Iter1, class _Iter2>
inline bool operator<(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) {
    return __x.base() < __y.base();
}

template <class _Iter1, class _Iter2>
inline bool operator!=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) {
    return !(__x == __y);
}

template <class _Iter1, class _Iter2>
inline bool operator>(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) {
    return __y < __x;
}

template <class _Iter1, class _Iter2>
inline bool operator>=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) {
    return !(__x < __y);
}

template <class _Iter1, class _Iter2>
inline bool operator<=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) {
    return !(__y < __x);
}

template <class _Iter1>
inline bool operator!=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) {
    return !(__x == __y);
}

template <class _Iter1>
inline bool operator>(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) {
    return __y < __x;
}

template <class _Iter1>
inline bool operator>=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) {
    return !(__x < __y);
}

template <class _Iter1>
inline bool operator<=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter1>& __y) {
    return !(__y < __x);
}

#ifndef _LIBCPP_CXX03_LANG
template <class _Iter1, class _Iter2>
inline auto
operator-(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) 
-> decltype(__x.base() - __y.base())
{
    return __x.base() - __y.base();
}
#else
template <class _Iter1, class _Iter2>
inline typename __wrap_iter<_Iter1>::difference_type
operator-(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) 
{
    return __x.base() - __y.base();
}
#endif

template <class _Iter>
inline __wrap_iter<_Iter>
operator+(typename __wrap_iter<_Iter>::difference_type __n,
          __wrap_iter<_Iter> __x) 
{
    __x += __n;
    return __x;
}

template <class _Iter>
struct __libcpp_is_trivial_iterator
    : public _LIBCPP_BOOL_CONSTANT(is_pointer<_Iter>::value) {};
    
template <class _Iter>
struct __libcpp_is_trivial_iterator<move_iterator<_Iter> >
    : public _LIBCPP_BOOL_CONSTANT(__libcpp_is_trivial_iterator<_Iter>::value) {};

template <class _Iter>
struct __libcpp_is_trivial_iterator<reverse_iterator<_Iter> >
    : public _LIBCPP_BOOL_CONSTANT(__libcpp_is_trivial_iterator<_Iter>::value) {};

template <class _Iter>
struct __libcpp_is_trivial_iterator<__wrap_iter<_Iter> >
    : public _LIBCPP_BOOL_CONSTANT(__libcpp_is_trivial_iterator<_Iter>::value) {};


template <class _Tp, size_t _Np>
inline _LIBCPP_CONSTEXPR_AFTER_CXX11
_Tp*
begin(_Tp (&__array)[_Np])	{
    return __array;
}

template <class _Tp, size_t _Np>
inline _LIBCPP_CONSTEXPR_AFTER_CXX11
_Tp* end(_Tp (&__array)[_Np])	{
    return __array + _Np;
}

#if !defined(_LIBCPP_CXX03_LANG)

template <class _Cp>
auto begin(_Cp& __c) -> decltype(__c.begin())	{
    return __c.begin();
}

template <class _Cp>
auto begin(const _Cp& __c) -> decltype(__c.begin())	{
    return __c.begin();
}

template <class _Cp>
auto end(_Cp& __c) -> decltype(__c.end())	{
    return __c.end();
}

template <class _Cp>
auto end(const _Cp& __c) -> decltype(__c.end()) {
    return __c.end();
}

template <class _Tp, size_t _Np>
reverse_iterator<_Tp*> rbegin(_Tp (&__array)[_Np])	{
    return reverse_iterator<_Tp*>(__array + _Np);
}

template <class _Tp, size_t _Np>
reverse_iterator<_Tp*> rend(_Tp (&__array)[_Np])	{
    return reverse_iterator<_Tp*>(__array);
}

template <class _Ep>
reverse_iterator<const _Ep*> rbegin(initializer_list<_Ep> __il)	{
    return reverse_iterator<const _Ep*>(__il.end());
}

template <class _Ep>
reverse_iterator<const _Ep*> rend(initializer_list<_Ep> __il)	{
    return reverse_iterator<const _Ep*>(__il.begin());
}

template <class _Cp>
auto cbegin(const _Cp& __c) -> decltype(_VSTD::begin(__c))	{
    return _VSTD::begin(__c);
}

template <class _Cp>
auto cend(const _Cp& __c) -> decltype(_VSTD::end(__c))	{
    return _VSTD::end(__c);
}

template <class _Cp>
auto rbegin(_Cp& __c) -> decltype(__c.rbegin())	{
    return __c.rbegin();
}

template <class _Cp>
auto rbegin(const _Cp& __c) -> decltype(__c.rbegin())	{
    return __c.rbegin();
}

template <class _Cp>
auto rend(_Cp& __c) -> decltype(__c.rend())	{
    return __c.rend();
}

template <class _Cp>
auto rend(const _Cp& __c) -> decltype(__c.rend())	{
    return __c.rend();
}

template <class _Cp>
auto crbegin(const _Cp& __c) -> decltype(_VSTD::rbegin(__c))	{
    return _VSTD::rbegin(__c);
}

template <class _Cp>
auto crend(const _Cp& __c) -> decltype(_VSTD::rend(__c))	{
    return _VSTD::rend(__c);
}

#endif


#else  // defined(_LIBCPP_CXX03_LANG)

template <class _Cp>
inline
typename _Cp::iterator
begin(_Cp& __c)
{
    return __c.begin();
}

template <class _Cp>
inline
typename _Cp::const_iterator
begin(const _Cp& __c)
{
    return __c.begin();
}

template <class _Cp>
inline
typename _Cp::iterator
end(_Cp& __c)
{
    return __c.end();
}

template <class _Cp>
inline
typename _Cp::const_iterator
end(const _Cp& __c)
{
    return __c.end();
}

#endif  // !defined(_LIBCPP_CXX03_LANG)


template <class _Cont>
inline
constexpr auto size(const _Cont& __c)
_NOEXCEPT_(noexcept(__c.size()))
-> decltype        (__c.size())
{ return            __c.size(); }

template <class _Tp, size_t _Sz>
inline
constexpr size_t size(const _Tp (&)[_Sz]) noexcept { return _Sz; }

template <class _Cont>
constexpr auto empty(const _Cont& __c)
_NOEXCEPT_(noexcept(__c.empty()))
-> decltype        (__c.empty())
{ return            __c.empty(); }

template <class _Tp, size_t _Sz>
constexpr bool empty(const _Tp (&)[_Sz]) noexcept { return false; }

template <class _Ep>
constexpr bool empty(initializer_list<_Ep> __il) noexcept { return __il.size() == 0; }

template <class _Cont> constexpr
inline
auto data(_Cont& __c)
_NOEXCEPT_(noexcept(__c.data()))
-> decltype        (__c.data())
{ return            __c.data(); }

template <class _Cont> constexpr
inline
auto data(const _Cont& __c)
_NOEXCEPT_(noexcept(__c.data()))
-> decltype        (__c.data()) 
{ return            __c.data(); }

template <class _Tp, size_t _Sz>
inline
constexpr _Tp* data(_Tp (&__array)[_Sz]) noexcept { return __array; }

template <class _Ep>
inline
constexpr const _Ep* data(initializer_list<_Ep> __il) noexcept { return __il.begin(); }
#endif


