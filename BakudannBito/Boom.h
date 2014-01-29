#pragma once

#include "point.h"

namespace Sequence {
namespace SoloGame {
	class State;
}
}

namespace Map {

using Sequence::SoloGame::State;

#define Interface class
Interface IMapObject
{
	// 플레이어가 해당 Object가 존재하는 칸에 갈 수 있나?
	virtual bool isBlock() const = 0;
	virtual point pos() const = 0;
	virtual void draw(const State* const state) const = 0;
	virtual void update(State* state) = 0;
};

enum BoomStatus
{
	BoomWait = 0,
	BoomExplosion,
	BoomEnd
};

struct Boom : public IMapObject
{
	Boom(int time, int owner, point position, int rage);

	bool isBlock() const;
	point pos() const;
	void draw(const State* const state) const;
	void update(State* state);

	int mDDAY;	
	int mOwner;
	point mPosition;
	int mRange;
	BoomStatus mStatus;
};

} // namespace Map {
