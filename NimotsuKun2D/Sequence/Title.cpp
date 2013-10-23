#include "GameLib/Framework.h"
#include "Title.h"
#include "GameInstance.h"

void Title::input()
{
	if (GameLib::Framework::instance().isKeyTriggered(' '))
		gameInstance().requestSequence(SEQUENCE_GAME);
}

void Title::draw()
{
	auto f = GameLib::Framework::instance();
	int height = f.height();
	int width  = f.width();

	titleImage.draw(0, 0, 0, 0, width, height);
}