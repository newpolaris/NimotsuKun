#pragma once

#include <algorithm>
#include <vector>
#include <iostream>

#include "point.h"

namespace Sequence {
namespace SoloGame {
class State;
using std::vector;

// TODO: position, blockSize, range, boom ������ ���� 
// �� Local client GUI ���鿡�� �Ұ���. �ٸ� �װ� �ڹ������� �Ұ���
// ������ server �� callback�� ��ٸ� �������� ���� �ʿ�.
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
