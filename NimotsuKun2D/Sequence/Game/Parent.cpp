#include "GameLib/GameLib.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/Game/Loading.h"
#include "Sequence/Game/Clear.h"
#include "Sequence/Game/Menu.h"
#include "Sequence/Game/Play.h"
#include "Sequence/GameInstance.h"
#include "State.h"

namespace Sequence{
namespace Game{

Parent::Parent(int stageID) 
	: mState(0)
    , mStageID(stageID)
	, mPlay(0)
	, mMenu(0)
	, mClear(0) 
    , mLoading(0)
    , mNext(SEQUENCE_NONE)
{
	//?€?ã«??ƒ¼??
    mLoading = new Loading();
}

Parent::~Parent() {
	SAFE_DELETE(mState);
	SAFE_DELETE(mPlay);
	SAFE_DELETE(mMenu);
	SAFE_DELETE(mClear);
	SAFE_DELETE(mLoading);
}

void Parent::update(GrandParent* parent)
{
	if (mPlay)
		mPlay->update(this);
	else if (mMenu)
		mMenu->update(this);
	else if (mClear)
		mClear->update(this);
	else if (mLoading)
        mLoading->update(this);
    else
		HALT("bakana!"); 

    switch (mNext) {
    case SEQUENCE_STAGE_SELECT:
        parent->moveTo(GrandParent::SEQUENCE_STAGE_SELECT); 
        break;
    case SEQUENCE_TITLE:
	    parent->moveTo(GrandParent::SEQUENCE_TITLE); 
        break;
    case SEQUENCE_PLAY:
        SAFE_DELETE(mLoading);
        SAFE_DELETE(mMenu);
        mPlay = new Play();
        break;
    case SEQUENCE_CLEAR:
        SAFE_DELETE(mPlay);
        mClear = new Clear();
        break;
    case SEQUENCE_MENU:
        SAFE_DELETE(mPlay);
        mMenu = new Menu();
        break;
    }
	mNext = SEQUENCE_NONE; 
}

void Parent::startLoading() {
	mState = State::initalizeWithStage(mStageID);
}

void Parent::moveTo(SeqID next) {
	mNext = next;
}

State* Parent::state() {
	return mState;
}

} //namespace Game
} //namespace Sequence
