#ifndef MAP_HPP
#define MAP_HPP

#include <stdexcept>
#include "iterator_m.hpp"
#include "tree.hpp"
#include "utils.hpp"

namespace ft {
	template < class Key, class T, class Compare = ft::less<Key>,
				class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map	{
		public:

			typedef Key     								key_type;
			typedef T       								mapped_type;
			typedef ft::pair<key_type, mapped_type> 		value_type;
			typedef Compare     							key_compare;

			class value_compare : std::binary_function<value_type, value_type, bool> {
				friend class map<key_type, mapped_type, key_compare, Alloc>;
				protected:
					Compare 					comp;
					value_compare (Compare c) : comp(c) {}
				public:
					bool operator() (const value_type& x, const value_type& y) const { 
						return (comp(x.first, y.first)); }
			};

			typedef Alloc  																		allocator_type;
			typedef typename allocator_type::reference											reference;
			typedef typename allocator_type::const_reference									const_reference;
			typedef typename allocator_type::pointer     										pointer;
			typedef typename allocator_type::const_pointer 										const_pointer;
			typedef typename ft::Binary_search_tree<value_type, key_compare>::iterator			iterator;
			typedef typename ft::Binary_search_tree<value_type, key_compare>::const_iterator 	const_iterator;
			typedef typename ft::reverse_iterator<iterator>										reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator> 								const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type 					difference_type;
			typedef size_t 																		size_type;

			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc),	_comp(comp), _bst()	{}

			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) : _alloc(alloc), _comp(comp), _bst() {
				this->insert(first, last);
			}
			
			map(const map& x) :	_alloc(x._alloc), _comp(x._comp), _bst() { this->insert(x.begin(), x.end()); }

			~map() { this->clear(); }

			map& operator= (const map& x) {
				if (&x == this)
					return (*this);
				this->clear();
				this->insert(x.begin(), x.end());
				return (*this);
			}

			iterator begin() { return (iterator(_bst._last_node->left, _bst._last_node)); }

			const_iterator begin() const { return (const_iterator(_bst._last_node->left, _bst._last_node)); }

			iterator end() { return (iterator(_bst._last_node, _bst._last_node)); }

			const_iterator end() const { return (const_iterator(_bst._last_node, _bst._last_node)); }

			reverse_iterator rbegin() { return (reverse_iterator(this->end())); }

			const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->end())); }

			reverse_iterator rend() { return (reverse_iterator(this->begin())); }

			const_reverse_iterator rend() const { return (const_reverse_iterator(this->begin())); }

			bool empty() const { return (_bst._last_node->parent == _bst._last_node); }

			size_type size() const { return (_bst._last_node->value.first); }

			size_type max_size() const { return (_bst.max_size()); }

			mapped_type& operator[] (const key_type& k)	{
				iterator tmp = this->find(k);
				if (tmp == this->end())
					this->insert(ft::make_pair(k, mapped_type()));
				tmp = this->find(k);
				return ((*tmp).second);
			} 

			pair<iterator,bool> insert (const value_type& val) { return (_bst.insertPair(val)); }

			iterator insert (iterator position, const value_type& val) { (void)position; return (_bst.insertPair(val).first); }

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
				difference_type n = distance(first, last);
				while (n--)
					this->insert(*(first++));
			}

			void erase (iterator position) { this->erase((*position).first); }

			size_type erase (const key_type& k) {
				if (this->find(k) == this->end())
					return (0);
				_bst.removeByKey(ft::make_pair(k, mapped_type()));
				return (1);
			}

			void erase (iterator first, iterator last) {
				while (first != last)
					this->erase((*(first++)).first);
			}

			void swap (map& x) { _bst.swap(x._bst); }

			void clear() { this->erase(this->begin(), this->end()); }

			key_compare key_comp() const { return (key_compare()); }

			value_compare value_comp() const { return (value_compare(key_compare())); }

			iterator find (const key_type& k) { return (iterator(_bst.searchByKey(ft::make_pair(k, mapped_type())), _bst._last_node)); }

			const_iterator find (const key_type& k) const { return (const_iterator(_bst.searchByKey(ft::make_pair(k, mapped_type())), _bst._last_node)); }

			size_type count (const key_type& k) const {
				const_iterator beg = this->begin();
				const_iterator end = this->end();
				while (beg != end)
					if ((*(beg++)).first == k)
						return (1);
				return (0);
			}

			iterator lower_bound (const key_type& k) {
				iterator beg = this->begin();
				iterator end = this->end();
				while (beg != end) {
					if (_comp((*beg).first, k) == false)
						break;
					beg++;
				}
				return (beg);
			}

			const_iterator lower_bound (const key_type& k) const { return (const_iterator(this->lower_bound(k))); }

			iterator upper_bound (const key_type& k) {
				iterator beg = this->begin();
				iterator end = this->end();

				while (beg != end) {
					if (_comp(k, (*beg).first))
						break;
					beg++;
				}
				return (beg);
			}

			const_iterator upper_bound (const key_type& k) const { return (const_iterator(this->upper_bound(k))); }

			ft::pair<const_iterator, const_iterator> equal_range (const key_type& k) const { return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }

			ft::pair<iterator, iterator> equal_range (const key_type& k) { return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }

			allocator_type 	get_allocator() const { return allocator_type(_bst._alloc()); }

		private:

			template<class InputIterator>
        	difference_type distance (InputIterator first, InputIterator last) 	{
        	    typename ft::iterator_traits<InputIterator>::difference_type rtn = 0;
        	    while (first != last) {
        	        first++;
        	        rtn++;
        	    }
        	    return (rtn);
        	}

			allocator_type                          _alloc;
			Compare                                 _comp;
			Binary_search_tree<value_type, Compare>  _bst;

	};

	template <class Key, class T, class Compare, class Alloc>
  	bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		  return lhs == rhs;
	  }

	template <class Key, class T, class Compare, class Alloc>
  	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		  return !(lhs == rhs);
	  }
	
	template <class Key, class T, class Compare, class Alloc>
  	bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	  }
	
	template <class Key, class T, class Compare, class Alloc>
  	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		  return !(lhs > rhs);
	  }
	
	template <class Key, class T, class Compare, class Alloc>
  	bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		  return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	  }
	
	template <class Key, class T, class Compare, class Alloc>
  	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		  return !(lhs < rhs);
	  }
}

#endif















// namespace ft {

// 	template < class Key, class T, class Compare = less<Key>,class Alloc = std::allocator<pair<const Key, T> > >
// 	class map
// 	{
// 		public:
// 			typedef Key     						key_type;
// 			typedef T       						mapped_type;
// 			typedef pair<key_type, mapped_type> 	value_type;
// 			typedef Compare     					key_compare;

// 			class value_compare : std::binary_function<value_type, value_type, bool>		{
// 				friend class map<key_type, mapped_type, key_compare, Alloc>;
				
// 				protected:
// 					Compare comp;
// 					value_compare (Compare c) : comp(c) {}
				
// 				public:
// 					bool operator() (const value_type& x, const value_type& y) const
// 					{ return (comp(x.first, y.first)); }
// 			};

// 			typedef Alloc  														allocator_type;
// 			typedef typename allocator_type::reference   						reference;
// 			typedef typename allocator_type::const_reference 					const_reference;
// 			typedef typename allocator_type::pointer     						pointer;
// 			typedef typename allocator_type::const_pointer 						const_pointer;
// 			typedef typename tree<value_type, key_compare>::iterator 			iterator;
// 			typedef typename tree<value_type, key_compare>::const_iterator		const_iterator;
// 			typedef typename std::reverse_iterator<iterator>    				reverse_iterator;
// 			typedef typename std::reverse_iterator<const_iterator> 				const_reverse_iterator;
// 			typedef ptrdiff_t												 	difference_type;
// 			typedef size_t 														size_type;

// 		private:
// 			allocator_type                          _alloc;
// 			Compare                                 _comp;
// 			tree<value_type, Compare>  				_tree;
// 		public:
// 			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp),_tree()	{}

// 			template <class InputIterator>
// 			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),const allocator_type& alloc = allocator_type(),
// 			typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = NULL) :	_alloc(alloc),_comp(comp),_tree() {
// 				// bool is_valid;
// 				// if (!(is_valid = std::is_input_iterator_tagged<typename iterator_traits<InputIterator>::iterator_category >::value))
// 				// 	throw std::logic_error("map: logic error");
// 				this->insert(first, last);
// 			}

// 			map(const map& x) :	_alloc(x._alloc),_comp(x._comp),_tree()	{
// 				this->insert(x.begin(), x.end());
// 			}

// 			~map() { this->clear(); }

// 			map& operator= (const map& x)	{
// 				if (&x == this)
// 					return (*this);
// 				this->clear();
// 				this->insert(x.begin(), x.end());
// 				return (*this);
// 			}

// 			iterator begin(){ return (iterator(_tree._last_node->left, _tree._last_node)); }

// 			const_iterator begin() const{ return (const_iterator(_tree._last_node->left, _tree._last_node)); }

// 			iterator end() { return (iterator(_tree._last_node, _tree._last_node)); }

// 			const_iterator end() const	{ return (const_iterator(_tree._last_node, _tree._last_node)); }

// 			reverse_iterator rbegin() { return (reverse_iterator(this->end())); }

// 			const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->end())); }

// 			reverse_iterator rend() { return (reverse_iterator(this->begin())); }

// 			const_reverse_iterator rend() const	{ return (const_reverse_iterator(this->begin())); }

// 			bool empty() const	{ return (_tree._last_node->parent == _tree._last_node); }

// 			size_type size() const { return (_tree._last_node->value.first); }

// 			size_type max_size() const { return (_tree.max_size()); }

// 			mapped_type& operator[] (const key_type& k)	{
// 				iterator tmp = this->find(k);

// 				if (tmp == this->end())
// 					this->insert(make_pair(k, mapped_type()));
// 				tmp = this->find(k);
// 				return ((*tmp).second);
// 			} 

// 			pair<iterator,bool> insert (const value_type& val)	{ return (_tree.insertPair(val)); }

// 			iterator insert (iterator position, const value_type& val)	{(void)position; return (_tree.insertPair(val).first); }

// 			template <class InputIterator>
// 			void insert (InputIterator first, InputIterator last,
// 			typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
// 				// bool is_valid;
// 				// if (!(is_valid = std::is_input_iterator_tagged<typename iterator_traits<InputIterator>::iterator_category >::value))
// 				// 	throw std::logic_error("map: logic error");

// 				difference_type n = distance(first, last);
// 				while (n--)
// 					this->insert(*(first++));
// 			}

// 			void erase (iterator position)	{ this->erase((*position).first); }

// 			size_type erase (const key_type& k)	{
// 				if (this->find(k) == this->end())
// 					return (0);
// 				_tree.removeByKey(make_pair(k, mapped_type()));
// 				return (1);
// 			}

// 			void erase (iterator first, iterator last)	{
// 				while (first != last)
// 					this->erase((*(first++)).first);
// 			}

// 			void swap (map& x)	{ _tree.swap(x._tree); }

// 			void clear() { this->erase(this->begin(), this->end()); }

// 			key_compare key_comp() const { return (key_compare()); }

// 			value_compare value_comp() const { return (value_compare(key_compare())); }

// 			iterator find (const key_type& k) { return (iterator(_tree.searchByKey(make_pair(k, mapped_type())), _tree._last_node)); }

// 			const_iterator find (const key_type& k) const { return (const_iterator(_tree.searchByKey(make_pair(k, mapped_type())), _tree._last_node)); }

// 			size_type count (const key_type& k) const	{
// 				const_iterator beg = this->begin();
// 				const_iterator end = this->end();

// 				while (beg != end)
// 					if ((*(beg++)).first == k)
// 						return (1);
// 				return (0);
// 			}

// 			iterator lower_bound (const key_type& k) {
// 				iterator beg = this->begin();
// 				iterator end = this->end();

// 				while (beg != end)	{
// 					if (_comp((*beg).first, k) == false)
// 						break;
// 					beg++;
// 				}
// 				return (beg);
// 			}

// 			const_iterator lower_bound (const key_type& k) const { return (const_iterator(this->lower_bound(k))); }

// 			iterator upper_bound (const key_type& k) {
// 				iterator beg = this->begin();
// 				iterator end = this->end();

// 				while (beg != end)	{
// 					if (_comp(k, (*beg).first))
// 						break;
// 					beg++;
// 				}
// 				return (beg);
// 			}

// 			const_iterator upper_bound (const key_type& k) const { return (const_iterator(this->upper_bound(k))); }

// 			pair<const_iterator, const_iterator> equal_range (const key_type& k) const	{ return (make_pair(this->lower_bound(k), this->upper_bound(k))); }

// 			pair<iterator, iterator> equal_range (const key_type& k) { return (make_pair(this->lower_bound(k), this->upper_bound(k))); }

// 	};
// }































// 	// template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
// 	// class map	{
// 	// 	public:
// 	// 		typedef Key															key_type;
// 	// 		typedef T															mapped_type;
// 	// 		typedef ft::pair<const key_type, mapped_type>						value_type;
// 	// 		typedef Compare														key_compare;
// 	// 		typedef Alloc														allocator_type;
// 	// 		typedef typename allocator_type::value_type&						reference;
// 	// 		typedef typename allocator_type::const value_type&					const_reference;
// 	// 		typedef typename allocator_type::value_type*						pointer;
// 	// 		typedef typename allocator_type::const value_type*					const_pointer;

// 	// 		typedef ft::tree<value_type, value_compare, allocator_type> 		tree_type;
			
// 	// 		typedef typename ft::iterator_m<Key, T>								iterator;
// 	// 		typedef typename ft::iterator_m<const Key, const T>					const_iterator;
// 	// 		typedef typename std::reverse_iterator<iterator>					reverse_iterator;
// 	// 		typedef typename std::reverse_iterator<const_iterator>				const_reverse_iterator;
// 	// 		typedef typename ft::iterator_traits<iterator>::diffeerence_type	difference_type;
// 	// 		typedef size_t														size_type;
		
// 	// // template <class Key1, class T1, class Compare1, class Alloc1>
// 	// class value_compare : std::binary_function<value_type, value_type, bool>
// 	// {   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
// 	//   		friend class map;
// 	// 	protected:
// 	// 	  	Compare comp;
// 	// 	  	value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
// 	// 	public:
// 	// 	  	typedef bool result_type;
// 	// 	  	typedef value_type first_argument_type;
// 	// 	  	typedef value_type second_argument_type;
// 	// 	  	bool operator() (const value_type& x, const value_type& y) const {
// 	// 			return comp(x.first, y.first);
// 	// 	  	}
// 	// };
		
// 	// private:
// 	// 	allocator_type	_alloc;
// 	// 	tree_type		_tree;
// 	// 	key_compare		_comp;
// 	// 	size_type		_size;

// 	// 	// //(constructor)
// 	// 	// // empty (1)	
// 	// 	// explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
// 	// 	// // range (2)	
// 	// 	// template <class InputIterator>
//   	// 	// map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
// 	// 	// // copy (3)	
// 	// 	// map (const map& x);
		
// 	// 	// //(destructor)
// 	// 	// ~map();

// 	// 	// //operator=
// 	// 	// map& operator= (const map& x);

// 	// 	// //iterators
// 	// 	// iterator 									begin();
// 	// 	// const_iterator 								begin() const;
// 	// 	// iterator 									end();
// 	// 	// const_iterator 								end() const;
// 	// 	// reverse_iterator 							rbegin();
// 	// 	// const_reverse_iterator 						rbegin() const;
// 	// 	// reverse_iterator 							rend();
// 	// 	// const_reverse_iterator 						rend() const;

// 	// 	// //capacity
// 	// 	// bool 										empty() const;
// 	// 	// size_type 									size() const;
// 	// 	// size_type 									max_size() const;

// 	// 	// //Element access:
// 	// 	// mapped_type& 								operator[] (const key_type& k);

// 	// 	// //modifiers	
// 	// 	// std::pair<iterator,bool> 					insert (const value_type& val);	// single element (1)
// 	// 	// iterator 									insert (iterator position, const value_type& val);  // with hint (2)
// 	// 	// template <class InputIterator>
// 	// 	// void 										insert (InputIterator first, InputIterator last); // range (3)	
//     //  	// void 										erase (iterator position);
// 	// 	// size_type 									erase (const key_type& k);
//     //  	// void 										erase (iterator first, iterator last);
// 	// 	// void 										swap (map& x);
// 	// 	// void 										clear();

// 	// 	// //Observers:
// 	// 	// key_compare 									key_comp() const;
// 	// 	// value_compare 								value_comp() const;

// 	// 	// //operations
// 	// 	// iterator 									find (const key_type& k);
// 	// 	// const_iterator 								find (const key_type& k) const;
// 	// 	// size_type 									count (const key_type& k) const;
// 	// 	// iterator 									lower_bound (const key_type& k);
// 	// 	// const_iterator 								lower_bound (const key_type& k) const;
// 	//     // iterator 									upper_bound (const key_type& k);
// 	// 	// const_iterator 								upper_bound (const key_type& k) const;
// 	// 	// std::pair<const_iterator,const_iterator> 	equal_range (const key_type& k) const;
// 	// 	// std::pair<iterator,iterator>             	equal_range (const key_type& k);

// 	// 	// //Allocator
// 	// 	// allocator_type 								get_allocator() const;

// 	// 	// //Non-member functions
// 	// 	// template <class Key1, class T1, class Compare1, class Alloc1>
// 	// 	// friend bool operator== ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );
// 	// 	// template <class Key1, class T1, class Compare1, class Alloc1>
// 	// 	// friend bool operator!= ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );
// 	// 	// template <class Key1, class T1, class Compare1, class Alloc1>
// 	// 	// friend bool operator<  ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );
// 	// 	// template <class Key1, class T1, class Compare1, class Alloc1>
// 	// 	// friend bool operator<= ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );
// 	// 	// template <class Key1, class T1, class Compare1, class Alloc1>
// 	// 	// friend bool operator>  ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );
// 	// 	// template <class Key1, class T1, class Compare1, class Alloc1>
// 	// 	// friend bool operator>= ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );

// 	// 	// //(constructor)
// 	// 	explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
// 	// 		_alloc(alloc), _tree(tree_type(comp, alloc)), _comp(comp), _size(0) {}
		
// 	// 	template <class InputIterator>
//   	// 	map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), 
// 	// 	  typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0) :
// 	// 	   _alloc(alloc), _tree(first, last, compare, _alloc), _comp(comp), _size(0) {}
		
// 	// 	map (const map& x) { *this = x; }

// 	// 	map& operator= (const map& x) {
// 	// 		if (this == &x)
// 	// 			return *this;
// 	// 		_alloc = x._alloc;
// 	// 		_tree = x._tree;
// 	// 		_comp = x._comp;
// 	// 		_size = x._size;
// 	// 		const_iterator begin = x.begin();
// 	// 		const_iterator end = x.end();
// 	// 		insert(begin, end);
// 	// 		return *this;
// 	// 	}

// 	// 	mapped_type& 	operator[] (const key_type& k) {
// 	// 		return insert(make_pair(k, mapped_type())).first->second;
// 	// 	}
		
// 	// 	~map() {
// 	// 		clear();
// 	// 		_alloc.destroy();
// 	// 	}
		
// 	// 	//capacity
// 	// 	bool 					empty() const {	return _size == 0;	}
// 	// 	size_type 				size() const { return _size; }
// 	// 	size_type 				max_size() const { return _alloc.max_size(); }

// 	// 	// //iterators
// 	// 	iterator 				begin() { return _tree.begin(); }
// 	// 	const_iterator 			begin() const { return _tree.begin(); }
// 	// 	iterator 				end() { return _tree.end(); }
// 	// 	const_iterator 			end() const { return _tree.end(); }
// 	// 	reverse_iterator 		rbegin() { return reverse_iterator(end()); }
// 	// 	const_reverse_iterator 	rbegin() const { return reverse_iterator(end()); }
// 	// 	reverse_iterator 		rend() { return reverse_iterator(begin()); }
// 	// 	const_reverse_iterator 	rend() const { return reverse_iterator(begin()); }

// 	// 	//Allocator
// 	// 	allocator_type 			get_allocator() const { return allocator_type(_tree._alloc()); }

// 	// 	//modifiers	
// 	// 	// single element (1)
// 	// 	std::pair<iterator,bool> 					insert (const value_type& val) { return _tree.insert(val);}	
// 	// 	// with hint (2)
// 	// 	iterator 									insert (iterator position, const value_type& val) { return _tree.insert(position._node, val); }
// 	// 	// range (3)	
// 	// 	template <class InputIterator>
// 	// 	void 										insert (InputIterator first, InputIterator last) {
// 	// 		for (iterator it = end(); first != last; ++first)
// 	// 			insert(it._node, *first);
// 	// 	}

//     //  	void 										erase (iterator position) { _tree.erase(position._node); }
// 	// 	size_type 									erase (const key_type& k) { return _tree.erase_unique(k); }
//     //  	void 										erase (iterator f, iterator l) { _tree.erase(f._node, l._node); }
// 	// 	void 										clear() { _tree.clear(); }
// 	// 	void 										swap (map& x) { 
// 	// 		std::swap(_comp, x._comp);
// 	// 		std::swap(_size, x._size);
// 	// 		std::swap(_alloc, x._alloc);
// 	// 		_tree.swap(x._tree);
// 	// 	}

// 	// 	//Observers:
// 	// 	key_compare				key_comp() const {return _comp; }
// 	// 	value_compare			value_comp() const { return value_compare(_comp); }

// 	// 	// //operations
// 	// 	iterator 									find (const key_type& k) { return _tree.find(k); }
// 	// 	const_iterator 								find (const key_type& k) const { return _tree.find(k); }
// 	// 	size_type 									count (const key_type& k) const { return _tree.count(k); }
// 	// 	iterator 									lower_bound (const key_type& k) { return _tree.lower_bound(k); }
// 	// 	const_iterator 								lower_bound (const key_type& k) const { return _tree.lower_bound(k); }
// 	//     iterator 									upper_bound (const key_type& k) {  return _tree.upper_bound(k); }
// 	// 	const_iterator 								upper_bound (const key_type& k) const { return _tree.upper_bound(k); }
// 	// 	std::pair<iterator,iterator>             	equal_range (const key_type& k) { return _tree.equal_range(k);}
// 	// 	std::pair<const_iterator,const_iterator> 	equal_range (const key_type& k) const { return _tree.equal_range(k); }

// 	// };
	

// 	// template <class Key1, class T1, class Compare1, class Alloc1>
// 	// bool operator== ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );

// 	// template <class Key1, class T1, class Compare1, class Alloc1>
// 	// bool operator!= ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );

// 	// template <class Key1, class T1, class Compare1, class Alloc1>
// 	// bool operator<  ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );
		
// 	// template <class Key1, class T1, class Compare1, class Alloc1>
// 	// bool operator<= ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );

// 	// template <class Key1, class T1, class Compare1, class Alloc1>
// 	// bool operator>  ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );
		
// 	// template <class Key1, class T1, class Compare1, class Alloc1>
// 	// bool operator>= ( const map<Key1, T1, Compare1, Alloc1>& lhs, const map<Key1, T1, Compare1, Alloc1>& rhs );

// // }

// // namespace std {
// // 	template <class Key, class T, class Compare, class Alloc>
// // 	void swap (ft::map<Key,T,Compare,Alloc>& x, ft::map<Key,T,Compare,Alloc>& y) {
// // 		x.swap(y);
// //   }
// // }

// #endif