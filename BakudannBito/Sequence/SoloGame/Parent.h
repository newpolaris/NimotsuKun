#pragma once

#include "Sequence/Game/Parent.h"

namespace Sequence {
class GameInstance;

namespace Game {
class Pause;
class Ready;
};

namespace SoloGame {
class Clear;
class Fail;
class Play;
class State;

class Parent : public Game::Parent
{
public:
    Parent();
	~Parent();
	void draw() const;
	void update(GrandParent*);
	void moveTo(SeqID);

private:
    SeqID mNext;
	State* mState;

    Clear* mClear;
    Fail* mFail;
    Play* mPlay;
    Game::Pause* mPause;
    Game::Ready* mReady;
};

} // namespace SoloGame
} // namespace Sequence
