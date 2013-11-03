#include "GameLib/Framework.h"
#include "Loading.h"
#include "GameInstance.h"
#include "Sequence/Game.h"

Loading::Loading()
	: image("data/image/loading.dds")
{
	m_startTime = GameLib::Framework::instance().time();
}

void Loading::input()
{
    static const unsigned expected_elapse_time = 1000;

    if (!gameInstance().GameObj()) {
		gameInstance().initGameObj();
    }

	if (GameLib::Framework::instance().time()-m_startTime >= expected_elapse_time)
		gameInstance().requestSequence(SEQUENCE_GAME);

	auto f = GameLib::Framework::instance();
    if (f.isKeyTriggered('q'))
		f.requestEnd();
}

void Loading::draw()
{
	auto f = GameLib::Framework::instance();
	int height = f.height();
	int width  = f.width();

	image.draw(0, 0, 0, 0, width, height);
}
