#pragma once

namespace Sequence{

class Title;
class StageSelect;

namespace Game {
	class Parent;
}

class GameInstance
{
public:
	enum SeqID{
		SEQUENCE_STAGE_SELECT,
		SEQUENCE_TITLE,
		SEQUENCE_GAME,
		SEQUENCE_NONE,
	};

	GameInstance();
	~GameInstance();
	void update();

	void moveTo( SeqID );
	void setStageID( int stageID );

private:
	StageSelect* mStageSelect;
	Title* mTitle;
    Game::Parent* mGame;

	SeqID mNext;
    int mStageID;
};

} //namespace Sequence
