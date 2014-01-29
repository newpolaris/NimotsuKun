#pragma once

#include <algorithm>
#include <vector>
#include <iostream>

#include "point.h"

namespace Sequence {
namespace SoloGame {
class State;
using std::vector;

// TODO: position, blockSize, range, boom 모조리 제거 
// 는 Local client GUI 측면에서 불가능. 다만 그걸 자발적으로 할건지
// 어디까지 server 측 callback을 기다릴 것인지는 선택 필요.
class Player
{
public:
	Player(int ID, point& position, point blockSize, int BoomRange=1, int BoomCountMax=1);

	void killed(int type);
	vector<point> getBoundary(point position) const;
    void update(State* state);
	void installBoom(State* state);
	bool isPath(State const * const, point prev, point next) const;
	vector<bool> PathMoveStatus(State const * const state, point prev, point next) const;
	void setPosition(point& position);
	point getPosition() const;
	
    void BoomRangeUp();
    void BoomCountUp();
	void draw(const State* state);

private:
	void movePlayer(State* state);

private:
    point mPosition;    // Current player's top-left position in pixel.
	point mBlockSize;	// Block size in pixel.

	int mID;
    int mBoomRange;     // Rear blast height = width = 2*mBoomRange+1
    int mBoomCount;     // # of used boom that not going off.
    int mBoomCountMax;  // # of boom can be installed.
};

} // namespace SoloGame {
} // namespace Sequence {
