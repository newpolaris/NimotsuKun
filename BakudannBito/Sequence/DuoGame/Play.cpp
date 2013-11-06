#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"

#include "Sequence/DuoGame/Play.h"
#include "Sequence/DuoGame/Parent.h"
#include "StringRenderer.h"

using namespace GameLib;

namespace Sequence {
namespace DuoGame {

Play::Play() : mImage("data/image/dummy.dds") {}

void Play::update(Parent* parent)
{
    using namespace GameLib;

	mImage.draw();

    StringRenderer::instance().draw("Play");
    StringRenderer::instance().draw("Please input space key go to pause", 0, 1);
    StringRenderer::instance().draw("Please input d key go to display result", 0, 2);

    if (Framework::instance().isKeyTriggered(' ')) {
        parent->moveTo(Parent::SEQUENCE_PAUSE);
    } else if (Framework::instance().isKeyTriggered('d')) {
        parent->moveTo(Parent::SEQUENCE_DISPLAYRESULT);
    }
}

} // namespace DuoGame 
} // namespace Sequence 

