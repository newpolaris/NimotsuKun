#pragma once

#include "Sequence/Game/Parent.h"

namespace Sequence {
class GameInstance;

namespace Game {
class Pause;
class Ready;
}

namespace DuoGame {
class Play;
class DisplayResult;

class Parent : public Game::Parent
{
public:
    Parent();
	~Parent();
	void update(GrandParent*);
	void moveTo(SeqID);

private:
    SeqID mNext;

    Game::Pause* mPause;
    Game::Ready* mReady;
    Play* mPlay;
    DisplayResult* mDisplayResult;
};

} // namespace DuoGame
} // namespace Sequence

