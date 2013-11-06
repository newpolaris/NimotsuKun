#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"

#include "Sequence/SoloGame/Pause.h"
#include "Sequence/SoloGame/Parent.h"
#include "StringRenderer.h"

using namespace GameLib;

namespace Sequence {
namespace SoloGame {

Pause::Pause() : mImage("data/image/dummy.dds") {}

void Pause::update(Parent* parent)
{
    using namespace GameLib;

	mImage.draw();

    StringRenderer::instance().draw("Pause");
    StringRenderer::instance().draw("Please input space key to Play", 0, 1);
    StringRenderer::instance().draw("Please input t key to Title", 0, 2);

    if (Framework::instance().isKeyTriggered(' ')) {
        parent->moveTo(Parent::SEQUENCE_PLAY);
    } else if (Framework::instance().isKeyTriggered('t')) {
        parent->moveTo(Parent::SEQUENCE_TITLE);
    }
}

} // namespace Sequence 
} // namespace SoloGame 

