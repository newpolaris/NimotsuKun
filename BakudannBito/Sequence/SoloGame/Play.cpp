#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"

#include "Sequence/SoloGame/Play.h"
#include "Sequence/SoloGame/Parent.h"
#include "StringRenderer.h"

using namespace GameLib;

namespace Sequence {
namespace SoloGame {

Play::Play() : mImage("data/image/dummy.dds") {}

void Play::update(Parent* parent)
{
    using namespace GameLib;

	parent->update();
	parent->draw();

    StringRenderer::instance().draw("Play");
    StringRenderer::instance().draw("Please input space key to Clear", 0, 1);
    StringRenderer::instance().draw("Please input f key to Fail", 0, 2);
    StringRenderer::instance().draw("Please input p key to Pause", 0, 3);

    if (Framework::instance().isKeyTriggered(' ')) 
        parent->moveTo(Parent::SEQUENCE_CLEAR);
     else if (Framework::instance().isKeyTriggered('f'))
        parent->moveTo(Parent::SEQUENCE_FAIL);
     else if (Framework::instance().isKeyTriggered('p'))
        parent->moveTo(Parent::SEQUENCE_PAUSE);
}

} // namespace Sequence 
} // namespace SoloGame 
