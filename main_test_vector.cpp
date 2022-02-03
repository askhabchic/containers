#include "vector.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "iterator_v.hpp"
#include "utils.hpp"
#include <iostream>
#include <memory>
#include <vector>

using namespace ft ;

class A {
private:
public:
	A();
	~A();
};

A::A() {}

A::~A() {}

int main() {
	// vector<int> vec_int;
	// // vector<int> vec_int_with_size(5);
	// // vector<char> vec_char(5, 'a');
	// // vector<A> vec_class;
	// vec_int.push_back(5);
	// vec_int.push_back(4);
	// vector<int>::iterator it = vec_int.begin();


	// vec_int.push_back(3);
	// // it = vec_int.begin();
	// // for ( ; it != vec_int.end(); ++it)
	// // 	std::cout << *it << " ";
	// // std::cout << "\n";
	// vec_int.push_back(2);
	// // it = vec_int.begin();
	// // for ( ; it != vec_int.end(); ++it)
	// // 	std::cout << *it << " ";
	// // std::cout << "\n";
	// vec_int.push_back(1);
	// // it = vec_int.begin();
	// // for ( ; it != vec_int.end(); ++it)
	// // 	std::cout << *it << " ";
	// // std::cout << "\n";
	// // vec_int.insert(vec_int.begin() + 2, 5, 99);
	// // vec_int.pop_back();
	// it = vec_int.begin();
	// for ( ; it != vec_int.end(); ++it)
	// 	std::cout << *it << " ";
	// std::cout << "\n";
	// std::cout << "vec_int.size() << " << vec_int.size() << "\n";
	// std::cout << "vec_int.front() << " << vec_int.front() << "\n";
	// std::cout << "vec_int.back() << " << vec_int.back() << "\n";
	// std::cout << "*vec_int.begin() << " << *vec_int.begin() << "\n";
	// // std::cout << "*vec_int.end() << " << *vec_int.end() << "\n";
	// // std::cout << "vec_int.max_size() << " << vec_int.max_size() << "\n";
	// std::cout << "vec_int.empty() << " << vec_int.empty() << "\n";
	// std::cout << "vec_int.capacity() << " << vec_int.capacity() << "\n";
	// vec_int.resize(8);
	// it = vec_int.begin();
	// for ( ; it != vec_int.end(); ++it)
	// 	std::cout << *it << " ";
	// std::cout << "\n";
	// std::cout << "vec_int.size() << " << vec_int.size() << "\n";
	// std::cout << "vec_int.capacity() << " << vec_int.capacity() << "\n";
	// vec_int.reserve(12);
	// std::cout << "vec_int.size() << " << vec_int.size() << "\n";
	// std::cout << "vec_int.capacity() << " << vec_int.capacity() << "\n";
	// vec_int.assign(4, 99);
	// // vec_int.push_back(100);
	// // vec_int.clear();
	// it = vec_int.begin();
	// for ( ; it != vec_int.end(); ++it)
	// 	std::cout << *it << " ";
	// std::cout << "\n";
	// std::cout << "vec_int.size() << " << vec_int.size() << "\n";
	// std::cout << "vec_int.capacity() << " << vec_int.capacity() << "\n";
	// // vec_int.push_back(105);
	// // it = vec_int.begin();
	// // for ( ; it != vec_int.end(); ++it)
	// // 	std::cout << *it << " ";
	// // std::cout << "\n";
	// // std::cout << "vec_int.size() << " << vec_int.size() << "\n";
	// // std::cout << "vec_int.capacity() << " << vec_int.capacity() << "\n";
	// vec_int.insert(vec_int.end() - 2, 4, 365);
	// it = vec_int.begin();
	// for ( ; it != vec_int.end(); ++it)
	// 	std::cout << *it << " ";
	// std::cout << "\n";
	// std::cout << "vec_int.size() << " << vec_int.size() << "\n";
	// std::cout << "vec_int.capacity() << " << vec_int.capacity() << "\n";
	// vec_int.insert(vec_int.end() - 1, 33);
	// it = vec_int.begin();
	// for ( ; it != vec_int.end(); ++it)
	// 	std::cout << *it << " ";
	// std::cout << "\n";
	// std::cout << "vec_int.size() << " << vec_int.size() << "\n";
	// std::cout << "vec_int.capacity() << " << vec_int.capacity() << "\n";
	// vec_int.reserve(4);
	// it = vec_int.begin();
	// for ( ; it != vec_int.end(); ++it)
	// 	std::cout << *it << " ";
	// std::cout << "\n";
	// std::cout << "vec_int.size() << " << vec_int.size() << "\n";
	// std::cout << "vec_int.capacity() << " << vec_int.capacity() << "\n";
	// vector<int> vec(vec_int);
	// // vector<int>::iterator it_vec = vec.begin();
	// // for ( ; it_vec != vec.end(); ++it_vec)
	// // 	std::cout << *it_vec << " ";

	// // vector<int> v(vec_int.begin(), vec_int.end());
	// // std::cout << "vec_class.size() << " << vec_class.size() << "\n";
	// // std::cout << "vec_int.max_size() << " << vec_class.max_size() << "\n";
	// // std::cout << "vec_class.capacity() << " << vec_class.capacity() << "\n";
	// // std::cout << "iterator begin - " << *it << std::endl;
	// // std::cout << "iterator end - " << *ite << std::endl;
	// // vector<int> vec_int_copy(vec_int);
	// vector<int> vector1;
    // std::vector<int> v;
    // vector<int> tmp;
    // tmp.assign(2600 * 1000, 1);
    // vector1.assign(4200 * 1000, 1);
    // vector1.insert(vector1.end() - 1000 * 1000, tmp.begin(), tmp.end());
    // v.push_back(vector1[3]);
    // v.push_back(vector1.size());
    // v.push_back(vector1.capacity());
	// // std::vector<int>::iterator std_ter = v.begin();
	// vector<int> int_vec;
	// int_vec.insert(int_vec.begin(), v.begin(), v.end());
	// // vector<int>::iterator it_vec = v.begin();
	// // for ( ; it_vec != v.end(); ++it_vec)
	// 	// std::cout << *it_vec << " ";
	// // std::cout << "\n";


	
	int _ratio = 1000;

	// vector<int> vector1;
    // std::vector<int> v;
    // vector1.assign(1100 * _ratio, 11);
    // vector<int> tmp(500000, 5);
	// vector<int> tmp2(1000000, 10);
	// vector<int> tmp3(1500000, 15);
	// vector<int> tmp4(3000000, 30);
    // // v.push_back(vector1[2]);
    // // v.push_back(vector1.size());
    // // v.push_back(vector1.capacity());
    // // long *adr1 = reinterpret_cast<long *>(&vector1);
    // // long *adr2 = reinterpret_cast<long *>(&tmp);
    // // vector1.swap(tmp);
    // // if (reinterpret_cast<long *>(&vector1) == adr1 && reinterpret_cast<long *>(&tmp) == adr2)
    // // 	v.push_back(1);
    // // v.push_back(vector1[2]);
    // // v.push_back(vector1.size());
    // // v.push_back(vector1.capacity());
    // vector1.swap(tmp3);
    // v.push_back(vector1[2]);
    // v.push_back(vector1.size());
    // v.push_back(vector1.capacity());
    // std::swap(vector1, tmp2);
    // v.push_back(vector1[2]);
    // v.push_back(vector1.size());
    // v.push_back(vector1.capacity());
    // std::swap(vector1, tmp4);
    // v.push_back(vector1[2]);
    // v.push_back(vector1.size());
    // v.push_back(vector1.capacity());
	// for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
	// 	std::cout << *it << " ";
	// std::cout << "\n";




	std::vector<int> vector2;
    std::vector<int> v2;
    vector2.assign(1100 * _ratio, 11);
    std::vector<int> tmp_std(500000, 5);
	std::vector<int> tmp2_std(1000000, 10);
	std::vector<int> tmp3_std(1500000, 15);
	std::vector<int> tmp4_std(3000000, 30);
    // v2.push_back(vector2[2]);
    // v2.push_back(vector2.size());
    // v2.push_back(vector2.capacity());
    // long *adr3 = reinterpret_cast<long *>(&vector2);
    // long *adr4 = reinterpret_cast<long *>(&tmp_std);
    // vector2.swap(tmp_std);
    // if (reinterpret_cast<long *>(&vector2) == adr3 && reinterpret_cast<long *>(&tmp_std) == adr4)
    // 	v2.push_back(1);
    // v2.push_back(vector2[2]);
    // v2.push_back(vector2.size());
    // v2.push_back(vector2.capacity());
    vector2.swap(tmp3_std);
    v2.push_back(vector2[2]);
    v2.push_back(vector2.size());
    v2.push_back(vector2.capacity());
    std::swap(vector2, tmp2_std);
    v2.push_back(vector2[2]);
    v2.push_back(vector2.size());
    v2.push_back(vector2.capacity());
    std::swap(vector2, tmp4_std);
    v2.push_back(vector2[2]);
    v2.push_back(vector2.size());
    v2.push_back(vector2.capacity());
	for (std::vector<int>::iterator it2 = v2.begin(); it2 != v2.end(); ++it2)
		std::cout << *it2 << " ";
	std::cout << "\n";
	return 0;
}