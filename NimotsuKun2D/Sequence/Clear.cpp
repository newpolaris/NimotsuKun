#include "GameLib/Framework.h"
#include "Clear.h"
#include "GameInstance.h"
#include "Sequence\Game.h"

Clear::Clear() : image("data/image/clear.dds")
{
	m_startTime = GameLib::Framework::instance().time();
}

void Clear::input()
{
    static const unsigned expected_elapse_time = 1000;

	if (GameLib::Framework::instance().time()-m_startTime > expected_elapse_time)
		gameInstance().requestSequence(SEQUENCE_STAGE_SELECT);

	auto f = GameLib::Framework::instance();
    if (f.isKeyTriggered('q'))
		f.requestEnd();
}

void Clear::draw()
{
    gameInstance().GameObj()->draw();
	gameInstance().drawBlackPanel();

	auto f = GameLib::Framework::instance();
	int height = f.height();
	int width  = f.width();

	image.draw(0, 0, 0, 0, width, height);
}

