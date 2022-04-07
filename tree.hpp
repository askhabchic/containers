#ifndef TREE_HPP
#define TREE_HPP

#include "utils.hpp"
#include "iterator_m.hpp"
#include <memory>


namespace ft {
	template <typename T>
    struct BST_Node {
        public :
            typedef T   value_type;

            value_type value;
            BST_Node* parent;
            BST_Node* left;
            BST_Node* right;

            BST_Node () : value(), parent(NULL), left(NULL), right(NULL) {}

            BST_Node (BST_Node* parent = NULL, BST_Node* left = NULL, BST_Node* right = NULL) : value(), parent(parent), left(left), right(right) {}
            
            BST_Node (const value_type& val, BST_Node* parent = NULL, BST_Node* left = NULL, BST_Node* right = NULL) : value(val), parent(parent), left(left), right(right) {}

            BST_Node (const BST_Node& nd) : value(nd.value), parent(nd.parent), left(nd.left), right(nd.right) {}

            virtual ~BST_Node() {}

            BST_Node &operator=(const BST_Node& nd) {
                if (nd == *this)
                    return (*this);
                this->value = nd.value;
                this->parent = nd.parent;
                this->left = nd.left;
                this->right = nd.right;
                return (*this);
            }

            bool operator==(const BST_Node& nd) {
                if (value == nd.value)
                    return (true);
                return (false);
            }
    };

	template <class T, class Compare = ft::less<T>, class Node = ft::BST_Node<T>,
			class Type_Alloc = std::allocator<T>, class Node_Alloc = std::allocator<Node> >
	class Binary_search_tree {
		public :

			typedef Binary_search_tree						self;
			typedef self&									self_reference;
			typedef T										value_type;
			typedef Node									node_type;
			typedef Node *									node_pointer;
			typedef Node_Alloc								node_alloc;
			typedef ft::BST_iterator<Node, Compare>			iterator;
			typedef ft::BST_const_iterator<Node, Compare>	const_iterator;
			typedef size_t									size_type;

			Binary_search_tree (const node_alloc& node_alloc_init = node_alloc()) :	_node_alloc(node_alloc_init) {
				_last_node = _node_alloc.allocate(1);
				_node_alloc.construct(_last_node, Node(_last_node, _last_node, _last_node));
			}

			~Binary_search_tree () {
				_node_alloc.destroy(_last_node);
				_node_alloc.deallocate(_last_node, 1);	
			}

			ft::pair<iterator, bool> insertPair(value_type to_insert) {
				Node * new_node = _node_alloc.allocate(1);
				Node * prev_node = _last_node;
				Node * start_node = _last_node->parent;

				// side == false = left; side == true = right;
				bool side = true;

				while (start_node != _last_node) {
					int curkey = start_node->value.first;
					if (curkey == to_insert.first)
						return (ft::make_pair(iterator(start_node, _last_node), false));
					prev_node = start_node;
					if (to_insert.first > curkey) {
						side = true;
						start_node = start_node->right;
					}
					else {
						side = false;
						start_node = start_node->left;
					}
				}
				_node_alloc.construct(new_node, Node(to_insert, prev_node, _last_node, _last_node));
				
				if (prev_node == _last_node)
					_last_node->parent = new_node;
				else if (side == true)
					prev_node->right = new_node;
				else
					prev_node->left = new_node;
				
				_last_node->left = _BST_get_lower_node(_last_node->parent);
				_last_node->right = _BST_get_higher_node(_last_node->parent);
				_last_node->value.first += 1;
				return (ft::make_pair(iterator(new_node, _last_node), true));
			}

			void removeByKey(value_type to_remove) { _removeByKey(_last_node->parent, to_remove); }

			node_pointer searchByKey(value_type to_remove) {
				node_pointer node = _last_node->parent;

				while (node != _last_node) {
					if (node->value.first == to_remove.first)
						return (node);
					if (node->value.first > to_remove.first)
						node = node->left;
					else
						node = node->right;
				}
				return (node);
			}

			void swap(self& x)	{
				if (&x == this)
					return ;
				
				node_pointer save = this->_last_node;
				this->_last_node = x._last_node;
				x._last_node = save;
			}

			size_type max_size() const { return (node_alloc().max_size()); }

			node_pointer    _last_node;
			node_alloc      _node_alloc;

		private :

			node_pointer _BST_get_lower_node(node_pointer root)	{
				while (root != _last_node && root->left != _last_node)
					root = root->left;
				return (root);
			}

			node_pointer _BST_get_higher_node(node_pointer root) {
				while (root != _last_node && root->right != _last_node)
					root = root->right;
				return (root);
			}

			void _replaceNodeInParent(node_pointer node, node_pointer new_node)	{
				if (node->parent != _last_node)	{
					if (_last_node->parent == node)
						_last_node->parent = new_node;

					if (node == node->parent->left)
						node->parent->left = new_node;
					else
						node->parent->right = new_node;
				}
				else
					_last_node->parent = new_node;

				_last_node->left = _BST_get_lower_node(_last_node->parent);
				_last_node->right = _BST_get_higher_node(_last_node->parent);
				_last_node->value.first--;
				
				new_node->parent = node->parent;
				
				_node_alloc.destroy(node);
				_node_alloc.deallocate(node, 1);
			}

			void _replaceDoubleChildren(node_pointer& to_remove, node_pointer new_node)	{
				if (new_node->parent != _last_node)	{
					if (new_node->parent != to_remove)
						new_node->parent->left = new_node->right;
				}
				
				new_node->parent = to_remove->parent;
				if (to_remove->left != new_node)
					new_node->left = to_remove->left;
				if (to_remove->right != new_node)
					new_node->right = to_remove->right;

				if (to_remove->parent != _last_node) {
					if (to_remove->parent->left == to_remove)
						to_remove->parent->left = new_node;
					else if (to_remove->parent->right == to_remove)
						to_remove->parent->right = new_node;
				}
				else
					_last_node->parent = new_node;
					
				if (to_remove->left != _last_node && to_remove->left != new_node)
					to_remove->left->parent = new_node;
				if (to_remove->right != _last_node && to_remove->right != new_node)
					to_remove->right->parent = new_node;

				if (to_remove->parent != _last_node) {
					to_remove->left = _last_node;
					to_remove->right = _last_node;
					to_remove->parent = new_node;
				}

				_last_node->left = _BST_get_lower_node(_last_node->parent);
				_last_node->right = _BST_get_higher_node(_last_node->parent);
				_last_node->value.first--;

				_node_alloc.destroy(to_remove);
				_node_alloc.deallocate(to_remove, 1);
			}

			void _removeByKey(node_pointer node, value_type to_remove) {
				if (to_remove.first < node->value.first) {
					_removeByKey(node->left, to_remove);
					return ;
				}

				if (to_remove.first > node->value.first) {
					_removeByKey(node->right, to_remove);
					return ;
				}

				if (node->left != _last_node && node->right != _last_node) {
					node_pointer successor = _BST_get_lower_node(node->right);
					_replaceDoubleChildren(node, successor);
					return ;
				}
				else if (node->left != _last_node)
					_replaceNodeInParent(node, node->left);
				else if (node->right != _last_node)
					_replaceNodeInParent(node, node->right);
				else
					_replaceNodeInParent(node, _last_node);
			}
	};
}
class TreeNodeValue;

class Node {
public:
    Node*           left;
    Node*           right;
    Node*           parent;
    bool            red;
    TreeNodeValue*  value;  // The value of tree node: normally, it is
                           //     a pair (key, value of key)
    Node() : left(0), right(0), parent(0), red(false), value(0) {}
};

typedef Node* NodePtr;

class TreeNodeValue {
public:
    TreeNodeValue() {}
    virtual ~TreeNodeValue() {}

    virtual int compareTo(const TreeNodeValue&) const = 0;

    bool operator==(const TreeNodeValue& k) const { return (compareTo(k) == 0); }
    bool operator!=(const TreeNodeValue& k) const { return (compareTo(k) != 0); }
    bool operator<(const TreeNodeValue& k) const { return (compareTo(k) < 0); }
    bool operator<=(const TreeNodeValue& k) const { return (compareTo(k) <= 0); }
    bool operator>(const TreeNodeValue& k) const { return (compareTo(k) > 0); }
    bool operator>=(const TreeNodeValue& k) const { return (compareTo(k) >= 0); }
};

// Every node of Red-Black tree is of red of black color.
// A leaf is an external NULL-node and has the black color.
// The root is black.
// The sons of red node must be black.
// Every path from the root to a leaf has the same number
// of black nodes (not including a root, but including a leaf).
class Tree {
public:
    // Header contains a pointer to the root of the tree as a left son.
    // The tree may be empty, in this case header->left == 0
    Node  header;
    int numNodes;

    Tree() : header(), numNodes(0) { header.red = true; }
    ~Tree() { clear(); }

    void clear() {removeSubtree(root());}
    void erase() { clear(); }
    void removeAll() { clear(); }


    Node* root() { return header.left; }
    const Node* root() const { return header.left; }

    int size() const { return numNodes; }

    // Find a key in a subtree
    // In: key         -- a key to find;
    //     subTreeRoot -- a root of a subtree. If subTreeRoot == 0,
    //                    then find in complete tree
    // Out: node       -- a pointer to the node that contains a key,
    //                    if key is in the set,
    //                    or a pointer to a node that should be parent to
    //                    the node with the key given.
    // Return value: 0,   if the key is found;
    //               < 0, if the key is not found, and the key is less
    //                       than the value in the node;
    //               > 0, if the key is not found, and the key is greater
    //                       than the value in the node.
    int find(const TreeNodeValue* key, const Node* subTreeRoot = 0, NodePtr* node = 0) const {
        const Node* x;
        const Node* y;
        if (!subTreeRoot) {
            x = root();
            y = &header;
        } else {
            x = subTreeRoot;
            y = x->parent;
        }
        int n = (-1);
        while (x) {
            const TreeNodeValue* current = x->value;
            n = key->compareTo(*current);
            y = x;
            if (!n) {
                if (node) 
                    *node = const_cast<Node*>(x);
                return 0;
            } else if (n < 0)
                x = x->left;
            else
                x = x->right;
        }
        if (node)
            *node = const_cast<Node*>(y);
        return n;
    }

    // Insert a key into the tree:
    //     create a new node and insert it as a leaf.
    // The color of a new node is red.
    // Should be called after the "find" method, which has returned
    //        a nonzero value (i.e. a key was not found)
    // Input: compare = result of comparing with a key of a parent node
    void insert(Node* parentNode,TreeNodeValue* key, int compare ) {
        assert(parentNode && compare);
        Node* x = new Node();
        x->value = key;
        x->parent = parentNode;
        if (parentNode == &header)
            x->red = false;
        else
            x->red = true;
        if (compare < 0) {
            assert(parentNode->left == 0);
            parentNode->left = x;
        } else {
            assert(parentNode != &header && parentNode->right == 0);
            parentNode->right = x;
        }
        ++numNodes;
        if (x != root())
            rebalanceAfterInsert(x);        
    }

    void rotateLeft(Node* x) {
        Node* y = x->right;
        assert(y);
        Node* p = x->parent;
        y->parent = p;
        if (x == p->left)
            p->left = y;
        else
            p->right = y;
        x->right = y->left;
        if (y->left)
            y->left->parent = x;
        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node* x) {
        Node* y = x->left;
        assert(y);
        Node* p = x->parent;
        y->parent = p;
        if (x == p->left)
            p->left = y;
        else
            p->right = y;
        x->left = y->right;
        if (y->right)
            y->right->parent = x;
        y->right = x;
        x->parent = y;
    }

    void rebalanceAfterInsert(Node* x) {
        assert(x->red);
        while (x != root() && x->parent->red) {
            if (x->parent == x->parent->parent->left) {
                Node* y = x->parent->parent->right;
                if (y && y->red) {
                    x->parent->red = false;
                    y->red = false;
                    x = x->parent->parent;
                    x->red = true;
                } else {
                    if (x == x->parent->right) {
                        x = x->parent;
                        rotateLeft(x);
                    }
                    assert(x == x->parent->left);
                    x->parent->red = false;
                    x->parent->parent->red = true;
                    rotateRight(x->parent->parent);
                }
            } else {
                assert(x->parent == x->parent->parent->right);
                Node* y = x->parent->parent->left;
                if (y && y->red) {
                    x->parent->red = false;
                    y->red = false;
                    x = x->parent->parent;
                    x->red = true;
                } else {
                    if (x == x->parent->left) {
                        x = x->parent;
                        rotateRight(x);
                    }
                    assert(x == x->parent->right);
                    x->parent->red = false;
                    x->parent->parent->red = true;
                    rotateLeft(x->parent->parent);
                }
            }
        }
        if (x == root())
            x->red = false;
    }

    int removeSubtree(Node* subTreeRoot) {
        int numRemoved = 0;
        if (!subTreeRoot)
            return 0;
        if (subTreeRoot->left)
            numRemoved += removeSubtree(subTreeRoot->left);
        if (subTreeRoot->right)
            numRemoved += removeSubtree(subTreeRoot->right);
        if (subTreeRoot->parent->left == subTreeRoot)
            subTreeRoot->parent->left = 0;
        else
            subTreeRoot->parent->right = 0;
        eraseNode(subTreeRoot);
        delete subTreeRoot;
        ++numRemoved;
        --numNodes;
        assert(numNodes >= 0);
        return numRemoved;
    }

    const Node* minimalNode(const Node* subTreeRoot = 0) const {
        const Node* x = subTreeRoot;
        if (!x)
            x = root();
        while (x && x->left)
            x = x->left;
        return x;
    }

    Node* minimalNode(const Node* subTreeRoot = 0) { return const_cast<Node*>(((const Tree*) this)->minimalNode(subTreeRoot)); }

    const Node* maximalNode(const Node* subTreeRoot = 0) const {
        const Node* x = subTreeRoot;
        if (!x)
            x = root();
        while (x && x->right)
            x = x->right;
        return x;
    }
    
    Node* maximalNode(const Node* subTreeRoot = 0) { return const_cast<Node*>(((const Tree*) this)->maximalNode(subTreeRoot)); }

    const Node* nextNode(const Node* node) const {
        assert(node);
        if (node == &header)
            return minimalNode();
        if (node->right)
            return minimalNode(node->right);
        else if (node == node->parent->left)
            return node->parent;
        else {
            const Node* x = node->parent;
            while (Node* x = node->parent)
                x = x->parent;
            return x->parent;
        }
    }

    Node* nextNode(Node* node) { return const_cast<Node*>(((const Tree*) this)->nextNode(node)); }

    const Node* previousNode(const Node* node) const {
        assert(node);
        if (node == minimalNode())
            return &header;
        if (node->left)
            return maximalNode(node->left);
        else if (node == node->parent->right)
            return node->parent;
        else {
            const Node* x = node->parent;
            while (x->parent && x == x->parent->left)
             x = x->parent;
            if (x->parent)
                return x->parent;
            else {
                assert(x == &header);
                return x;
            }
        }
    }

    Node* previousNode(Node* node) { return (Node*)(const_cast<Tree*>(this)->previousNode(node)); }

protected:
    void eraseNode(Node* node) { delete node->value; }

public:
    class const_iterator {
    protected:
        const Tree* tree;
        const Node* node;
    public:
        const_iterator(): tree(0), node(0) {}
        const_iterator( const Tree* t, const Node* n) : tree(t), node(n) {}
        bool operator==(const const_iterator& i) const { return (tree == i.tree && node == i.node); }
        bool operator!=(const const_iterator& i) const { return !operator==(i); }
        const_iterator& operator++() { node = tree->nextNode(node); return *this; }
        const_iterator& operator--() { node = tree->previousNode(node); return *this; }
        const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp; }
        const_iterator operator--(int) { const_iterator tmp = *this; --(*this); return tmp; }
        const Node& operator*() const { return *node; }
        const Node* operator->() const { return node; }
    };

    class iterator : public const_iterator {
    public:
        iterator() : const_iterator()   {}
        iterator(Tree* t, Node* n) : const_iterator(t, n)  {}
        Node& operator*() const {return const_cast<Node&>(((const const_iterator*) this)->operator*()); }
        Node* operator->() const {return const_cast<Node*>(((const const_iterator*) this)->operator->()); }
    };

    iterator begin() {return iterator(this, minimalNode());    }
    const_iterator begin() const {return const_iterator(this, minimalNode());    }
    iterator end() {return iterator(this, &header);    }
    const_iterator end() const {return const_iterator(this, &header);    }
};



    // template <typename T>
    // struct node    {
    //     public :
    //         typedef T   value_type;
    //         value_type value;
    //         node* parent;
    //         node* left;
    //         node* right;

    //         node () : value(), parent(NULL), left(NULL), right(NULL) {}
    //         node (node* parent = NULL, node* left = NULL, node* right = NULL) :  value(), parent(parent), left(left), right(right) {}
    //         node (const value_type& val, node* parent = NULL, node* left = NULL, node* right = NULL) : value(val), parent(parent),left(left),right(right) {}
    //         node (const node& nd) : value(nd.value),parent(nd.parent),left(nd.left),right(nd.right) {}
    //         ~node() {}

    //         node &operator=(const node& nd) {
    //             if (nd == *this)
    //                 return (*this);
    //             this->value = nd.value;
    //             this->parent = nd.parent;
    //             this->left = nd.left;
    //             this->right = nd.right;           
    //             return (*this);
    //         }
    //         bool operator==(const node& nd) {
    //             if (value == nd.value)
    //                 return (true);
    //             return (false);
    //         }
    // 	};

	// template <class T, class Compare = ft::less<T>, class Node = node<T>, class Type_Alloc = std::allocator<T>, class Node_Alloc = std::allocator<Node> >
	// class tree {
	// 	public :
	// 		typedef tree  self;
	// 		typedef self&   self_reference;
	// 		typedef T   value_type;
	// 		typedef Node node_type;
	// 		typedef Node *  node_pointer;
	// 		typedef Node_Alloc  node_alloc;
	// 		typedef ft::tree_iterator<Node, Compare> iterator;
	// 		typedef ft::tree_iterator<const Node, const Compare> const_iterator;
	// 		typedef size_t size_type;

	// 		tree (const node_alloc& node_alloc_init = node_alloc()) : _node_alloc(node_alloc_init) {
	// 			_last_node = _node_alloc.allocate(1);
	// 			_node_alloc.construct(_last_node, Node(_last_node, _last_node, _last_node));
	// 		}

	// 		~tree () {
	// 			_node_alloc.destroy(_last_node);
	// 			_node_alloc.deallocate(_last_node, 1);	
	// 		}

	// 		ft::pair<iterator, bool> insertPair(value_type to_insert) {
	// 			Node * new_node = _node_alloc.allocate(1);
	// 			Node * prev_node = _last_node;
	// 			Node * start_node = _last_node->parent;

	// 			// side == false = left; side == true = right;
	// 			bool side = true;

	// 			while (start_node != _last_node) {
	// 				int curkey = start_node->value.first;
	// 				if (curkey == to_insert.first)
	// 					return (ft::make_pair(iterator(start_node, _last_node), false));
	// 				prev_node = start_node;
	// 				if (to_insert.first > curkey)	{
	// 					side = true;
	// 					start_node = start_node->right;
	// 				}
	// 				else	{
	// 					side = false;
	// 					start_node = start_node->left;
	// 				}
	// 			}
	// 			_node_alloc.construct(new_node, Node(to_insert, prev_node, _last_node, _last_node));
				
	// 			if (prev_node == _last_node)
	// 				_last_node->parent = new_node;
	// 			else if (side == true)
	// 				prev_node->right = new_node;
	// 			else
	// 				prev_node->left = new_node;
				
	// 			_last_node->left = _get_lower_node(_last_node->parent);
	// 			_last_node->right = _get_higher_node(_last_node->parent);
	// 			_last_node->value.first += 1;
	// 			return (ft::make_pair(iterator(new_node, _last_node), true));
	// 		}

	// 		void removeByKey(value_type to_remove)	{ _removeByKey(_last_node->parent, to_remove); }

	// 		node_pointer searchByKey(value_type to_remove)	{
	// 			node_pointer node = _last_node->parent;

	// 			while (node != _last_node)
	// 			{
	// 				if (node->value.first == to_remove.first)
	// 					return (node);
	// 				if (node->value.first > to_remove.first)
	// 					node = node->left;
	// 				else
	// 					node = node->right;
	// 			}
	// 			return (node);
	// 		}

	// 		void swap(self& x)	{
	// 			if (&x == this)
	// 				return ;
				
	// 			node_pointer save = this->_last_node;
	// 			this->_last_node = x._last_node;
	// 			x._last_node = save;
	// 		}

	// 		size_type max_size() const { return (node_alloc().max_size()); }

	// 		node_pointer    _last_node;
	// 		node_alloc      _node_alloc;

	// 	private :
	// 		node_pointer _get_lower_node(node_pointer root)	{
	// 			while (root != _last_node && root->left != _last_node)
	// 				root = root->left;
	// 			return (root);
	// 		}

	// 		node_pointer _get_higher_node(node_pointer root) {
	// 			while (root != _last_node && root->right != _last_node)
	// 				root = root->right;
	// 			return (root);
	// 		}

	// 		void _replaceNodeInParent(node_pointer node, node_pointer new_node)	{
	// 			if (node->parent != _last_node)	{
	// 				if (_last_node->parent == node)
	// 					_last_node->parent = new_node;

	// 				if (node == node->parent->left)
	// 					node->parent->left = new_node;
	// 				else
	// 					node->parent->right = new_node;
	// 			}
	// 			else
	// 				_last_node->parent = new_node;

	// 			_last_node->left = _get_lower_node(_last_node->parent);
	// 			_last_node->right = _get_higher_node(_last_node->parent);
	// 			_last_node->value.first -= 1;
				
	// 			new_node->parent = node->parent;
				
	// 			_node_alloc.destroy(node);
	// 			_node_alloc.deallocate(node, 1);
	// 		}

	// 		void _replaceDoubleChildren(node_pointer& to_remove, node_pointer new_node)	{
	// 			if (new_node->parent != _last_node)	{
	// 				if (new_node->parent != to_remove)
	// 					new_node->parent->left = new_node->right;
	// 			}
				
	// 			new_node->parent = to_remove->parent;
	// 			if (to_remove->left != new_node)
	// 				new_node->left = to_remove->left;
	// 			if (to_remove->right != new_node)
	// 				new_node->right = to_remove->right;

	// 			if (to_remove->parent != _last_node) {
	// 				if (to_remove->parent->left == to_remove)
	// 					to_remove->parent->left = new_node;
	// 				else if (to_remove->parent->right == to_remove)
	// 					to_remove->parent->right = new_node;
	// 			}
	// 			else
	// 				_last_node->parent = new_node;
					
	// 			if (to_remove->left != _last_node && to_remove->left != new_node)
	// 				to_remove->left->parent = new_node;
	// 			if (to_remove->right != _last_node && to_remove->right != new_node)
	// 				to_remove->right->parent = new_node;

	// 			if (to_remove->parent != _last_node) {
	// 				to_remove->left = _last_node;
	// 				to_remove->right = _last_node;
	// 				to_remove->parent = new_node;
	// 			}

	// 			_last_node->left = _get_lower_node(_last_node->parent);
	// 			_last_node->right = _get_higher_node(_last_node->parent);
	// 			_last_node->value.first -= 1;

	// 			_node_alloc.destroy(to_remove);
	// 			_node_alloc.deallocate(to_remove, 1);
	// 		}

	// 		void _removeByKey(node_pointer node, value_type to_remove)	{
	// 			if (to_remove.first < node->value.first) {
	// 				_removeByKey(node->left, to_remove);
	// 				return ;
	// 			}

	// 			if (to_remove.first > node->value.first) {
	// 				_removeByKey(node->right, to_remove);
	// 				return ;
	// 			}

	// 			if (node->left != _last_node && node->right != _last_node)	{
	// 				node_pointer successor = _get_lower_node(node->right);
	// 				_replaceDoubleChildren(node, successor);
	// 				return ;
	// 			}
	// 			else if (node->left != _last_node)
	// 				_replaceNodeInParent(node, node->left);
	// 			else if (node->right != _last_node)
	// 				_replaceNodeInParent(node, node->right);
	// 			else
	// 				_replaceNodeInParent(node, _last_node);
	// 		}
	// };
// };








	// enum RBcolor { Black, Red };

	// template <class T>
	// struct node {
	// 	public:
	// 		T			key;
	// 		RBcolor		color;
	// 		struct node *begin, *left, *right, *parent;
	// 		value_type	*pair;
	// 		// node<T> *	_right;
	// 		// node<T> *	_parent;
	// 		node() : key(0), color(0), begin(NULL), left(this), right(this), parent(0), pair(new value_type()) { };
	// 		node(const value_type& val) : key(k), color(c), parent(p), left(l), right(r) { };
	// 		// node(T k, RBcolor c, node* p, node* l, node *r) : key(k), color(c), parent(p), left(l), right(r) { };
	// 		~node() { delete pair; }
	// };

	// template <class T, class NodePtr, class diff>
	// class tree_iter {
	// 	// typedef 
	// };


	// template<class T>
	// class tree {
	// 	public:
	// 		// node<T> *root; 
	// 		// node<T> ; 
	// 		tree();
	// 		~tree();

	// 		void clear();
	// 		void insert(T key);
	// 		void remove(T key);
	// 		node<T>* search(T key);
	// 		void print();
	// 		void preOrder();
	// 		void inOrder();
	// 		void postOrder();

	// 	private:
	// 		void lRotate(node<T>* &root, node<T>* x);
	// 		void rRotate(node<T>* &root, node<T>* y);

	// 		void insert(node<T>* &root, node<T>* node);
	// 		void insertFixUp(node<T>* &root, node<T>* node);
	// 		void _destroy(node<T>* &node);

	// 		void remove(node<T>* &root, node<T>* node);
	// 		void removeFixUp(node<T>* &root, node<T>* node, ft::node<T>* parent);

	// 		node<T>* search(node<T>* node, T key) const;
	// 		void print(node<T>* node) const;
	// 		void preOrder(node<T>* tree) const;
	// 		void inOrder(node<T>* tree) const;
	// 		void postOrder(node<T>* tree) const;
	// 		node<T>* root;

	// 	template<class T1>
	// 	tree<T1>::tree() : root(NULL) {
	// 		root = NULL;
	// 	}

	// 	template<class T1>
	// 	~tree<T1>::tree(){
	// 		_destroy(root);
	// 	}

	// 	void tree<T1>::clear() {
			
	// 	}

	// 	template<class T1>
	// 	void tree<T1>::lRotate(node<T1>* &root, node<T1>* x) {
	// 		ft::node<T1>* y = x->right;
	// 		x->right = y->left;
	// 		if (y->left)
	// 			y->left->parent = x;
	// 		y->parent = x->parent;
	// 		if (!x->parent)
	// 			root = y;
	// 		else  {
	// 			if (x == x->parent->left)
	// 				x->parent->left = y;
	// 			else
	// 				x->parent->right = y;
	// 		}
	// 		y->left = x;
	// 		x->parent = y;
	// 	}

	// 	template<class T1>
	// 	void tree<T1>::rRotate(node<T1>* &root, node<T1>*y) {
	// 		ft::node<T1>* x = y->left;
	// 		y->left = x->right;
	// 		if (x->right)
	// 			x->right->parent = y;
	// 		x->parent = y->parent;
	// 		if (!y->parent)
	// 			root = x;
	// 		else {
	// 			if (y == y->parent->right)
	// 				y->parent->right = x;
	// 			else
	// 				y->parent->left = x;
	// 		}
	// 		x->right = y;
	// 		y->parent = x;
	// 	}

	// 	template<class T>
	// 	void tree<T>::insert(T key) {
	// 		node<T> * new_node = new node<T>(key, Red, NULL, NULL, NULL);
	// 		insert(root, new_node);
	// 	}

	// 	template<class T>
	// 	void tree<T>::insert(node<T>* &root, node<T>* node) {
	// 		node<T> *x = root;
	// 		node<T> *y = NULL;
	// 		while (x) {
	// 			y = x;
	// 			if (node->key > y->key)
	// 				x = x->right;
	// 			else
	// 				x = x->left;
	// 		}
	// 		node->parent = y;
	// 		if (y) {
	// 			if (node->key > y->key)
	// 				y->right = node;
	// 			else
	// 				y->left = node;
	// 		}
	// 		else
	// 			root = node;
	// 		node->color = Red;
	// 		insertFixUp(root, node);
	// 	}

	// 	template <class T>
	// 	void tree<T>::insertFixUp(node<T>* &root, node<T>* node) {
	// 		node<T>*parent;
	// 		parent = node->parent;
	// 		while (node != tree::root && parent->color == Red) {
	// 			node<T>*gp = parent->parent;
	// 			if (gp->left == parent) {
	// 				node<T>*uncle = gp->right;
	// 				if (uncle && uncle->color == Red) {
	// 					parent->color = Black;
	// 					uncle->color = Black;
	// 					gp->color = Red;
	// 					node = gp;
	// 					parent = node->parent;
	// 				}
	// 				else {
	// 					if (parent->right == node) {
	// 						lRotate(root, parent);
	// 						swap(node, parent);
	// 					}
	// 					rRotate(root, gp);
	// 					gp->color = Red;
	// 					parent->color = Black;
	// 					break ;
	// 				}
	// 			}
	// 			else {
	// 				node<T>*uncle = gp->left;
	// 				if (uncle && uncle->color = Red) {
	// 					gp->color = Red;
	// 					parent->color = Black;
	// 					uncle->color = Black;

	// 					node = gp;
	// 					parent = node->parent;
	// 				}
	// 				else {
	// 					if (parent->left = node) {
	// 						rRotate(root, parent);
	// 						swap(parent, node);
	// 					}
	// 					lRotate(root, gp);
	// 					parent->color = Black;
	// 					gp->color = Red;
	// 					break ;
	// 				}
	// 			}
	// 		}
	// 		root->color = Black;
	// 	}

	// 	template<class T>
	// 	void tree<T>::_destroy(node<T>* &node) {
	// 		if (!node)
	// 			return ;
	// 		_destroy(node->left);
	// 		_destroy(node->right);
	// 		delete node;
	// 		node = NULL;
	// 	}

	// 	template<class T>
	// 	tree<T>::remove(T key) {
	// 		node<T>*tmp = search(root, key);
	// 		if (tmp)
	// 			remove(root, tmp);
	// 	}

	// 	void tree<T>::remove(node<T>* &root, node<T>* node) {
	// 		node<T>*child, *parent;
	// 		RBcolor color;
	// 		if (node->left && node->right) {
	// 			node<T>*replace = node;
	// 			replace = node->right;
	// 			while (replace->left)
	// 				replace = replace->left;
	// 			if (node->parent) {
	// 				if (node->parent->left == node)
	// 					node->parent->left = replace;
	// 				else
	// 					node->parent->right = replace;
	// 			}
	// 			else
	// 				root = replace;
	// 			child = replace->right;
	// 			parent = replace->parent;
	// 			color = replace->color;
	// 			if (parent == node)
	// 				parent = replace;
	// 			else {
	// 				if (child)
	// 					child->parent = parent;
	// 				parent->left = child;

	// 				replace->right = node->right;
	// 				node->right->parent = replace;
	// 			}
	// 			replace->parent = node->parent;
	// 			replace->color = node->color;
	// 			replace->left = node->left;
	// 			node->left->parent = replace;
	// 			if (color == Black)
	// 				removeFixUp(root, child, parent);
	// 			delete node;
	// 			return ;
	// 		}
	// 		if (node->left)
	// 			child = node->left;
	// 		else
	// 			childe = node->right;
	// 		parent = node->parent;
	// 		color = node->color;
	// 		if (child)
	// 			child->parent = parent;
	// 		if (parent) {
	// 			if (node == parent->left)
	// 				parent->left = child;
	// 			else
	// 				parent->right = child;
	// 		}
	// 		else
	// 			tree::root = child;
	// 		if (color == Black)
	// 			removeFixUp(root, child, parent);
	// 		delete node;
	// 	}

	// 	template<class T>
	// 	void tree<T>::removeFixUp(node<T>* &root, node<T>* node, node<T>* parent) {
	// 		node<T>* nd;
	// 		while((!node) || node->color == Black && node != tree::root) {
	// 			if (parent->left == node) {
	// 				nd = parent->right;
	// 				if (nd->color == Red) {
	// 					nd->color = Black;
	// 					parent->color = Red;
	// 					lRotate(root, parent);
	// 					nd = parent->right;
	// 				}
	// 				else {
	// 					if (!(nd->right) || nd->right->color == Black) {
	// 						nd->left->color = Black;
	// 						nd->color = Red;
	// 						rRotate(root, nd);
	// 						nd = parent->right;
	// 					}
	// 					nd->color = parent->color;
	// 					parent->color = Black;
	// 					nd->right->color = Black;
	// 					lRotate(root, parent);
	// 					nd = root;
	// 					break ;
	// 				}
	// 			}
	// 			else {
	// 				nd = parent->left;
	// 				if (nd->color = Red) {
	// 					nd->color = Black;
	// 					parent->color = Red;
	// 					rRotate(rrot, nd);
	// 					nd = parent->left;
	// 				}
	// 				if ((!nd->left || nd->left->color == Black) && (!nd->right || nd->right->color == Black)) {
	// 					nd->color = Red;
	// 					node = parent;
	// 					parent = node->parent;
	// 				}
	// 				else {
	// 					if (!(nd->left) || nd->left->color == Black) {
	// 						nd->right->color = Black;
	// 						nd->color = Red;
	// 						lRotate(root, nd);
	// 						nd = parent->left;
	// 					}
	// 				nd->color = parent->color;
	// 				parent->color = Black;
	// 				nd->left->color = Black;
	// 				rRotate(root, parent);
	// 				node = root;
	// 				break ;
	// 				}
	// 			}
	// 		}
	// 		if (node)
	// 			node->color = Black;
	// 	}

	// 	template<class T>
	// 	node<T>* tree<T>::search(T key) {
	// 		return search(root, key);
	// 	}

	// 	template<class T>
	// 	node<T>* tree<T>::search(node<T>* node, T key) const {
	// 		if (node == NULL || node->key == key)
	// 			return node;
	// 		else {
	// 			if (key > node->key)
	// 				return search(node->right, key);
	// 			else
	// 				return search(node->left, key);
	// 		}
	// 	}

	// 	template<class T>
	// 	void tree<T>::print() {
	// 		if (!root)
	// 			std::cout << "empty tree\n";
	// 		else
	// 			print(root);
	// 	}

	// 	template<class T>
	// 	void tree<T>::print(node<T>* node) const {
	// 		if (!node)
	// 			return ;
	// 		if (!node->parent)
	// 			std::cout << node->key << "(" << node->color << ") is root\n";
	// 		else if (node->parent->left == node)
	// 			std::cout << node->key << "(" << node->color << ") is " << node->parent->key << "'s left child\n";
	// 		else
	// 			std::cout << node->key << "(" << node->color << ") is " << node->parent->key << "'s right child\n";
	// 		print(node->left);
	// 		print(node->right);
	// 	}

	// 	template<class T>
	// 	void tree<T>::preOrder() {
	// 		if (!root)
	// 			std::cout << "empty tree\n";
	// 		else
	// 			preOrder(root);
	// 	}

	// 	template<class T>
	// 	void tree<T>::preOrder(node<T>* tree) const {
	// 		if (tree) {
	// 			std::cout << tree->key << " ";
	// 			preOrder(tree->left);
	// 			preOrder(tree->right);
	// 		}
	// 	}

	// 	template<class T>
	// 	void tree<T>::inOrder() {
	// 		if (!root)
	// 			std::cout << "empty tree\n";
	// 		else
	// 			inOrder(root);
	// 	}

	// 	template<class T>
	// 	void tree<T>::inOrder(node<T>* tree) const {
	// 		if (tree) {
	// 			inOrder(tree->left);
	// 			std::cout << tree->key << " ";
	// 			inOrder(tree->right);
	// 		}
	// 	}

	// 	template<class T>
	// 	void tree<T>::postOrder() {
	// 		if (!root)
	// 			std::cout << "empty tree\n";
	// 		else
	// 			postOrder(root);
	// 	}

	// 	template<class T>
	// 	void tree<T>::postOrder(node<T>* tree) const {

	// 	}
	// };
// }

#endif