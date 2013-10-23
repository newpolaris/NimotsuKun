#include "GameInstance.h"
#include "Sequence\Title.h"
#include "Sequence\Game.h"
#include "GameLib/Framework.h"

namespace GameLib {
    void Framework::update() {
		gameInstance().update();
    }
}

GameInstance& gameInstance()
{
	static GameInstance inst;
	return inst;
}

void GameInstance::update() 
{
	switch (mSequence)
	{
	case SEQUENCE_TITLE:
		title_->update();
		break;
	case SEQUENCE_GAME:
		game_->update();
		break;
	}

	if (mReqSequence != mSequence)
		changeSequence();
}

void GameInstance::requestSequence(Sequence seq)
{
	mReqSequence = seq;
}

void GameInstance::clearScreen()
{
    unsigned* vram = GameLib::Framework::instance().videoMemory();
    unsigned windowWidth  = GameLib::Framework::instance().width();
	unsigned windowHeight = GameLib::Framework::instance().height();

    for (int y=0; y < windowHeight; ++y)
    for (int x=0; x < windowWidth;  ++x)
	{
		vram[y*windowWidth+x] = 0;
	}
}

void GameInstance::changeSequence()
{
	mSequence = mReqSequence;

	switch (mReqSequence)
	{
	case SEQUENCE_GAME:
		clearScreen();
		game_.reset(Game::initalize_Game());
	}
}

GameInstance::GameInstance() 
	: mSequence(SEQUENCE_TITLE)
	, gameStage(0)
	, title_(new Title()) {}

