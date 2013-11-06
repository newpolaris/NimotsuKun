#pragma once

namespace Sequence {
class GameInstance;

namespace DuoGame {
class Pause;
class Play;
class Ready;
class DisplayResult;

class Parent
{
public:
    typedef Sequence::GameInstance GrandParent;
    enum SeqID {
        SEQUENCE_PAUSE,
        SEQUENCE_PLAY,
        SEQUENCE_READY,
        SEQUENCE_DISPLAYRESULT,

        SEQUENCE_TITLE,
        SEQUENCE_NONE
    };

    Parent();
	~Parent();
	void update(GrandParent*);
	void moveTo(SeqID);

private:
    SeqID mNext;

    Pause* mPause;
    Play* mPlay;
    Ready* mReady;
    DisplayResult* mDisplayResult;
};

} // namespace DuoGame
} // namespace Sequence

