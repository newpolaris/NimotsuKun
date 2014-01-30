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
	// �÷��̾ �ش� Object�� �����ϴ� ĭ�� �� �� �ֳ�?
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

	int mDDAY;			// ������ �ð�.
	int mOwner;			// Player ID �Ҹ�� ID�� ��ź�� ��������Ѵ�.
	int mRange;			// ȭ�� ũ��.
	point mPosition;	// ��ġ
	BoomStatus mStatus;
};

} // namespace Map {
