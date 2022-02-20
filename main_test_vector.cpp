#include "vector.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "iterator_v.hpp"
#include "utils.hpp"
#include <iostream>
#include <memory>
#include <vector>

using namespace ft ;

class B {
public:
	char *l;
	int i;
	B():l(nullptr), i(1) {};
	B(const int &ex) {
		this->i = ex;
		this->l = new char('a');
	};
	virtual ~B() {
		delete this->l;
		this->l = nullptr;
	};
};

class A : public B {
public:
	A():B(){};
	A(const B* ex){
		this->l = new char(*(ex->l));
		this->i = ex->i;
		if (ex->i == -1) throw "n";
	}
	~A() {
		delete this->l;
		this->l = nullptr;
	};
};

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

	std::cout << "ft::vector\n";
	vector<int> vector1;
    std::vector<int> v;
	// vector1.assign(1000, 1);
    vector<int> tmp;
    // tmp.assign(2600 * _ratio, 1);
    // vector1.assign(2200 * _ratio, 1);
    // vector1.insert(vector1.end() - 1400 * _ratio, tmp.begin(), tmp.end());
    // v.push_back(vector1[3]);
    // v.push_back(vector1.size());
    // v.push_back(vector1.capacity());

	vector1.assign(2600 * _ratio, 1);
    v.push_back(*(vector1.insert(vector1.end() - 800 * _ratio, 44)));
    v.push_back(vector1.size());
    v.push_back(vector1.capacity());
    std::unique_ptr<B> k2(new B(3));
    std::unique_ptr<B> k3(new B(4));
    std::unique_ptr<B> k4(new B(-1));
    vector<A> vv;
    vector<B*> v1;

    v1.push_back(&(*k2));
    v1.push_back(&(*k3));
    v1.push_back(&(*k4));
    // vv.insert(vv.begin(), v1.begin(), v1.end());
    try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
    catch (...) {
    	v.push_back(vv.size());
    	v.push_back(vv.capacity());
    }

	// tmp.assign(2600 * _ratio, 1);
    // vector1.assign(4200 * _ratio, 1);
    // vector1.insert(vector1.end() - 1000 * _ratio, tmp.begin(), tmp.end());
    // v.push_back(vector1[3]);
    // v.push_back(vector1.size());
    // v.push_back(vector1.capacity());

	// vector1.assign(100, 3);
    // std::vector<int> v;
	// vector<int> tmp0(vector1);
	// vector<int> tmp(1000 * _ratio, 4), tmp2(1000 * _ratio, 5);
	// // tmp = tmp2;
	// vector<int> tmp3(tmp);
    // vector<int> tmp4(tmp.begin(), tmp.end());
    // v.push_back(tmp4.size());
    // v.push_back(tmp4.capacity());
    // v.push_back(tmp[2]);
    // v.push_back(tmp3[2]);
    // v.push_back(tmp4[2]);
    // try { vector<int> tmp5(-1, -1); }
    // catch (std::exception &e) { v.push_back(1); }

    // vector1.assign(9900 * _ratio, 11);
    // vector<int> tmp(500000, 5);
	// vector<int> tmp2(1000000, 10);
	// vector<int> tmp3(1500000, 15);
	// vector<int> tmp4(3000000, 30);
    // // vector1.swap(tmp);
	// std::cout << vector1.size() << ", cap - " << vector1.capacity() << "\n";
	// vector1.resize(5000 * _ratio);	
	// std::cout << vector1.size() << ", cap - " << vector1.capacity() << "\n";
	// vector1.reserve(5000 * _ratio);
    // // // // v.push_back(vector1[2]);
    // v.push_back(vector1.size());
    // v.push_back(vector1.capacity());
	// vector1.resize(7000 * _ratio);
	// std::cout << vector1.size() << ", cap - " << vector1.capacity() << "\n";
    // v.push_back(vector1.size());
    // v.push_back(vector1.capacity());
	// vector1.resize(15300 * _ratio);
	// std::cout << vector1.size() << ", cap - " << vector1.capacity() << "\n";
    // v.push_back(vector1.size());
    // v.push_back(vector1.capacity());
    // v.push_back(vector1[65]);
	// std::cout << v.back() << "\n";
    // // // long *adr1 = reinterpret_cast<long *>(&vector1);
    // // // long *adr2 = reinterpret_cast<long *>(&tmp);
    // // // vector1.swap(tmp);
    // // // if (reinterpret_cast<long *>(&vector1) == adr1 && reinterpret_cast<long *>(&tmp) == adr2)
    // // // 	v.push_back(1);
    // // // v.push_back(vector1[2]);
    // // // v.push_back(vector1.size());
    // // // v.push_back(vector1.capacity());
	// v.push_back(*(vector1.begin()));
	// v.push_back(*(vector1.begin() + 1));
	// v.push_back(*(vector1.rbegin()));
	// v.push_back(*(vector1.rbegin() + 1));
	// v.push_back(*(vector1.rend()));
	// v.push_back(*(vector1.rend() - 1));
	// v.push_back(*(vector1.rend() - 2));
    // // vector1.swap(tmp3);
    // // v.push_back(vector1[2]);
    // // v.push_back(vector1.size());
    // // v.push_back(vector1.capacity());
    // // std::swap(vector1, tmp2);
    // // v.push_back(vector1[2]);
    // // v.push_back(vector1.size());
    // // v.push_back(vector1.capacity());
    // // std::swap(vector1, tmp4);
    // // v.push_back(vector1[2]);
    // // v.push_back(vector1.size());
    // // v.push_back(vector1.capacity());
	for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << " ";
	std::cout << "\n";




	// std::cout << "std::vector\n";
	// std::vector<int> vector2;
    // std::vector<int> v2;
	// vector2.assign(1000, 1);
    // std::vector<int> tmp1;
    // tmp1.assign(2600 * _ratio, 1);
    // vector2.assign(2200 * _ratio, 1);
    // vector2.insert(vector2.end() - 1400 * _ratio, tmp1.begin(), tmp1.end());
    // v2.push_back(vector2[3]);
    // v2.push_back(vector2.size());
    // v2.push_back(vector2.capacity());

	// vector2.assign(1000, 1);
    // vector2.assign(9900 * _ratio, 11);
    // std::vector<int> tmp_std(500000, 5);
	// std::vector<int> tmp2_std(1000000, 10);
	// std::vector<int> tmp3_std(1500000, 15);
	// std::vector<int> tmp4_std(3000000, 30);
    // // v2.push_back(vector2[2]);
    // // v2.push_back(vector2.size());
    // // v2.push_back(vector2.capacity());
    // // long *adr3 = reinterpret_cast<long *>(&vector2);
    // // long *adr4 = reinterpret_cast<long *>(&tmp_std);
    // vector2.swap(tmp_std);
	// std::cout << vector2.size() << ", cap - " << vector2.capacity() << "\n";
    // // if (reinterpret_cast<long *>(&vector2) == adr3 && reinterpret_cast<long *>(&tmp_std) == adr4)
    // // 	v2.push_back(1);
    // // v2.push_back(vector2[2]);
	// vector2.resize(5000 * _ratio);
	// std::cout << vector2.size() << ", cap - " << vector2.capacity() << "\n";
	// vector2.reserve(5000 * _ratio);
    // // // // v.push_back(vector1[2]);
    // v2.push_back(vector2.size());
    // v2.push_back(vector2.capacity());
	// vector2.resize(7000 * _ratio);
	// std::cout << vector2.size() << ", cap - " << vector2.capacity() << "\n";
    // v2.push_back(vector2.size());
    // v2.push_back(vector2.capacity());
	// vector2.resize(15300 * _ratio);
	// std::cout << vector2.size() << ", cap - " << vector2.capacity() << "\n";
    // v2.push_back(vector2.size());
    // v2.push_back(vector2.capacity());
    // v2.push_back(vector2[65]);

    // // v2.push_back(vector2.size());
    // // v2.push_back(vector2.capacity());
	// v2.push_back(*(vector2.begin()));
	// v2.push_back(*(vector2.begin() + 1));
	// v2.push_back(*(vector2.rbegin()));
	// v2.push_back(*(vector2.rbegin() + 1));
	// v2.push_back(*(vector2.rend()));
	// v2.push_back(*(vector2.rend() - 1));
	// v2.push_back(*(vector2.rend() - 2));
    // // vector2.swap(tmp3_std);
    // // v2.push_back(vector2[2]);
    // // v2.push_back(vector2.size());
    // // v2.push_back(vector2.capacity());
    // // std::swap(vector2, tmp2_std);
    // // v2.push_back(vector2[2]);
    // // v2.push_back(vector2.size());
    // // v2.push_back(vector2.capacity());
    // // std::swap(vector2, tmp4_std);
    // // v2.push_back(vector2[2]);
    // // v2.push_back(vector2.size());
    // // v2.push_back(vector2.capacity());
	// for (std::vector<int>::iterator it2 = v2.begin(); it2 != v2.end(); ++it2)
	// 	std::cout << *it2 << " ";
	// std::cout << "\n";
	return 0;
}