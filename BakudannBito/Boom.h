#pragma once

#include "point.h"
#include "Sequence\IState.h"

namespace Sequence {
namespace SoloGame {
	class State;
}
}

namespace Map {
using Sequence::IMapObjectRequest;

class IMapObject
{
	// 플레이어가 해당 Object가 존재하는 칸에 갈 수 있나?
	virtual bool isBlock() const = 0;
	virtual point pos() const = 0;
	virtual void draw(const IMapObjectRequest* const mapRequest) const = 0;
	virtual void update(Sequence::SoloGame::State* state) = 0;
};
} // namespace Map {

namespace Map {

using Sequence::SoloGame::State;

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
	void draw(const IMapObjectRequest* const mapRequest) const;
	void update(State* state);

	int mDDAY;			// 터지는 시간.
	int mOwner;			// Player ID 소멸시 ID의 폭탄을 돌려줘야한다.
	int mRange;			// 화염 크기.
	point mPosition;	// 위치
	BoomStatus mStatus;
};

} // namespace Map {
