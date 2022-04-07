#include "map.hpp"
#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>

	template<class T>
	std::string equal(const T& std, const T& ft) {
		return std == ft ? "+" : "x";
	}

	template<class T>
	bool equalbool(const T& m1, const T& m2) {
		return (m1 == m2 ? true : false);
	}

	template<class T1, class T2>
	std::string equalContent(const std::map<T1, T2> &std_map, const ft::map<T1, T2> &ft_map ) {
		typename ft::map<T1, T2>::const_iterator ft_it;
		typename std::map<T1, T2>::const_iterator std_it;
		if (ft_map.size() != std_map.size()) 
			return "x";
		std_it = std_map.begin();
		for (ft_it = ft_map.begin(); ft_it != ft_map.end(); ft_it++) {
			if ((*ft_it).first != (*std_it).first || (*ft_it).second != (*std_it).second)
				return "x";
			std_it++;
		}
		return "+";
	}

	template<class T>
	static bool printValue(std::fstream&fs, const T& std, const T& ft) {
		fs << "===========================================\n";
		fs << "Value:\n";
		fs << "STL  : " << std << "\n";
		fs << "FT   : [" << equal(std, ft) << "]: " << ft << "\n";
		fs << "===========================================\n";
		return std == ft ? true : false;
	}

	bool printBoolResult(std::fstream& fs, bool stl_bool, bool ft_bool) {
    	fs << "\nBool result : \n";
    	fs << " - STL : " << (stl_bool ? "true" : "false") << std::endl;
    	fs << " - FT  : " << (ft_bool ? "true" : "false") << std::endl;
    	return (stl_bool == ft_bool);
	}

	template <class T1, class T2>
	bool compareMaps (std::fstream& fs,	std::map<T1, T2>& std_map, ft::map<T1, T2>& ft_map) {
		std::string std_emp = ((std_map.empty() == 1) ? "true" : "false");
		size_t std_size = std_map.size();
		size_t std_max_size = std_map.max_size();

		std::string ft_emp = ((ft_map.empty() == 1) ? "true" : "false");
		size_t ft_size = ft_map.size();
		size_t ft_max_size = ft_map.max_size();

		bool empty = equalbool(ft_emp, std_emp);
		bool size = equalbool(ft_size, std_size);
		bool max_size = equalbool(ft_emp, std_emp);
		std::string content = equalContent(std_map, ft_map);

		typename ft::map<T1, T2>::const_iterator ft_it;
		typename std::map<T1, T2>::const_iterator std_it;

		fs << "map attributes:\nSTD:\n";
		fs << "Empty   : " << std_emp << "\n";
		fs << "Size    : " << std_size << "\n";
		fs << "Max_size: " << std_max_size << "\n";
		fs << "Content : [";

		for (std_it = std_map.begin(); std_it != std_map.end(); std_it++ ) {
			fs << "[" << (*std_it).first << ", " << (*std_it).second << "]";
		}
		fs << "]";

		fs << "map attributes:\nFT:\n";
		fs << "Empty   : " << ft_emp << "\n";
		fs << "Size    : " << ft_size << "\n";
		fs << "Max_size: " << ft_max_size << "\n";
		fs << "Content : [";

		for (ft_it = ft_map.begin(); ft_it != ft_map.end(); ft_it++ ) {
			fs << "[" << (*ft_it).first << ", " << (*ft_it).second << "]";
		}
		fs << "]";

		if (empty == false) return false;
		else if (size == false) return false;
		else if (max_size == false) return false;
		else if (content == "x") return false;
		return true;
	}

	// template <class T1, class T2>
	void test_map() {
		std::cout << "MAP:\n";

		std::fstream fs;
		std::cout << "Constructors: ";

		fs.open("./test/map/default_constructor", std::fstream::in | std::fstream::out | std::fstream::trunc );
		
		//default constructor 
		{
			std::map<int, std::string>std_map;
			ft::map<int, std::string>ft_map;
			std::cout << ((compareMaps(fs, std_map, ft_map)) == true ? "[OK]" : "[FAIL]");
			fs << "----------------------\n";
			fs << "default constructor: \n";
			fs << "ft::map<T1, T2>ft_map\n";
			fs << "std::map<T1, T2>std_map\n";
			fs.close();
		}

		//range constructor 
		{
			const int range_f[] = {6, 19, 75, 20, 43, 100, 5, 81};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/range_constructor", std::fstream::in | std::fstream::out | std::fstream::trunc );
			compareMaps(fs, std_map, ft_map);

			std::map<int, std::string> std_map_r(std_map.begin(), std_map.end());
			ft::map<int, std::string> ft_map_r(ft_map.begin(), ft_map.end());
			
			std::cout << ((compareMaps(fs, std_map_r, ft_map_r)) == true ? "[OK]" : "[FAIL]");

			fs << "----------------------\n";
			fs << "range constructor: \n";
			fs << "ft::map<T1, T2>ft_map_r\n";
			fs << "std::map<T1, T2>std_map_r\n";
			fs.close();
		}

		//copy constructor
		{
			const int range_f[] = {6, 19, 75, 20, 43, 100, 5, 81};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}
			
			fs.open("./test/map/copy_constructor", std::fstream::in | std::fstream::out | std::fstream::trunc );
			compareMaps(fs, std_map, ft_map);

			std::map<int, std::string> std_map_copy(std_map);
			ft::map<int, std::string> ft_map_copy(ft_map);

			std::cout << ((compareMaps(fs, std_map_copy, ft_map_copy)) == true ? "[OK]" : "[FAIL]");

			fs << "----------------------\n";
			fs << "copy constructor: \n";
			fs << "ft::map<T1, T2>ft_map_copy\n";
			fs << "std::map<T1, T2>std_map_copy\n";
			fs.close();
		}

		//operator =
		{
			const int range_f[] = {6, 19, 75, 20, 43, 100, 5, 81};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/operator=", std::fstream::in | std::fstream::out | std::fstream::trunc );
			compareMaps(fs, std_map, ft_map);

			std::map<int, std::string> std_map_copy = std_map;
			ft::map<int, std::string> ft_map_copy = ft_map;

			std::cout << ((compareMaps(fs, std_map_copy, ft_map_copy)) == true ? "[OK]" : "[FAIL]");

			fs << "----------------------\n";
			fs << "operator= : \n";
			fs << "ft::map<T1, T2>ft_map_copy\n";
			fs << "std::map<T1, T2>std_map_copy\n";
			fs.close();
		}

		std::cout << "\nIterators: ";

		//begin()
		{
			const int range_f[] = {86, 196, 775, 120, 413, 1000, 53, 841};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/iterator_begin", std::fstream::in | std::fstream::out | std::fstream::trunc );
			compareMaps(fs, std_map, ft_map);
			std::cout << "[" << ((printValue(fs, (*std_map.begin()).first, (*ft_map.begin()).first)) == true ? "[OK]" : "[FAIL]");
			std::cout << (printValue(fs, (*std_map.begin()).second, (*ft_map.begin()).second) == true ? "[OK]" : "[FAIL]");
			std::cout << "]";

			fs << "----------------------\n";
			fs << "iterator begin() : \n";
			fs << "ft::map<T1, T2>::iterator ft_map.begin()\n";
			fs << "std::map<T1, T2>::iterator std_map.begin()\n";
			fs.close();
		}

		//const_iterator begin()
		{
			const int range_f[] = {86, 196, 775, 120, 413, 1000, 53, 841};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/const_iterator_begin", std::fstream::in | std::fstream::out | std::fstream::trunc );

			std::map<int, std::string>::const_iterator std_it = std_map.begin();
			ft::map<int, std::string>::const_iterator ft_it = ft_map.begin();

			compareMaps(fs, std_map, ft_map);
			std::cout << "[" << ((printValue(fs, (*std_it).first, (*ft_it).first)) == true ? "[OK]" : "[FAIL]");
			std::cout << ((printValue(fs, (*std_it).second, (*ft_it).second)) == true ? "[OK]" : "[FAIL]");
			std::cout << "]";

			fs << "----------------------\n";
			fs << "const_iterator begin() : \n";
			fs << "ft::map<T1, T2>::const_iterator ft_it\n";
			fs << "std::map<T1, T2>::const_iterator std_it\n";
			fs.close();
		}

		//iterator end()
		{
			const int range_f[] = {8, 16, -75, 10, 13, 3000, 903, 187};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/iterator_end", std::fstream::in | std::fstream::out | std::fstream::trunc );

			std::map<int, std::string>::iterator std_it = std_map.end();
			ft::map<int, std::string>::iterator ft_it = ft_map.end();
			
			compareMaps(fs, std_map, ft_map);

			--std_it;
			--ft_it;

			std::cout << "[" << ((printValue(fs, (*std_it).first, (*ft_it).first)) == true ? "[OK]" : "[FAIL]");
			std::cout << ((printValue(fs, (*std_it).second, (*ft_it).second)) == true ? "[OK]" : "[FAIL]");
			std::cout << "]";

			fs << "----------------------\n";
			fs << "iterator end() : \n";
			fs << "ft::map<T1, T2>::iterator ft_map.end()\n";
			fs << "std::map<T1, T2>::iterator std_map.end()\n";
			fs.close();
		}

		//const_iterator end()
		{
			const int range_f[] = {8, 16, -75, 10, 13, 3000, 903, 187};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/const_iterator_end", std::fstream::in | std::fstream::out | std::fstream::trunc );

			std::map<int, std::string>::const_iterator std_it = std_map.end();
			ft::map<int, std::string>::const_iterator ft_it = ft_map.end();
			
			compareMaps(fs, std_map, ft_map);

			--std_it;
			--ft_it;

			std::cout << "[" << ((printValue(fs, (*std_it).first, (*ft_it).first)) == true ? "[OK]" : "[FAIL]");
			std::cout << ((printValue(fs, (*std_it).second, (*ft_it).second)) == true ? "[OK]" : "[FAIL]");
			std::cout << "]";

			fs << "----------------------\n";
			fs << "const_iterator end() : \n";
			fs << "ft::map<T1, T2>::const_iterator ft_map.end()\n";
			fs << "std::map<T1, T2>::const_iterator std_map.end()\n";
			fs.close();
		}

		//rbegin()
		{
			const int range_f[] = {8657, 78452, 257, -23576, 0, 4656, 23, -346};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/rbegin", std::fstream::in | std::fstream::out | std::fstream::trunc );

			std::map<int, std::string>::reverse_iterator std_it = std_map.rbegin();
			ft::map<int, std::string>::reverse_iterator ft_it = ft_map.rbegin();
			
			compareMaps(fs, std_map, ft_map);

			++std_it;
			++ft_it;

			std::cout << "[" << ((printValue(fs, (*std_it).first, (*ft_it).first)) == true ? "[OK]" : "[FAIL]");
			std::cout << ((printValue(fs, (*std_it).second, (*ft_it).second)) == true ? "[OK]" : "[FAIL]");
			std::cout << "]";

			fs << "----------------------\n";
			fs << "reverse_iterator rbegin() : \n";
			fs << "ft::map<T1, T2>::reverse_iterator ft_map.rbegin()\n";
			fs << "std::map<T1, T2>::reverse_iterator std_map.rbegin()\n";
			fs.close();
		}

		//const rbegin()
		{
			const int range_f[] = {8657, 78452, 257, -23576, 0, 4656, 23, -346};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/const_rbegin", std::fstream::in | std::fstream::out | std::fstream::trunc );

			std::map<int, std::string>::const_reverse_iterator std_it = std_map.rbegin();
			ft::map<int, std::string>::const_reverse_iterator ft_it = ft_map.rbegin();
			
			compareMaps(fs, std_map, ft_map);

			std::cout << "[" << (printValue(fs, (*std_it).first, (*ft_it).first) == true ? "[OK]" : "[FAIL]");
			std::cout << (printValue(fs, (*std_it).second, (*ft_it).second) == true ? "[OK]" : "[FAIL]");
			std::cout << "]";

			fs << "----------------------\n";
			fs << "const_reverse_iterator rbegin() : \n";
			fs << "ft::map<T1, T2>::const_reverse_iterator ft_map.rbegin()\n";
			fs << "std::map<T1, T2>::const_reverse_iterator std_map.rbegin()\n";
			fs.close();
		}

		//rend()
		{
			const int range_f[] = {8657, 78452, 257, -23576, 0, 4656, 23, -346};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/rend", std::fstream::in | std::fstream::out | std::fstream::trunc );

			std::map<int, std::string>::reverse_iterator std_it = std_map.rend();
			ft::map<int, std::string>::reverse_iterator ft_it = ft_map.rend();
			
			compareMaps(fs, std_map, ft_map);

			--std_it;
			--ft_it;

			std::cout << "[" << (printValue(fs, (*std_it).first, (*ft_it).first) == true ? "[OK]" : "[FAIL]");
			std::cout << (printValue(fs, (*std_it).second, (*ft_it).second) == true ? "[OK]" : "[FAIL]");
			std::cout << "]";

			fs << "----------------------\n";
			fs << "reverse_iterator rend() : \n";
			fs << "ft::map<T1, T2>::reverse_iterator ft_map.rend()\n";
			fs << "std::map<T1, T2>::reverse_iterator std_map.rend()\n";
			fs.close();
		}

		//const rend()
		{
			const int range_f[] = {8657, 78452, 257, -23576, 0, 4656, 23, -346};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/const_rend", std::fstream::in | std::fstream::out | std::fstream::trunc );

			std::map<int, std::string>::const_reverse_iterator std_it = std_map.rend();
			ft::map<int, std::string>::const_reverse_iterator ft_it = ft_map.rend();
			
			compareMaps(fs, std_map, ft_map);

			--(--std_it);
			--(--ft_it);

			std::cout << "[" << (printValue(fs, (*std_it).first, (*ft_it).first) == true ? "[OK]" : "[FAIL]");
			std::cout << (printValue(fs, (*std_it).second, (*ft_it).second) == true ? "[OK]" : "[FAIL]");
			std::cout << "]";

			fs << "----------------------\n";
			fs << "const_reverse_iterator rend() : \n";
			fs << "ft::map<T1, T2>::const_reverse_iterator ft_map.rend()\n";
			fs << "std::map<T1, T2>::const_reverse_iterator std_map.rend()\n";
			fs.close();
		}

		std::cout << "\nCapapcity: ";

		//empty true
		{
			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			fs.open("./test/map/empty", std::fstream::in | std::fstream::out | std::fstream::trunc );
			compareMaps(fs, std_map, ft_map);
			std::cout << ((printValue(fs, std_map.empty(), ft_map.empty()) == true) ? "[OK]" : "[FAIL]");

			fs << "----------------------\n";
			fs << "empty(1) : \n";
			fs << "ft::map<T1, T2> ft_map.empty()\n";
			fs << "std::map<T1, T2> std_map.empty()\n";
			fs.close();
		}

		//empty false
		{
			const int range_f[] = {8657, 78452, 257, -23576, 0, 4656, 23, -346};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/not_empty", std::fstream::in | std::fstream::out | std::fstream::trunc );

			compareMaps(fs, std_map, ft_map);
			std::cout << ((printValue(fs, std_map.empty(), ft_map.empty()) == true) ? "[OK]" : "[FAIL]");

			fs << "----------------------\n";
			fs << "empty(0) : \n";
			fs << "ft::map<T1, T2> ft_map.empty()\n";
			fs << "std::map<T1, T2> std_map.empty()\n";
			fs.close();
		}

		//size()
		{
			const int range_f[] = {8657, 78452, 257, -23576, 0, 4656, 23, -346};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/size", std::fstream::in | std::fstream::out | std::fstream::trunc );
			compareMaps(fs, std_map, ft_map);
			std::cout << ((printValue(fs, std_map.size(), ft_map.size()) == true) ? "[OK]" : "[FAIL]");

			std_map.insert(std::make_pair(21, "New content"));
			ft_map.insert(ft::make_pair(21, "New content"));
			std::cout << ((printValue(fs, std_map.size(), ft_map.size()) == true) ? "[OK]" : "[FAIL]");

			fs << "----------------------\n";
			fs << "size() : \n";
			fs << "ft::map<T1, T2> ft_map.size()\n";
			fs << "std::map<T1, T2> std_map.size()\n";
			fs.close();
		}

		//max_size()
		{
			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			fs.open("./test/map/max_size", std::fstream::in | std::fstream::out | std::fstream::trunc );
			compareMaps(fs, std_map, ft_map);
			std::cout << ((printValue(fs, std_map.max_size(), ft_map.max_size()) == true) ? "[OK]" : "[FAIL]");

			fs << "----------------------\n";
			fs << "max_size() : \n";
			fs << "ft::map<T1, T2> ft_map.max_size()\n";
			fs << "std::map<T1, T2> std_map.max_size()\n";
			fs.close();
		}

		std::cout << "\nElement access: ";

		//operator[]
		{
			const int range_f[] = {867, 452, 257, -276, 0, 466, 23, -6};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/operator_at", std::fstream::in | std::fstream::out | std::fstream::trunc );
			compareMaps(fs, std_map, ft_map);
			std::cout << ((printValue(fs, std_map[-9], ft_map[-9]) == true) ? "[OK]" : "[FAIL]");

			std_map[-6] = "changed";
			ft_map[-6] = "changed";

			std::cout << ((printValue(fs, std_map[-9], ft_map[-9]) == true) ? "[OK]" : "[FAIL]");
			
			fs << "----------------------\n";
			fs << "operator[] : \n";
			fs << "ft::map<T1, T2> ft_map[]\n";
			fs << "std::map<T1, T2> std_map[]\n";
			fs.close();
		}

		//value insert
		{
			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			std_map.insert(std::make_pair(21, "school"));
			ft_map.insert(ft::make_pair(21, "school"));
			fs.open("./test/map/insert(value)", std::fstream::in | std::fstream::out | std::fstream::trunc );
			std::cout << ((compareMaps(fs, std_map, ft_map) == true) ? "[OK]" : "[FAIL]");

			fs << "----------------------\n";
			fs << "insert(value) : \n";
			fs << "ft::map<T1, T2> ft_map.insert(pair)\n";
			fs << "std::map<T1, T2> std_map.insert(pair)\n";
			fs.close();
		}

		std::cout << "\nModifiers: ";

		//hint insert
		{
			const int range_f[] = {867, 452, 257, -276, 0, 466, 23, -6};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/insert(hint)", std::fstream::in | std::fstream::out | std::fstream::trunc );
			compareMaps(fs, std_map, ft_map);

			std_map.insert(++(std_map.begin()), std::make_pair(21, "School"));
			ft_map.insert(++(ft_map.begin()), ft::make_pair(21, "School"));

			std::cout << ((compareMaps(fs, std_map, ft_map) == true) ? "[OK]" : "[FAIL]");

			fs << "----------------------\n";
			fs << "insert(hint) : \n";
			fs << "ft::map<T1, T2> ft_map.insert(iterator, pair)\n";
			fs << "std::map<T1, T2> std_map.insert(iterator, pair)\n";
			fs.close();
		}

		//range insert
		{
			const int range_f[] = {867, 452, 257, -276, 0, 466, 23, -6};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;
			std::map<int, std::string> std_map2;
			ft::map<int, std::string> ft_map2;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
				std_map2.insert(std::make_pair(range_f[i] + 1000, range_s[i] + "_second"));
				ft_map2.insert(ft::make_pair(range_f[i] + 1000, range_s[i] + "_second"));
			}

			fs.open("./test/map/insert(range)", std::fstream::in | std::fstream::out | std::fstream::trunc );
			compareMaps(fs, std_map, ft_map);
			compareMaps(fs, std_map2, ft_map2);

			std_map.insert(std_map2.begin(), std_map2.end());
			ft_map.insert(ft_map2.begin(), ft_map2.end());

			std::cout << ((compareMaps(fs, std_map, ft_map) == true) ? "[OK]" : "[FAIL]");
			std::cout << ((compareMaps(fs, std_map2, ft_map2) == true) ? "[OK]" : "[FAIL]");
			fs << "----------------------\n";
			fs << "insert(range) : \n";
			fs << "ft::map<T1, T2> ft_map.insert(iterator f, iterator l)\n";
			fs << "ft::map<T1, T2> ft_map2.insert(iterator f, iterator l)\n";
			fs << "std::map<T1, T2> std_map.insert(iterator f, iterator l)\n";
			fs << "std::map<T1, T2> std_map2.insert(iterator f, iterator l)\n";
			fs.close();
		}

		//erase value
		{
			const int range_f[] = {867, 452, 257, -276, 0, 466, 23, -6};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/erase(value)", std::fstream::in | std::fstream::out | std::fstream::trunc );
			compareMaps(fs, std_map, ft_map);

			std_map.erase(std_map.begin());
			ft_map.erase(ft_map.begin());

			std::cout << ((compareMaps(fs, std_map, ft_map) == true) ? "[OK]" : "[FAIL]");
			fs << "----------------------\n";
			fs << "erase(value) : \n";
			fs << "ft::map<T1, T2> ft_map.erase(iterator)\n";
			fs << "std::map<T1, T2> std_map.erase(iterator)\n";
			fs.close();
		}

		//erase key
		{
			const int range_f[] = {867, 452, 257, -276, 0, 466, 23, -6};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/erase(key)", std::fstream::in | std::fstream::out | std::fstream::trunc );
			compareMaps(fs, std_map, ft_map);

			std_map.erase(466);
			ft_map.erase(466);

			std::cout << ((compareMaps(fs, std_map, ft_map) == true) ? "[OK]" : "[FAIL]");
			fs << "----------------------\n";
			fs << "erase(key) : \n";
			fs << "ft::map<T1, T2> ft_map.erase(key)\n";
			fs << "std::map<T1, T2> std_map.erase(key)\n";
			fs.close();
		}

		//erase range
		{
			const int range_f[] = {867, 452, 257, -276, 0, 466, 23, -6};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/erase(range)", std::fstream::in | std::fstream::out | std::fstream::trunc );
			compareMaps(fs, std_map, ft_map);

			std::map<int, std::string>::iterator std_begin = std_map.begin();
			ft::map<int, std::string>::iterator ft_begin = ft_map.begin();
			std::map<int, std::string>::iterator std_end = std_map.end();
			ft::map<int, std::string>::iterator ft_end = ft_map.end();

			for (int i = 0; i < 2; i++) {
				std_begin++;
				ft_begin++;
			}
			std_end--;
			ft_end--;

			std_map.insert(std_begin, std_end);
			ft_map.insert(ft_begin, ft_end);

			std::cout << ((compareMaps(fs, std_map, ft_map) == true) ? "[OK]" : "[FAIL]");
			fs << "----------------------\n";
			fs << "erase(range) : \n";
			fs << "ft::map<T1, T2> ft_map.erase(iterator f, iterator l)\n";
			fs << "std::map<T1, T2> std_map.erase(iterator f, iterator l)\n";
			fs.close();
		}

		//swap
		{
			const int range_f[] = {867, 452, 257, -276, 0, 466, 23, -6};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;
			std::map<int, std::string> std_map2;
			ft::map<int, std::string> ft_map2;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
				std_map2.insert(std::make_pair(range_f[i] + 1000, range_s[i] + "_second"));
				ft_map2.insert(ft::make_pair(range_f[i] + 1000, range_s[i] + "_second"));
			}

			fs.open("./test/map/swap", std::fstream::in | std::fstream::out | std::fstream::trunc );
			compareMaps(fs, std_map, ft_map);
			compareMaps(fs, std_map2, ft_map2);

			std_map.swap(std_map2);
			ft_map.swap(ft_map2);

			std::cout << ((compareMaps(fs, std_map, ft_map) == true) ? "[OK]" : "[FAIL]");
			std::cout << ((compareMaps(fs, std_map2, ft_map2) == true) ? "[OK]" : "[FAIL]");
			fs << "----------------------\n";
			fs << "swap : \n";
			fs << "ft::map<T1, T2> ft_map.swap\n";
			fs << "std::map<T1, T2> std_map.swap\n";
			fs.close();
		}

		//clear()
		{
			const int range_f[] = {867, 452, 257, -276, 0, 466, 23, -6};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/clear", std::fstream::in | std::fstream::out | std::fstream::trunc );
			compareMaps(fs, std_map, ft_map);

			std_map.clear();
			ft_map.clear();

			std::cout << ((compareMaps(fs, std_map, ft_map) == true) ? "[OK]" : "[FAIL]");
			fs << "----------------------\n";
			fs << "clear : \n";
			fs << "ft::map<T1, T2> ft_map.clear\n";
			fs << "std::map<T1, T2> std_map.clear\n";
			fs.close();
		}

		std::cout << "\nObservers: ";

		//key_compare
		{
			std::map<int, std::string>::key_compare std_key = std::map<int, std::string>().key_comp();
			ft::map<int, std::string>::key_compare ft_key = ft::map<int, std::string>().key_comp();

			bool std_result = std_key(21, 100);
			bool ft_result = ft_key(21, 100);

			fs.open("./test/map/key_compare", std::fstream::in | std::fstream::out | std::fstream::trunc );
			std::cout << ((printBoolResult(fs, std_result, ft_result) == true) ? "[OK]" : "[FAIL]");
			fs << "----------------------\n";
			fs << "key_compare : \n";
			fs << "ft::map<T1, T2> ft_map.key_comp\n";
			fs << "std::map<T1, T2> std_map.key_comp\n";
			fs.close();
		}

		//value_comp
		// {
		// 	std::map<int, std::string>::key_compare std_key = std::map<int, std::string>().value_comp();
		// 	ft::map<int, std::string>::key_compare ft_key = ft::map<int, std::string>().value_comp();

		// 	bool std_result = std_key(std::make_pair(42, "France"), std::make_pair(21, "Russia"));
		// 	bool ft_result = ft_key(ft::make_pair(42, "France"), ft::make_pair(21, "Russia"));

		// 	fs.open("./test/map/value_comp", std::fstream::in | std::fstream::out | std::fstream::trunc );
		// 	std::cout << ((printBoolResult(fs, std_result, ft_result) == true) ? "[OK]" : "[FAIL]");
		// 	fs << "----------------------\n";
		// 	fs << "value_comp : \n";
		// 	fs << "ft::map<T1, T2> ft_map.value_comp\n";
		// 	fs << "std::map<T1, T2> std_map.value_comp\n";
		// 	fs.close();
		// }

		std::cout << "\nOperations: ";

		//find(if exist)
		{
			const int range_f[] = {57, -456, 3245, -67, 123, 78, 2532, -675};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/find_exist", std::fstream::in | std::fstream::out | std::fstream::trunc );
			
			std::map<int, std::string>::iterator std_it = std_map.find(78);
			ft::map<int, std::string>::iterator ft_it = ft_map.find(78);
			
			compareMaps(fs, std_map, ft_map);

			std::cout << "[" << ((printValue(fs, (*std_it).first, (*ft_it).first) == true) ? "[OK]" : "[FAIL]");
			std::cout << ((printValue(fs, (*std_it).second, (*ft_it).second) == true) ? "[OK]" : "[FAIL]") << "]";

			fs << "----------------------\n";
			fs << "find(if exist) : \n";
			fs << "ft::map<T1, T2> ft_map.find()\n";
			fs << "std::map<T1, T2> std_map.find()\n";
			fs.close();
		}

		//find (not exist)
		{
			const int range_f[] = {57, -456, 3245, -67, 123, 78, 2532, -675};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/find_not_exist", std::fstream::in | std::fstream::out | std::fstream::trunc );
			
			std::map<int, std::string>::iterator std_it = std_map.find(12);
			ft::map<int, std::string>::iterator ft_it = ft_map.find(12);
			
			compareMaps(fs, std_map, ft_map);

			std::cout << (printBoolResult(fs, (std_it == std_map.end()), (ft_it == ft_map.end())) == true ? "[OK]" : "[FAIL]");
			fs << "----------------------\n";
			fs << "find(if not exist) : \n";
			fs << "ft::map<T1, T2> ft_map.find()\n";
			fs << "std::map<T1, T2> std_map.find()\n";
			fs.close();
		}

		//count
		{
			const int range_f[] = {-78, 234, 632, 67, 4, 264, -125, -86};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/count", std::fstream::in | std::fstream::out | std::fstream::trunc );
			
			compareMaps(fs, std_map, ft_map);

			std::cout << "[" << (printBoolResult(fs, (std_map.count(264) > 0), (ft_map.count(264) > 0)) == true ? "[OK]" : "[FAIL]");
			std::cout << (printBoolResult(fs, (std_map.count(10) > 0), (ft_map.count(10) > 0)) == true ? "[OK]" : "[FAIL]");
			std::cout << "]";
			fs << "----------------------\n";
			fs << "count() : \n";
			fs << "ft::map<T1, T2> ft_map.count()\n";
			fs << "std::map<T1, T2> std_map.count()\n";
			fs.close();
		}

		//lower_bound
		{
			const int range_f[] = {-78, 234, 632, 67, 4, 264, -125, -86};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/lower_bound", std::fstream::in | std::fstream::out | std::fstream::trunc );
			
			compareMaps(fs, std_map, ft_map);

			std::map<int, std::string>::iterator std_it = std_map.lower_bound(12);
			ft::map<int, std::string>::iterator ft_it = ft_map.lower_bound(12);

			std::cout << "[" << ((printValue(fs, (*std_it).first, (*ft_it).first) == true) ? "[OK]" : "[FAIL]");
			std::cout << ((printValue(fs, (*std_it).second, (*ft_it).second) == true) ? "[OK]" : "[FAIL]") << "]";
			fs << "----------------------\n";
			fs << "lower_bound() : \n";
			fs << "ft::map<T1, T2> ft_map.lower_bound()\n";
			fs << "std::map<T1, T2> std_map.lower_bound()\n";
			fs.close();
		}

		//upper_bound
		{
			const int range_f[] = {-78, 234, 632, 67, 4, 264, -125, -86};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/upper_bound", std::fstream::in | std::fstream::out | std::fstream::trunc );
			
			compareMaps(fs, std_map, ft_map);

			std::map<int, std::string>::iterator std_it = std_map.upper_bound(67);
			ft::map<int, std::string>::iterator ft_it = ft_map.upper_bound(67);

			std::cout << "[" << ((printValue(fs, (*std_it).first, (*ft_it).first) == true) ? "[OK]" : "[FAIL]");
			std::cout << ((printValue(fs, (*std_it).second, (*ft_it).second) == true) ? "[OK]" : "[FAIL]") << "]";
			fs << "----------------------\n";
			fs << "upper_bound() : \n";
			fs << "ft::map<T1, T2> ft_map.upper_bound()\n";
			fs << "std::map<T1, T2> std_map.upper_bound()\n";
			fs.close();
		}

		//equal_range
		{
			const int range_f[] = {-78, 234, 632, 67, 4, 264, -125, -86};
			const std::string range_s[]  = {"one", "two", "three", "four", "ber", "ike", "och", "durt"};

			std::map<int, std::string> std_map;
			ft::map<int, std::string> ft_map;

			for (int i = 0; i < 8; i++) {
				std_map.insert(std::make_pair(range_f[i], range_s[i]));
				ft_map.insert(ft::make_pair(range_f[i], range_s[i]));
			}

			fs.open("./test/map/equal_range", std::fstream::in | std::fstream::out | std::fstream::trunc );
			
			compareMaps(fs, std_map, ft_map);

			std::cout << "[" << ((printValue(fs, (*(std_map.equal_range(67).first)).first, (*(ft_map.equal_range(67).first)).first) == true) ? "[OK]" : "[FAIL]");
			std::cout << ((printValue(fs, (*(std_map.equal_range(67).second)).first, (*(ft_map.equal_range(67).second)).first) == true) ? "[OK]" : "[FAIL]") << "]";
			fs << "----------------------\n";
			fs << "equal_range() : \n";
			fs << "ft::map<T1, T2> ft_map.equal_range()\n";
			fs << "std::map<T1, T2> std_map.equal_range()\n";
			fs.close();
			std::cout << std::endl;
		}
	}

	int main() {
		test_map();
		// std::map<int, std::string> std_map;
		// ft::map<int, std::string> ft_map;
		// ft::map<int, std::string> mymap;
		// std::map<int, std::string> stdmap;
		// ft_map.insert(ft_map.begin(), ft::make_pair(1, "first"));
		// ft_map.insert(ft_map.begin(), ft::make_pair(2, "second"));
		// std_map.insert(std_map.begin(), std::make_pair(1, "ber"));
		// std_map.insert(std_map.begin(), std::make_pair(2, "ike"));

		// mymap.insert(ft_map.begin(), ft_map.end());
		// stdmap.insert(std_map.begin(), std_map.end());

		// std::string ft_em = "null";
		// std::string std_em = "null";
		// std::string myem = "null";
		// std::string stdem = "null";
		// if (ft_map.empty() ) ft_em = "true"; else ft_em = "false";
		// std::cout << "map is empty? - " << ft_em << "\n";
		// if (std_map.empty()) std_em = "true"; else std_em = "false";
		// std::cout << "map is empty? - " << std_em << "\n";
		// if (mymap.empty()) myem = "true"; else myem = "false";
		// std::cout << "map is empty? - " << myem << "\n";
		// if (stdmap.empty()) stdem = "true"; else stdem = "false";
		// std::cout << "map is empty? - " << stdem << "\n";

		// std::cout << "------------------------------------\n";
		// std::cout << "ft_map size = " << ft_map.size() << "\n";
		// std::cout << "std_map size = " << std_map.size() << "\n";
		// std::cout << "mymap size = " << mymap.size() << "\n";
		// std::cout << "stdmap size = " << stdmap.size() << "\n";

		// std::cout << "------------------------------------\n";

		// std::cout << "ft_map first = " << ft_map.find(1)->first << ", second = " << ft_map.find(1)->second << "\n";
		// std::cout << "std_map first = " << std_map.find(1)->first << ", second = " << std_map.find(1)->second<< "\n";
		// std::cout << "mymap first = " << mymap.find(1)->first << ", second = " << mymap.find(1)->second << "\n";
		// std::cout << "stdmap first = " << stdmap.find(1)->first << ", second = " << stdmap.find(1)->second<< "\n";

		// ft::map<int, std::string>::iterator it_ft = ft_map.begin();
		// std::map<int, std::string>::iterator it_std = std_map.begin();
		// ft_map.insert(ft::make_pair(it_std->first, it_std->second));
		// std_map.insert(std::make_pair(it_ft->first, it_ft->second));
		// ft::map<int, std::string>::iterator iter_ft = ft_map.end();
		// std::map<int, std::string>::iterator iter_std = std_map.end();
		// for ( ; it_ft != ft_map.end(); it_ft++)
		// 	std::cout << it_ft->first << "-" << it_ft->second << "\n";
		// std::cout << "\n";
		
		// std::cout << "------------------------------------\n";
		// std::cout << "ft_map.operator[] = " << ft_map.operator[](1) << "\n";
		// std::cout << "std_map.operator[] = " << std_map.operator[](1) << "\n";
		// std::cout << "mymap.operator[] = " << mymap.operator[](1) << "\n";
		// std::cout << "stdmap.operator[] = " << stdmap.operator[](1) << "\n";
		
		// for ( ; it_std != iter_std; it_std++)
		// 	std::cout << it_std->first << "-" << it_std->second << "\n";
		// 	std::cout << "\n";

		return 0;
	}