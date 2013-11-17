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

    // 해당 방향으로 update 가능한지 조사.
    // if (state->isPossibleToMove(mPosition, direction)) {
    if (true) {
		const int stepMax = mStepMax;
        const int stepHalf = mStepMax/2;

        // step update 구문.
        step += direction;

        // pos update 루틴.
		auto posUpdate = [stepHalf, stepMax](int& Pos, int& step) {
			if (step > stepHalf-1) {
				Pos++;
				step -= stepMax;
			} else if (step < -stepHalf) {
				Pos--;
				step += stepMax;
			}
		};

		posUpdate(mPosition.x, step.x);
		posUpdate(mPosition.y, step.y);
    }
}

void Player::draw(const State* state)
{
    point blockSize = point(state->mSrcW, state->mSrcH);
    point pos = mPosition * blockSize;
    pos += step*blockSize/point(mStepMax, mStepMax);

    state->draw(pos.x, pos.y, State::MAP_PLAYER);
}

} // namespace SoloGame
} // namespace Sequence
