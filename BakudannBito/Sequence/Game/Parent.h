#pragma once

class State;

namespace Sequence {
class GameInstance;

namespace Game {

class Play;
class Menu;
class Clear;
class Loading;

class Parent 
{
public:
	typedef Sequence::GameInstance GrandParent; //祖父

	enum SeqID {
		SEQUENCE_STAGE_SELECT, //上階�?
		SEQUENCE_TITLE, //上階�?
		SEQUENCE_MENU,
		SEQUENCE_CLEAR,
		SEQUENCE_PLAY,
		SEQUENCE_NONE
	};

	Parent(int stageID);
	~Parent();

	void moveTo(SeqID);
	void update(GrandParent*);
    void startLoading();
    State* state();

private:
	int mStageID;
	State* mState;
    SeqID mNext;

	Play* mPlay;
	Menu* mMenu;
	Clear* mClear;
    Loading* mLoading;
};

} // namespace Game
} // namespace Sequence

