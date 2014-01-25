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
    Player(point& position, point blockSize, 
		   int BoomRange=1, int BoomCountMax=1)
		: mBoomRange(BoomRange)
        , mBoomCountMax(BoomCountMax)
        , mBoomCount(0)
        , mBlockSize(blockSize) 
	{
		setPosition(position);
	}

	void setPosition(point& position)
	{
		mPosition = position*mBlockSize;
	}

	point getPosition() const
	{
		return mPosition / mBlockSize;
	}
	
	std::vector<point> getBound(point position) const
	{
		point sz = mBlockSize-point(1,1);
		std::vector<point> bound;
		bound.push_back(position);
		bound.push_back(position+point(sz.x, 0));
		bound.push_back(position+sz);
		bound.push_back(position+point(0, sz.y));

		std::for_each(bound.begin(), bound.end(), [&](point& i){ i /= mBlockSize; });

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

    int mBoomRange;     // Rear blast height = width = 2*mBoomRange+1
    int mBoomCount;     // # of used boom that not going off.
    int mBoomCountMax;  // # of boom can be installed.
};

} // namespace SoloGame {
} // namespace Sequence {
