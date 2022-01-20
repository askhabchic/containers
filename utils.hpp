#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft {

	template <class iterator, class value_type>
	value_type& copy_backward(iterator first, iterator last, const value_type& val) {
		for (; last != first; )
			*--val = *--last;
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
}

#endif