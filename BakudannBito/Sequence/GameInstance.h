#pragma once

namespace Sequence {

class Title;
class Ending;
class GameOver;

namespace SoloGame {
	class Parent;
}
namespace DuoGame {
	class Parent;
}

class GameInstance
{
public:
	enum SeqID {
		SEQUENCE_TITLE,
        SEQUENCE_ENDING,
        SEQUENCE_GAMEOVER,
        SEQUENCE_SOLOGAME,
        SEQUENCE_DUOGAME,
		SEQUENCE_NONE,
	};

	GameInstance();
	~GameInstance();
	void update();

	void moveTo( SeqID );
	void setStageID( int stageID );

private:
	Title* mTitle;
    Ending* mEnding;
    GameOver* mGameOver;
    SoloGame::Parent* mSoloGame;
    DuoGame::Parent* mDuoGame;

	SeqID mNext;
    int mStageID;
};

} //namespace Sequence
