#include "GameLib/Framework.h"

#include <algorithm>
#include <iterator>
#include "Sequence/SoloGame/Player.h"
#include "Sequence/SoloGame/State.h"
#include "Map.h"

#include <type_traits>

namespace Sequence {
namespace SoloGame {
using std::vector;

Player::Player(int ID, point& position, point blockSize, 
			   int BoomRange, int BoomCountMax)
	: mID(ID)
	, mBoomRange(BoomRange)
	, mBoomCountMax(BoomCountMax)
	, mBoomCount(0)
	, mBlockSize(blockSize) 
{
	setPosition(position);
}

void Player::BoomRangeUp()
{
	mBoomRange++;
}

void Player::BoomCountUp()
{
	mBoomCountMax++;
}

namespace {
vector<bool> isObstacle(const State* const state, vector<point>& nextPositions)
{
	using std::for_each;

	vector<bool> ret;
	for_each(nextPositions.begin(), nextPositions.end(),
		[&](point& i) { ret.push_back(state->isObstacle(i)); });

	return ret;
};
} // namespace {

vector<point> Player::getBoundary(point position) const
{
	vector<point> bound;
	point sz = mBlockSize-point(1,1);
	bound.push_back(position);
	bound.push_back(position+point(sz.x, 0));
	bound.push_back(position+sz);
	bound.push_back(position+point(0, sz.y));

	return bound;
}

void Player::installBoom(State* state)
{
	if (state->installBoom(mID, getPosition(), mBoomRange, 3))
		mBoomCount--;
}

void Player::update(State* state)
{
    // if (!alive)
    //    return;

	movePlayer(state);

	using GameLib::Framework;
	Framework f = Framework::instance();

	if (f.isKeyOn('B')) {
		// 성공할 경우만. 줄인다. (서버 응답 대기필요.. B는 홀딩해야되는데 어렵네)
		installBoom(state);
	}
}

void Player::setPosition(point& position)
{
	mPosition = position*mBlockSize;
}

point Player::getPosition() const
{
	point pt = mPosition + mBlockSize/2;
	return pt / mBlockSize;
}

vector<bool> Player::PathMoveStatus(State const * const state, point prev, point next) const
{
	using std::copy_if;
	using std::for_each;
	using std::transform;
	using std::back_inserter;

	vector<point> playerBoundary = getBoundary(next);
	auto convertToBlock = [&](point i) { return i / mBlockSize; };

	transform(playerBoundary.begin(), playerBoundary.end(),
				playerBoundary.begin(), convertToBlock);

	vector<bool> result = isObstacle(state, playerBoundary);

	point sz = mBlockSize-point(1,1);
	point prevCenter = prev + sz/2;
	point currentBlock = convertToBlock(prevCenter);

	vector<bool> sameAsCurentBlock;
	for (int i = 0; i < playerBoundary.size(); i++)
		sameAsCurentBlock.push_back(playerBoundary[i] == currentBlock);

	vector<bool> resultOr;
	for (int i = 0; i < result.size(); i++)
		resultOr.push_back(result[i] | sameAsCurentBlock[i]);

	return resultOr;
}

bool Player::isPath(State const * const state, point prev, point next) const
{
	vector<bool> result = PathMoveStatus(state, prev, next);

	// 북 동 남 서
	point testIndices[4] = { point(0, 1), point(1, 2), point(2,3), point(3,0) };

	point direction = next - prev;

	bool ret = true;

	if (direction.y < 0) {
		ret &= result[testIndices[0].x];
		ret &= result[testIndices[0].y];
	} else if (direction.y > 0) {
		ret &= result[testIndices[2].x];
		ret &= result[testIndices[2].y];
	}

	if (direction.x > 0) {
		ret &= result[testIndices[1].x];
		ret &= result[testIndices[1].y];
	} else if (direction.x < 0) {
		ret &= result[testIndices[3].x];
		ret &= result[testIndices[3].y];
	}

	return ret;
}

void Player::movePlayer(State* state)
{
	using GameLib::Framework;
	using std::for_each;

	point direction(0, 0);

	Framework f = Framework::instance();

    if (f.isKeyOn('w'))
        direction += point(0,-1);
    else if (f.isKeyOn('s'))
        direction += point(0,+1);
    if (f.isKeyOn('a'))
        direction += point(-1,0);
    else if (f.isKeyOn('d'))
        direction += point(+1,0);

	point newDirection = mPosition+direction;

    // 해당 방향으로 update 가능한지 조사.
    if (isPath(state, mPosition, newDirection))
		mPosition = newDirection;

	// 양쪽 입력 중 하나라도 가능한지 조사 후 move!
	else if (std::abs(direction.x) + std::abs(direction.y) > 1) {
		if (isPath(state, mPosition, mPosition+point(direction.x, 0)))
			mPosition = mPosition + point(direction.x, 0);
		else if (isPath(state, mPosition, mPosition+point(0, direction.y)))
			mPosition = mPosition + point(0, direction.y);
	}

	// 아래 내역 option 으로 분리하려면 구조를 어떻게 잡아야 할까?
	// : if (OPTION == TRUE) ?
	else {
		// 여타 Puzzle 게임과 같은 미끄러지며 보상하는 기능.
		point OneWay = direction;
		if (std::abs(OneWay.y) > 0)
			OneWay.x = 0;

		auto sum = [] (point i) { return i.x + i.y; };
		const point test = point(-1, 1);

		vector<bool> pass = PathMoveStatus(state, mPosition, mPosition+OneWay);

		point testIndices[4] = { point(0, 1), point(3, 2), point(0,3), point(1,2) };
		vector<point> testIndex(&testIndices[0], &testIndices[4]);

		// 동시 입력 가능성 없음. 이동하지 않는 경우는 이미 걸러짐.
		const int index = (direction.y<0)*0 + (direction.y>0)*1 + (direction.x<0)*2 + (direction.x>0)*3;

		const point indexPoint = testIndex[index];
		const point someResult = point(pass[indexPoint.x], pass[indexPoint.y]);
		const int sign = sum(someResult * point(-1, 1));

		mPosition += sign * (index < 2 ? point(1, 0) : point(0, 1));
	}
}

void Player::draw(const State* state)
{
	state->draw(mPosition.x, mPosition.y, Map::MAP_PLAYER, false);
}

} // namespace SoloGame
} // namespace Sequence
