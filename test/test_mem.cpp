    pointer allocate(size_type __n, allocator<void>::const_pointer = 0) //1809
        {
        if (__n > max_size())
            __throw_length_error("allocator<T>::allocate(size_t n)"
                                 " 'n' exceeds maximum supported size");
        return static_cast<pointer>(_VSTD::__libcpp_allocate(__n * sizeof(_Tp), _LIBCPP_ALIGNOF(_Tp)));
        }


vector<_Tp, _Allocator>::__push_back_slow_path(_Up& __x) //1614
{
    allocator_type& __a = this->__alloc();
    __split_buffer<value_type, allocator_type&> __v(__recommend(size() + 1), size(), __a);
    // __v.push_back(_VSTD::forward<_Up>(__x));
    __alloc_traits::construct(__a, _VSTD::__to_raw_pointer(__v.__end_), _VSTD::forward<_Up>(__x));
    __v.__end_++;
    __swap_out_circular_buffer(__v);
}

void vector<_Tp, _Allocator>::push_back(const_reference __x) 
{
    if (this->__end_ != this->__end_cap())
    {
        __RAII_IncreaseAnnotator __annotator(*this);
        __alloc_traits::construct(this->__alloc(),
                                  _VSTD::__to_raw_pointer(this->__end_), __x);
        __annotator.__done();
        ++this->__end_;
    }
    else
        __push_back_slow_path(__x);
}

template <class _Allocator>
typename vector<bool, _Allocator>::iterator
vector<bool, _Allocator>::insert(const_iterator __position, size_type __n, const value_type& __x)
{
    iterator __r;
    size_type __c = capacity();
    if (__n <= __c && size() <= __c - __n)
    {
        const_iterator __old_end = end();
        __size_ += __n;
        _VSTD::copy_backward(__position, __old_end, end());
        __r = __const_iterator_cast(__position);
    }
    else
    {
        vector __v(__alloc());
        __v.reserve(__recommend(__size_ + __n));
        __v.__size_ = __size_ + __n;
        __r = _VSTD::copy(cbegin(), __position, __v.begin());
        _VSTD::copy_backward(__position, cend(), __v.end());
        swap(__v);
    }
    _VSTD::fill_n(__r, __n, __x);
    return __r;
}

typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::insert(const_iterator __position, size_type __n, const_reference __x)
{
    pointer __p = this->__begin_ + (__position - begin());
    if (__n > 0)
    {
        if (__n <= static_cast<size_type>(this->__end_cap() - this->__end_))
        {
            size_type __old_n = __n;
            pointer __old_last = this->__end_;
            if (__n > static_cast<size_type>(this->__end_ - __p))
            {
                size_type __cx = __n - (this->__end_ - __p);
                __construct_at_end(__cx, __x);
                __n -= __cx;
            }
            if (__n > 0)
            {
                __RAII_IncreaseAnnotator __annotator(*this, __n);
                __move_range(__p, __old_last, __p + __old_n);
                __annotator.__done();
                const_pointer __xr = pointer_traits<const_pointer>::pointer_to(__x);
                if (__p <= __xr && __xr < this->__end_)
                    __xr += __old_n;
                _VSTD::fill_n(__p, __n, *__xr);
            }
        }
        else
        {
            allocator_type& __a = this->__alloc();
            __split_buffer<value_type, allocator_type&> __v(__recommend(size() + __n), __p - this->__begin_, __a);
            __v.__construct_at_end(__n, __x);
            __p = __swap_out_circular_buffer(__v, __p);
        }
    }
    return __make_iter(__p);
}

template <class _Allocator>
template <class _InputIterator>
vector<bool, _Allocator>::insert(const_iterator __position, _InputIterator __first, _InputIterator __last)
{
    difference_type __off = __position - begin();
    iterator __p = __const_iterator_cast(__position);
    iterator __old_end = end();
    for (; size() != capacity() && __first != __last; ++__first)
    {
        ++this->__size_;
        back() = *__first;
    }
    vector __v(__alloc());
    if (__first != __last)    {
        try         {
            __v.assign(__first, __last);
            difference_type __old_size = static_cast<difference_type>(__old_end - begin());
            difference_type __old_p = __p - begin();
            reserve(__recommend(size() + __v.size()));
            __p = begin() + __old_p;
            __old_end = begin() + __old_size;
        }
        catch (...)        {
            erase(__old_end, end());
            throw;
        }
    }
    __p = _VSTD::rotate(__p, __old_end, end());
    insert(__p, __v.begin(), __v.end());
    return begin() + __off;
}

template <class _BidirectionalIterator, class _OutputIterator>
_OutputIterator __copy_backward(_BidirectionalIterator __first, _BidirectionalIterator __last, _OutputIterator __result)
{
    while (__first != __last)
        *--__result = *--__last;
    return __result;
}

template <class _Tp, class _Up>
typename enable_if <is_same<typename remove_const<_Tp>::type, _Up>::value &&
    is_trivially_copy_assignable<_Up>::value, _Up*>::type
__copy_backward(_Tp* __first, _Tp* __last, _Up* __result) {
    const size_t __n = static_cast<size_t>(__last - __first);
    if (__n > 0)
    {
        __result -= __n;
        _VSTD::memmove(__result, __first, __n * sizeof(_Up));
    }
    return __result;
}

template <class _BidirectionalIterator1, class _BidirectionalIterator2>
_BidirectionalIterator2 copy_backward(_BidirectionalIterator1 __first, _BidirectionalIterator1 __last,
              _BidirectionalIterator2 __result)
{
    return _VSTD::__copy_backward(__unwrap_iter(__first),
                                  __unwrap_iter(__last),
                                  __unwrap_iter(__result));
}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::insert(const_iterator __position, size_type __n, const_reference __x)
{
    pointer __p = this->__begin_ + (__position - begin());
    if (__n > 0)
    {
        if (__n <= static_cast<size_type>(this->__end_cap() - this->__end_))
        {
            size_type __old_n = __n;
            pointer __old_last = this->__end_;
            if (__n > static_cast<size_type>(this->__end_ - __p))
            {
                size_type __cx = __n - (this->__end_ - __p);
                __construct_at_end(__cx, __x);
                __n -= __cx;
            }
            if (__n > 0)
            {
                __RAII_IncreaseAnnotator __annotator(*this, __n);
                __move_range(__p, __old_last, __p + __old_n);
                __annotator.__done();
                const_pointer __xr = pointer_traits<const_pointer>::pointer_to(__x);
                if (__p <= __xr && __xr < this->__end_)
                    __xr += __old_n;
                _VSTD::fill_n(__p, __n, *__xr);
            }
        }
        else
        {
            allocator_type& __a = this->__alloc();
            __split_buffer<value_type, allocator_type&> __v(__recommend(size() + __n), __p - this->__begin_, __a);
            __v.__construct_at_end(__n, __x);
            __p = __swap_out_circular_buffer(__v, __p);
        }
    }
    return __make_iter(__p);
}

template <class _Tp, class _Allocator>
template <class _InputIterator>
vector<_Tp, _Allocator>::insert(const_iterator __position, _InputIterator __first, _InputIterator __last) {
    difference_type __off = __position - begin();
    pointer __p = this->__begin_ + __off;
    allocator_type& __a = this->__alloc();
    pointer __old_last = this->__end_;
    for (; this->__end_ != this->__end_cap() && __first != __last; ++__first)
    {
        __RAII_IncreaseAnnotator __annotator(*this);
        __alloc_traits::construct(__a, _VSTD::__to_raw_pointer(this->__end_),
                                  *__first);
        ++this->__end_;
        __annotator.__done();
    }
    __split_buffer<value_type, allocator_type&> __v(__a);
    if (__first != __last)    {
        try        {
            __v.__construct_at_end(__first, __last);
            difference_type __old_size = __old_last - this->__begin_;
            difference_type __old_p = __p - this->__begin_;
            reserve(__recommend(size() + __v.size()));
            __p = this->__begin_ + __old_p;
            __old_last = this->__begin_ + __old_size;
        }
        catch (...)        {
            erase(__make_iter(__old_last), end());
            throw;
        }
    }
    __p = _VSTD::rotate(__p, __old_last, this->__end_);
    insert(__make_iter(__p), make_move_iterator(__v.begin()), make_move_iterator(__v.end()));
    return begin() + __off;
}

typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::erase(const_iterator __position)
{
    _LIBCPP_ASSERT(__position != end(),
        "vector::erase(iterator) called with a non-dereferenceable iterator");
    difference_type __ps = __position - cbegin();
    pointer __p = this->__begin_ + __ps;
    this->__destruct_at_end(_VSTD::move(__p + 1, this->__end_, __p));
    this->__invalidate_iterators_past(__p-1);
    iterator __r = __make_iter(__p);
    return __r;
}

template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::iterator
vector<_Tp, _Allocator>::erase(const_iterator __first, const_iterator __last)
{
    _LIBCPP_ASSERT(__first <= __last, "vector::erase(first, last) called with invalid range");
    pointer __p = this->__begin_ + (__first - begin());
    if (__first != __last) {
        this->__destruct_at_end(_VSTD::move(__p + (__last - __first), this->__end_, __p));
        this->__invalidate_iterators_past(__p - 1);
    }
    iterator __r = __make_iter(__p);
    return __r;
}

__split_buffer<_Tp, _Allocator>::__destruct_at_end(pointer __new_last, false_type) _NOEXCEPT
{
    while (__new_last != __end_)
        __alloc_traits::destroy(__alloc(), __to_raw_pointer(--__end_));
}

template <class _Cp, bool _IsConst>
inline _LIBCPP_INLINE_VISIBILITY
__bit_iterator<_Cp, false>
move(__bit_iterator<_Cp, _IsConst> __first, __bit_iterator<_Cp, _IsConst> __last, __bit_iterator<_Cp, false> __result)
{
    return _VSTD::copy(__first, __last, __result);
}

//------------------------------------------------------------------------------
template<class T, class A>
vvector<T,A>& vvector<T,A>::operator=(const vvector& v) {
    cout << this << " \t\tvvector::operator=(const vvector& v)" << endl;
    if(this==&v) return *this;
 
    if(v.sz<=space) {
        copy(v);
        sz=v.sz;
        return *this;
    }
    T* p = alloc.allocate(v.space);
    for(int i=0; i<v.sz; i++)
        alloc.construct(&p[i],v.elem[i]);
    for(int i=0; i<sz; i++)
        alloc.destroy(&elem[i]);
    alloc.deallocate(elem,space);
    elem = p;
    space = sz = v.sz;
    return *this;
}

template <class _Tp, class _Allocator>
void vector<_Tp, _Allocator>::resize(size_type __sz, const_reference __x) {
    size_type __cs = size();
    if (__cs < __sz)
        this->__append(__sz - __cs, __x);
    else if (__cs > __sz)
        this->__destruct_at_end(this->__begin_ + __sz);
}

template <class _Tp, class _Allocator>
void vector<_Tp, _Allocator>::__append(size_type __n, const_reference __x)
{
    if (static_cast<size_type>(this->__end_cap() - this->__end_) >= __n)
        this->__construct_at_end(__n, __x);
    else
    {
        allocator_type& __a = this->__alloc();
        __split_buffer<value_type, allocator_type&> __v(__recommend(size() + __n), size(), __a);
        __v.__construct_at_end(__n, __x);
        __swap_out_circular_buffer(__v);
    }
}

template <class _Tp, class _Allocator>
void vector<_Tp, _Allocator>::__construct_at_end(size_type __n, const_reference __x)
{
    allocator_type& __a = this->__alloc();
    do     {
        __RAII_IncreaseAnnotator __annotator(*this);
        __alloc_traits::construct(__a, _VSTD::__to_raw_pointer(this->__end_), __x);
        ++this->__end_;
        --__n;
        __annotator.__done();
    } while (__n > 0);
}

template <typename T>
struct Allocator
{
    using value_type = T;

    Allocator() = default;
 
    T* allocate( std::size_t N )
    {
        N *= sizeof( T );
        std::cout << "Allocation " << N << " bytes" << std::endl;
        return static_cast< T* >( ::operator new( N ) );
    }
 
    void deallocate( T *ptr, std::size_t N ) 
    {
        std::cout << "Deallocation " << (N * sizeof * ptr) << " bytes" << std::endl;
        ::operator delete( ptr );
    }
};