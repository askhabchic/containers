#include <iostream>
#include <string>
#include <deque>

#include <stdexcept>
#include <memory>


#if 1 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	// namespace ft = std;
#else
	#include <map.hpp>
	#include <stack.hpp>
	#include <vector.hpp>
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

// template<typename T>
// class MutantStack : public ft::stack<T>
// {
// public:
// 	MutantStack() {}
// 	MutantStack(const MutantStack<T>& src) { *this = src; }
// 	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
// 	{
// 		this->c = rhs.c;
// 		return *this;
// 	}
// 	~MutantStack() {}

// 	typedef typename ft::stack<T>::container_type::iterator iterator;

// 	iterator begin() { return this->c.begin(); }
// 	iterator end() { return this->c.end(); }
// };
// template <T>
// class it {
// 	operator ++ ()
// 	T *i;
// };

// class rev_it {

// 	operator ++(){
// 		i--;
// 	}
// 	it i;
// };

int main(int argc, char** argv) {
	// std::vector<int> vec;
	// std::vector<int> v(vec);
	// vec.push_back(1);
	// vec.push_back(10);
	std::vector<int> vec_int;
	// vector<int> vec_int_with_size(5);
	// vector<char> vec_char(5, 'a');
	// vector<A> vec_class;
	vec_int.push_back(5);
	// vec_int.push_back(4);
	// vec_int.push_back(3);
	// vec_int.push_back(2);
	// vec_int.push_back(1);
	std::vector<int> vec(vec_int);
	std::cout << "front() - " << vec.front() << "\n";
	std::cout << "back() - " << vec.back() << "\n";
	std::cout << "begin() - " << *vec.begin() << "\n";
	std::cout << "end() - " << *vec.end() << "\n";
	// vec.push_back(1);
	// vec.push_back(11);
	// vec.push_back(1);
	// vec.push_back(13);
	// vec.push_back(21);
	// std::vector<int>::iterator it = vec.begin();
	// std::vector<int>::iterator ite = vec.end();
	// std::vector<int>::allocator_type alloc;
	// std::cout << "\nsize - " << vec.size() << "\n";
	// std::cout << "capacity - " << vec.capacity() << "\n";
	// it = vec.begin();
	// ite = vec.end();
	// std::cout << "begin = " << *it << "\n";
	// std::cout << "end = " << *(ite - 1) << "\n";
	// for ( ; it != ite; ++it) {
	// 	std::cout << *it << " ";
	// }
	// vec.insert(vec.begin() + 2, 11, 99);
	// std::cout << "\nsize - " << vec.size() << "\n";
	// std::cout << "capacity - " << vec.capacity() << "\n";
	// it = vec.begin();
	// ite = vec.end();
	// std::cout << "begin = " << *it << "\n";
	// std::cout << "end = " << *(ite - 1) << "\n";
	// for ( ; it != ite; ++it) {
	// 	std::cout << *it << " ";
	// }
	// const std::string str = "test";
	// std::vector<std::string> vec_string(str);
	// std::vector<int>::allocator_type alloc_v = v.get_allocator();
	// std::__swap_allocator(alloc, alloc_v);
	//  = &vec[1];
	// for ( ; it != ite; ++it) {
	// 	std::cout << *it << " ";
	// }
	// std::cout << std::endl;
	// std::vector<int> v2(6, 2);
	// vec.assign(v2.operator[](0), v2.operator[](5));
	// vec.insert(vec.begin(), 1, 2);
	// std::cout << std::endl;
	// std::cout << "size - " << vec.size() << "\n";
	// std::cout << "capacity - " << vec.capacity() << "\n";
	// it = vec.begin();
	// ite = vec.end();
	// std::cout << "begin = " << *it << "\n";
	// std::cout << "end = " << *ite << "\n";
	// for ( ; it != ite; ++it) {
	// 	std::cout << *it << " ";
	// }
	// vec.assign(6, 111111);
	// std::equal();
	// std::vector<int>::pointer p;
	// alloc.construct(p, vec.at(3));
	// std::cout << "\n" << p << " = " << *p << std::endl;
	// std::cout << "before[1] = " << vec.operator[](1) << "\n";
	// std::cout << "before[2] = " << vec.operator[](2) << "\n";
	// vec.erase((vec.begin() + 1), (vec.begin() + 2));
	// std::cout << "after[1] = " << vec.operator[](1) << "\n";
	// std::cout << "after[2] = " << vec.operator[](2) << "\n";
	// size_t M = 5000000000000000000;
	// size_t N = vec.capacity();
	// try
	// {
	// 	vec.insert(it, M, 32);
	// 	std::cout << "size aftere insert = " << vec.size() << "\n";
	// 	std::cout << "vec.capacity - " << N << "\n";
	// 	if (N < vec.size() + M ) {
	// 		std::cout << vec.max_size() << "\n";
	// 		N = vec.max_size() - N / 2 < N ? 0 : N + N / 2;
	// 		std::cout << "N = vec.max_size() .... = " << N << "\n";
	// 		if ( N < vec.size() + M) {
	// 			N = vec.size() + M;
	// 			std::cout << N << "\n";
	// 		}
	// 	}
	// }
	// catch(const std::length_error& le)
	// {
	// 	std::cerr << "Lenght error: " << le.what() << '\n';
	// }
	// if (vec.max_size() - vec.size() < M) 
	

	// else if (vec.size() + M > vec.capacity())
	// for ( ; it != ite; ++it) {
	// 	std::cout << *it << " ";
	// }
	// std::cout << std::endl << "it = " << *it << std::endl; 
	// it = vec.begin();
	// ite = vec.end();
	// vec.insert(it, -2, 45);
	// it = vec.begin();
	// ite = vec.end();
	// for ( ; it != ite; ++it) {
	// 	std::cout << *it << " ";
	// }
	// std::cout << std::endl << "it = " << *(it--)<< std::endl; 
	// it = vec.begin();
	// ite = vec.end();
	// vec.assign(it, it + 2);
	// it = vec.begin();
	// ite = vec.end();
	// for ( ; it != ite; ++it) {
	// 	std::cout << *it << " ";
	// }
	// std::cout << std::endl << "it = " << *it << std::endl; 

	// if (argc != 2)
	// {
	// 	std::cerr << "Usage: ./test seed" << std::endl;
	// 	std::cerr << "Provide a seed please" << std::endl;
	// 	std::cerr << "Count value:" << COUNT << std::endl;
	// 	return 1;
	// }
	// const int seed = atoi(argv[1]);
	// srand(seed);

	// ft::vector<std::string> vector_str;
	// ft::vector<int> vector_int;
	// ft::stack<int> stack_int;
	// ft::vector<Buffer> vector_buffer;
	// ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	// ft::map<int, int> map_int;

	// for (int i = 0; i < COUNT; i++)
	// {
	// 	vector_buffer.push_back(Buffer());
	// }

	// for (int i = 0; i < COUNT; i++)
	// {
	// 	const int idx = rand() % COUNT;
	// 	vector_buffer[idx].idx = 5;
	// }
	// ft::vector<Buffer>().swap(vector_buffer);

	// try
	// {
	// 	for (int i = 0; i < COUNT; i++)
	// 	{
	// 		const int idx = rand() % COUNT;
	// 		vector_buffer.at(idx);
	// 		std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
	// 	}
	// }
	// catch(const std::exception& e)
	// {
	// 	//NORMAL ! :P
	// }
	
	// for (int i = 0; i < COUNT; ++i)
	// {
	// 	map_int.insert(ft::make_pair(rand(), rand()));
	// }

	// int sum = 0;
	// for (int i = 0; i < 10000; i++)
	// {
	// 	int access = rand();
	// 	sum += map_int[access];
	// }
	// std::cout << "should be constant with the same seed: " << sum << std::endl;

	// {
	// 	ft::map<int, int> copy = map_int;
	// }
	// MutantStack<char> iterable_stack;
	// for (char letter = 'a'; letter <= 'z'; letter++)
	// 	iterable_stack.push(letter);
	// for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	// {
	// 	std::cout << *it;
	// }
	// std::cout << std::endl;
	return (0);
} 