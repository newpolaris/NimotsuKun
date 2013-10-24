#include "GameLib/Framework.h"
#include "StageSelect.h"
#include "GameInstance.h"

void StageSelect::input()
{
	auto f = GameLib::Framework::instance();

	int stage = 0;

	if (f.isKeyTriggered('1'))
		stage = 1;
	else if (f.isKeyTriggered('2'))
		stage = 2;
	else if (f.isKeyTriggered('3'))
		stage = 3;
	else if (f.isKeyTriggered('4'))
		stage = 4;
	else if (f.isKeyTriggered('5'))
		stage = 5;
	else if (f.isKeyTriggered('6'))
		stage = 6;
	else if (f.isKeyTriggered('7'))
		stage = 7;
	else if (f.isKeyTriggered('8'))
		stage = 8;
	else if (f.isKeyTriggered('9'))
		stage = 9;

	if (stage != 0) {
		gameInstance().changeStage(stage);
		gameInstance().requestSequence(SEQUENCE_LOAD);
	}

    if (f.isKeyTriggered('q'))
		f.requestEnd();
}

void StageSelect::draw()
{
	auto f = GameLib::Framework::instance();
	int height = f.height();
	int width  = f.width();

	image.draw(0, 0, 0, 0, width, height);
}
