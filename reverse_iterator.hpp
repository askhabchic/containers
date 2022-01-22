#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator.hpp"
#include "iterator_v.hpp"

namespace ft {
	template<class Iterator>
	class reverse_iterator : public iterator_v<ft::random_access_iterator_tag>	{
	public:
		typedef	Iterator																		iterator_type;
		typedef typename iterator<ft::random_access_iterator_tag, Iterator>::difference_type	difference_type;
		typedef typename iterator<ft::random_access_iterator_tag, Iterator>::value_type			value_type;
		typedef typename iterator<ft::random_access_iterator_tag, Iterator>::pointer			pointer;
		typedef typename iterator<ft::random_access_iterator_tag, Iterator>::reference			reference;
		typedef typename iterator<ft::random_access_iterator_tag, Iterator>::iterator_category 	iterator_category;	
		typedef reverse_iterator<Iterator>														rit;
	
	protected:
		iterator_type			_it;

	public:
		reverse_iterator() {}
		~reverse_iterator();
		explicit reverse_iterator (iterator_type it) : _it(it) {}
		template <class Iter>
  		reverse_iterator (const reverse_iterator<Iter>& rev_it) : _it(rev_it.base()) {}

		iterator_type base() const														   { return _it; }
		reference operator*() const							   { reverse_iterator tmp = _it; return *--tmp; }
		pointer operator->() const 														   { return &(operator*()); }
		reverse_iterator& operator++() 											    { --_it; return *this; };
		reverse_iterator  operator++(int)		  { reverse_iterator tmp = *this; ++(*this); return tmp;	}
		reverse_iterator& operator--()												{ ++_it; return *this; };
		reverse_iterator  operator--(int)		  { reverse_iterator tmp = *this; --(*this); return tmp;	}
		reverse_iterator& operator+= (difference_type n)				  		 { _it -= n; return *this; }
		reverse_iterator& operator-= (difference_type n)						 { _it += n; return *this; }
		reverse_iterator operator- (difference_type n) const { reverse_iterator tmp = *this; return tmp + n; 	}
		reverse_iterator operator+ (difference_type n) const 							   { return *this -(n); }
		reference operator[] (difference_type n) const 									   { return *(*_it + n); }
	};

	template <class Iterator>
  	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n,
        const reverse_iterator<Iterator>& rev_it) {
			return rev_it + n;
	}

	template <class Iterator>
  	typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs,
   		const reverse_iterator<Iterator>& rhs) { 
			return lhs.base() - rhs.base();
	}

	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() == rhs.base(); }

	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return !(lhs == rhs); }

	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() < rhs.base(); }

	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return !(rhs < lhs); }

	template <class Iterator>
	bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return rhs > lhs;	}

	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return !(rhs > lhs); }

}

#endif