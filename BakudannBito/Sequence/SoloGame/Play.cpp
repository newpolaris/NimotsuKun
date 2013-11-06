#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"

#include "Sequence/SoloGame/Play.h"
#include "Sequence/SoloGame/Parent.h"
#include "StringRenderer.h"

using namespace GameLib;

namespace Sequence {
namespace SoloGame {

Play::Play() {}

void Play::update(Parent* parent)
{
    using namespace GameLib;

    StringRenderer::instance().draw("Play");
    StringRenderer::instance().draw("Please input space key to Clear", 0, 1);
    StringRenderer::instance().draw("Please input f key to Fail", 0, 2);

    if (Framework::instance().isKeyTriggered(' ')) {
        parent->moveTo(Parent::SEQUENCE_CLEAR);
    } else if (Framework::instance().isKeyTriggered('f')) {
        parent->moveTo(Parent::SEQUENCE_FAIL);
    }
}

} // namespace Sequence 
} // namespace SoloGame 
