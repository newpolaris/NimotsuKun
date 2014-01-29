#pragma once

struct point
{
	int* begin() { return &x; }
	int* end() { return begin()+2; }

	point() : x(0), y(0) {}
	point(int _x, int _y) : x(_x), y(_y) {}
	point(int _v) : x(_v), y(_v) {}

    point operator*(const point& po) const
    {
        return point(po.x*x, po.y*y);
    }

    point operator/(const point& po) const
    {
        return point(x/po.x, y/po.y);
    }

	point operator+(const point& po) const
	{
		return point(po.x+x, po.y+y);
	}

    point operator-(const point& po) const
    {
        return point(x-po.x, y-po.y);
    }

	bool operator==(const point& po)
	{
		return x == po.x && y == po.y;
	}

    point& operator*=(const point& po)
    {
        x *= po.x;
        y *= po.y;

		return *this;
    }

    point& operator/=(const point& po)
    {
        x /= po.x;
        y /= po.y;

		return *this;
    }

    point& operator+=(const point& po)
    {
        x += po.x;
        y += po.y;

		return *this;
    }
	
	bool operator!=(const point& po)
	{
		return po.x == x && po.y == y;
	}
    
	int x;
	int y;
};

template <typename T>
point operator* (T i, const point& p)
{
	return point(i) * p;
}