#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator.hpp"
#include "iterator_v.hpp"

namespace ft {
	template<class Iterator>
	class reverse_iterator {
	public:
		typedef	Iterator																		iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::difference_type					difference_type;
		typedef typename ft::iterator_traits<iterator_type>::value_type							value_type;
		typedef typename ft::iterator_traits<iterator_type>::pointer							pointer;
		typedef typename ft::iterator_traits<iterator_type>::reference							reference;
		typedef typename ft::iterator_traits<iterator_type>::iterator_category					iterator_category;	
	
	protected:
		iterator_type			_it;

	public:
		reverse_iterator() : _it(NULL) {}
		explicit reverse_iterator (iterator_type it) : _it(it) {}
		template <class Iter>
  		reverse_iterator (const reverse_iterator<Iter>& rev_it, typename ft::enable_if<std::is_convertible<Iter, Iterator>::value>::type* = 0) : _it(rev_it.base()) {}
		template <class Iter>
  		reverse_iterator &operator=(const reverse_iterator<Iter>& rev_it) { _it = rev_it.base(); return *this; }
		~reverse_iterator(){}

		reference operator*() const								  { iterator_type tmp = _it; return *--tmp; }
		pointer operator->() const 														   { return &(operator*()); }
		reverse_iterator& operator++() 											    { --_it; return *this; };
		reverse_iterator  operator++(int)			   { reverse_iterator tmp(*this); --_it; return tmp;	}
		reverse_iterator& operator--()												{ ++_it; return *this; };
		reverse_iterator  operator--(int)			   { reverse_iterator tmp(*this); ++_it; return tmp;	}
		reverse_iterator operator+ (difference_type n) const 							   { return reverse_iterator(_it - n); }
		reverse_iterator& operator+= (difference_type n)				  		 { _it -= n; return *this; }
		reverse_iterator operator- (difference_type n) const 							   { return reverse_iterator(_it + n); 	}
		reverse_iterator& operator-= (difference_type n)						 { _it += n; return *this; }
		reference operator[] (difference_type n) const 									   { return *(*_it + n); }
		iterator_type base() const														   { return _it; }
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