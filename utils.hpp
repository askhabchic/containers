#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <memory>
#include "iterator_traits.hpp"

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


	template <class T> struct less : std::binary_function <T,T,bool> {
  		bool operator() (const T& x, const T& y) const {return x<y;}
	};
	
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
  	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
  		while (first1!=last1) {
    		if (!(*first1 == *first2))
      			return false;
    		++first1; ++first2;
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

	template <class T1, class T2>
    struct pair        {
        public :
            typedef T1 first_type;
            typedef T2 second_type;

            first_type first;
            second_type second;

            pair() : first(), second() {}

            template<class U, class V>
            pair (const pair<U, V>& pr) : first(pr.first), second(pr.second) {}

            pair (const first_type& a, const second_type& b) : first(a), second(b) {}

            pair& operator= (const pair& pr) { 
				if (*this == pr)
                    return (*this);
                this->first = pr.first;
                this->second = pr.second;
                return (*this);
            }
    };
    
    template <class T1, class T2>
        bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
            return (lhs.first == rhs.first && lhs.second == rhs.second);
        }

    template <class T1, class T2>
        bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
            return !(lhs == rhs);
        }
    
    template <class T1, class T2>
        bool operator<  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
            return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
        }

    template <class T1, class T2>
        bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
            return !(rhs < lhs);
        }

    template <class T1, class T2>
        bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
            return (rhs < lhs);
        }

    template <class T1, class T2>
        bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
            return !(lhs < rhs);
        }
    
    template <class T1, class T2>
        ft::pair<T1,T2> make_pair(T1 x, T2 y) {
            return (ft::pair<T1, T2>(x, y));
        }
	

	template <class K, class Tp>
	struct _value_type {
		typedef K									key_type;
		typedef Tp									mapped_type;
		typedef pair<const key_type, mapped_type>	value_type;	

	private:
		value_type	c;

		_value_type();
		_value_type(value_type const &);
		_value_type& operator=(value_type const &);
		~_value_type();

	public:
		value_type& get_value() { return c; }
		const value_type& get_value() const { return c; }
	};
}

#endif