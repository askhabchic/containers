#ifndef ITERATOR_V_HPP
#define ITERATOR_V_HPP

#include "iterator.hpp"
#include "utils.hpp"

namespace ft {
	template<class T>
	class iterator_v { /*
	: public iterator< typename iterator_traits<T*>::difference_type,
										typename iterator_traits<iterator_type>::value_type,		
										typename iterator_traits<iterator_type>::pointer,			
										typename iterator_traits<iterator_type>::reference,			
										typename iterator_traits<iterator_type>::iterator_category>	*/
	public:
		typedef T																	iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::difference_type		difference_type;
		typedef typename ft::iterator_traits<iterator_type>::value_type				value_type;
		typedef typename ft::iterator_traits<iterator_type>::pointer				pointer;
		typedef typename ft::iterator_traits<iterator_type>::reference				reference;
		typedef typename ft::iterator_traits<iterator_type>::iterator_category	 	iterator_category;	
	
	protected:
		iterator_type			_it;
	
	public:
		// Member functions:
		iterator_v() : _it(NULL) {};
		explicit iterator_v (iterator_type it) : _it(it) {}
		template <class Vi>
		iterator_v(const iterator_v<Vi> & vit) : _it(vit._it) {};
		template <class Vi>
		iterator_v& operator=(const iterator_v<Vi> & vit) {
			_it = vit._it;
			return *this;
		}
		~iterator_v() 															{};
		
		reference 	operator*() const 													  { return *_it; };
		pointer 	operator->() const 													  { return &(*_it); };
		iterator_v&	operator++() 												   { ++_it; return *this; };
		iterator_v 	operator++(int) 					     { iterator_v tmp = _it; ++_it; return tmp; };
		iterator_v&	operator--() 												   { --_it; return *this; };
		iterator_v 	operator--(int)				   			 { iterator_v tmp = _it; --_it; return tmp; };
		iterator_v 	operator+ (difference_type n) const	{ iterator_v tmp = *this; tmp += n; return tmp; };
		iterator_v& operator+=(difference_type n)							    { _it += n; return *this; };
		iterator_v 	operator- (difference_type n) const									  { return *this + (-n); };
		iterator_v&	operator-=(difference_type n) 										  { return *this += -n; };
		reference 	operator[](difference_type n) const 								  { return *(*_it + n); };
		pointer		base() const														  { return _it; };

		bool operator== (const iterator_v& rhs) {
			return _it == rhs._it;
		}

		bool operator!= (const iterator_v& rhs) {
			return !(_it == rhs._it);
		}
		bool operator<  (const iterator_v<T>& rhs) {
			return _it < rhs._it;
		}

		bool operator>  (const iterator_v<T>& rhs) {
			return _it > rhs._it;
		}

		bool operator<= (const iterator_v<T>& rhs) {
			return _it <= rhs._it;
		}

		bool operator>= (const iterator_v<T>& rhs) {
			return _it >= rhs._it;
		}


		friend bool operator==  (const iterator_v<T>& lhs, const iterator_v<T>& rhs);
		friend bool operator!=  (const iterator_v<T>& lhs, const iterator_v<T>& rhs);
		friend bool operator<  (const iterator_v<T>& lhs, const iterator_v<T>& rhs);
		friend bool operator>  (const iterator_v<T>& lhs, const iterator_v<T>& rhs);
		friend bool operator<= (const iterator_v<T>& lhs, const iterator_v<T>& rhs);
		friend bool operator>= (const iterator_v<T>& lhs, const iterator_v<T>& rhs);
	};

	// Non-member function overloads:
	template <class T>
	bool operator== (const iterator_v<T>& lhs, const iterator_v<T>& rhs) {
		return lhs.base() == rhs.base();		};
	
	template <class T>
	bool operator!= (const iterator_v<T>& lhs, const iterator_v<T>& rhs) {
		return !(lhs == rhs);		};

	template <class T>
	bool operator<  (const iterator_v<T>& lhs, const iterator_v<T>& rhs) {
		return lhs.base() < rhs.base();		};

	template <class T>
	bool operator>  (const iterator_v<T>& lhs, const iterator_v<T>& rhs) {
		return lhs.base() > rhs.base();		};

	template <class T>
	bool operator<= (const iterator_v<T>& lhs, const iterator_v<T>& rhs) {
		return lhs.base() <= rhs.base();		};
	
	template <class T>
	bool operator>= (const iterator_v<T>& lhs, const iterator_v<T>& rhs) {
		return lhs.base() >= rhs.base();		};
}

#endif