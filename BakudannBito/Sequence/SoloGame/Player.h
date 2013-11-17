#pragma once

namespace SoloGame {
namespace Sequence {

class Player
{
public:
    Player(point& position, int BoomRange=1, int BoomCountMax=1)
        : mPosition(position)
        , mBoomRange(BoomRange)
        , mBoomCountMax(BoomCountMax)
        , mBoomCount(0)
    {
    }

    void BoomRangeUp()
    {
        mBoomRange++;
    }

    void BoomCountUp()
    {
        mBoomCountMax++;
    }

    void draw()
    {
    }

private:
    point mPosition;    // Current player's position in block dim.

    int mBoomRange;     // Rear blast height = width = 2*mBoomRange+1
    int mBoomCount;     // # of used boom that not going off.
    int mBoomCountMax;  // # of boom can be installed.
};

} // namespace SoloGame {
} // namespace Sequence {
