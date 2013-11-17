#include "GameLib/GameLib.h"

#include "Sequence/GameInstance.h"
#include "Sequence/SoloGame/Parent.h"
#include "Sequence/SoloGame/Fail.h"
#include "Sequence/SoloGame/Clear.h"
#include "Sequence/SoloGame/Play.h"
#include "Sequence/SoloGame/State.h"
#include "Sequence/Game/Pause.h"
#include "Sequence/Game/Ready.h"

namespace Sequence {
namespace SoloGame {

Parent::Parent() 
    : mNext(SEQUENCE_NONE) 
    , mClear(0)
    , mFail(0)
    , mPause(0)
    , mPlay(0)
	, mState(State::initalizeWithStage(1))
    , mReady(new Game::Ready()) {}

Parent::~Parent()
{
	SAFE_DELETE(mState);
    SAFE_DELETE(mClear);
    SAFE_DELETE(mFail);
    SAFE_DELETE(mPause);
    SAFE_DELETE(mPlay);
    SAFE_DELETE(mReady);
}

void Parent::draw() const
{
	mState->draw();
}

void Parent::moveTo(Parent::SeqID next)
{
    mNext = next;
}

void Parent::update()
{
	mState->update(this);
}

void Parent::update(GrandParent* parent)
{
    if (mClear)
        mClear->update(this);
    else if (mFail)
        mFail->update(this);
    else if (mPause)
        mPause->update(this);
    else if (mPlay)
        mPlay->update(this);
    else if (mReady)
        mReady->update(this);

    switch (mNext) {
    case SEQUENCE_CLEAR:
        SAFE_DELETE(mPlay);
        mClear = new Clear();
        break;
    case SEQUENCE_FAIL:
        SAFE_DELETE(mPlay);
        mFail = new Fail();
        break;
    case SEQUENCE_PAUSE:
        SAFE_DELETE(mPlay);
        mPause = new Game::Pause();
        break;
    case SEQUENCE_PLAY:
        SAFE_DELETE(mReady);
        SAFE_DELETE(mPause);
        mPlay = new Play();
        break;
    case SEQUENCE_READY:
        SAFE_DELETE(mClear);
        SAFE_DELETE(mFail);
        mReady = new Game::Ready(); 
        break;
    case SEQUENCE_ENDING:
        SAFE_DELETE(mClear);
        parent->moveTo(GrandParent::SEQUENCE_ENDING);
        break;
    case SEQUENCE_GAMEOVER:
        SAFE_DELETE(mFail);
        parent->moveTo(GrandParent::SEQUENCE_GAMEOVER);
        break;
    case SEQUENCE_TITLE:
        SAFE_DELETE(mPause);
        parent->moveTo(GrandParent::SEQUENCE_TITLE);
        break;
    default:
        break;
    }

    mNext = SEQUENCE_NONE;
}

} // namespace SoloGame
} // namespace Sequence
