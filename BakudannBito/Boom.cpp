#include "Boom.h"

#include "Map.h"
#include "time.h"
#include "Sequence\SoloGame\State.h"

namespace Map {

Boom::Boom(int time, int owner, point position, int range) : 
	mDDAY(time),
	mOwner(owner),
	mPosition(position), 
	mRange(range),
	mStatus(BoomWait)
{
}

bool Boom::isBlock() const {
	return mStatus != BoomExplosion;
}

point Boom::pos() const {
	return mPosition;
}

void Boom::draw(const IMapObjectRequest* const mapRequest) const {
	if (mStatus == BoomWait) {
		mapRequest->draw(mPosition.x, mPosition.y, MAP_BOOM, true);
	} else if (mStatus == BoomExplosion) {
		mapRequest->draw(mPosition.x, mPosition.y, MAP_BOOM_BLAST_CENTER, true);
	}
}

void Boom::update(Sequence::SoloGame::State* state) {
	int currentTime = theTime.getCurrentTime();
	int afterTime = currentTime - mDDAY;

	if (afterTime >= 1000) {
		mStatus = BoomEnd;
		// state->boomRemove();
	} else if (afterTime >= 0) {
		mStatus = BoomExplosion;
		// ¾Ë¸®°í (¿¬¼â Æø¹ß ¼öÇà)
		// state->boomExplosion();
		// Æø¹ß ¹üÀ§ Á¤º¸ °¡Á®¿È.
		// state->getBoomBlastInfo()
	}
}

} // namespace Map {