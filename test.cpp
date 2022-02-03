#include <vector>
#include <iostream>

using namespace std;

int main() {

	vector<int> vec_int;
	// vector<int> vec_int_with_size(5);
	// vector<char> vec_char(5, 'a');
	// vector<A> vec_class;
	vec_int.push_back(5);
	vec_int.push_back(4);
	vector<int>::iterator it = vec_int.begin();


	vec_int.push_back(3);
	// it = vec_int.begin();
	// for ( ; it != vec_int.end(); ++it)
	// 	std::cout << *it << " ";
	// std::cout << "\n";
	vec_int.push_back(2);
	// it = vec_int.begin();
	// for ( ; it != vec_int.end(); ++it)
	// 	std::cout << *it << " ";
	// std::cout << "\n";
	vec_int.push_back(1);
	// it = vec_int.begin();
	// for ( ; it != vec_int.end(); ++it)
	// 	std::cout << *it << " ";
	// std::cout << "\n";
	// vec_int.insert(vec_int.begin() + 2, 5, 99);
	// vec_int.pop_back();
	it = vec_int.begin();
	for ( ; it != vec_int.end(); ++it)
		std::cout << *it << " ";
	std::cout << "\n";
	std::cout << "vec_int.size() << " << vec_int.size() << "\n";
	std::cout << "vec_int.front() << " << vec_int.front() << "\n";
	std::cout << "vec_int.back() << " << vec_int.back() << "\n";
	std::cout << "*vec_int.begin() << " << *vec_int.begin() << "\n";
	// std::cout << "*vec_int.end() << " << *vec_int.end() << "\n";
	// std::cout << "vec_int.max_size() << " << vec_int.max_size() << "\n";
	std::cout << "vec_int.empty() << " << vec_int.empty() << "\n";
	std::cout << "vec_int.capacity() << " << vec_int.capacity() << "\n";
	vec_int.resize(8);
	it = vec_int.begin();
	for ( ; it != vec_int.end(); ++it)
		std::cout << *it << " ";
	std::cout << "\n";
	std::cout << "vec_int.size() << " << vec_int.size() << "\n";
	std::cout << "vec_int.capacity() << " << vec_int.capacity() << "\n";
	vec_int.reserve(12);
	std::cout << "vec_int.size() << " << vec_int.size() << "\n";
	std::cout << "vec_int.capacity() << " << vec_int.capacity() << "\n";
	vec_int.assign(4, 99);
	// vec_int.push_back(100);
	it = vec_int.begin();
	for ( ; it != vec_int.end(); ++it)
		std::cout << *it << " ";
	std::cout << "\n";
	std::cout << "vec_int.size() << " << vec_int.size() << "\n";
	std::cout << "vec_int.capacity() << " << vec_int.capacity() << "\n";
	vec_int.insert(vec_int.end() - 1, 33);
	it = vec_int.begin();
	for ( ; it != vec_int.end(); ++it)
		std::cout << *it << " ";
	std::cout << "\n";
	// std::cout << "vec_int.size() << " << vec_int.size() << "\n";
	// std::cout << "vec_int.capacity() << " << vec_int.capacity() << "\n";
	// vec_int.reserve(4);
	// it = vec_int.begin();
	// for ( ; it != vec_int.end(); ++it)
	// 	std::cout << *it << " ";
	// std::cout << "\n";
	std::cout << "vec_int.size() << " << vec_int.size() << "\n";
	std::cout << "vec_int.capacity() << " << vec_int.capacity() << "\n";
	vector<int> v(vec_int.begin(), vec_int.end());
	vector<int>::iterator itv = v.begin();
	for ( ; itv != v.end(); ++itv)
		std::cout << *it << " ";
	std::cout << "\n";
	std::cout << "v.size() << " << v.size() << "\n";
	std::cout << "v.capacity() << " << v.capacity() << "\n";
  	std::vector<int> second (4,100);                       // four ints with value 100
	for (vector<int>::iterator its = second.begin(); its != second.end(); ++its)
		cout << " " << *its;
	cout << "\n";
	std::cout << "second.size() << " << second.size() << "\n";
	std::cout << "second.capacity() << " << second.capacity() << "\n";
  	std::vector<int> third (second.begin(),second.end()); 
	for (vector<int>::iterator itt = third.begin(); itt != third.end(); ++itt)
		cout << " " << *itt;
	cout << "\n";
	std::cout << "third.size() << " << third.size() << "\n";
	std::cout << "third.capacity() << " << third.capacity() << "\n";
	vector<int> emp;
	emp.push_back(88);
	emp.push_back(77);
	emp.push_back(66);
	emp.insert(emp.begin() + 1, 3, 55);
	for (vector<int>::iterator item = emp.begin(); item != emp.end(); ++item)
		cout << " " << *item;
	cout << "\n";
	std::cout << "emp.size() << " << emp.size() << "\n";
	std::cout << "emp.capacity() << " << emp.capacity() << "\n";
	vector<int> copy_emp(emp.begin(), emp.end());
	for (vector<int>::iterator coit = copy_emp.begin(); coit != copy_emp.end(); ++coit)
		cout << " " << *coit;
	cout << "\n";
	std::cout << "copy_emp.size() << " << copy_emp.size() << "\n";
	std::cout << "copy_emp.capacity() << " << copy_emp.capacity() << "\n";

	
	return 0;
}