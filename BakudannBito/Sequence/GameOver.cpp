#include "GameLib/Framework.h"

#include "StringRenderer.h"
#include "Sequence/GameInstance.h"
#include "Sequence/GameOver.h"

namespace Sequence {

GameOver::GameOver() : mImage("data/image/dummy.dds") 
{
}

void GameOver::update(GameInstance* parent)
{
    using namespace GameLib;

	mImage.draw();

    StringRenderer::instance().draw("Game Over");
    StringRenderer::instance().draw("Please input space key go to Title", 0, 1);

    if (Framework::instance().isKeyTriggered(' '))
        parent->moveTo(GameInstance::SEQUENCE_TITLE);
}

} // namespace Sequence