#pragma once

namespace Sequence {
class GameInstance;

namespace Game {

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
        SEQUENCE_DISPLAYRESULT,

        SEQUENCE_ENDING,
        SEQUENCE_GAMEOVER,
        SEQUENCE_TITLE,
        SEQUENCE_NONE
    };

	virtual void moveTo(SeqID)=0;
	virtual void update(GrandParent*)=0;
	virtual void draw() const=0;
};

} // namespace Game
} // namespace Sequence

