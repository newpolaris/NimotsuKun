#include "GameInstance.h"
#include "Sequence/Title.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/StageSelect.h"
#include "Sequence/Game/Clear.h"
#include "Sequence/Game/Menu.h"
#include "Sequence/Loading.h"
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

bool GameInstance::initGameObj()
{
	game_.reset(Game::initalizeWithStage(m_stage));
	return true;
}

void GameInstance::reset()
{
	game_->reset(); 
}

void GameInstance::update() 
{
	sequence_->update();

	if (mReqSequence != mSequence)
		changeSequence();
}

void GameInstance::requestSequence(SequenceType seq)
{
	mReqSequence = seq;
}

void GameInstance::clearScreen()
{
    unsigned* vram = GameLib::Framework::instance().videoMemory();
    unsigned windowWidth  = GameLib::Framework::instance().width();
	unsigned windowHeight = GameLib::Framework::instance().height();

    for (unsigned y=0; y < windowHeight; ++y)
    for (unsigned x=0; x < windowWidth;  ++x)
	{
		vram[y*windowWidth+x] = 0;
	}
}

void GameInstance::drawBlackPanel()
{
    unsigned* vram = GameLib::Framework::instance().videoMemory();
    unsigned windowWidth  = GameLib::Framework::instance().width();
    unsigned windowHeight = GameLib::Framework::instance().height();

    for (unsigned y=0; y < windowHeight; ++y)
    for (unsigned x=0; x < windowWidth;  ++x)
	{
		size_t dst_pos = y*windowWidth+x;
		unsigned dst = vram[dst_pos];

		unsigned dr = dst & 0x00ff0000;
		unsigned dg = dst & 0x0000ff00;
		unsigned db = dst & 0x000000ff;

		dr /= 2;
		dg /= 2;
		db /= 2;

		vram[dst_pos] = 0xff<<24|(dr&0xff0000)|(dg&0x00ff00)|db;
	}
}

void GameInstance::changeSequence()
{
    clearScreen();

	mSequence = mReqSequence;

	switch (mReqSequence)
	{
	case SEQUENCE_STAGE_SELECT:
		game_.reset();
		sequence_.reset(new StageSelect());
		break;

	case SEQUENCE_LOAD:
		game_.reset();
		sequence_.reset(new Loading());
		break;

	case SEQUENCE_GAME:
		sequence_ = game_;
		break;
	case SEQUENCE_CLEAR:
		sequence_.reset(new Clear());
		break;

	case SEQUENCE_MENU:
		sequence_.reset(new Menu());
		break;
	case SEQUENCE_TITLE:
		game_.reset();
		sequence_.reset(new Title());
		break;
	}
}

GameInstance::GameInstance() 
	: mSequence(SEQUENCE_TITLE)
	, m_stage(0)
	, sequence_(new Title()) {}

