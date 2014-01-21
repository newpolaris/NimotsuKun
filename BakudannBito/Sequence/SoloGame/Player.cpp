#include "GameLib/Framework.h"

#include "Sequence/SoloGame/Player.h"
#include "Sequence/SoloGame/State.h"

namespace Sequence {
namespace SoloGame {

void Player::update(State* state)
{
	using GameLib::Framework;

    // if (!alive)
    //    return;

    point direction(0,0);

	Framework f = Framework::instance();

    if (f.isKeyOn('w'))
        direction += point(0,-1);
    else if (f.isKeyOn('s'))
        direction += point(0,+1);
    if (f.isKeyOn('a'))
        direction += point(-1,0);
    else if (f.isKeyOn('d'))
        direction += point(+1,0);

	std::vector<point> bounds = getBound(mPosition+direction);

    // 해당 방향으로 update 가능한지 조사.
    if (state->isPossibleToMove(bounds))
		mPosition += direction;
}

void Player::draw(const State* state)
{
    state->draw(mPosition.x, mPosition.y, State::MAP_PLAYER);
}

} // namespace SoloGame
} // namespace Sequence
