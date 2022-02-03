#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include "iterator.hpp"
#include "iterator_v.hpp"

#define ENABLE_IF_IS_INTEGRAL(value_type) \
 typename enable_if<is_integral< value_type >::value, void>::type

#define ENABLE_IF_IS_NOT_INTEGRAL(value_type) \
 typename enable_if<!is_integral< value_type >::value, void>::type

namespace ft {

	template <bool, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if<true, T> {typedef T type;};

	template <class Tp, Tp v>
	struct integral_constant	{
	    static  const Tp      		value = v;
	    typedef Tp               	value_type;
	    typedef integral_constant 	type;
	    operator value_type() const {return value;}
	};

	typedef integral_constant<bool, true>  true_type; 
	typedef integral_constant<bool, false> false_type;

	template <class T> struct is_integral                     : public false_type {};
	template <>        struct is_integral<bool>               : public true_type {};
	template <>        struct is_integral<char>               : public true_type {};
	template <>        struct is_integral<signed char>        : public true_type {};
	template <>        struct is_integral<unsigned char>      : public true_type {};
	template <>        struct is_integral<wchar_t>            : public true_type {};
	template <>        struct is_integral<char16_t>           : public true_type {};
	template <>        struct is_integral<char32_t>           : public true_type {};
	template <>        struct is_integral<short>              : public true_type {};
	template <>        struct is_integral<unsigned short>     : public true_type {};
	template <>        struct is_integral<int>                : public true_type {};
	template <>        struct is_integral<unsigned int>       : public true_type {};
	template <>        struct is_integral<long>               : public true_type {};
	template <>        struct is_integral<unsigned long>      : public true_type {};
	template <>        struct is_integral<long long>          : public true_type {};
	template <>        struct is_integral<unsigned long long> : public true_type {};
	template <>        struct is_integral<__int128_t>         : public true_type {};
	template <>        struct is_integral<__uint128_t>        : public true_type {};


		template <class Ts>
		void    swap(Ts& a, Ts& b){
			Ts tmp = a;
			a = b;
			b = tmp;
		}
		
		template <class T1, class T2>
		T1 copy_st(T1 first, T1 last, T2& val, typename ft::enable_if<std::is_convertible<T1, T1>::value>::type* = 0) {
			for (; first != last; ++val, ++first)
				*val = *first;
			return val;
		}

	template <class T1, class value_type>
	void fill_st(T1 first, T1 last, value_type& val) {
		for ( ; first != last; ++first)
			*first = val;
	}

	template <class iterator, class value_type>
	value_type& copy_backward(iterator first, iterator last, value_type& val) {
		for (; last != first; )
			*(--val) = *(--last);
		return val;
	}

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
	    while (first1 != last1) {
			if (*first1++ != *first2)
				return false;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)	{
	  for (; first1 != last1; ++first1, ++first2)	  {
	    if (first2 == last2 || *first2 < *first1) 
			return false;
	    else if (*first1 < *first2) 
			return true;
	  }
	  return (first2 != last2);
	}

	template <class RanIt, class D> inline
	void advance (RanIt &I, D N) {
		I += N;
	}

	// template<class RandomIter, class D>
	// ENABLE_IF_IS_NOT_INTEGRAL(RandomIter)
	// Distance(RandomIter first, RandomIter last, D& n) {
	// 	n += last - first;
	// }

}

#endif