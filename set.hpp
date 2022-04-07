#ifndef SET_HPP
#define SET_HPP

#include "utils.hpp"
#include "tree.hpp"
#include <set>

namespace ft {
	template < class Key, class Compare = ft::less<Key>, class Alloc = std::allocator<Key> >
	class set {
		public:
			typedef Key																				key_type;
		    typedef key_type																		value_type;
		    typedef Compare																			key_compare;
		    typedef key_compare																		value_compare;
		    typedef Alloc																			allocator_type;
		    typedef value_type&																		reference;
		    typedef const value_type&																const_reference;
			typedef typename allocator_type::pointer												pointer;
			typedef typename allocator_type::const_pointer											const_pointer;
			typedef typename ft::Binary_search_tree<value_type, key_compare, allocator_type>		tree_type;
			typedef typename ft::Binary_search_tree<Node<value_type>*, value_type>::iterator		iterator;
			typedef typename ft::Binary_search_tree<Node<value_type>*, value_type>::const_iterator	const_iterator;
			typedef typename ft::reverse_iterator<iterator> 										reverse_iterator;
			typedef typename ft::const_reverse_iterator<iterator>									const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type								difference_type;
			typedef size_t																			size_type;
	private:
		tree_type  _tree;
	public:
		explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(tree_type(comp, alloc)) {}

		template <class InputIterator>
  		set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(tree_type(first, last, comp, alloc)) {}

		set (const set& x) : _tree(tree_type(x._tree)) {}

		~set() {}

		set& operator= (const set& x) { this->_tree = other._tree; return *this; }

		allocator_type get_allocator() const { return _tree.get_allocator(); }

		size_type size() const { return _tree.size(); }

		size_type max_size() const { return _tree.max_size(); }

		bool empty() const { return _tree.empty(); }

		value_compare value_comp() const { return _tree.value_comp(); }

		key_compare key_comp() const { return _tree.value_comp(); }

		iterator begin() { return _tree.begin(); }

		const_iterator begin() const { return _tree.begin(); }

		iterator end() { return _tree.end(); }

		const_iterator end() const { return _tree.end(); }

		reverse_iterator rbegin() { return _tree.rbegin(); }

		const_reverse_iterator rbegin() const { return _tree.rbegin(); }

		reverse_iterator rend() { return _tree.rend(); }
		
		const_reverse_iterator rend() const { return _tree.rend(); }

		void clear() { _tree.clear(); }

		void swap(set &s) { _tree.swap(s._tree); }

		iterator find(const Key& key) { return _tree.find(key); }
		
		const_iterator find(const Key& key) const { return _tree.find(key); }

		size_type count(const Key &key) const { return _tree.count(key); }

		iterator lower_bound(const key_type &k) { return _tree.lower_bound(k); }

		const_iterator lower_bound(const key_type &k) const { return _tree.lower_bound(k); }
	
		iterator upper_bound(const key_type &k) { return _tree.upper_bound(k); }

		const_iterator upper_bound(const key_type &k) const { return _tree.upper_bound(k); }

		pair<iterator, iterator> equal_range(const key_type &k) { return _tree.equal_range(k); }
		
		pair<const_iterator, const_iterator> equal_range(const key_type &k) const { return _tree.equal_range(k); }

		pair<iterator, bool> insert(const value_type &value) { return _tree.insert(value); }

		iterator insert (iterator position, const value_type& val) { return _tree.insert(position, val); }

		template <class InputIterator>
  		void insert (typename ft:enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::value first, InputIterator last) { _tree.insert(first, last); }
		
		void erase(iterator position) { _tree.erase(position); }

		size_type erase(const Key &k) { return _tree.erase(k); }

		void erase(iterator first, iterator last) { _tree.erase(first, last); }

		template<class K, class Comp, class Alloc>
		friend bool operator==(const set<K, Comp, Alloc>& lhs, const set<K, Comp, Alloc>& rhs);

		template<class K, class Comp, class Alloc>
		friend bool operator<(const set<K, Comp, Alloc>& lhs, const set<K, Comp, Alloc>& rhs);
	};

	template<class key, class comp, class alloc>
	bool operator==(const set<key, comp, alloc>& lhs, const set<key, comp, alloc>& rhs) { return lhs._tree == rhs._tree; }

	template<class key, class comp, class alloc>
	bool operator!=(const set<key, comp, alloc>& lhs, const set<key, comp, alloc>& rhs) { return !(lhs._tree == rhs._tree); }
	
	template<class key, class comp, class alloc>
	bool operator< (const set<key, comp, alloc>& lhs, const set<key, comp, alloc>& rhs) { return lhs._tree < rhs._tree); }

	template<class key, class comp, class alloc>
	bool operator> (const set<key, comp, alloc>& lhs, const set<key, comp, alloc>& rhs) { return rhs < lhs; }

	template<class key, class comp, class alloc>
	bool operator<= (const set<key, comp, alloc>& lhs, const set<key, comp, alloc>& rhs) { return !(lhs > rhs); }

	template<class key, class comp, class alloc>
	bool operator>= (const set<key, comp, alloc>& lhs, const set<key, comp, alloc>& rhs) { return !(lhs < rhs); }
}

namespace ft {
	template<class Key, class Compare, class Alloc>
	void swap(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs) { lhs.swap(rhs); }
}

#endif