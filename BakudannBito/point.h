#pragma once

struct point
{
	point() : x(0), y(0) {}
	point(int _x, int _y) : x(_x), y(_y) {}
	point operator+(const point& po) const
	{
		return point(po.x+x, po.y+y);
	}

    point operator*(const point& po) const
    {
        return point(po.x*x, po.y*y);
    }

    point operator/(const point& po) const
    {
        return point(x/po.x, y/po.y);
    }

	bool operator==(const point& po)
	{
		return x == po.x && y == po.y;
	}

    point& operator+=(const point& po)
    {
        x += po.x;
        y += po.y;

		return *this;
    }
    
	int x;
	int y;
};

