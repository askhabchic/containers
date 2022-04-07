#include "stack.hpp"
#include "vector.hpp"
#include <vector>
#include <stack>

int main() {
	std::vector<std::string> res;
	std::vector<std::string> res2;
	res.push_back(typeid(std::vector<int>::iterator::iterator_category).name());
	res.push_back(typeid(std::vector<int>::iterator::value_type).name());
	res.push_back(typeid(std::vector<int>::iterator::difference_type).name());
	res.push_back(typeid(std::vector<int>::iterator::iterator_type).name());
	res.push_back(typeid(std::vector<int>::iterator::pointer).name());
	res.push_back(typeid(std::vector<int>::iterator::reference).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::iterator_category).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::value_type).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::difference_type).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::pointer).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::reference).name());
	std::cout << "std::vector\n";
	for (size_t i = 0; i < res.size(); ++i)
		std::cout << res[i] << "\n";

	res2.push_back(typeid(ft::vector<int>::iterator::iterator_category).name());
	res2.push_back(typeid(ft::vector<int>::iterator::value_type).name());
	res2.push_back(typeid(ft::vector<int>::iterator::difference_type).name());
	res2.push_back(typeid(ft::vector<int>::iterator::iterator_type).name());
	res2.push_back(typeid(ft::vector<int>::iterator::pointer).name());
	res2.push_back(typeid(ft::vector<int>::iterator::reference).name());
	res2.push_back(typeid(ft::vector<int>::reverse_iterator::iterator_category).name());
	res2.push_back(typeid(ft::vector<int>::reverse_iterator::value_type).name());
	res2.push_back(typeid(ft::vector<int>::reverse_iterator::difference_type).name());
	res2.push_back(typeid(ft::vector<int>::reverse_iterator::pointer).name());
	res2.push_back(typeid(ft::vector<int>::reverse_iterator::reference).name());
	std::cout << "ft::vector\n";
	for (size_t i = 0; i < res2.size(); ++i)
		std::cout << res2[i] << "\n";
	if (res == res2)
		std::cout << "true\n";
	else
		std::cout << "false\n";
	return res == res2;
}