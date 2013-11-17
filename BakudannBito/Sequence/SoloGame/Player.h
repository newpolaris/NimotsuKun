#pragma once

#include "point.h"

namespace Sequence {
namespace SoloGame {
class State;

class Player
{
public:
    Player(point& position, int BoomRange=1, int BoomCountMax=1)
        : mPosition(position)
        , mBoomRange(BoomRange)
        , mBoomCountMax(BoomCountMax)
        , mBoomCount(0)
        , mStepMax(30) {}

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
    const int mStepMax;

    point mPosition;    // Current player's position in block dim.
    point step;         // Used to sub block precision move.

    int mBoomRange;     // Rear blast height = width = 2*mBoomRange+1
    int mBoomCount;     // # of used boom that not going off.
    int mBoomCountMax;  // # of boom can be installed.
};

} // namespace SoloGame {
} // namespace Sequence {
