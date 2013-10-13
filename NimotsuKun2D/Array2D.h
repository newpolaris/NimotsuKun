#pragma once

#include <vector>
#include "map_info.h"

class Array2D
{
private:
    const unsigned size_x;
    const unsigned size_y;
    std::vector<map_info> map; 

public:
    Array2D(unsigned x, unsigned y) 
        : size_x(x)
        , size_y(y)
        , map(x*y)
    {}

    unsigned size() const { return map.size(); }

    map_info& operator[](int idx)
    {
        return map[idx];
    }

	const map_info& operator()(int x, int y) const
	{
		return map[y*size_x+x];
	}

	map_info& operator()(int x, int y) 
	{
		return map[y*size_x+x];
	}

	map_info& operator()(const point& po) 
	{
		return operator()(po.x, po.y);
	}

	const map_info& operator()(const point& po) const
	{
		return operator()(po.x, po.y);
	}

};
