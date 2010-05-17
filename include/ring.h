#ifndef RING_H
#define RING_H

#include <cstddef>
#include <algorithm>

template<typename T>
class Ring
{
public:
	typedef T              value_type;
    typedef T&             reference;
    typedef const T&       const_reference;
    typedef std::size_t    size_type;
    typedef std::ptrdiff_t difference_type;
		
	Ring( size_type n)
	{
		N = n;
		fence = 0;
		sz = 0;
		elems = new T[N];
	};
	
	inline ~Ring()
	{
		delete[] elems;
	};
	
	void push_back(const T& x)
	{
		sz = (sz < N) ? sz+1 : N;
	
		elems[ fence ] = x;
		
		fence = (fence == (N-1)) ? 0 : fence + 1;
	};
	
	reference operator[]( size_type i )
	{
		return elems[ (sz<N) ? i : ((fence+i)<N) ? fence+i : i-N+fence ];
	};
	
	
	inline size_type size()const { return sz; };
	inline size_type max_size()const { return N; };

protected:
	T 		*elems;

	size_type	N;	//Max size of container
	size_type	fence;  
	size_type	sz;	//count of elements in container
};

#endif
