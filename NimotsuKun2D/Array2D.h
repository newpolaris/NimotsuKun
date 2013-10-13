#pragma once

#include <vector>
#include "point.h"

template <typename T>
class Array2D
{
public:
    typedef T value_type; 
    const unsigned size_x;
    const unsigned size_y;

private:
    std::vector<T> map; 

public:
    Array2D(unsigned x, unsigned y) 
        : size_x(x)
        , size_y(y)
        , map(x*y)
    {}

    unsigned size() const { return map.size(); }

    T& operator[](int idx)
    {
        return map[idx];
    }

	const T& operator()(int x, int y) const
	{
		return map[y*size_x+x];
	}

	T& operator()(int x, int y) 
	{
		return map[y*size_x+x];
	}

	T& operator()(const point& po) 
	{
		return operator()(po.x, po.y);
	}

	const T& operator()(const point& po) const
	{
		return operator()(po.x, po.y);
	}
};
