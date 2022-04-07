#ifndef ITERATOR_M_HPP
#define ITERATOR_M_HPP

// #include "iterator.hpp"
#include "utils.hpp"

namespace ft {
	template<class TreeIt>
	class iterator_m	{
		typedef typename TreeIt::Node					Node;
		typedef typename TreeIt::ptr_traits				ptr_traits;

		TreeIt	_node; //*_node;

	public:
		typedef std::bidirectional_iterator_tag			iterator_category;
		typedef typename Node::map_value_type			value_type;
		typedef typename TreeIt::difference_type		difference_type;
		typedef value_type&								reference;
		typedef typename Node::map_value_type_pointer	pointer;

		iterator_m() : _node(0) {}
		iterator_m(TreeIt it) : _node(it) {}
		~iterator_m();
		reference	operator*() const								{ return this->_node->_key; }
		pointer		operator->() const								{ return &this->_node->_key; }
		iterator_m&	operator++() 									{ ++_node; return *this; }
		iterator_m	operator++(int) 								{ iterator_m _it(*this); ++(*this); return _it; }
		iterator_m&	operator--() 									{ --_node; return *this; }
		iterator_m	operator--(int) 								{ iterator_m _it(*this); --(*this); return _it; }
		friend bool operator==(const iterator_m& x, const iterator_m& y) 	{ return x._node == y._node; }
		friend bool operator!=(const iterator_m& x, const iterator_m& y) 	{ return x._node != y._node; }

	};
	
	template <typename T, class Compare >
	class tree_iterator : std::iterator<std::bidirectional_iterator_tag, T>	{
		public :
			typedef typename T::value_type    value_type;
			typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
			typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::difference_type   difference_type;
			typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::pointer   pointer;
			typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::reference reference;

			tree_iterator(const Compare& comp = Compare()) : _node(),_last_node(),_comp(comp){}

			tree_iterator(T * node_p, T * last_node, const Compare& comp = Compare()):_node(node_p), _last_node(last_node),
				_comp(comp)	{}

			tree_iterator(const tree_iterator& bst_it):_node(bst_it._node),_last_node(bst_it._last_node), _comp(){}

			~tree_iterator() { }

			tree_iterator &operator=(const tree_iterator& bst_it)
			{
				if (*this == bst_it)
					return (*this);
				this->_node = bst_it._node;
				this->_last_node = bst_it._last_node;
				this->_comp = bst_it._comp;
				return (*this);
			}

			bool operator==(const tree_iterator& bst_it)	{ return (this->_node == bst_it._node); }

			bool operator!=(const tree_iterator& bst_it) { return (this->_node != bst_it._node); }

			reference operator*() const	{ return (this->_node->value); }

			pointer operator->() const { return (&this->_node->value); }

			tree_iterator& operator++(void) {
				T* cursor = _node;
				if (_node->right == _last_node)
				{
					cursor = _node->parent;
					while (cursor != _last_node
						&& _comp(cursor->value.first, _node->value.first))
						cursor = cursor->parent;
					_node = cursor;
				}
				else if (cursor == _last_node)
					_node = _last_node->right;
				else
				{
					cursor = _node->right;
					if (cursor == _last_node->parent
						&& cursor->right == _last_node)
						_node = cursor;
					else
					{
						while (cursor->left != _last_node)
							cursor = cursor->left;
					}
					_node = cursor;
				}
				return (*this);
			}

			tree_iterator operator++(int){ tree_iterator tmp(*this); operator++(); return (tmp);	}

			tree_iterator& operator--(void) {
				T* cursor = _node;
				if (_node->left == _last_node)
				{
					cursor = _node->parent;
					while (cursor != _last_node
						&& !_comp(cursor->value.first, _node->value.first))
						cursor = cursor->parent;
					_node = cursor;
				}
				else if (cursor == _last_node)
					_node = _last_node->right;
				else
				{
					cursor = _node->left;
					if (cursor == _last_node->parent
						&& cursor->left == _last_node)
						_node = cursor;
					else
					{
						while (cursor->right != _last_node)
							cursor = cursor->right;
					}
					_node = cursor;
				}
				return (*this);
			}


			tree_iterator operator--(int) { tree_iterator tmp(*this);	operator--(); return (tmp);	}            

			T *			_node;
			T *			_last_node;
			Compare     _comp;
	};

	template <typename T, class Compare >
	class BST_iterator : std::iterator<std::bidirectional_iterator_tag, T>	{
		public :

			typedef typename T::value_type    value_type;
			typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
			typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::difference_type   difference_type;
			typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::pointer   pointer;
			typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::reference reference;
			
			BST_iterator(const Compare& comp = Compare()) : _node(), _last_node(), _comp(comp) {}
			BST_iterator(T * node_p, T * last_node,	const Compare& comp = Compare()) : _node(node_p),
				_last_node(last_node), _comp(comp)	{}

			BST_iterator(const BST_iterator& bst_it) : _node(bst_it._node),	_last_node(bst_it._last_node),
				_comp()	{}

			virtual ~BST_iterator() { }

			BST_iterator &operator=(const BST_iterator& bst_it)	{
				if (*this == bst_it)
					return (*this);
				this->_node = bst_it._node;
				this->_last_node = bst_it._last_node;
				this->_comp = bst_it._comp;
				return (*this);
			}

			bool operator==(const BST_iterator& bst_it)	{ return (this->_node == bst_it._node); }

			bool operator!=(const BST_iterator& bst_it)	{ return (this->_node != bst_it._node); }

			reference operator*() const	{ return (this->_node->value); }

			pointer operator->() const { return (&this->_node->value); }

			BST_iterator& operator++(void) {
				T* cursor = _node;

				if (_node->right == _last_node)
				{
					cursor = _node->parent;
					while (cursor != _last_node
						&& _comp(cursor->value.first, _node->value.first))
						cursor = cursor->parent;
					_node = cursor;
				}
				else if (cursor == _last_node)
					_node = _last_node->right;
				else
				{
					cursor = _node->right;
					if (cursor == _last_node->parent
						&& cursor->right == _last_node)
						_node = cursor;
					else
					{
						while (cursor->left != _last_node)
							cursor = cursor->left;
					}
					_node = cursor;
				}
				return (*this);
			}

			BST_iterator operator++(int) {
				BST_iterator tmp(*this);
				operator++();
				return (tmp);
			}

			BST_iterator& operator--(void)
			{
				T* cursor = _node;

				if (_node->left == _last_node)
				{
					cursor = _node->parent;
					while (cursor != _last_node
						&& !_comp(cursor->value.first, _node->value.first))
						cursor = cursor->parent;
					_node = cursor;
				}
				else if (cursor == _last_node)
					_node = _last_node->right;
				else
				{
					cursor = _node->left;
					if (cursor == _last_node->parent
						&& cursor->left == _last_node)
						_node = cursor;
					else
					{
						while (cursor->right != _last_node)
							cursor = cursor->right;
					}
					_node = cursor;
				}
				return (*this);
			}

			BST_iterator operator--(int) { BST_iterator tmp(*this);operator--(); return (tmp); }            

			T *			_node;
			T *			_last_node;
			Compare     _comp;
	};

	template <typename T, class Compare >
	class BST_const_iterator : std::iterator<std::bidirectional_iterator_tag, T>
	{
		public :

			typedef typename T::value_type    value_type;
			typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
			typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::difference_type   difference_type;
			typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::pointer   pointer;
			typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::reference reference;

			BST_const_iterator(const Compare& comp = Compare())	: _node(), _last_node(), _comp(comp) {}

			BST_const_iterator(T * node_p, T * last_node, const Compare& comp = Compare()) :
				_node(node_p),	_last_node(last_node),	_comp(comp)	{}

			BST_const_iterator(const BST_const_iterator& bst_it) : _node(bst_it._node),	_last_node(bst_it._last_node),
				_comp()	{}

			BST_const_iterator(const BST_iterator<T, Compare>& bst_it) : _node(bst_it._node),
				_last_node(bst_it._last_node),	_comp()	{}

			~BST_const_iterator() { }

			BST_const_iterator &operator=(const BST_const_iterator& bst_it)
			{
				if (*this == bst_it)
					return (*this);
				this->_node = bst_it._node;
				this->_last_node = bst_it._last_node;
				this->_comp = bst_it._comp;
				return (*this);
			}
			
			bool operator==(const BST_const_iterator& bst_it)
			{ return (this->_node == bst_it._node); }

			bool operator!=(const BST_const_iterator& bst_it)
			{ return (this->_node != bst_it._node); }

			reference operator*() const
			{ return (this->_node->value); }

			pointer operator->() const
			{ return (&this->_node->value); }

			BST_const_iterator& operator++(void)
			{
				T * cursor = _node;

				if (_node->right == _last_node)
				{
					cursor = _node->parent;
					while (cursor != _last_node
						&& _comp(cursor->value.first, _node->value.first))
						cursor = cursor->parent;
					_node = cursor;
				}
				else if (cursor == _last_node)
					_node = _last_node->right;
				else
				{
					cursor = _node->right;
					if (cursor == _last_node->parent
						&& cursor->right == _last_node)
						_node = cursor;
					else
					{
						while (cursor->left != _last_node)
							cursor = cursor->left;
					}
					_node = cursor;
				}
				return (*this);
			}

			BST_const_iterator operator++(int)
			{
				BST_const_iterator tmp(*this);
				operator++();
				return (tmp);
			}

			BST_const_iterator& operator--(void)
			{
				T * cursor = _node;

				if (_node->left == _last_node)
				{
					cursor = _node->parent;
					while (cursor != _last_node
						&& !_comp(cursor->value.first, _node->value.first))
						cursor = cursor->parent;
					_node = cursor;
				}
				else if (cursor == _last_node)
					_node = _last_node->right;
				else
				{
					cursor = _node->left;
					if (cursor == _last_node->parent
						&& cursor->left == _last_node)
						_node = cursor;
					else
					{
						while (cursor->right != _last_node)
							cursor = cursor->right;
					}
					_node = cursor;
				}
				return (*this);
			}

			BST_const_iterator operator--(int)
			{
				BST_const_iterator tmp(*this);
				operator--();
				return (tmp);
			}            

			T *         _node;
			T *         _last_node;
			Compare     _comp;
	};
// }

template <class Iterator>
    class reverse_iterator    {
        public:

            typedef Iterator    iterator_type;
            typedef typename std::iterator_traits<Iterator>::iterator_category iterator_category;
            typedef typename std::iterator_traits<Iterator>::value_type      value_type;
            typedef typename std::iterator_traits<Iterator>::difference_type     difference_type;
            typedef typename std::iterator_traits<Iterator>::pointer     pointer;
            typedef typename std::iterator_traits<Iterator>::reference   reference;
            
            reverse_iterator() : _elem() {}

            explicit reverse_iterator (iterator_type it) : _elem(it) {}

            template <class Iter>
            reverse_iterator (const reverse_iterator<Iter>& rev_it) : _elem(rev_it.base()) {}

            virtual ~reverse_iterator() {}

            iterator_type base() const { return (_elem); }

            reference operator*() const { iterator_type tmp = _elem; return (*(--tmp)); }

            reverse_iterator operator+ (difference_type n) const { return (reverse_iterator(_elem - n)); }

            reverse_iterator& operator++() { --_elem; return (*this); }

            reverse_iterator operator++(int) { reverse_iterator tmp = *this; ++(*this); return (tmp); }

            reverse_iterator& operator+= (difference_type n) { _elem -= n; return (*this); }

            reverse_iterator operator- (difference_type n) const { return (reverse_iterator(_elem + n)); }

            reverse_iterator& operator--() { ++_elem; return (*this); }

            reverse_iterator operator--(int) { reverse_iterator tmp = *this; --(*this); return (tmp); }

            reverse_iterator& operator-= (difference_type n) { _elem += n; return (*this); }

            pointer operator->() const { return &(operator*()); }
            reference operator[] (difference_type n) const { return (this->base()[-n - 1]); }

        private:
            iterator_type     _elem;
    };

    template <class Iterator>
        bool operator== (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() == rhs.base()); }

    template <class Iterator_L, class Iterator_R>
        bool operator== (const reverse_iterator<Iterator_L>& lhs,
                        const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() == rhs.base()); }

    template <class Iterator>
        bool operator!= (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() != rhs.base()); }

    template <class Iterator_L, class Iterator_R>
        bool operator!= (const reverse_iterator<Iterator_L>& lhs,
                        const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() != rhs.base()); }

    template <class Iterator>
        bool operator<  (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() > rhs.base()); }

    template <class Iterator_L, class Iterator_R>
        bool operator< (const reverse_iterator<Iterator_L>& lhs,
                        const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() > rhs.base()); }

    template <class Iterator>
        bool operator<= (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() >= rhs.base()); }

    template <class Iterator_L, class Iterator_R>
        bool operator<= (const reverse_iterator<Iterator_L>& lhs,
                        const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() >= rhs.base()); }

    template <class Iterator>
        bool operator> (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() < rhs.bash()); }

    template <class Iterator_L, class Iterator_R>
        bool operator> (const reverse_iterator<Iterator_L>& lhs,
                        const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() < rhs.base()); }

    template <class Iterator>
        bool operator>= (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() <= rhs.base()); }

    template <class Iterator_L, class Iterator_R>
        bool operator>= (const reverse_iterator<Iterator_L>& lhs,
                        const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() <= rhs.base()); }

    template <class Iterator>
        reverse_iterator<Iterator> operator+ (
            typename reverse_iterator<Iterator>::difference_type n,
            const reverse_iterator<Iterator>& rev_it) { return (rev_it + n); }

    template <class Iterator>
        typename reverse_iterator<Iterator>::difference_type operator- (
            const reverse_iterator<Iterator>& lhs,
            const reverse_iterator<Iterator>& rhs) { return (lhs.base() - rhs.base()); }

    template <class Iterator_L, class Iterator_R>
        bool operator- (const reverse_iterator<Iterator_L>& lhs,
                        const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() - rhs.base()); }
};

#endif


// namespace ft
// {
// 	template <typename T, class Compare >
// 	class tree_iterator : std::iterator<ft::bidirectional_iterator_tag, T>
// 	{
// 		public :

// 			typedef typename T::value_type    value_type;
// 			typedef typename std::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
// 			typedef typename std::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type   difference_type;
// 			typedef typename std::iterator<ft::bidirectional_iterator_tag, value_type>::pointer   pointer;
// 			typedef typename std::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;

// 			tree_iterator(const Compare& comp = Compare()) :	_node(),_last_node(),_comp(comp){}

// 			tree_iterator(T * node_p, T * last_node,	const Compare& comp = Compare()):_node(node_p),	_last_node(last_node),
// 				_comp(comp)	{}

// 			tree_iterator(const tree_iterator& bst_it):_node(bst_it._node),_last_node(bst_it._last_node),	_comp(){}

// 			virtual ~tree_iterator() { }

// 			tree_iterator &operator=(const tree_iterator& bst_it)
// 			{
// 				if (*this == bst_it)
// 					return (*this);
// 				this->_node = bst_it._node;
// 				this->_last_node = bst_it._last_node;
// 				this->_comp = bst_it._comp;
// 				return (*this);
// 			}

// 			bool operator==(const tree_iterator& bst_it)	{ return (this->_node == bst_it._node); }

// 			bool operator!=(const tree_iterator& bst_it) { return (this->_node != bst_it._node); }

// 			reference operator*() const	{ return (this->_node->value); }

// 			pointer operator->() const { return (&this->_node->value); }

// 			tree_iterator& operator++(void) {
// 				T* cursor = _node;
// 				if (_node->right == _last_node)
// 				{
// 					cursor = _node->parent;
// 					while (cursor != _last_node
// 						&& _comp(cursor->value.first, _node->value.first))
// 						cursor = cursor->parent;
// 					_node = cursor;
// 				}
// 				else if (cursor == _last_node)
// 					_node = _last_node->right;
// 				else
// 				{
// 					cursor = _node->right;
// 					if (cursor == _last_node->parent
// 						&& cursor->right == _last_node)
// 						_node = cursor;
// 					else
// 					{
// 						while (cursor->left != _last_node)
// 							cursor = cursor->left;
// 					}
// 					_node = cursor;
// 				}
// 				return (*this);
// 			}

// 			tree_iterator operator++(int){ tree_iterator tmp(*this); operator++(); return (tmp);	}

// 			tree_iterator& operator--(void) {
// 				T* cursor = _node;
// 				if (_node->left == _last_node)
// 				{
// 					cursor = _node->parent;
// 					while (cursor != _last_node
// 						&& !_comp(cursor->value.first, _node->value.first))
// 						cursor = cursor->parent;
// 					_node = cursor;
// 				}
// 				else if (cursor == _last_node)
// 					_node = _last_node->right;
// 				else
// 				{
// 					cursor = _node->left;
// 					if (cursor == _last_node->parent
// 						&& cursor->left == _last_node)
// 						_node = cursor;
// 					else
// 					{
// 						while (cursor->right != _last_node)
// 							cursor = cursor->right;
// 					}
// 					_node = cursor;
// 				}
// 				return (*this);
// 			}


// 			tree_iterator operator--(int) { tree_iterator tmp(*this);	operator--(); return (tmp);
// 			}            

// 			T *			_node;
// 			T *			_last_node;
// 			Compare     _comp;


// /*
// ** Binary Search Tree:
// ** Classement method of nodes values in tree. If a node value is
// ** superior to the a node, it's classed at right, otherwise at left
// ** if it's lower. Like :
// **
// **                  42
// **                 /  \
// **               15    58
// **              /  \
// **             2    26    
// */

// 	template <class T, class Compare = std::less<T>, class Node = ft::BST_Node<T>,
// 			class Type_Alloc = std::allocator<T>, class Node_Alloc = std::allocator<Node> >
// 	class Binary_search_tree {
// 		public :
// 			typedef Binary_search_tree  self;
// 			typedef self&   self_reference;
// 			typedef T   value_type;
// 			typedef Node node_type;
// 			typedef Node *  node_pointer;
// 			typedef Node_Alloc  node_alloc;
// 			typedef ft::tree_iterator<Node, Compare> iterator;
// 			typedef ft::BST_const_iterator<Node, Compare> const_iterator;
// 			typedef size_t size_type;

// 			Binary_search_tree (const node_alloc& node_alloc_init = node_alloc()) :	_node_alloc(node_alloc_init) {
// 				_last_node = _node_alloc.allocate(1);
// 				_node_alloc.construct(_last_node, Node(_last_node, _last_node, _last_node));
// 			}

// 			~Binary_search_tree () {
// 				_node_alloc.destroy(_last_node);
// 				_node_alloc.deallocate(_last_node, 1);	
// 			}

// 			ft::pair<iterator, bool> insertPair(value_type to_insert) {
// 				Node * new_node = _node_alloc.allocate(1);
// 				Node * prev_node = _last_node;
// 				Node * start_node = _last_node->parent;

// 				// side == false = left; side == true = right;
// 				bool side = true;

// 				while (start_node != _last_node) {
// 					int curkey = start_node->value.first;
// 					if (curkey == to_insert.first)
// 						return (ft::make_pair(iterator(start_node, _last_node), false));
// 					prev_node = start_node;
// 					if (to_insert.first > curkey)	{
// 						side = true;
// 						start_node = start_node->right;
// 					}
// 					else	{
// 						side = false;
// 						start_node = start_node->left;
// 					}
// 				}
// 				_node_alloc.construct(new_node, Node(to_insert, prev_node, _last_node, _last_node));
				
// 				if (prev_node == _last_node)
// 					_last_node->parent = new_node;
// 				else if (side == true)
// 					prev_node->right = new_node;
// 				else
// 					prev_node->left = new_node;
				
// 				_last_node->left = _BST_get_lower_node(_last_node->parent);
// 				_last_node->right = _BST_get_higher_node(_last_node->parent);
// 				_last_node->value.first += 1;
// 				return (ft::make_pair(iterator(new_node, _last_node), true));
// 			}

// 			void removeByKey(ft::value_type to_remove)	{ _removeByKey(_last_node->parent, to_remove); }

// 			node_pointer searchByKey(value_type to_remove)	{
// 				node_pointer node = _last_node->parent;

// 				while (node != _last_node)
// 				{
// 					if (node->value.first == to_remove.first)
// 						return (node);
// 					if (node->value.first > to_remove.first)
// 						node = node->left;
// 					else
// 						node = node->right;
// 				}
// 				return (node);
// 			}

// 			void swap(self& x)	{
// 				if (&x == this)
// 					return ;
				
// 				node_pointer save = this->_last_node;
// 				this->_last_node = x._last_node;
// 				x._last_node = save;
// 			}

// 			size_type max_size() const { return (node_alloc().max_size()); }

// 			node_pointer    _last_node;
// 			node_alloc      _node_alloc;

// 		private :
// 			node_pointer _BST_get_lower_node(node_pointer root)	{
// 				while (root != _last_node && root->left != _last_node)
// 					root = root->left;
// 				return (root);
// 			}

// 			node_pointer _BST_get_higher_node(node_pointer root) {
// 				while (root != _last_node && root->right != _last_node)
// 					root = root->right;
// 				return (root);
// 			}

// 			void _replaceNodeInParent(node_pointer node, node_pointer new_node)	{
// 				if (node->parent != _last_node)	{
// 					if (_last_node->parent == node)
// 						_last_node->parent = new_node;

// 					if (node == node->parent->left)
// 						node->parent->left = new_node;
// 					else
// 						node->parent->right = new_node;
// 				}
// 				else
// 					_last_node->parent = new_node;

// 				_last_node->left = _BST_get_lower_node(_last_node->parent);
// 				_last_node->right = _BST_get_higher_node(_last_node->parent);
// 				_last_node->value.first -= 1;
				
// 				new_node->parent = node->parent;
				
// 				_node_alloc.destroy(node);
// 				_node_alloc.deallocate(node, 1);
// 			}

// 			void _replaceDoubleChildren(node_pointer& to_remove, node_pointer new_node)	{
// 				if (new_node->parent != _last_node)	{
// 					if (new_node->parent != to_remove)
// 						new_node->parent->left = new_node->right;
// 				}
				
// 				new_node->parent = to_remove->parent;
// 				if (to_remove->left != new_node)
// 					new_node->left = to_remove->left;
// 				if (to_remove->right != new_node)
// 					new_node->right = to_remove->right;

// 				if (to_remove->parent != _last_node) {
// 					if (to_remove->parent->left == to_remove)
// 						to_remove->parent->left = new_node;
// 					else if (to_remove->parent->right == to_remove)
// 						to_remove->parent->right = new_node;
// 				}
// 				else
// 					_last_node->parent = new_node;
					
// 				if (to_remove->left != _last_node && to_remove->left != new_node)
// 					to_remove->left->parent = new_node;
// 				if (to_remove->right != _last_node && to_remove->right != new_node)
// 					to_remove->right->parent = new_node;

// 				if (to_remove->parent != _last_node) {
// 					to_remove->left = _last_node;
// 					to_remove->right = _last_node;
// 					to_remove->parent = new_node;
// 				}

// 				_last_node->left = _BST_get_lower_node(_last_node->parent);
// 				_last_node->right = _BST_get_higher_node(_last_node->parent);
// 				_last_node->value.first -= 1;

// 				_node_alloc.destroy(to_remove);
// 				_node_alloc.deallocate(to_remove, 1);
// 			}

// 			void _removeByKey(node_pointer node, value_type to_remove)	{
// 				if (to_remove.first < node->value.first) {
// 					_removeByKey(node->left, to_remove);
// 					return ;
// 				}

// 				if (to_remove.first > node->value.first) {
// 					_removeByKey(node->right, to_remove);
// 					return ;
// 				}

// 				if (node->left != _last_node && node->right != _last_node)	{
// 					node_pointer successor = _BST_get_lower_node(node->right);
// 					_replaceDoubleChildren(node, successor);
// 					return ;
// 				}
// 				else if (node->left != _last_node)
// 					_replaceNodeInParent(node, node->left);
// 				else if (node->right != _last_node)
// 					_replaceNodeInParent(node, node->right);
// 				else
// 					_replaceNodeInParent(node, _last_node);
// 			}
// 	};
// };
