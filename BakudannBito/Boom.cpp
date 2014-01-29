#include "Boom.h"

#include "Map.h"
#include "Sequence\SoloGame\State.h"

namespace Map {

Boom::Boom(int time, int owner, point position, int range)
	: mDDAY(time), mOwner(owner), mPosition(position), mRange(range) {}

bool Boom::isBlock() const {
	return mStatus != BoomExplosion;
}

point Boom::pos() const {
	return mPosition;
}

void Boom::draw(const State* const state) const {
	state->draw(mPosition.x, mPosition.y, MAP_INFO::MAP_BOOM, true);
}

void Boom::update(Sequence::SoloGame::State* state) {

}

} // namespace Map {