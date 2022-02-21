#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <iostream>
#include <stdexcept>

namespace ft {
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
	class map	{
		public:
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef std::pair<const key_type, mapped_type>	value_type;
		typedef Compare									key_compare;
		typedef std::less<key_type>						value_compare;
		typedef Alloc									allocator_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef value_type*								pointer;
		typedef const value_type*						const_pointer;
		typedef std::iterator<Key, T>					iterator;
		typedef const std::iterator<Key, T>				const_iterator;
		typedef std::reverse_iterator<iterator>			reverse_iterator;
		typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef ptrdiff_t								difference_type;
		typedef size_t									size_type;


		// //(constructor)
		// // empty (1)	
		// explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
		// // range (2)	
		// template <class InputIterator>
  		// map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
		// // copy (3)	
		// map (const map& x);
		
		// //(destructor)
		// ~map();

		// //operator=
		// map& operator= (const map& x);

		// //iterators
		// iterator 									begin();
		// const_iterator 								begin() const;
		// iterator 									end();
		// const_iterator 								end() const;
		// reverse_iterator 							rbegin();
		// const_reverse_iterator 						rbegin() const;
		// reverse_iterator 							rend();
		// const_reverse_iterator 						rend() const;

		// //capacity
		// bool 										empty() const;
		// size_type 									size() const;
		// size_type 									max_size() const;

		// //Element access:
		// mapped_type& 								operator[] (const key_type& k);

		// //modifiers	
		// std::pair<iterator,bool> 					insert (const value_type& val);	// single element (1)
		// iterator 									insert (iterator position, const value_type& val);  // with hint (2)
		// template <class InputIterator>
		// void 										insert (InputIterator first, InputIterator last); // range (3)	
     	// void 										erase (iterator position);
		// size_type 									erase (const key_type& k);
     	// void 										erase (iterator first, iterator last);
		// void 										swap (map& x);
		// void 										clear();

		// //Observers:
		// key_compare 									key_comp() const;
		// value_compare 								value_comp() const;

		// //operations
		// iterator 									find (const key_type& k);
		// const_iterator 								find (const key_type& k) const;
		// size_type 									count (const key_type& k) const;
		// iterator 									lower_bound (const key_type& k);
		// const_iterator 								lower_bound (const key_type& k) const;
	    // iterator 									upper_bound (const key_type& k);
		// const_iterator 								upper_bound (const key_type& k) const;
		// std::pair<const_iterator,const_iterator> 	equal_range (const key_type& k) const;
		// std::pair<iterator,iterator>             	equal_range (const key_type& k);

		// //Allocator
		// allocator_type 								get_allocator() const;

		// //Non-member functions
		// template <class Key1, class T1, class Compare1, class Alloc1>
		// friend bool operator== ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );

		// template <class Key1, class T1, class Compare1, class Alloc1>
		// friend bool operator!= ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );

		// template <class Key1, class T1, class Compare1, class Alloc1>
		// friend bool operator<  ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );
		
		// template <class Key1, class T1, class Compare1, class Alloc1>
		// friend bool operator<= ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );

		// template <class Key1, class T1, class Compare1, class Alloc1>
		// friend bool operator>  ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );
		
		// template <class Key1, class T1, class Compare1, class Alloc1>
		// friend bool operator>= ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );
	};
	

	template <class Key1, class T1, class Compare1, class Alloc1>
	bool operator== ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );

	template <class Key1, class T1, class Compare1, class Alloc1>
	bool operator!= ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );

	template <class Key1, class T1, class Compare1, class Alloc1>
	bool operator<  ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );
		
	template <class Key1, class T1, class Compare1, class Alloc1>
	bool operator<= ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );

	template <class Key1, class T1, class Compare1, class Alloc1>
	bool operator>  ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );
		
	template <class Key1, class T1, class Compare1, class Alloc1>
	bool operator>= ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );
}

#endif