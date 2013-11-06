#include "GameLib/Framework.h"

#include "StringRenderer.h"
#include "Sequence/GameInstance.h"
#include "Sequence/Ending.h"

namespace Sequence {

Ending::Ending() : mImage("data/image/dummy.dds") 
{
}

void Ending::update(GameInstance* parent)
{
    using namespace GameLib;

	mImage.draw();

    StringRenderer::instance().draw("Ending");
    StringRenderer::instance().draw("Please input space key go to Title", 0, 1);

    if (Framework::instance().isKeyTriggered(' '))
        parent->moveTo(GameInstance::SEQUENCE_TITLE);
}

} //namespace Sequence