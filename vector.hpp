#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
// #include <iterator>
#include <stdexcept>
#include "iterator.hpp"
#include "iterator_v.hpp"
#include <iostream>
#include <algorithm>

namespace ft {

	template <class T, class alloc = std::allocator<T> > // generic template
	class vector {
	public:
		typedef T														value_type;
		typedef alloc													allocator_type;
		typedef size_t													size_type;
		typedef typename allocator_type::reference 						reference;
		typedef typename allocator_type::const_reference 				const_reference;
		typedef typename allocator_type::pointer 						pointer;
		typedef typename allocator_type::const_pointer 					const_pointer;
		typedef typename ft::iterator_v<T>::iterator					iterator;        			//поменять на свой итератор
		typedef typename ft::iterator_v<T>::const_iterator				const_iterator;  			//поменять на свой итератор
		// typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
		// typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;


		//(constructor)
		// explicit vector (const allocator_type& alloc = allocator_type()); //empty container constructor (default constructor)
		// explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()); //fill constructor
		// template <class InputIterator>
	    // vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()); //range constructor
		// vector (const vector& x); //copy constructor

		//(destructor)
		// virtual 					~vector();

		//operator=
		// vector& 					operator= (const vector& x);

		//iterators
		// iterator 					begin();
		// const_iterator 				begin() const;
		// iterator 					end();
		// const_iterator 				end() const;
		// reverse_iterator 			rbegin();
		// const_reverse_iterator 		rbegin() const;
		// reverse_iterator 			rend();
		// const_reverse_iterator 		rend() const;
		
		//capacity
		// size_type 					size() const;
		// size_type 					max_size() const;
		// void 						resize (size_type n, value_type val = value_type());
		// size_type 					capacity() const;
		// bool 						empty() const;
		// void 						reserve (size_type n);

		//Element access:
		// reference 					operator[] (size_type n);
		// const_reference 				operator[] (size_type n) const;
		// reference 					at (size_type n);
		// const_reference 				at (size_type n) const;
		// reference 					front();
		// const_reference 				front() const;
		// reference 					back();
		// const_reference 				back() const;

		//Modifiers:
		// template <class InputIterator>
  		// void 						assign (InputIterator first, InputIterator last);	//range
		// void 						assign (size_type n, const value_type& val);  		//fill
		// void 						push_back (const value_type& val);
		// void 						pop_back();
		// iterator 					insert (iterator position, const value_type& val); //single element
	    // void 						insert (iterator position, size_type n, const value_type& val);  //fill
		// template <class InputIterator>
    	// void 						insert (iterator position, InputIterator first, InputIterator last); //range
		// iterator 					erase (iterator position);
		// iterator 					erase (iterator first, iterator last);
		// void 						swap (vector& x);
		// void 						clear();

		//Allocator:
		// allocator_type 				get_allocator() const;

		//Non-member function overloads:
		// template <class T, class Alloc>
			// bool 					operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		// template <class T, class Alloc>
			// bool 					operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		// template <class T, class Alloc>
			// bool 					operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		// template <class T, class Alloc>
			// bool 					operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		// template <class T, class Alloc>
	  		// bool 					operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		// template <class T, class Alloc>
	  		// bool 					operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		// template <class T, class Alloc>
  			// void 					swap (vector<T,Alloc>& x, vector<T,Alloc>& y);

		// Construstors:	
		explicit vector (const allocator_type& allocator = allocator_type()) : _begin(NULL), _end(NULL), _cap_end(NULL), _alloc(allocator) {
			}; //empty container constructor (default constructor)

		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& allocator = allocator_type()) {
			try			{
				_begin = allocator.allocate(n);
			}
			catch(const std::bad_alloc& e)
			{
				std::cerr << e.what() << '\n';
			}
		}; //fill constructor

		template <class InputIterator>
	    vector (InputIterator first, InputIterator last, const allocator_type& allocator = allocator_type()); //range constructor
		
		vector (const vector& x); //copy constructor

		//iterators
		iterator 					begin()			{ return _begin; };
		const_iterator 				begin() const	{ return _begin ; };
		iterator 					end()			{ return _end;};
		const_iterator 				end() const		{ return _end; };
		// reverse_iterator 			rbegin();
		// const_reverse_iterator 		rbegin() const;
		// reverse_iterator 			rend();
		// const_reverse_iterator 		rend() const;

		//Modifiers:
		template <class InputIterator>
  		void 		assign (InputIterator first, InputIterator last) { //range
		}

		void 		assign (size_type n, const value_type& val) { //fill

		}

		iterator	insert (iterator position, const value_type& val) {
			size_type S = size() == 0 ? 0 : position - begin();
			insert(position, (size_type)1, val);
			return begin() + S;
		}

	    void		insert (iterator position, size_type n, const value_type& val) {
			
			// value_type tmp = val;
			// size_type s = capacity();
			// if (n == 0) ;
			// else if (n > max_size() - size())
			// 	throw std::length_error("vector<T> length error");
			// else if (size() + n > capacity()) {
			// 	s = max_size() - s / 2 < s ? 0 : s + s / 2;
			// 	if (s < size() + n)
			// 		s = size() + n;
			// }
			// pointer Ptr = _alloc.allocate(s);
			// pointer Pcopy;
			// try	{
			// 	Pcopy = copy(begin(), position, Ptr);
			// 	Pcopy = fill(Pcopy, n, tmp);
			// 	copy(position, end(), Pcopy);
			// }
			// catch(const std::bad_alloc& ba)	{
			// 	for (; Ptr != Pcopy; ++Ptr)
			// 		_alloc.destroy(Ptr);
			// 	_alloc.deallocate(Ptr, s);
			// 	std::cerr << "bad_alloc caught: " << ba.what() << '\n';
			// 	throw ;
			// }
			// if (_begin != 0) {
			// 	for (; _begin != _end; ++_begin)
			// 		_alloc.destroy(_begin);
			// 	_alloc.deallocate(_begin, _end - _begin);
			// 	_end = Ptr + s;
			// 	_cap_end = Ptr + size() + n;
			// 	_begin = Ptr;
			// }
			// else if ((size_type) (end() - position) < n) {
			// 	copy(position, end(), position.base() + n);
			// 	try	{
			// 		fill(_end, n - (end() - position), tmp);
			// 	}
			// 	catch(const std::bad_alloc& ba)	{
			// 		for (; (position.base() + n) != _end + n; ++(position.base() + n))
			// 			_alloc.destroy(position.base() + n);
			// 		std::cerr << "bad_alloc caught: " << ba.what() << '\n';
			// 		throw;
			// 	}
			// }
			// else {
			// 	iterator n_end = end();
			// 	_end = copy(n_end - n, n_end, _end);
			// 	copy_backward(position, n_end - n, tmp);
			// 	fill(position, position + n, tmp);
			// }
		}

		template <class InputIterator>
    	void		insert (iterator position, InputIterator first, InputIterator last) {
			// if ()
		}
		void 		push_back (const value_type& val) {
			insert(end(), val);
		};
		void 		pop_back() {
			erase(end() -1);
		}
		iterator 	erase (iterator position) {
			return erase(position, position + 1);
		}
		iterator 	erase (iterator first, iterator last) {
			if (first <= last)
				throw std::out_of_range("vector<T> out of range error");
			if (first != last) {
				pointer ptr = copy(last, end(), first.base());
				for (; ptr != last; ++ptr)
					_alloc.destroy(ptr);
				_end = ptr;
			}
			return first;
		}
		void 		swap (vector& x) {
			if (_alloc == x._alloc) {
				swap(_begin, x._begin);
				swap(_end, x._end);
				swap(_cap_end, x._cap_end);
			}
			// std::__swap_allocator(_alloc, x._alloc);
		}
		void 		clear() {
			erase(_begin, _end);
		}

		//capacity
		size_type 	size() const					{ return (_begin == 0 ? 0 : _end - _begin);	}
		size_type	max_size() const 				{ return _alloc.max_size();	}
		void 		resize (size_type n, value_type val = value_type()) {
			if (size() > n)
				erase(begin() + n, end());
			else if (size() < n) {
				if (n > capacity())
					reallocate();
				else
					insert();
			}
		}
		size_type	capacity() const				{ return (_begin == 0 ? 0 : _cap_end - _begin);	}
		bool 		empty() const					{ return size() == 0;}
		void 		reserve (size_type n) {
			if (n > max_size())
				throw std::length_error("vector<T> length error");
			else if (n > capacity()) {
				reallocate(n);
			}
		}

		//Element access:
		reference			operator[] (size_type n)		{ return *(_begin + n);	}
		const_reference 	operator[] (size_type n) const	{ return *(_begin + n); }
		reference 			at (size_type n) {
			if (n > size())
				throw std::out_of_range("vector<T> out of range error");
			return *(_begin + n);
		}
		const_reference		at (size_type n) const {
			if (n > size())
				throw std::out_of_range("vector<T> out of range error");
			return *(_begin + n);
		}
		reference 			front() { return *_begin;	}
		const_reference 	front() const { return *_begin;	}
		reference 			back() { return *_end - 1;	}
		const_reference 	back() const { return *_end - 1;	}

		//Allocator:
		allocator_type 		get_allocator() const { return _alloc; }

	protected:
		allocator_type		_alloc;
		pointer				_begin;
		pointer				_end;
		pointer				_cap_end;

		void reallocate(size_type n) {
			pointer ptr = _alloc.allocate(n);
			try		{
				copy(begin(), end(), ptr);
			}
			catch(const std::bad_alloc& ba) {
				_alloc.deallocate(ptr, n);
				std::cerr << "bad_alloc caught: " << ba.what() << '\n';
			}
			if (_begin != 0) {
				for (; _begin != _end; ++_begin)
					_alloc.destroy(_begin);
				_alloc.deallocate(_begin, _end - _begin);
			}
			_begin = ptr;
			_end = ptr + size();
			_cap_end = ptr + n;
			return ptr;
		}

		template <class Ts>
		void    swap(Ts& a, Ts& b){
		    Ts tmp = a;
		    a = b;
		    b = tmp;
		}

		pointer copy(iterator First, iterator Last, pointer P) {
			pointer tmp = P;
			try		{
				for (; First != Last; ++First, ++P)
					_alloc.construct(P, *First);
			}
			catch(const std::bad_alloc& ba) {
				for (; tmp != P; ++tmp)
					_alloc.destroy(tmp);
				throw ;
				std::cerr << "bad_alloc caught: " << ba.what() << '\n';
			}
			return P;
		}
		pointer fill(pointer P, size_type n, const value_type& val) {
			pointer tmp = P;
			try		{
				for (; 0 < n; --n, ++P)
					_alloc.construct(P, *val);
			}
			catch(const std::bad_alloc& ba) {
				for (; tmp != P; ++tmp)
					_alloc.destroy(tmp);
				throw ;
				std::cerr << "bad_alloc caught: " << ba.what() << '\n';
			}
			return P;
		}
		value_type& copy_backward(iterator first, iterator second, const value_type& val) {
			for (; first != second; )
				*--val = *--second;
			return val;
		}
		iterator iterator_cast(iterator it) { 
			return begin() + (it - begin());
		}
	};
}

#endif