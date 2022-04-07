#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
// #include <iterator>
#include <stdexcept>
// #include "iterator_.hpp"
#include "iterator_v.hpp"
// #include "reverse_iterator.hpp"
#include "utils.hpp"
#include <iostream>


namespace ft {
	template <class T, class alloc = std::allocator<T> > // generic template
	class vector {
	public:
		typedef T														value_type;
		typedef alloc													allocator_type;
		typedef size_t													size_type;
		typedef value_type&						 						reference;
		typedef const value_type&						 				const_reference;
		typedef value_type*						 						pointer;
		typedef const value_type*					 					const_pointer;
		typedef ft::iterator_v<T*>										iterator;        			
		typedef ft::iterator_v<const T*>								const_iterator;  			
		typedef ft::reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef ptrdiff_t												difference_type;

		// protected:
			// allocator_type		_alloc;
			// pointer				_begin;
			// pointer				_end;
			// pointer				_cap_end;
			// size_type			_size;

		//(constructor)
		// explicit vector (const allocator_type& alloc = allocator_type()); //empty container constructor (default constructor)
		// explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()); //fill constructor
		// template <class InputIterator>
		// vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()); //range constructor
		// vector (const vector& x); //copy constructor

		//(destructor)
		// virtual 						~vector();

		//operator=
		// vector& 						operator= (const vector& x);

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
		explicit vector (const allocator_type& allocator = allocator_type()) : _alloc(allocator), _begin(NULL), _end(NULL), _cap_end(NULL), _size(0) {
			}; //empty container constructor (default constructor)

		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& allocator = allocator_type()) : _alloc(allocator) {
			try			{
				_begin = _alloc.allocate(n);
				_end = _cap_end = _begin;
				_size = 0;
				insert(begin(), n, val);
			}
			catch(const std::bad_alloc& e) {
				std::cerr << e.what() << '\n';
			}
		}; //fill constructor

		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type& allocator = allocator_type(),
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0) : _alloc(allocator) {
			difference_type dif = distance(first, last);
			if (dif > 0) {
				if (!(_begin = _alloc.allocate(dif)))
					throw std::bad_alloc();
				_end = _cap_end = _begin + dif;
				_size = dif;
				assign(first, last);
			}
		} //range constructor
		
		vector (const vector& x) : _alloc(x._alloc), _begin(NULL), _end(NULL), _cap_end(NULL), _size(0) {	
			*this = x;
		} //copy constructor

		//operator=
		vector& 					operator= (const vector& x) {
			assign(x.begin(), x.end()); //leaks
			return *this;
		}

		//(destructor)
		~vector() {
			if (_begin)
				destroy_dealloc(_begin, _end, capacity());
		}

		//iterators
		iterator 					begin()			{ return iterator(_begin); };
		const_iterator 				begin() const	{ return iterator(_begin); };
		iterator 					end()			{ return iterator(_end); };
		const_iterator 				end() const		{ return iterator(_end); };
		reverse_iterator 			rbegin()		{ return reverse_iterator(end()); };
		const_reverse_iterator 		rbegin() const	{ return const_reverse_iterator(end()); };
		reverse_iterator 			rend()			{ return reverse_iterator(begin()); };
		const_reverse_iterator 		rend() const	{ return const_reverse_iterator(begin()); };

		//Modifiers:
		template <class InputIterator>
		ENABLE_IF_IS_NOT_INTEGRAL(InputIterator)
  		assign (InputIterator first, InputIterator last) { //range
			if (first > last)
		  		throw std::range_error("vector<T>::assign: range error");
			clear();
			insert(begin(), first, last); //leak
		}

		void 		assign (size_type n, const value_type& val) { //fill
			clear();
			insert(begin(), n, val);
		}

		iterator	insert (iterator position, const value_type& val) {
			difference_type dif = distance(begin(), position);
			size_type S = size() == 0 ? 0 : dif;   
			insert(position, 1, val);
			return begin() + S;
		}

		void		insert (iterator position, size_type n, const value_type& val) {
			value_type tmp = val;
			size_type s = size(); 
			size_type cap = capacity();
			if (!n)
				return ;
			else if (n > max_size() - s)
				throw std::length_error("vector<T> length error");
			else if (s + n > cap) {
				cap = s + n > capacity() * 2 ? s + n : capacity() * 2;
				pointer ptr = _alloc.allocate(cap);
				pointer tmp_ptr;
				try	{
					tmp_ptr = uninitialized_copy(begin(), position, ptr);
					tmp_ptr = fill(tmp_ptr, n, tmp);
					uninitialized_copy(position, end(), tmp_ptr);
				}
				catch(const std::bad_alloc& ba)	{
					destroy_dealloc(ptr, tmp_ptr, cap);
					std::cerr << "bad_alloc caught: " << ba.what() << '\n';
				}
				if (_begin)
					destroy_dealloc(_begin, _end, static_cast<size_type>(_end - _begin));
				_begin = ptr;
				_size += n;
				_end = ptr + size();
				_cap_end = ptr + cap;
			}
			else if (size_type(distance(position, end())) < n) {
				pointer pos_n = position.base() + n;
				uninitialized_copy(position, end(), pos_n);
				try	{
					fill(_end, n - (distance(position, end())), tmp); }
				catch(const std::bad_alloc& ba)	{
					for ( ; pos_n != _end + n; ++pos_n)
						_alloc.destroy(pos_n);
					std::cerr << "bad_alloc caught: " << ba.what() << '\n';
				}
				_end += n;
				_size += n;
				fill_st(position, end() - n, val);
			}
			else {
				iterator tmp = end();
				_end = uninitialized_copy(tmp - n, tmp, _end);
				ft::copy_backward(position, tmp - n, tmp);
				fill_st(position, position + n, val);
				_size += n;
			}
		}

		template <class InputIterator>
		ENABLE_IF_IS_NOT_INTEGRAL(InputIterator)
		insert (iterator position, InputIterator first, InputIterator last) {
			if (position < begin() || position > end() || first > last)
				throw std::logic_error("vector: logic error");
			difference_type dif = distance(first, last);
			size_type cap = capacity();
			if (!dif) {
				return ; }
			else if (size_t(dif) > max_size() - size())
				throw std::length_error("vector<T> length error");
			else if (size() + dif > cap) {
				cap = _size + static_cast<unsigned long>(dif) > capacity() * 2 ? _size + dif : capacity() * 2;
				pointer ptr = _alloc.allocate(cap);  //leak
				difference_type range1 = distance(first, last);
				difference_type range2 = distance(position, end());
				try	{
					uninitialized_copy(begin(), position, ptr);
					uninitialized_copy(first, last, ptr + distance(begin(),position));
					uninitialized_copy(position, end(), ptr + distance(first, last)); 
				}
				catch(const std::bad_alloc& ba) {
					destroy_dealloc(ptr, ptr + cap, cap);
					std::cerr << "bad_alloc caught: " << ba.what() << '\n';
					throw ;
				}
				if (_begin)
					destroy_dealloc(_begin, _end, _end - _begin);
				// std::cout << _begin << "\n";
				_begin = ptr;
				_size += dif;
				_end = ptr + size();
				_cap_end = ptr + cap;
			}
			else if (distance(position, end()) < dif) {
				pointer pos = position.base() + dif;
				uninitialized_copy(position, end(), pos);
				InputIterator mid = first;
				ft::advance(mid, distance(position, end()));
				try {
					uninitialized_copy(mid, last, _end);
				}
				catch(const std::bad_alloc& ba) {
					for ( ; pos != _end + dif; ++pos)
						_alloc.destroy(pos);
					std::cerr << "bad_alloc caught: " << ba.what() << '\n';
					throw ;
				}
				_size += dif;
				_end += dif;
				std::copy(first, mid, position);
			}
			else if (0 < dif) {
				iterator tmp = end();
				_end = uninitialized_copy(tmp - dif, tmp, _end);
				ft::copy_backward(position, tmp - dif, tmp);
				std::copy(first, last, position);
				_size += dif;
			}
		}

		void 		push_back (const value_type& val) {
			if (size() == capacity()) {
				size_type n = capacity() == 0 ? 1 : capacity()  * 2;
				reserve(n);
			}
			_begin[_size] = val;
			++_size;
			_end = _begin + _size;
		}

		void 		pop_back() {
			_alloc.destroy(_begin + _size);
			_size--;
			_end = _begin + _size;
		}
		
		iterator 	erase (iterator position) {
			size_t dif = static_cast<size_t>(distance(begin(), position));
			for (size_t i = dif; i <= _size; ++i)
				_begin[i] = _begin[i + 1];
			--_size;
			return position;
		}

		iterator 	erase (iterator first, iterator last) {
			if (first > last)
				throw std::out_of_range("vector<T>::erase: out of range error");
			difference_type dif = distance(first, last);
			if (first != last) {
				pointer ptr = std::copy(last, end(), first.base());
				for (; ptr != &(*last); ++ptr)
					_alloc.destroy(ptr);
				_end = ptr;
				_size -= dif;
			}
			return first;
		}

		void 		swap (vector& x) {
			if (*this != x) {
				std::swap(_alloc, x._alloc);
				std::swap(_begin, x._begin);
				std::swap(_end, x._end);
				std::swap(_cap_end, x._cap_end);
				std::swap(_size, x._size);
			}
		}

		void 		clear() {
			pointer new_end = _end;
			for (; _begin != new_end; --new_end)
				_alloc.destroy(new_end);
			_end = new_end;
			_size = 0;
		}

		//capacity
		size_type 	size() const					{ return _size;	}
		size_type	max_size() const 				{ return _alloc.max_size();	}
		size_type	capacity() const				{ return (_begin == 0 ? 0 : _cap_end - _begin);	}
		bool 		empty() const					{ return size() == 0;}

		void 		resize (size_type n, value_type val = value_type()) {
			if (n > max_size())
				throw std::length_error("vector<T>::reserve: length error");
			else if (n == _size)
				return ;
			else if (_size > n) {
				for (; _size != n; )
					pop_back();
			}
			else {
				size_type sz = alloc_capacity(n);
				reserve(sz);
				for (size_type i = _size; i < n; ++i)
					push_back(val);
				_cap_end = _begin + sz;
			}
		}

		void 		reserve (size_type n) {
			if (n > max_size())
				throw std::length_error("vector<T>::reserve: length error");
			else if (n > capacity()) {
				pointer ptr = _alloc.allocate(n);
				reallocate(begin(), end(), ptr, n);
				_begin = ptr;
				_end = ptr + size();
				_cap_end = ptr + n;
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
		
		reference 			front() 			{ return *(begin());	}
		const_reference 	front() 	const { return *(begin());	}
		reference 			back() 				{ return *(end() - 1);	}
		const_reference 	back() 		const { return *(end() - 1);	}
		value_type			*data()				{ return _begin;}

		//Allocator:
		allocator_type 		get_allocator() const { return _alloc; }

		template <class T1, class Alloc>
		friend bool operator== (const vector<T1,Alloc>& lhs, const vector<T1,Alloc>& rhs); 
		template <class T1, class Alloc>
		friend bool operator!= (const vector<T1,Alloc>& lhs, const vector<T1,Alloc>& rhs);
		template <class T1, class Alloc>
		friend bool operator<  (const vector<T1,Alloc>& lhs, const vector<T1,Alloc>& rhs);
		template <class T1, class Alloc>
		friend bool operator<= (const vector<T1,Alloc>& lhs, const vector<T1,Alloc>& rhs);
		template <class T1, class Alloc>
	  	friend bool operator>  (const vector<T1,Alloc>& lhs, const vector<T1,Alloc>& rhs);
		template <class T1, class Alloc>
	  	friend bool operator>= (const vector<T1,Alloc>& lhs, const vector<T1,Alloc>& rhs);
		template <class T1, class Alloc>
  		friend void swap (vector<T1,Alloc>& x, vector<T1,Alloc>& y);

	protected:
		allocator_type		_alloc;
		pointer				_begin;
		pointer				_end;
		pointer				_cap_end;
		size_type			_size;


		template <class initer>
		typename vector<initer>::difference_type distance (initer first, initer last) {
			difference_type n = 0;
			for (; first != last; ++first) {
				++n;
				if (first == last)
					return n;
			}
			return n;
		}

		size_type alloc_capacity(size_type n) {
			size_type sz = 0;
			if (capacity() * 2 < n) 
				sz = n;
			else if (capacity() > n)
				sz = capacity();
			else
				sz = capacity() * 2;
			return sz;
		}

		void	destroy_dealloc(pointer first, pointer last, size_type n) {
			pointer tmp = first;
			for (; tmp != last; ++tmp)
				_alloc.destroy(tmp);
			_alloc.deallocate(first, n);
		}

		void reallocate(iterator first, iterator last, pointer ptr, size_type n) {
			difference_type diff = _end - _begin;
			try		{
				std::uninitialized_copy(first, last, ptr);
			}
			catch(const std::bad_alloc& ba) {
				_alloc.deallocate(ptr, n);
				std::cerr << "bad_alloc caught: " << ba.what() << '\n';
			}
			if (_begin)
				destroy_dealloc(_begin, _end, diff);
		}

		template<class InputIterator, class ForwardIterator>
		  ForwardIterator uninitialized_copy ( InputIterator first, InputIterator last,
		                                       ForwardIterator result )	{
		  for (; first!=last; ++result, ++first)
		    new (static_cast<void*>(&*result))
		      typename iterator_traits<ForwardIterator>::value_type(*first);
		  return result;
		}

		pointer copy(iterator First, iterator Last, pointer P) {
			pointer tmp = P;
			try	{
				for (; First != Last; First++, P++)
					_alloc.construct(P, *First);
			}
			catch(const std::bad_alloc& ba) {
				for (; tmp != P; ++tmp)
					_alloc.destroy(tmp);
				std::cerr << "bad_alloc caught: " << ba.what() << '\n';
				throw ;
			}
			return P;
		}

		pointer ufill(pointer P, size_type n, const value_type &val) {
			pointer Pt = P;
			try	{
				for (; 0 < n; --n, ++P)
					_alloc.construct(P, val);
			}
			catch(const std::exception& e) {
				for (; Pt != P; ++Pt)
					_alloc.destroy(Pt);
				std::cerr << e.what() << '\n';
			}
			
		}

		pointer fill(pointer P, size_type n, const value_type& val) {
			pointer tmp = P;
			try	{
				for (; 0 < n; --n, ++P)
					_alloc.construct(P, val);
			}
			catch(const std::bad_alloc& ba) {
				for (; tmp != P; ++tmp)
					_alloc.destroy(tmp);
				std::cerr << "bad_alloc caught: " << ba.what() << '\n';
				throw ;
			}
			return P;
		}
	};

	//Non-member function overloads:
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { 
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs == rhs);
	}
	
	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { 
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { 
		return !(lhs > rhs);
	}
	template <class T, class Alloc>
  	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}

	template <class T, class Alloc>
  	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { 
		return !(lhs < rhs);
	}

	// template <class T, class Alloc>
	// void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) { x.swap(y); }
}


namespace std {
	template <class T, class Alloc>
  	void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y) {
		x.swap(y);
	}
}

#endif