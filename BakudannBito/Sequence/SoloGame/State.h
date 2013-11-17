#pragma once

#include "file.h"
#include "point.h"
#include "image.h"
#include "Array2D.h"

namespace Sequence {
namespace SoloGame {

class Parent;
class Player;

class State
{
public:
    enum MAP_INFO {
        MAP_NONE,
        MAP_BLOCK,
        MAP_BOX,
        MAP_PLAYER,
        MAP_MONSTER,
        MAP_BOOM,
        MAP_BOOM_ADD,
        MAP_BOOM_RANGE_UP,
    };

	static State* initalizeWithStage(int stage);
	~State();
    void draw() const;
    void draw(int x, int y, MAP_INFO type) const;
    void update(Parent* parent);

private:
	static point findOutMapSize(buffer_type& buffer);

	State(buffer_type& stageData, int sx, int sy);

public:
    const int mSrcW;
    const int mSrcH;

private:
    int mX;
    int mY;
	Image mImage;
    Array2D<MAP_INFO> map;

	Player* mPlayer;
};

} // namespace SoloGame
} // namespace Sequence
