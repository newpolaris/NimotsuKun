#include "GameLib/Framework.h"
#include "GameInstance.h"
#include "Menu.h"
#include "Sequence/Game.h"

void Menu::input()
{
	auto f = GameLib::Framework::instance();

	if (f.isKeyOn('2'))
		gameInstance().requestSequence(SEQUENCE_STAGE_SELECT);
    else if (f.isKeyOn('3'))
		gameInstance().requestSequence(SEQUENCE_TITLE);
    else if (f.isKeyOn('4'))
		gameInstance().requestSequence(SEQUENCE_GAME);
    else if (f.isKeyOn('q'))
		f.requestEnd();
    else if (f.isKeyTriggered('1'))
	{
		gameInstance().reinit();
		gameInstance().requestSequence(SEQUENCE_GAME);
	}
}

void Menu::draw()
{
	auto f = GameLib::Framework::instance();

    gameInstance().GameObj()->draw();
	gameInstance().drawBlackPanel();

	int height = f.height();
	int width  = f.width();

	titleImage.draw(0, 0, 0, 0, width, height);
}
