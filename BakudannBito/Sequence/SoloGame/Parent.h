#pragma once

namespace Sequence {
class GameInstance;

namespace SoloGame {
class Clear;
class Fail;
class Pause;
class Play;
class Ready;

class Parent
{
public:
    typedef Sequence::GameInstance GrandParent;
    enum SeqID {
        SEQUENCE_CLEAR,
        SEQUENCE_FAIL,
        SEQUENCE_PAUSE,
        SEQUENCE_PLAY,
        SEQUENCE_READY,

        SEQUENCE_ENDING,
        SEQUENCE_GAMEOVER,
        SEQUENCE_TITLE,
        SEQUENCE_NONE
    };

    Parent();
	~Parent();
	void update(GrandParent*);
	void moveTo(SeqID);

private:
    SeqID mNext;

    Clear* mClear;
    Fail* mFail;
    Pause* mPause;
    Play* mPlay;
    Ready* mReady;
};

} // namespace SoloGame

} // namespace Sequence
