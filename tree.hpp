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
    TreeNodeValue*  value;
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

class Tree {
public:
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

#endif