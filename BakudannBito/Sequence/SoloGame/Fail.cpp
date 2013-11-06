#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"

#include "Sequence/SoloGame/Fail.h"
#include "Sequence/SoloGame/Parent.h"
#include "StringRenderer.h"

using namespace GameLib;

namespace Sequence {
namespace SoloGame {

Fail::Fail() : mImage("data/image/dummy.dds") {}

void Fail::update(Parent* parent)
{
    using namespace GameLib;

	mImage.draw();

    StringRenderer::instance().draw("Fail");
    StringRenderer::instance().draw("Please input space key go to Ready", 0, 1);
    StringRenderer::instance().draw("Please input g key to game over", 0, 2);

    if (Framework::instance().isKeyTriggered(' ')) {
        parent->moveTo(Parent::SEQUENCE_READY);
    } else if (Framework::instance().isKeyTriggered('g')) {
        parent->moveTo(Parent::SEQUENCE_GAMEOVER);
    }
}

} // namespace Sequence 
} // namespace SoloGame 

