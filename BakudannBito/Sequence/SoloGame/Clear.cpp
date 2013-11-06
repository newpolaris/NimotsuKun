#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"

#include "Sequence/SoloGame/Clear.h"
#include "Sequence/SoloGame/Parent.h"
#include "StringRenderer.h"

using namespace GameLib;

namespace Sequence {
namespace SoloGame {

Clear::Clear() : mImage("data/image/dummy.dds") {}

void Clear::update(Parent* parent)
{
    using namespace GameLib;

	mImage.draw();

    StringRenderer::instance().draw("Clear");
    StringRenderer::instance().draw("Please input space key go to Ready", 0, 1);
    StringRenderer::instance().draw("Please input e key go to Ending", 0, 2);

    if (Framework::instance().isKeyTriggered(' ')) {
        parent->moveTo(Parent::SEQUENCE_READY);
    } else if (Framework::instance().isKeyTriggered('e')) {
        parent->moveTo(Parent::SEQUENCE_ENDING);
    }
}

} // namespace Sequence 
} // namespace SoloGame 
