#include "vector.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "iterator_v.hpp"
#include "utils.hpp"
#include <iostream>

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
	vector<int> vec_int(5);
	// vector<char> vec_char('a');
	// vector<A> vec_class;
	// vec_int.push_back(5);
	// vec_int.push_back(4);
	// vec_int.push_back(3);
	// vec_int.push_back(2);
	// vec_int.push_back(1);
	// vec_int.pop_back();
	vector<int>::iterator it = vec_int.begin();
	vector<int>::iterator ite = vec_int.end();
	// for ( ; it != ite; ++it)
	// 	std::cout << *it << std::endl;
	// vector<int> vec_int_copy(vec_int);
}

// invalid operands to binary expression ('ft::vector<int, std::__1::allocator<int> >::iterator' (aka 'ft::iterator<long, int, int *, int &, ft::random_access_iterator_tag>') and
    //   								  'ft::vector<int, std::__1::allocator<int> >::iterator')
                        // else if (static_cast<size_type>(end() - position) < n) {