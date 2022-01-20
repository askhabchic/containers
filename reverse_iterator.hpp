#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator.hpp"

namespace ft {
	template<class Iterator>
	class reverse_iterator : public iterator<	typename iterator_traits<Iterator*>::difference_type,
												typename iterator_traits<Iterator*>::value_type,
												typename iterator_traits<Iterator*>::pointer,
												typename iterator_traits<Iterator*>::reference,
												typename iterator_traits<Iterator*>::iterator_iategory>	{
	public:
		typedef	Iterator																		iterator_type;
		typedef typename iterator<ft::random_access_iterator_tag, Iterator>::difference_type	difference_type;
		typedef typename iterator<ft::random_access_iterator_tag, Iterator>::value_type			value_type;
		typedef typename iterator<ft::random_access_iterator_tag, Iterator>::pointer			pointer;
		typedef typename iterator<ft::random_access_iterator_tag, Iterator>::reference			reference;
		typedef typename iterator<ft::random_access_iterator_tag, Iterator>::iterator_iategory 	iterator_iategory;	
	
	protected:
		iterator_type			_it;

	public:
		reverse_iterator();
		explicit reverse_iterator (iterator_type it);
		template <class Iter>
  		reverse_iterator (const reverse_iterator<Iter>& rev_it);

		iterator_type base() const;
		reference operator*() const;
		reverse_iterator operator+ (difference_type n) const;
		reverse_iterator& operator++();
		reverse_iterator  operator++(int)	{ reverse_iterator tmp = *this; ++(*this); return tmp;	}
		reverse_iterator& operator+= (difference_type n) {}
		reverse_iterator operator- (difference_type n) const {}
		reverse_iterator& operator--();
		reverse_iterator  operator--(int)	{ reverse_iterator tmp = *this; --(*this); return tmp;	}
		reverse_iterator& operator-= (difference_type n);
		pointer operator->() const 											{ return &(operator*()); }
		reference operator[] (difference_type n) const 	{}
	};

	template <class Iterator>
  	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n,
        const reverse_iterator<Iterator>& rev_it) {

	}


	template <class Iterator>
  	typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs,
   		const reverse_iterator<Iterator>& rhs) {

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