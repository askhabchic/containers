#include "vector.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "iterator_v.hpp"
#include "utils.hpp"
#include <iostream>
#include <memory>

using namespace ft ;

class A {
private:
public:
	A();
	~A();
};

A::A() {
}

A::~A() {
}


int main() {
	vector<int> vec_int;
	// vector<int> vec_int_with_size(5);
	// vector<char> vec_char(5, 'a');
	vector<A> vec_class;
	// vec_int.push_back(5);
	// vec_int.push_back(4);
	// vec_int.push_back(3);
	// vec_int.push_back(2);
	// vec_int.push_back(1);
	// vec_int.pop_back();
	std::cout << "vec_int.size() << " << vec_int.size() << "\n";
	// std::cout << "*vec_int.begin() << " << *vec_int.begin() << "\n";
	// std::cout << "*vec_int.end() << " << *vec_int.end() << "\n";
	std::cout << "vec_int.max_size() << " << vec_int.max_size() << "\n";
	std::cout << "vec_int.empty() << " << vec_int.empty() << "\n";
	std::cout << "vec_int.capacity() << " << vec_int.capacity() << "\n";
	std::cout << "vec_class.size() << " << vec_class.size() << "\n";
	std::cout << "vec_class.capacity() << " << vec_class.capacity() << "\n";
	// vector<int>::iterator it = vec_int.begin();
	// vector<int>::iterator ite = vec_int.end();
	// std::cout << "iterator begin - " << *it << std::endl;
	// std::cout << "iterator end - " << *ite << std::endl;
	// for ( ; it != ite; ++it)
	// 	std::cout << *it << std::endl;
	// vector<int> vec_int_copy(vec_int);
}

// invalid operands to binary expression ('ft::vector<int, std::__1::allocator<int> >::iterator' (aka 'ft::iterator<long, int, int *, int &, ft::random_access_iterator_tag>') and
    //   								  'ft::vector<int, std::__1::allocator<int> >::iterator')
                        // else if (static_cast<size_type>(end() - position) < n) {

// template<class T, class alloc = std::__1::allocator<T>> ft::iterator_v<T *> ft::vector<T, alloc>::end()  - ft::iterator_v<T *> position

// invalid operands to binary expression ('ft::vector<int, std::__1::allocator<int> >::iterator' (aka 'iterator_v<int *>') 
// 									  and 'ft::vector<int, std::__1::allocator<int> >::iterator')
                                        // fill(_end, n - (end() - position), tmp); }