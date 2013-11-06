#include "GameLib/GameLib.h"
#include "Sequence/GameInstance.h"
#include "Sequence/DuoGame/Parent.h"

#include "Sequence/Game/Ready.h"
#include "Sequence/Game/Pause.h"
#include "Sequence/DuoGame/Play.h"
#include "Sequence/DuoGame/DisplayResult.h"

namespace Sequence {
namespace DuoGame {

Parent::Parent() 
    : mNext(SEQUENCE_NONE) 
    , mPause(0)
    , mPlay(0)
    , mReady(new Game::Ready())
    , mDisplayResult(0) {}

Parent::~Parent()
{
    SAFE_DELETE(mPause);
    SAFE_DELETE(mPlay);
    SAFE_DELETE(mReady);
    SAFE_DELETE(mDisplayResult);
}

void Parent::moveTo(SeqID next)
{
    mNext = next;
}

void Parent::update(GrandParent* parent)
{
    if (mPause)
        mPause->update(this);
    else if (mPlay)
        mPlay->update(this);
    else if (mReady)
        mReady->update(this);
    else if (mDisplayResult)
        mDisplayResult->update(this);

    switch (mNext) {
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
        SAFE_DELETE(mDisplayResult);
        mReady = new Game::Ready(); 
        break;
    case SEQUENCE_DISPLAYRESULT:
        SAFE_DELETE(mPlay);
        mDisplayResult = new DisplayResult();
        break;
    case SEQUENCE_TITLE:
        SAFE_DELETE(mPause);
        SAFE_DELETE(mDisplayResult);
        parent->moveTo(GrandParent::SEQUENCE_TITLE);
        break;
    default:
        break;
    }

    mNext = SEQUENCE_NONE;
}

} // namespace DuoGame
} // namespace Sequence

