#pragma once

#include <algorithm>
#include <vector>
#include <iostream>

#include "point.h"

namespace Sequence {
namespace SoloGame {
class State;

class Player
{
public:
    Player(point& position, point blockSize, point playerSize, 
		   int BoomRange=1, int BoomCountMax=1)
		: mBoomRange(BoomRange)
        , mBoomCountMax(BoomCountMax)
        , mBoomCount(0)
		, mPlayerSize(playerSize)
        , mBlockSize(blockSize) 
	{
		setPosition(position);
	}

	void setPosition(point& position)
	{
		mPosition = position*mBlockSize;
		mPosition += (mBlockSize-mPlayerSize)/2;
	}

	point getPosition() const
	{
		return mPosition / mBlockSize;
	}
	
	std::vector<point> getBound(point position) const
	{
		point sz = mPlayerSize-point(1,1);
		std::vector<point> bound;
		bound.push_back(position);
		bound.push_back(position+point(sz.x, 0));
		bound.push_back(position+point(0, sz.y));
		bound.push_back(position+sz);

#if _DEBUG
		std::for_each(bound.begin(), bound.end(), 
			[&](point& i){ std::cout << i.x << " " << i.y << std::endl; });
#endif
		std::for_each(bound.begin(), bound.end(), [&](point& i){ i /= mBlockSize; });

#if _DEBUG
		std::for_each(bound.begin(), bound.end(), 
			[&](point& i){ std::cout << i.x << " " << i.y << std::endl; });
#endif
		return bound;
	}

    void update(State* state);

    void BoomRangeUp()
    {
        mBoomRange++;
    }

    void BoomCountUp()
    {
        mBoomCountMax++;
    }

	void draw(const State* state);

private:
    point mPosition;    // Current player's top-left position in pixel.
	point mBlockSize;	// Block size in pixel.
	point mPlayerSize;	// Block size in pixel.

    int mBoomRange;     // Rear blast height = width = 2*mBoomRange+1
    int mBoomCount;     // # of used boom that not going off.
    int mBoomCountMax;  // # of boom can be installed.
};

} // namespace SoloGame {
} // namespace Sequence {
